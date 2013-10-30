#include "ER_ItemEntity.h"

ER_ItemEntity::ER_ItemEntity(QString name)
	: ER_ItemComponent(name)
{
	qreal defaultLength = 20, dynamicLength = componentName.length() * 2.5; // ��name�j�p�վ���ؼe��
	
	QVector<QPointF> pointVector;
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), -defaultLength));
	pointVector.push_back(QPointF(-(defaultLength + dynamicLength), defaultLength));
	pointVector.push_back(QPointF(defaultLength + dynamicLength, defaultLength));

	componentPainterPath.addPolygon(QPolygonF(pointVector));
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

ER_ItemEntity::~ER_ItemEntity(void)
{
}

void ER_ItemEntity::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	// �e�~��
	QPen pen( Qt::black );
	pen.setWidth(3);
	painter->setPen(pen);
	painter->drawRect(boundingRect().adjusted(3, 2, -2, -3));
	
	// �e��r
	QFont font=painter->font() ;
	font.setPointSize(10);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);

	paintBorder(painter);
}
