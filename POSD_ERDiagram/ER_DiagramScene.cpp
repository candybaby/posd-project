#include "ER_DiagramScene.h"
#include "Tool_Function.h"
#define POSITION_MAX_WIDTH 4000
#define POSITION_MAX_HEIGTH 3000
#define POSITION_BLOCK_WIDTH 200
#define POSITION_BLOCK_HEIGTH 300

ER_DiagramScene::ER_DiagramScene(QObject *parent)
	: QGraphicsScene(parent)
{
	positionManager = new ER_PositionManager(POSITION_MAX_WIDTH, POSITION_MAX_HEIGTH, POSITION_BLOCK_WIDTH, POSITION_BLOCK_HEIGTH);
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