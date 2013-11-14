#include "ER_GUIState.h"
#include <QDebug>

ER_GUIState::ER_GUIState(ER_DiagramScene* scene)
{
	this->scene = scene;
}

void ER_GUIState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	// virtual
}

void ER_GUIState::mouseMoveEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	// virtual
}

void ER_GUIState::mouseReleaseEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	// virtual
}