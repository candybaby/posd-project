#pragma once
#ifndef _POSITION_MANAGER_ 
#define _POSITION_MANAGER_
#include <QtGui>
#include <map>

using namespace std;

class ER_PositionManager
{
public:
	ER_PositionManager(qreal, qreal, qreal, qreal);
	~ER_PositionManager(void);
	QPointF getPosition(qreal);

private:
	qreal maxWidth;
	qreal maxHeight;
	qreal blockWidth;
	qreal blockHeight;
	qreal columnSize;// ¼e
	qreal rowSize;   // °ª
	map<qreal, qreal> positionMap;
	qreal itemCounter;
};
#endif