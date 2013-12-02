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
	this->presentationModel->registerModelObserver(this);
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
		//presentationModel->setComponentPos(itemComponent->getId(), itemComponent->pos().x(), itemComponent->pos().y());
	}
	qDebug() << "Scene Update";
	update(0, 0, width(), height());//更新畫面
}

// 加入item 內容從檔案取得
void ER_DiagramScene::updateItemsFromFile()
{
	gui->changeToPointerMode(); // 自動切換state
	clearItems();
	string nodesMessage = presentationModel->getGuiNodes();
	addItemNodes(QString(QString::fromLocal8Bit(nodesMessage.c_str())));

	string connectionsMessage = presentationModel->getGuiConnections();
	addItemConnections(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));

	updateItemPosition();
}

// 設定mode
void ER_DiagramScene::setMode(Mode mode)
{
	QGraphicsItem* preViewItem;
	gui->setDeleteEnable(false);
	switch(mode)
	{
		case Pointer:
			changeState(new ER_GUIPointerState(this));
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

// 滑鼠按鈕下壓事件
void ER_DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	state->mousePressEvent(pressEvent);
}

// 滑鼠移動事件
void ER_DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* moveEvent)
{
	state->mouseMoveEvent(moveEvent);
}

// 滑鼠按鈕放開事件
void ER_DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* releaseEvent)
{
	state->mouseReleaseEvent(releaseEvent);
}

void ER_DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* doubleClickEvent)
{
	state->mouseDoubleClickEvent(doubleClickEvent);
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
	presentationModel->addNode(ERD_Component::Attribute, entityName.toStdString(), position.x(), position.y());
	
	gui->changeToPointerMode(); // 自動切換state
}

// 新增Entity
void ER_DiagramScene::addItemEntity(QString entityName, QPointF position)
{
	presentationModel->addNode(ERD_Component::Entity, entityName.toStdString(), position.x(), position.y());

	gui->changeToPointerMode(); // 自動切換state
}

// 新增Relatuionship
void ER_DiagramScene::addItemRelationship(QString entityName, QPointF position)
{
	presentationModel->addNode(ERD_Component::Relationship, entityName.toStdString(), position.x(), position.y());

	gui->changeToPointerMode(); // 自動切換state
}

// 新增item連線
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
}

// 取消所有items選取
void ER_DiagramScene::cancelItemsSelected()
{
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		((ER_ItemComponent *)*it)->setSelected(false);
	}
}

// 清除items
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
	//qDebug() << QString(QString::fromLocal8Bit(message.c_str()));
}

// redo
void ER_DiagramScene::redo()
{
	string message = presentationModel->redo();
	//qDebug() << QString(QString::fromLocal8Bit(message.c_str()));
}

// deleteItem
void ER_DiagramScene::deleteItem()
{
	QList<QGraphicsItem*> itemList = selectedItems();
	if (itemList.size() >= 2)
	{
		qDebug() << "Can Not Delete Mutiple Selected Items";
	}
	else // size = 1
	{
		for (int i = 0; i < itemList.size(); i++)
		{
			ER_ItemComponent* item = (ER_ItemComponent*)itemList.at(i);
			//qDebug() << item->getId();
			presentationModel->deleteComponent(item->getId());
		}
	}
	checkCanDeleteStatus();
}

// 更新 新增Component
void ER_DiagramScene::updateAddComponent(string message)
{
	addItemNodes(QString(QString::fromLocal8Bit(message.c_str())));
	//qDebug() << "updateAddComponent";
}

// 更新 連線Component
void ER_DiagramScene::updateConnectComponents(string message)
{
	addItemConnections(QString::fromLocal8Bit(message.c_str()));
	//qDebug() << "updateConnectComponents";
}

void ER_DiagramScene::tryToSetPrimaryKey(int id)
{
	presentationModel->setIsPrimaryKey(id);
	//qDebug() << "tryToSetPrimaryKey id : " << id;
}

// 更新 Set Primary Key
void ER_DiagramScene::updateSetPrimaryKey(int id, bool flag)
{
	ER_ItemAttribute* item = (ER_ItemAttribute*)getItemComponentById(id);
	item->setIsPrimaryKey(flag);
	update(0, 0, width(), height());
	//qDebug() << "id :" << id << ", flag : " << flag;
}

// 更新 Delete Components
void ER_DiagramScene::updateDeleteComponents(string message)
{
	QString qMessage = QString::fromLocal8Bit(message.c_str());
	QStringList itemIdList = qMessage.split(',');
	for (int i = 0; i < itemIdList.size(); i++)
	{
		deleteItemById(itemIdList.at(i).toInt());
	}
	update(0, 0, width(), height());
	//qDebug() << "updateDeleteComponents :" << QString::fromLocal8Bit(message.c_str());
}

// 刪除特定id
void ER_DiagramScene::deleteItemById(int id)
{
	ER_ItemComponent* item = getItemComponentById(id);
	removeItem(item);
}

// 更新 undo enable
void ER_DiagramScene::updateUndoEnable(bool flag)
{
	gui->setUndoEnable(flag);
	//qDebug() << "updateUndoEnable : " << flag;
}

// 更新 redo enable
void ER_DiagramScene::updateRedoEnable(bool flag)
{
	gui->setRedoEnable(flag);
	//qDebug() << "updateRedoEnable : " << flag;
}

// 設定delete button enable
void ER_DiagramScene::setDeleteButtonEnable(bool flag)
{
	gui->setDeleteEnable(flag);
}

// 檢查可以使用刪除的情況
void ER_DiagramScene::checkCanDeleteStatus()
{
	QList<QGraphicsItem*> itemList = selectedItems();
	if (itemList.size() == 1) // 多選不能刪 不支援
	{
		setDeleteButtonEnable(true);
	}
	else
	{
		setDeleteButtonEnable(false);
	}
	//qDebug() << "checkCanDeleteStatus";
}

// 更新 Edit Text
void ER_DiagramScene::updateEditText(int id, string text)
{
	ER_ItemComponent* item = getItemComponentById(id);
	item->setName(QString(QString::fromLocal8Bit(text.c_str())));
	//qDebug() << "updateEditText id : " << id;
	updateItemPosition();
}

void ER_DiagramScene::updateEditTextReject()
{

}

void ER_DiagramScene::updateMoveComponent(string message)
{
	QString qMessage = QString(QString::fromLocal8Bit(message.c_str()));
	QStringList idList = qMessage.split(',');
	for (int i = 0; i < idList.size(); i++)
	{
		int id = idList.at(i).toInt();
		int posX = presentationModel->getComponentPosXById(id);
		int posY = presentationModel->getComponentPosYById(id);
		ER_ItemComponent* item = getItemComponentById(id);
		item->setPos(posX, posY);
		qDebug()<< posX << "," << posY;
	}
	
	qDebug() << "updateMove" << QString(QString::fromLocal8Bit(message.c_str()));
}

void ER_DiagramScene::moveSelectedItem(int deltaX, int deltaY)
{
	QList<QGraphicsItem*> itemList = selectedItems();
	QString idQString;
	for (int i = 0; i < itemList.size(); i++)
	{
		if (i != 0)
		{
			idQString += ',';
		}
		idQString += QString::number(((ER_ItemComponent*)itemList.at(i))->getId());
	}
	qDebug() << idQString;
	presentationModel->moveComponent(idQString.toStdString(), deltaX, deltaY);
}