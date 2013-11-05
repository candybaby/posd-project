#include "ER_ItemConnection.h"
#include <QtCore/qmath.h>
#define INIT_LENGTH 20
#define EXTRA_LENGTH 6
#define TWO 2
#define PEN_WIDTH 3
#define TEN 10

ER_ItemConnection::ER_ItemConnection(QString cardinalityString)
	: ER_ItemComponent(cardinalityString)
{
	QLineF _Line = QLineF(QPointF(0, 0), QPointF(INIT_LENGTH, 0));
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

// 設定線段 邊框
void ER_ItemConnection::setInitShape()
{
	qreal extra = EXTRA_LENGTH, cosValue, sinValue;
	qreal startX = line.p1().x();
	qreal startY = line.p1().y();
	qreal endX = line.p2().x();
	qreal endY = line.p2().y();
	cosValue = (endY - startY) / qSqrt((endY - startY) * (endY - startY) + (endX - startX) * (endX - startX));
	sinValue = (endX - startX) / qSqrt((endY - startY) * (endY - startY) + (endX - startX) * (endX - startX));
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
	textPosPoint = QPoint((startX + endX) / TWO + abs(xValue), (startY + endY) / TWO - abs(yValue));

	componentPen.setColor(Qt::black);
	componentPen.setWidth(PEN_WIDTH);
}

void ER_ItemConnection::setLine(const QLineF &qLine)
{
	this->line = qLine;
}

// 設定線段起點鐘點
void ER_ItemConnection::calculateLinePoint()
{
	int startIndex = startComponent->getConnectionIndex(endComponent->pos());
	int endIndex = endComponent->getConnectionIndex(startComponent->pos());
	QLineF qLine;
	qLine = QLineF(startComponent->getConnectionPointVector().at(startIndex), endComponent->getConnectionPointVector().at(endIndex));
	setLine(qLine);
}

// 更新position
void ER_ItemConnection::updatePosition()
{
	if (!(startComponent->pos().isNull() || endComponent->pos().isNull()))
	{
		calculateLinePoint();
		setInitShape();
	}
}

// 畫(template method)
void ER_ItemConnection::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawLine(line);
}

// 畫文字(template method)
void ER_ItemConnection::paintText(QPainter* painter)
{
	// 畫文字
	QFont font = painter->font() ;
	font.setPointSize(TEN);
	painter->setFont(font);
	painter->drawText(textPosPoint, componentName);
}

// 畫邊框(template method)
void ER_ItemConnection::paintBorder(QPainter* painter)
{
	if (isSelected())
	{
		QPen pen(Qt::red);
		pen.setWidth(PEN_WIDTH); 
		painter->setPen(pen);
		painter->drawLine(line);
		painter->setPen(componentPen);
	}
}
