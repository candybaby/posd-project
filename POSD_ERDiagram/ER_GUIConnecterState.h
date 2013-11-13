#pragma once
#ifndef _ER_GUICONNECTERSTATE_
#define _ER_GUICONNECTERSTATE_
#include "ER_GUIState.h"

class ER_GUIConnecterState : public ER_GUIState
{
public:
	ER_GUIConnecterState(ER_DiagramScene*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};
#endif
