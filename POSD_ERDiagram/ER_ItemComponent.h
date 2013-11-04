#pragma once
#ifndef _ITEM_COMPONENT_ 
#define _ITEM_COMPONENT_
#include <QGraphicsScene>
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
	qreal getId();
	void setId(qreal);
	virtual void updatePosition();
	void setDiagramScene(QGraphicsScene*);
protected:
	virtual void doPaint(QPainter*);
	virtual void paintText(QPainter*);
	virtual void paintBorder(QPainter*);
	QGraphicsScene* diagramScene;
	QPainterPath componentPainterPath;
	QString componentName;
	qreal id;
	QPen componentPen;
};


#endif