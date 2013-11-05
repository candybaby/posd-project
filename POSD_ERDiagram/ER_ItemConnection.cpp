#include "ER_ItemConnection.h"
#include <QtCore/qmath.h>

ER_ItemConnection::ER_ItemConnection(QString cardinalityString)
	: ER_ItemComponent(cardinalityString)
{
	QLineF _Line = QLineF(QPointF(0, 0), QPointF(20, 0));
	setLine(_Line);
	setInitShape();
	setFlag(QGraphicsItem::ItemIsMovable, false); 
}

ER_ItemConnection::ER_ItemConnection(QString cardinalityString, ER_ItemComponent* startItem, ER_ItemComponent* endItem)
	: ER_ItemComponent(cardinalityString)
{
	setConnection(startItem, endItem);
	setFlag(QGraphicsItem::ItemIsMovable, false);
}

ER_ItemConnection::~ER_ItemConnection(void)
{
}

void ER_ItemConnection::setConnection(ER_ItemComponent* startItem, ER_ItemComponent* endItem)
{
	this->startComponent = startItem;
	this->endComponent = endItem;
	updatePosition();
}

void ER_ItemConnection::setInitShape()
{
	qreal extra = 6, cosValue, sinValue;
	qreal startX = line.p1().x();
	qreal startY = line.p1().y();
	qreal endX = line.p2().x();
	qreal endY = line.p2().y();
	cosValue = (endY-startY)/qSqrt((endY-startY)*(endY-startY)+(endX-startX)*(endX-startX));
	sinValue = (endX-startX)/qSqrt((endY-startY)*(endY-startY)+(endX-startX)*(endX-startX));
	qreal xValue = extra * cosValue;
	qreal yValue = extra * sinValue;

	QVector<QPointF> pointVector;
	pointVector.push_back(QPointF(startX + xValue, startY - yValue));
	pointVector.push_back(QPointF(endX + xValue, endY - yValue));
	pointVector.push_back(QPointF(endX - xValue, endY + yValue));
	pointVector.push_back(QPointF(startX - xValue, startY + yValue));
	pointVector.push_back(QPointF(startX + xValue, startY - yValue));

	componentPainterPath.~QPainterPath();
	componentPainterPath.addPolygon(QPolygonF(pointVector));
	textPosPoint = QPoint((startX + endX) / 2 + abs(xValue), (startY + endY) / 2 - abs(yValue));

	componentPen.setColor(Qt::black);
	componentPen.setWidth(3);
}

void ER_ItemConnection::setLine(const QLineF &qLine)
{
	this->line = qLine;
}

void ER_ItemConnection::calculateLinePoint()
{
	qreal startX = startComponent->pos().x();
	qreal startY = startComponent->pos().y();
	qreal endX = endComponent->pos().x();
	qreal endY = endComponent->pos().y();
	qreal sinValue;
	sinValue = (endX-startX)/qSqrt((endY-startY)*(endY-startY)+(endX-startX)*(endX-startX));
	QLineF qLine;
	qLine = QLineF(startComponent->getConnectionPointVector().at(0), endComponent->pos());
	setLine(qLine);
}

void ER_ItemConnection::updatePosition()
{
	if (!(startComponent->pos().isNull() || endComponent->pos().isNull()))
	{
		calculateLinePoint();
		setInitShape();
	}
}

void ER_ItemConnection::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawLine(line);
}

void ER_ItemConnection::paintText(QPainter* painter)
{
	// µe¤å¦r
	QFont font = painter->font() ;
	font.setPointSize(10);
	painter->setFont(font);
	painter->drawText(textPosPoint, componentName);
}

void ER_ItemConnection::paintBorder(QPainter* painter)
{
	if (isSelected())
	{
		QPen pen(Qt::red);
		pen.setWidth(3); 
		painter->setPen(pen);
		painter->drawLine(line);
		painter->setPen(componentPen);
	}
}
