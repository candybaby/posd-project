#include "ER_ItemRelationship.h"

ER_ItemRelationship::ER_ItemRelationship(QString name)
	: ER_ItemComponent(name)
{
	defaultLength = 25;
	dynamicLength = componentName.length() * 2.5; // 依name大小調整邊框寬度

	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));
	pointVector.push_back(QPointF(0, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), 0));
	pointVector.push_back(QPointF(0, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));

	componentPainterPath.addPolygon(QPolygonF(pointVector));
	componentPen.setColor(Qt::black);
	componentPen.setWidth(3);
}


ER_ItemRelationship::~ER_ItemRelationship(void)
{
}

void ER_ItemRelationship::doPaint(QPainter *painter)
{
	pointVector.clear();
	pointVector.push_back(QPointF(defaultLength + dynamicLength - 2, 0));
	pointVector.push_back(QPointF(0, -(defaultLength - 2)));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength - 2), 0));
	pointVector.push_back(QPointF(0, defaultLength - 2));
	pointVector.push_back(QPointF(defaultLength + dynamicLength - 2, 0));

	painter->setPen(componentPen);
	painter->drawPolygon(QPolygonF(pointVector));
}
