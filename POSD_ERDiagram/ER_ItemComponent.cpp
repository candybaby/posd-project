#include "ER_ItemComponent.h"

ER_ItemComponent::ER_ItemComponent(QString name)
{
	componentName = name;
}

ER_ItemComponent::~ER_ItemComponent(void)
{
}

QRectF ER_ItemComponent::boundingRect() const
{
	return componentPainterPath.boundingRect();
}

QPainterPath ER_ItemComponent::shape() const
{
	return componentPainterPath;
}

void ER_ItemComponent::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void ER_ItemComponent::paintBorder(QPainter *painter)
{
	if (this->isSelected())
	{
		QPen pen( Qt::red );
		pen.setWidth(2);
		painter->setPen(pen);
		painter->drawPath(componentPainterPath); 
	}
}