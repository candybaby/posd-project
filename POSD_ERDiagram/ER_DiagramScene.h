#pragma once
#ifndef _ER_DIAGRAMSCENE_
#define _ER_DIAGRAMSCENE_
#include <QtGui>
#include <QGraphicsScene>
#include "QGraphicsItem"
#include "ER_ItemComponent.h"
#include "ER_MessageBoxManager.h"
#include "ER_ItemEntity.h"
#include "ER_ItemAttribute.h"
#include "ER_ItemRelationship.h"
#include "ER_ItemConnection.h"
#include "ER_ItemFactory.h"

class ER_DiagramScene : public QGraphicsScene
{
	Q_OBJECT
public:
	ER_DiagramScene(QObject *parent = 0);
	~ER_DiagramScene(void);
	void addItem(QGraphicsItem *item);
	QVector<QGraphicsItem *> getComponentItems();
	void addItemNodes(QString);
	void addItemConnections(QString);
	ER_ItemComponent* getItemComponentById(qreal);
	void updateItemPosition();
private:
	QVector<QGraphicsItem *> componentItems;
	ER_ItemFactory* itemFactory;
};
#endif