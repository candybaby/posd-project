#pragma once
#ifndef _ER_GUIADDATTRIBUTESTATE_
#define _ER_GUIADDATTRIBUTESTATE_
#include "ER_GUIAddNodeState.h"

class ER_GUIAddAttributeState : public ER_GUIAddNodeState
{
public:
	ER_GUIAddAttributeState(ER_DiagramScene*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};
#endif
