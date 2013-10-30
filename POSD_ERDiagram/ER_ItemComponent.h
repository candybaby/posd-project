#pragma once
#ifndef _ITEM_COMPONENT_ 
#define _ITEM_COMPONENT_
#include <QGraphicsItem>
#include <QPainter>

class ER_ItemComponent : public QGraphicsItem
{
public:
	ER_ItemComponent(QString);
	~ER_ItemComponent(void);
	virtual QRectF boundingRect() const;
	virtual QPainterPath shape() const;
	virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	virtual void paintBorder(QPainter*);
protected:
	QPainterPath componentPainterPath;
	QString componentName;
};


#endif