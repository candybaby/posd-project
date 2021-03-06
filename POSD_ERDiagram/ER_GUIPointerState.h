#pragma once
#ifndef _ER_GUIPOINTERSTATE_
#define _ER_GUIPOINTERSTATE_
#include "ER_GUIState.h"

class ER_DiagramScene;
class ER_GUIPointerState : public ER_GUIState
{
public:
	ER_GUIPointerState(ER_DiagramScene*);
	~ER_GUIPointerState();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	void mouseMoveEvent(QGraphicsSceneMouseEvent*);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
	QGraphicsItem* item;
	int pressPosX;
	int pressPosY;
};
#endif
