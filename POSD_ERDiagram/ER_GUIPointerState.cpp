#include "ER_GUIPointerState.h"

ER_GUIPointerState::ER_GUIPointerState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
	item = NULL;
}

ER_GUIPointerState::~ER_GUIPointerState()
{
	scene->cancelItemsSelected();
}

void ER_GUIPointerState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		item = scene->itemAt(pressEvent->scenePos());
		if (item != NULL)
		{
			pressPosX = item->pos().x();
			pressPosY = item->pos().y();
			scene->sendEvent(item, pressEvent);
		}
		else
		{
			scene->resetAllItemsSelected();
		}
	}
}

void ER_GUIPointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* moveEvent)
{
	if (item != NULL)
	{
		scene->sendEvent(item, moveEvent);
	}
}

void ER_GUIPointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* releaseEvent)
{
	if (releaseEvent->button() == Qt::LeftButton)
	{
		if (item != NULL)
		{
			int deltaX = item->pos().x() - pressPosX;
			int deltaY = item->pos().y() - pressPosY;
			if (!(deltaX == 0 && deltaY == 0))
			{
				scene->moveSelectedItem(deltaX, deltaY);
			}
			scene->sendEvent(item, releaseEvent);
		}
	}
	scene->checkCanEditItemsStatus();
	item = NULL;
}