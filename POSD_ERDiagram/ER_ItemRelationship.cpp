#include "ER_ItemRelationship.h"

ER_ItemRelationship::ER_ItemRelationship(QString name)
	: ER_ItemComponent(name)
{
	defaultLength = 25;
	dynamicLength = componentName.length() * 2.5; // ��name�j�p�վ���ؼe��

	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));
	pointVector.push_back(QPointF(0, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), 0));
	pointVector.push_back(QPointF(0, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, 0));

	componentPainterPath.addPolygon(QPolygonF(pointVector));
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}


ER_ItemRelationship::~ER_ItemRelationship(void)
{
}

void ER_ItemRelationship::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	pointVector.clear();
	pointVector.push_back(QPointF(defaultLength + dynamicLength - 2, 0));
	pointVector.push_back(QPointF(0, -(defaultLength - 2)));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength - 2), 0));
	pointVector.push_back(QPointF(0, defaultLength - 2));
	pointVector.push_back(QPointF(defaultLength + dynamicLength - 2, 0));

	// �e�~��
	QPen pen( Qt::black );
	pen.setWidth(3);
	painter->setPen(pen);
	painter->drawPolygon(QPolygonF(pointVector));

	// �e��r
	QFont font=painter->font() ;
	font.setPointSize(10);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);

	paintBorder(painter);
}
