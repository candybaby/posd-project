#pragma once
#ifndef _ITEM_ATTRIBUTE_ 
#define _ITEM_ATTRIBUTE_
#include <QGraphicsItem>
#include <QPainter>
#include "ER_ItemComponent.h"

class ER_ItemAttribute : public ER_ItemComponent
{
public:
	ER_ItemAttribute(QString);
	ER_ItemAttribute(QString, bool);
	~ER_ItemAttribute(void);
	void initAttribute();
protected:
	void doPaint(QPainter*);
	void paintText(QPainter*);
	bool isPrimaryKey;
};

#endif

