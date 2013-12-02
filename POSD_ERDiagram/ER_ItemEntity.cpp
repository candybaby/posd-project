#include "ER_ItemEntity.h"
#define WIDTH_LENGTH 20
#define WORD_LENGTH 2.5
#define PEN_WIDTH 3
#define FOUR 4

ER_ItemEntity::ER_ItemEntity(QString name)
	: ER_ItemComponent(name)
{
	adjustNameSize();
}

ER_ItemEntity::~ER_ItemEntity(void)
{
}

void ER_ItemEntity::adjustNameSize()
{
	qreal defaultLength = WIDTH_LENGTH, dynamicLength = componentName.length() * WORD_LENGTH; // 依name大小調整邊框寬度

	QVector<QPointF> pointVector;
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));

	componentPainterPath = QPainterPath();
	componentPainterPath.addPolygon(QPolygonF(pointVector));

	componentPen.setColor(Qt::black);
	componentPen.setWidth(PEN_WIDTH);

	originalConnectionPoint.clear();
	originalConnectionPoint.push_back(QPointF(0, defaultLength - FOUR));
	originalConnectionPoint.push_back(QPointF(defaultLength + dynamicLength - FOUR, 0));
	originalConnectionPoint.push_back(QPointF(0, -(defaultLength - FOUR)));
	originalConnectionPoint.push_back(QPointF(-(defaultLength + dynamicLength - FOUR), 0));
}

// 畫(template method)
void ER_ItemEntity::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawRect(boundingRect().adjusted(FOUR, FOUR, -FOUR, -FOUR));
}
