#include "ER_ItemEntity.h"

ER_ItemEntity::ER_ItemEntity(QString name)
	: ER_ItemComponent(name)
{
	qreal defaultLength = 20, dynamicLength = componentName.length() * 2.5; // 依name大小調整邊框寬度
	
	QVector<QPointF> pointVector;
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));

	componentPainterPath.addPolygon(QPolygonF(pointVector));

	componentPen.setColor(Qt::black);
	componentPen.setWidth(3);
}

ER_ItemEntity::~ER_ItemEntity(void)
{
}

void ER_ItemEntity::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawRect(boundingRect().adjusted(3, 2, -2, -3));
}
