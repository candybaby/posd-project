#pragma once
#ifndef _ITEM_ENTITY_ 
#define _ITEM_ENTITY_
#include <QGraphicsItem>
#include <QPainter>
#include "ER_ItemComponent.h"

class ER_ItemEntity : public ER_ItemComponent
{
public:
	ER_ItemEntity(QString);
	~ER_ItemEntity(void);
	virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif
