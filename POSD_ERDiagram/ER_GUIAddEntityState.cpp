#include "ER_GUIAddEntityState.h"

ER_GUIAddEntityState::ER_GUIAddEntityState(ER_DiagramScene* scene)
	: ER_GUIAddNodeState(scene)
{
}

void ER_GUIAddEntityState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	qDebug() << "AddEntityState";
}
