#include "ER_DiagramScene.h"
#include "Tool_Function.h"
#include "ER_GUI.h"
#include "ER_GUIPointerState.h"
#include "ER_GUIConnecterState.h"
#include "ER_GUIAddEntityState.h"
#include "ER_GUIAddRelatiuonshipState.h"
#include "ER_GUIAddAttributeState.h"
#include "ER_GUISetPrimaryKeyState.h"
#include <QDebug>
#include <QInputDialog>
#define POSITION_MAX_WIDTH 4000
#define POSITION_MAX_HEIGTH 3000
#define POSITION_BLOCK_WIDTH 200
#define POSITION_BLOCK_HEIGTH 300

ER_DiagramScene::ER_DiagramScene(ER_PresentationModel* presentationModel, QObject *parent)
	: QGraphicsScene(parent)
{
	this->presentationModel = presentationModel;
	positionManager = new ER_PositionManager(POSITION_MAX_WIDTH, POSITION_MAX_HEIGTH, POSITION_BLOCK_WIDTH, POSITION_BLOCK_HEIGTH);
	this->state = new ER_GUIPointerState(this);
	gui = (ER_GUI*)parent;
	this->presentationModel->modelRegisterObserver(this);
}

ER_DiagramScene::~ER_DiagramScene(void)
{
}

// Override addItem
void ER_DiagramScene::addItem(QGraphicsItem* item)
{
	QGraphicsScene::addItem(item);
	componentItems.push_back(item);
	((ER_ItemComponent *)item)->setDiagramScene(this);
}

// Override removeItem
void ER_DiagramScene::removeItem(QGraphicsItem* item)
{
	componentItems.erase(componentItems.begin() + componentItems.indexOf(item));
	QGraphicsScene::removeItem(item);
}

// ���oComponentItems
QVector<QGraphicsItem *> ER_DiagramScene::getComponentItems()
{
	return componentItems;
}

// ���o�S�wid��item
ER_ItemComponent* ER_DiagramScene::getItemComponentById(qreal targetId)
{
	ER_ItemComponent* targetResult;
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		ER_ItemComponent* itemComponent = ((ER_ItemComponent *)*it);
		if (itemComponent->getId() == targetId)
		{
			targetResult = itemComponent;
		}
	}
	return targetResult;
}

// �ھ�message �NItem new�X �å[��scene�W
void ER_DiagramScene::addItemNodes(QString message)
{
	QStringList componentsList = message.split('\n');

	for (int i = 0; i < componentsList.size() - 1; i++)
	{
		QStringList componentList = componentsList.at(i).split(',');
		ER_ItemComponent* item = itemFactory->createItemNodes(componentList);
		addItem(item);
	}
}

// �ھ�message �NConnection new�X �å[��scene�W
void ER_DiagramScene::addItemConnections(QString message)
{
	QStringList componentsList = message.split('\n');

	for (int i = 0; i < componentsList.size() - 1; i++)
	{
		QStringList componentList = componentsList.at(i).split(',');
		ER_ItemComponent* item = itemFactory->createItemConnections(componentList);
		ER_ItemConnection* connection = (ER_ItemConnection*)item;
		qreal nodeId = componentList.at(3).toInt();
		qreal otherNodeId = componentList.at(4).toInt();
		connection->setConnection(getItemComponentById(nodeId), getItemComponentById(otherNodeId));
		addItem(item);
	}
}

// ��sItem����m
void ER_DiagramScene::updateItemPosition()
{
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		ER_ItemComponent* itemComponent = ((ER_ItemComponent *)*it);
		itemComponent->updatePosition();
		presentationModel->setComponentPos(itemComponent->getId(), itemComponent->pos().x(), itemComponent->pos().y());
	}
	qDebug() << "Scene Update";
	update(0, 0, width(), height());//��s�e��
}

// �[�Jitem ���e�q�ɮר��o
void ER_DiagramScene::addItemsFromModel()
{
	gui->changeToPointerMode(); // �۰ʤ���state
	clearItems();
	string nodesMessage = presentationModel->getGuiNodes();
	addItemNodes(QString(QString::fromLocal8Bit(nodesMessage.c_str())));

	string connectionsMessage = presentationModel->getGuiConnections();
	addItemConnections(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));

	updateItemPosition();
}

void ER_DiagramScene::updateItems(QString message)
{
	qDebug() << "updateItems : " << message;
	QStringList componentsList = message.split('\n');

	for (int i = 0; i < componentsList.size() - 1; i++)
	{
		QStringList componentList = componentsList.at(i).split(',');
		ER_ItemComponent* item = getItemComponentById(componentList.at(0).toInt());
		item->setName(componentList.at(1));
	}
}

// �D�n��sname
void ER_DiagramScene::updateItemsName()
{
	string nodesMessage = presentationModel->getGuiNodes();
	updateItems(QString(QString::fromLocal8Bit(nodesMessage.c_str())));
	string connectionsMessage = presentationModel->getGuiConnections();
	updateItems(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));
	
	update(0, 0, width(), height());//��s�e��
}

// �]�wmode
void ER_DiagramScene::setMode(Mode mode)
{
	QGraphicsItem* preViewItem;
	gui->setDeleteEnable(false);
	switch(mode)
	{
		case Pointer:
			changeState(new ER_GUIPointerState(this));
			gui->setDeleteEnable(true);
			break;
		case InsertAttribute:
			preViewItem = new ER_ItemAttribute("");
			changeState(new ER_GUIAddAttributeState(this, preViewItem));
			break;
		case InsertEntity:
			preViewItem = new ER_ItemEntity("");
			changeState(new ER_GUIAddEntityState(this, preViewItem));
			break;
		case InsertRelationship:
			preViewItem = new ER_ItemRelationship("");
			changeState(new ER_GUIAddRelatiuonshipState(this, preViewItem));
			break;
		case Connecter:
			changeState(new ER_GUIConnecterState(this));
			break;
		case SetPrimaryKey:
			changeState(new ER_GUISetPrimaryKeyState(this));
			break;
	}
}

// �ƹ����s�U���ƥ�
void ER_DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	state->mousePressEvent(pressEvent);
}

// �ƹ����ʨƥ�
void ER_DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* moveEvent)
{
	state->mouseMoveEvent(moveEvent);
}

// �ƹ����s��}�ƥ�
void ER_DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* releaseEvent)
{
	state->mouseReleaseEvent(releaseEvent);
}

// �󴫪��A
void ER_DiagramScene::changeState(ER_GUIState* nextState)
{
	delete state;
	state = nextState;
}

// �s�WAttribute
void ER_DiagramScene::addItemAttribute(QString entityName, QPointF position)
{
	string idString = presentationModel->addNode(ERD_Component::Attribute, entityName.toStdString(), position.x(), position.y());
	
	gui->changeToPointerMode(); // �۰ʤ���state
}

// �s�WEntity
void ER_DiagramScene::addItemEntity(QString entityName, QPointF position)
{
	string idString = presentationModel->addNode(ERD_Component::Entity, entityName.toStdString(), position.x(), position.y());

	gui->changeToPointerMode(); // �۰ʤ���state
}

// �s�WRelatuionship
void ER_DiagramScene::addItemRelationship(QString entityName, QPointF position)
{
	string idString = presentationModel->addNode(ERD_Component::Relationship, entityName.toStdString(), position.x(), position.y());

	gui->changeToPointerMode(); // �۰ʤ���state
}

// �s�Witem�s�u
void ER_DiagramScene::addItemConnection(qreal targetId, qreal sourceId)
{
	qreal tempId = presentationModel->getCurrentId(); // �s�u��id
	string message = presentationModel->getAddConnectionMessage(targetId, sourceId);
	QString cardinality = "";
	if (message.find("ask cardinality") != std::string::npos)
	{
		QStringList candidateChoose;
		candidateChoose << "1" << "N";
		bool ok;
		while (!(message.find("has been connected to the node") != std::string::npos))
		{
			cardinality = QInputDialog::getItem(0, "Cardinality", "Choose:", candidateChoose, 0, false, &ok);
			if (ok && !cardinality.isEmpty())
			{
				if (cardinality == candidateChoose.at(0))
				{
					message = presentationModel->addConnection(targetId, sourceId, ERD_Connection::one);
				}
				else if (cardinality == candidateChoose.at(1))
				{
					message = presentationModel->addConnection(targetId, sourceId, ERD_Connection::n);
				}
			}
		}
	}
}

// �����Ҧ�items���
void ER_DiagramScene::cancelItemsSelected()
{
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		((ER_ItemComponent *)*it)->setSelected(false);
	}
}

// �M��items
void ER_DiagramScene::clearItems()
{
	items().clear();
	while (componentItems.size() > 0)
	{
		QGraphicsItem* delData = componentItems.back();
		componentItems.pop_back();
		delete delData;
	}
}

// undo
void ER_DiagramScene::undo()
{
	string message = presentationModel->undo();
	qDebug() << QString(QString::fromLocal8Bit(message.c_str()));
}

// redo
void ER_DiagramScene::redo()
{
	string message = presentationModel->redo();
	qDebug() << QString(QString::fromLocal8Bit(message.c_str()));
}

// deleteItem
void ER_DiagramScene::deleteItem()
{
	
}

void ER_DiagramScene::observerUpdate()
{
	qDebug() << "observerUpdate()";
}

// ��s �s�WComponent
void ER_DiagramScene::updateAddComponent(string message)
{
	addItemNodes(QString(QString::fromLocal8Bit(message.c_str())));
	qDebug() << "updateAddComponent";
}

// ��s �s�uComponent
void ER_DiagramScene::updateConnectComponents(string message)
{
	addItemConnections(QString::fromLocal8Bit(message.c_str()));
	qDebug() << "updateConnectComponents";
}

void ER_DiagramScene::tryToSetPrimaryKey(int id)
{
	presentationModel->setIsPrimaryKey(id);
	qDebug() << "tryToSetPrimaryKey id : " << id;
}

// ��s Set Primary Key
void ER_DiagramScene::updateSetPrimaryKey(int id, bool flag)
{
	ER_ItemAttribute* item = (ER_ItemAttribute*)getItemComponentById(id);
	item->setIsPrimaryKey(flag);
	update(0, 0, width(), height());//��s�e��
	qDebug() << "id :" << id << ", flag : " << flag;
}