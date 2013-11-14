#include "ER_GUIAddAttributeState.h"

ER_GUIAddAttributeState::ER_GUIAddAttributeState(ER_DiagramScene* scene)
	: ER_GUIAddNodeState(scene)
{
}

void ER_GUIAddAttributeState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	ER_GUIAddNodeState::mousePressEvent(pressEvent);
	if (!nodeName.isEmpty())
	{
		scene->addItemAttribute(nodeName, pressEvent->scenePos());
	}
}
