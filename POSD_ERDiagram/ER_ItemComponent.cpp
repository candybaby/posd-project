#include "ER_ItemComponent.h"
#include "ER_DiagramScene.h"
#define NUMBER_TEN 10
#define BORDER_SIZE 2
#define SIN_45_ANGLE 0.7
#define POSITION_0 0
#define POSITION_1 1
#define POSITION_2 2
#define POSITION_3 3

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

// 畫(template method)
void ER_ItemComponent::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	doPaint(painter);
	paintText(painter);
	paintBorder(painter);
}

// 畫文字(template method)
void ER_ItemComponent::paintText(QPainter *painter)
{
	// 畫文字
	QFont font = painter->font() ;
	font.setPointSize(NUMBER_TEN);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);
}

// 畫(template method)
void ER_ItemComponent::doPaint(QPainter *painter)
{
	// virtual
}

// 畫邊框(template method)
void ER_ItemComponent::paintBorder(QPainter *painter)
{
	if (this->isSelected())
	{
		QPen pen(Qt::red);
		pen.setWidth(BORDER_SIZE);
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

// 更新position
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
}

void ER_ItemComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	if (preSelected == isSelected() && !isMoveEventTrigger && QGraphicsItem::ItemIsSelectable)
	{
		setSelected(!preSelected);
	}
	isMoveEventTrigger = false;   //重置
}

void ER_ItemComponent::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
	isMoveEventTrigger = true;
	((ER_DiagramScene*)diagramScene)->updateItemPosition();
}

int ER_ItemComponent::getConnectionIndex(const QPointF &point)
{
	bool isRightSide;
	qreal sinValue;
	qreal startX = pos().x();
	qreal startY = pos().y();
	qreal endX = point.x();
	qreal endY = point.y();
	isRightSide = (startX <= endX);
	sinValue = -(endY - startY) / qSqrt((endY - startY) * (endY - startY)+(endX - startX) * (endX - startX));
	if (sinValue <= 1 && sinValue > SIN_45_ANGLE)
	{
		return POSITION_2;
	}
	else if (sinValue <= SIN_45_ANGLE && sinValue > -SIN_45_ANGLE)
	{
		return isRightSide ? POSITION_1 : POSITION_3;
	}
	else
	{
		return POSITION_0;
	}
}