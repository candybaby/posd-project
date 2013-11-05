#include "ER_PositionManager.h"
#define LENGTH 80
#define TWO 2

ER_PositionManager::ER_PositionManager(qreal width, qreal height, qreal blockWidth, qreal blockHeight)
{
	this->maxWidth = width;
	this->maxHeight = height;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->columnSize = maxWidth / blockWidth;
	this->rowSize = maxHeight / blockHeight;
	this->itemCounter = 0;
}

ER_PositionManager::~ER_PositionManager(void)
{
}

// ¨ú±o¦ì¸m
QPointF ER_PositionManager::getPosition(qreal id)
{
	qreal centerX = maxWidth / TWO;
	qreal centerY = maxHeight / TWO;

	qreal length = LENGTH;

	qreal posX = centerX + length * itemCounter * qSin(itemCounter);
	qreal posY = centerY + length * itemCounter * qCos(itemCounter);

	QPointF point = QPointF(posX, posY);
	positionMap.insert(pair<qreal, qreal> (itemCounter, id));
	itemCounter++;
	return point;
}
