#include "ER_ItemAttribute.h"
#define WIDTH_LENGTH 50
#define WORD_LENGTH 2.5
#define MODIFY_LENGTH 5
#define FOUR 4
#define TWO 2
#define PEN_WIDTH 2

ER_ItemAttribute::ER_ItemAttribute(QString name)
	: ER_ItemComponent(name)
{
	isPrimaryKey = false;
	adjustNameSize();
}

ER_ItemAttribute::ER_ItemAttribute(QString name, bool primaryKeyFlag)
	: ER_ItemComponent(name)
{
	isPrimaryKey = primaryKeyFlag;
	adjustNameSize();
}

ER_ItemAttribute::~ER_ItemAttribute(void)
{
}

// 自動調整大小
void ER_ItemAttribute::adjustNameSize()
{
	qreal defaultLength = WIDTH_LENGTH, dynamicLength = componentName.length() * WORD_LENGTH; // 依name大小調整邊框寬度
	qreal ellipseWidth = defaultLength + MODIFY_LENGTH + dynamicLength;
	qreal ellipseHeight = defaultLength;
	componentPainterPath = QPainterPath();
	componentPainterPath.addEllipse(QRectF(-(ellipseWidth / TWO), -(ellipseHeight / TWO), ellipseWidth, ellipseHeight));
	componentPen.setColor(Qt::black);
	componentPen.setWidth(PEN_WIDTH);
	originalConnectionPoint.clear();
	originalConnectionPoint.push_back(QPointF(0, ellipseHeight / TWO - FOUR));
	originalConnectionPoint.push_back(QPointF(ellipseWidth / TWO - FOUR, 0));
	originalConnectionPoint.push_back(QPointF(0, -(ellipseHeight / TWO - FOUR)));
	originalConnectionPoint.push_back(QPointF(-(ellipseWidth / TWO - FOUR), 0));
}

// 畫(template method)
void ER_ItemAttribute::doPaint(QPainter *painter)
{
	painter->setPen(componentPen);
	painter->drawEllipse(boundingRect().adjusted(FOUR, FOUR, -FOUR, -FOUR));
}

// 畫文字(template method)
void ER_ItemAttribute::paintText(QPainter *painter)
{
	// 畫文字
	QFont font = painter->font() ;
	font.setPointSize(10);
	font.setUnderline(isPrimaryKey);
	painter->setFont(font);
	painter->drawText(boundingRect(), Qt::AlignCenter, componentName);
}

void ER_ItemAttribute::setIsPrimaryKey(bool flag)
{
	isPrimaryKey = flag;
}

bool ER_ItemAttribute::getIsPrimaryKey()
{
	return isPrimaryKey;
}