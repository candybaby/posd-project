#include "ER_GUIAddRelatiuonshipState.h"

ER_GUIAddRelatiuonshipState::ER_GUIAddRelatiuonshipState(ER_DiagramScene* scene, QGraphicsItem* preViewItem)
	: ER_GUIAddNodeState(scene, preViewItem)
{
}

void ER_GUIAddRelatiuonshipState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	ER_GUIAddNodeState::mousePressEvent(pressEvent);
	if (!nodeName.isEmpty())
	{
		scene->addItemRelationship(nodeName, pressEvent->scenePos());
	}
}
