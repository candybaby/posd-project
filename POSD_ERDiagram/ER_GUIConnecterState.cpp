#include "ER_GUIConnecterState.h"
#include <QDebug>

ER_GUIConnecterState::ER_GUIConnecterState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
}

void ER_GUIConnecterState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		pressSelectItem = scene->itemAt(pressEvent->scenePos());
	}
}

void ER_GUIConnecterState::mouseReleaseEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		releaseSelectItem = scene->itemAt(pressEvent->scenePos());
		if (pressSelectItem != NULL && releaseSelectItem != NULL)
		{
			// do 
			qDebug() << "Try Connect!";
			scene->addItemConnection(((ER_ItemComponent*)pressSelectItem)->getId(), ((ER_ItemComponent*)releaseSelectItem)->getId());
		}
		else
		{
			// 取消該次操作
			qDebug() << "Cancel Connect!";
		}
	}
}