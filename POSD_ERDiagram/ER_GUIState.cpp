#include "ER_GUIState.h"
#include <QDebug>

ER_GUIState::ER_GUIState(ER_DiagramScene* scene)
{
	this->scene = scene;
}

ER_GUIState::~ER_GUIState()
{
	// virtual
}

void ER_GUIState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	// virtual
}

void ER_GUIState::mouseMoveEvent(QGraphicsSceneMouseEvent* moveEvent)
{
	// virtual
}

void ER_GUIState::mouseReleaseEvent(QGraphicsSceneMouseEvent* releaseEvent)
{
	// virtual
}