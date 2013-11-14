#include "ER_DiagramScene.h"
#include "Tool_Function.h"
#include "ER_GUI.h"
#include "ER_GUIPointerState.h"
#include "ER_GUIConnecterState.h"
#include "ER_GUIAddEntityState.h"
#include "ER_GUIAddRelatiuonshipState.h"
#include "ER_GUIAddAttributeState.h"
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
	//this->state = new ER_GUIState(this);
}

ER_DiagramScene::~ER_DiagramScene(void)
{
}

// Override addItem
void ER_DiagramScene::addItem(QGraphicsItem *item)
{
	QGraphicsScene::addItem(item);
	componentItems.push_back(item);
	((ER_ItemComponent *)item)->setDiagramScene(this);
}

// 取得ComponentItems
QVector<QGraphicsItem *> ER_DiagramScene::getComponentItems()
{
	return componentItems;
}

// 取得特定id的item
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

// 根據message 將Item new出 並加到scene上
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

// 根據message 將Connection new出 並加到scene上
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

// 更新Item的位置
void ER_DiagramScene::updateItemPosition()
{
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		ER_ItemComponent* itemComponent = ((ER_ItemComponent *)*it);
		itemComponent->updatePosition();
	}
	update(0, 0, width(), height());//更新畫面
}

// 加入item 內容從檔案取得
void ER_DiagramScene::addItemsFromModel()
{
	clearItems();
	string nodesMessage = presentationModel->getGuiNodes();
	addItemNodes(QString(QString::fromLocal8Bit(nodesMessage.c_str())));

	string connectionsMessage = presentationModel->getGuiConnections();
	addItemConnections(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));

	updateItemPosition();
}

void ER_DiagramScene::setMode(Mode mode)
{
	switch(mode)
	{
	case Pointer:
		changeState(new ER_GUIPointerState(this));
		break;
	case Connecter:
		changeState(new ER_GUIConnecterState(this));
		break;
	case InsertAttribute:
		changeState(new ER_GUIAddAttributeState(this));
		break;
	case InsertEntity:
		changeState(new ER_GUIAddEntityState(this));
		break;
	case InsertRelationship:
		changeState(new ER_GUIAddRelatiuonshipState(this));
		break;
	}
}

void ER_DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	state->mousePressEvent(pressEvent);
}

void ER_DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	state->mouseMoveEvent(pressEvent);
}

void ER_DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	state->mouseReleaseEvent(pressEvent);
}

// 更換狀態
void ER_DiagramScene::changeState(ER_GUIState* nextState)
{
	delete state;
	state = nextState;
}

// 新增Attribute
void ER_DiagramScene::addItemAttribute(QString entityName, QPointF position)
{
	ER_ItemComponent* item = itemFactory->createItemAttribute(entityName);
	string id = presentationModel->addNode(ERD_Component::Attribute, entityName.toStdString());
	item->setId(std::stoi(id));
	item->setPos(position);
	addItem(item);
	gui->changeToPointerMode(); // 自動切換state
}

// 新增Entity
void ER_DiagramScene::addItemEntity(QString entityName, QPointF position)
{
	ER_ItemComponent* item = itemFactory->createItemEntity(entityName);
	string id = presentationModel->addNode(ERD_Component::Entity, entityName.toStdString());
	item->setId(std::stoi(id));
	item->setPos(position);
	addItem(item);
	gui->changeToPointerMode(); // 自動切換state
}

// 新增Relatuionship
void ER_DiagramScene::addItemRelationship(QString entityName, QPointF position)
{
	ER_ItemComponent* item = itemFactory->createItemRelationship(entityName);
	string id = presentationModel->addNode(ERD_Component::Relationship, entityName.toStdString());
	item->setId(std::stoi(id));
	item->setPos(position);
	addItem(item);
	gui->changeToPointerMode(); // 自動切換state
}

void ER_DiagramScene::addItemConnection(qreal targetId, qreal sourceId)
{
	qreal tempId = presentationModel->getCurrentId(); // 連線的id
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
	qDebug() << QString(QString::fromLocal8Bit(message.c_str()));
	if (message.find("has been connected to the node") != std::string::npos)
	{
		ER_ItemComponent* item = itemFactory->createItemConnection(cardinality);
		ER_ItemConnection* connection = (ER_ItemConnection*)item;
		connection->setConnection(getItemComponentById(targetId), getItemComponentById(sourceId));
		connection->setId(tempId);
		addItem(item);
	}
}

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