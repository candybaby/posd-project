#include "ER_GUIAddAttributeState.h"

ER_GUIAddAttributeState::ER_GUIAddAttributeState(ER_DiagramScene* scene, QGraphicsItem* preViewItem)
	: ER_GUIAddNodeState(scene, preViewItem)
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
