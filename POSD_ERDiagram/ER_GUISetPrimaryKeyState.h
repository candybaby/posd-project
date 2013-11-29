#pragma once
#ifndef _ER_GUISETPRIMAYKEYSTATE_
#define _ER_GUISETPRIMAYKEYSTATE_
#include "ER_GUIState.h"

class ER_DiagramScene;
class ER_GUISetPrimaryKeyState : public ER_GUIState
{
public:
	ER_GUISetPrimaryKeyState(ER_DiagramScene*);
	~ER_GUISetPrimaryKeyState();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
private:
	QGraphicsItem* item;
};
#endif
