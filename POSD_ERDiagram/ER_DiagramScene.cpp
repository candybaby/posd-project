#include "ER_DiagramScene.h"
#include "Tool_Function.h"


ER_DiagramScene::ER_DiagramScene(QObject *parent)
	: QGraphicsScene(parent)
{
	positionManager = new ER_PositionManager(1600, 1200, 200, 300);
}


ER_DiagramScene::~ER_DiagramScene(void)
{
}

void ER_DiagramScene::addItem(QGraphicsItem *item)
{
	QGraphicsScene::addItem(item);
	componentItems.push_back(item);
	((ER_ItemComponent *)item)->setDiagramScene(this);
}

QVector<QGraphicsItem *> ER_DiagramScene::getComponentItems()
{
	return componentItems;
}

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

void ER_DiagramScene::addItemNodes(QString message)
{
	//ER_MessageBoxManager::showMessageBox(message.toStdString());
	QStringList componentsList = message.split('\n');

	for (int i = 0; i < componentsList.size() - 1; i++)
	{
		QStringList componentList = componentsList.at(i).split(',');
		ER_ItemComponent* item = itemFactory->createItemNodes(componentList);
		addItem(item);
	}
}

void ER_DiagramScene::addItemConnections(QString message)
{
	//ER_MessageBoxManager::showMessageBox(message.toStdString());
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

void ER_DiagramScene::updateItemPosition()
{
	for (QVector<QGraphicsItem *>::iterator it = componentItems.begin(); it < componentItems.end(); it++)
	{
		ER_ItemComponent* itemComponent = ((ER_ItemComponent *)*it);
		itemComponent->updatePosition();
	}
	update(0, 0, width(), height());//��s�e��
}