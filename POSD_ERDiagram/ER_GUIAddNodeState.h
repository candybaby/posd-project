#pragma once
#ifndef _ER_GUIADDNODESTATE_
#define _ER_GUIADDNODESTATE_
#include "ER_GUIState.h"

class ER_GUIAddNodeState : public ER_GUIState
{
public:
	ER_GUIAddNodeState(ER_DiagramScene*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
protected:
	QString nodeName;
};
#endif
