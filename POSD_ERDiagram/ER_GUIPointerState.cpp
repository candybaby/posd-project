#include "ER_GUIPointerState.h"
#include <QDebug>

ER_GUIPointerState::ER_GUIPointerState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
}

void ER_GUIPointerState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	qDebug() << "PointerState";
	
}
