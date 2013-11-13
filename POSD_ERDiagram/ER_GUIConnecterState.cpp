#include "ER_GUIConnecterState.h"
#include <QDebug>

ER_GUIConnecterState::ER_GUIConnecterState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
}

void ER_GUIConnecterState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	qDebug() << "ConnecterState";
}
