#include "ER_ItemComponent.h"
#include <QDebug>

ER_ItemComponent::ER_ItemComponent(QString name)
{
	this->componentName = name;
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
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
	doPaint(painter);
	paintText(painter);
	paintBorder(painter);
}

void ER_ItemComponent::paintText(QPainter *painter)
{
	// µe¤å¦r
	QFont font = painter->font() ;
	font.setPointSize(10);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);
}

void ER_ItemComponent::doPaint(QPainter *painter)
{
	// virtual
}

void ER_ItemComponent::paintBorder(QPainter *painter)
{
	if (this->isSelected())
	{
		QPen pen( Qt::red );
		pen.setWidth(2);
		painter->setPen(pen);
		painter->drawPath(componentPainterPath);
		painter->setPen(componentPen);
	}
}

qreal ER_ItemComponent::getId()
{
	return id;
}

void ER_ItemComponent::setId(qreal value)
{
	id = value;
}

void ER_ItemComponent::updatePosition()
{
	qDebug() << "updatePosition";
	//virtual
}

void ER_ItemComponent::setDiagramScene(QGraphicsScene* diagramScene)
{
	this->diagramScene = diagramScene;
}