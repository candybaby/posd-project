#pragma once
#ifndef _ITEM_RELATIONSHIP_ 
#define _ITEM_RELATIONSHIP_
#include <QGraphicsItem>
#include <QPainter>
#include "ER_ItemComponent.h"

class ER_ItemRelationship : public ER_ItemComponent
{
public:
	ER_ItemRelationship(QString);
	~ER_ItemRelationship(void);
	virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
protected:
	QVector<QPointF> pointVector;
	qreal defaultLength;
	qreal dynamicLength;
};

#endif
