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
	virtual void adjustNameSize();
	qreal getId();
	void setId(qreal);
	virtual void setName(QString);
	QVector<QPointF> getConnectionPointVector();
	virtual void updatePosition();
	void setDiagramScene(QGraphicsScene*);
	void mousePressEvent(QGraphicsSceneMouseEvent *);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *);
	int getConnectionIndex(const QPointF &);

protected:
	virtual void doPaint(QPainter*);
	virtual void paintText(QPainter*);
	virtual void paintBorder(QPainter*);
	QGraphicsScene* diagramScene;
	QPainterPath componentPainterPath;
	QString componentName;
	qreal id;
	QPen componentPen;
	bool preSelected;
	bool isMoveEventTrigger;
	bool isPress;
	QVector<QPointF> originalConnectionPoint; // 初始4個點位置
	QVector<QPointF> lineConnectionPoint;
};
#endif