#include "ER_PositionManager.h"

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

QPointF ER_PositionManager::getPosition(qreal id)
{
	qreal columnNumber = (int)itemCounter % (int)columnSize;  //
	qreal rowNumber = (int)(itemCounter - columnNumber) / (int)columnSize;
	qreal posX = blockWidth * columnNumber + blockWidth / 2;
	qreal posY = blockHeight * rowNumber + blockHeight / 2;
	QPointF point = QPointF(posX, posY);
	positionMap.insert(pair<qreal, qreal> (itemCounter, id));
	itemCounter++;
	return point;
}
