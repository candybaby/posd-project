#include "ER_ItemComponent.h"
#include "ER_DiagramScene.h"
#include <QDebug>

ER_ItemComponent::ER_ItemComponent(QString name)
{
	this->componentName = name;
	setFlag(QGraphicsItem::ItemIsMovable, true);
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
		QPen pen(Qt::red);
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

QVector<QPointF> ER_ItemComponent::getConnectionPointVector()
{
	lineConnectionPoint.clear();
	for (int i = 0;i < originalConnectionPoint.size();i++)
	{
		QPointF point;
		point = originalConnectionPoint.at(i) + pos();
		lineConnectionPoint.push_back(point);
	}
	return lineConnectionPoint;
}

void ER_ItemComponent::updatePosition()
{
	if (pos().isNull())
	{
		QPointF point = ((ER_DiagramScene*)diagramScene)->positionManager->getPosition(id);
		setPos(point);
	}
}

void ER_ItemComponent::setDiagramScene(QGraphicsScene* diagramScene)
{
	this->diagramScene = diagramScene;
}

void ER_ItemComponent::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	preSelected = isSelected();
	QGraphicsItem::mousePressEvent(event);
	//qDebug() << "Press(Pre) : " << preSelected;
	//qDebug() << "Press(Current) : " << isSelected();
}

void ER_ItemComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	if (preSelected == isSelected() && QGraphicsItem::ItemIsSelectable)
	{
		setSelected(!preSelected);
	}
}

void ER_ItemComponent::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
	((ER_DiagramScene*)diagramScene)->updateItemPosition();
	qDebug() << "Move!";
}