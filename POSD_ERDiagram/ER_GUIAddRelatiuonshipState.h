#pragma once
#ifndef _ER_GUIADDRELATIONSHIPSTATE_
#define _ER_GUIADDRELATIONSHIPSTATE_
#include "ER_GUIAddNodeState.h"

class ER_GUIAddRelatiuonshipState : public ER_GUIAddNodeState
{
public:
	ER_GUIAddRelatiuonshipState(ER_DiagramScene*, QGraphicsItem*);
	void mousePressEvent(QGraphicsSceneMouseEvent*);
};
#endif
