#pragma once
#ifndef _ER_GUIADDENTITYSTATE_
#define _ER_GUIADDENTITYSTATE_
#include "ER_GUIAddNodeState.h"

class ER_GUIAddEntityState : public ER_GUIAddNodeState
{
public:
	ER_GUIAddEntityState(ER_DiagramScene*, QGraphicsItem*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};
#endif
