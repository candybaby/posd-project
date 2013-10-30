#include "ER_ItemAttribute.h"

ER_ItemAttribute::ER_ItemAttribute(QString name, bool primaryKeyFlag)
	: ER_ItemComponent(name)
{
	isPrimaryKey = primaryKeyFlag;
	qreal defaultLength = 50, dynamicLength = componentName.length() * 2.5; // ��name�j�p�վ���ؼe��
	componentPainterPath.addEllipse(QRectF(0, 0, defaultLength + 5 + dynamicLength, defaultLength));
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}


ER_ItemAttribute::~ER_ItemAttribute(void)
{
}

void ER_ItemAttribute::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	// �e�~��
	QPen pen( Qt::black );
	pen.setWidth(2);
	painter->setPen(pen);
	painter->drawEllipse(boundingRect().adjusted(2, 2, -2, -2));

	// �e��r
	QFont font=painter->font() ;
	font.setPointSize(10);
	font.setUnderline(isPrimaryKey);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);

	paintBorder(painter);
}
