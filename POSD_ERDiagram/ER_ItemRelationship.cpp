#include "ER_ItemRelationship.h"
#define WIDTH_LENGTH 25
#define WORD_LENGTH 2.5
#define PEN_WIDTH 3
#define FOUR 4

ER_ItemRelationship::ER_ItemRelationship(QString name)
	: ER_ItemComponent(name)
{
	defaultLength = WIDTH_LENGTH;
	dynamicLength = componentName.length() * WORD_LENGTH; // ��name�j�p�վ���ؼe��

	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));
	pointVector.push_back(QPointF(0, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), 0));
	pointVector.push_back(QPointF(0, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));

	componentPainterPath.addPolygon(QPolygonF(pointVector));
	componentPen.setColor(Qt::black);
	componentPen.setWidth(PEN_WIDTH);

	originalConnectionPoint.push_back(QPointF(0, defaultLength - FOUR));
	originalConnectionPoint.push_back(QPointF(defaultLength + dynamicLength - FOUR, 0));
	originalConnectionPoint.push_back(QPointF(0, -(defaultLength - FOUR)));
	originalConnectionPoint.push_back(QPointF(-(defaultLength + dynamicLength - FOUR), 0));
}

ER_ItemRelationship::~ER_ItemRelationship(void)
{
}

// �e(template method)
void ER_ItemRelationship::doPaint(QPainter *painter)
{
	pointVector.clear();
	pointVector.push_back(QPointF(defaultLength + dynamicLength - FOUR, 0));
	pointVector.push_back(QPointF(0, -(defaultLength - FOUR)));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength - FOUR), 0));
	pointVector.push_back(QPointF(0, defaultLength - FOUR));
	pointVector.push_back(QPointF(defaultLength + dynamicLength - FOUR, 0));

	painter->setPen(componentPen);
	painter->drawPolygon(QPolygonF(pointVector));
}
