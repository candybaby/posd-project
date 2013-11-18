#pragma once
#ifndef _ER_DIAGRAMSCENE_
#define _ER_DIAGRAMSCENE_
#include <QtGui>
#include <QGraphicsScene>
#include "QGraphicsItem"
#include "ER_PresentationModel.h"
#include "ER_ItemComponent.h"
#include "ER_MessageBoxManager.h"
#include "ER_ItemEntity.h"
#include "ER_ItemAttribute.h"
#include "ER_ItemRelationship.h"
#include "ER_ItemConnection.h"
#include "ER_ItemFactory.h"
#include "ER_PositionManager.h"

class ER_GUI;
class ER_GUIState;
class ER_DiagramScene : public QGraphicsScene
{
	Q_OBJECT
public:
	enum Mode {Pointer, Connecter, InsertAttribute, InsertEntity, InsertRelationship};
	ER_DiagramScene(ER_PresentationModel*, QObject *parent = 0);
	~ER_DiagramScene(void);
	void addItem(QGraphicsItem*);
	void removeItem(QGraphicsItem*);
	QVector<QGraphicsItem *> getComponentItems();
	void addItemNodes(QString);
	void addItemConnections(QString);
	ER_ItemComponent* getItemComponentById(qreal);
	void updateItemPosition();
	ER_PositionManager* positionManager;
	void addItemsFromModel();
	void setMode(Mode);
	void changeState(ER_GUIState*);
	void addItemAttribute(QString, QPointF);
	void addItemEntity(QString, QPointF);
	void addItemRelationship(QString, QPointF);
	void addItemConnection(qreal, qreal);
	void cancelItemsSelected();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
	void clearItems();
	QVector<QGraphicsItem *> componentItems;
	ER_ItemFactory* itemFactory;
	ER_PresentationModel* presentationModel;
	ER_GUIState* state;
	ER_GUI* gui;
};
#endif