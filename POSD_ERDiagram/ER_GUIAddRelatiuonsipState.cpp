#include "ER_GUIAddRelatiuonshipState.h"

ER_GUIAddRelatiuonshipState::ER_GUIAddRelatiuonshipState(ER_DiagramScene* scene)
	: ER_GUIAddNodeState(scene)
{
}

void ER_GUIAddRelatiuonshipState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	qDebug() << "AddRelationshipState";
}
