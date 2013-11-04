#include "ER_ItemAttribute.h"

ER_ItemAttribute::ER_ItemAttribute(QString name)
	: ER_ItemComponent(name)
{
	isPrimaryKey = false;
	initAttribute();
}

ER_ItemAttribute::ER_ItemAttribute(QString name, bool primaryKeyFlag)
	: ER_ItemComponent(name)
{
	isPrimaryKey = primaryKeyFlag;
	initAttribute();
}

ER_ItemAttribute::~ER_ItemAttribute(void)
{
}

void ER_ItemAttribute::initAttribute()
{
	qreal defaultLength = 50, dynamicLength = componentName.length() * 2.5; // 依name大小調整邊框寬度
	qreal ellipseWidth = defaultLength + 5 + dynamicLength;
	qreal ellipseHeight = defaultLength;
	componentPainterPath.addEllipse(QRectF(-(ellipseWidth / 2), -(ellipseHeight / 2), ellipseWidth, ellipseHeight));
	componentPen.setColor(Qt::black);
	componentPen.setWidth(2);
}

void ER_ItemAttribute::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawEllipse(boundingRect().adjusted(2, 2, -2, -2));
}

void ER_ItemAttribute::paintText(QPainter *painter)
{
	// 畫文字
	QFont font = painter->font() ;
	font.setPointSize(10);
	font.setUnderline(isPrimaryKey);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);
}
