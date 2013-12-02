#pragma once
#ifndef _ER_DIAGRAMSCENE_
#define _ER_DIAGRAMSCENE_
#include <QtGui>
#include <QGraphicsScene>
#include "QGraphicsItem"
#include "ER_PresentationModel.h"
#include "ER_ItemComponent.h"
#include "ER_ItemEntity.h"
#include "ER_ItemAttribute.h"
#include "ER_ItemRelationship.h"
#include "ER_ItemConnection.h"
#include "ER_ItemFactory.h"
#include "ER_PositionManager.h"
#include "ER_Observer.h"

class ER_GUI;
class ER_GUIState;
class ER_DiagramScene : public QGraphicsScene, public ER_Observer
{
	Q_OBJECT
public:
	enum Mode 
	{
		Pointer,  
		InsertAttribute, 
		InsertEntity, 
		InsertRelationship,
		Connecter,
		SetPrimaryKey
	};
	ER_DiagramScene(ER_PresentationModel*, QObject *parent = 0);
	~ER_DiagramScene(void);
	void addItem(QGraphicsItem*);
	void removeItem(QGraphicsItem*);
	QVector<QGraphicsItem *> getComponentItems();
	void addItemNodes(QString);
	void addItemConnections(QString);
	void updateModelComponentPosition();
	ER_ItemComponent* getItemComponentById(qreal);
	void updateItemPosition();
	ER_PositionManager* positionManager;
	void setMode(Mode);
	void changeState(ER_GUIState*);
	void addItemAttribute(QString, QPointF);
	void addItemEntity(QString, QPointF);
	void addItemRelationship(QString, QPointF);
	void addItemConnection(qreal, qreal);
	void cancelItemsSelected();
	void undo();
	void redo();
	void deleteItem();
	void updateItemsFromFile();
	void updateAddComponent(string);
	void updateConnectComponents(string);
	void tryToSetPrimaryKey(int);
	void updateSetPrimaryKey(int, bool);
	void updateDeleteComponents(string);
	void deleteItemById(int);
	void updateRedoEnable(bool);
	void updateUndoEnable(bool);
	void setDeleteButtonEnable(bool);
	void checkCanDeleteStatus();
	void updateEditText(int, string);
	void updateEditTextReject();
	void updateMoveComponent(string);
	void moveSelectedItem(int, int);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);

private:
	void clearItems();
	QVector<QGraphicsItem *> componentItems;
	ER_ItemFactory* itemFactory;
	ER_PresentationModel* presentationModel;
	ER_GUIState* state;
	ER_GUI* gui;
};
#endif