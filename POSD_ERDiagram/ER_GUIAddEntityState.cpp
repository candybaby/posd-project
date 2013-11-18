#include "ER_GUIAddEntityState.h"

ER_GUIAddEntityState::ER_GUIAddEntityState(ER_DiagramScene* scene, QGraphicsItem* preViewItem)
	: ER_GUIAddNodeState(scene, preViewItem)
{
}

void ER_GUIAddEntityState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	ER_GUIAddNodeState::mousePressEvent(pressEvent);
	if (!nodeName.isEmpty())
	{
		scene->addItemEntity(nodeName, pressEvent->scenePos());
	}
}
