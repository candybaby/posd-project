#pragma once
#ifndef _ER_GUISTATE_
#define _ER_GUISTATE_
#include "ER_DiagramScene.h"

class ER_DiagramScene;
class ER_GUIState
{
public:
	ER_GUIState(ER_DiagramScene*);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
protected:
	ER_DiagramScene* scene;
};
#endif