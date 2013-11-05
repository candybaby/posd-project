#pragma once
#ifndef _ITEM_CONNECTION_ 
#define _ITEM_CONNECTION_
#include <QGraphicsLineItem>
#include "ER_ItemComponent.h"

class ER_ItemConnection : public ER_ItemComponent
{
public:
	ER_ItemConnection(QString);
	ER_ItemConnection(QString, ER_ItemComponent*, ER_ItemComponent*);
	~ER_ItemConnection(void);
	void setConnection(ER_ItemComponent*, ER_ItemComponent*);
	void setInitShape();
	void setLine(const QLineF &);
	void calculateLinePoint();
	void updatePosition();

protected:
	void doPaint(QPainter*);
	void paintText(QPainter*);
	void paintBorder(QPainter*);

private:
	ER_ItemComponent* startComponent;
	ER_ItemComponent* endComponent;
	QLineF line;
	QPoint textPosPoint;
};
#endif