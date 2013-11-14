#include "ER_GUIPointerState.h"

ER_GUIPointerState::ER_GUIPointerState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
}

void ER_GUIPointerState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		item = scene->itemAt(pressEvent->scenePos());
		if (item != NULL)
		{
			scene->sendEvent(item, pressEvent);
		}
		else
		{
			resetAllItemsSelected();
		}
	}
}

void ER_GUIPointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (item != NULL)
	{
		scene->sendEvent(item, pressEvent);
	}
}

void ER_GUIPointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		if (item != NULL)
		{
			scene->sendEvent(item, pressEvent);
		}
	}
}

// 全部item設為未選取
void ER_GUIPointerState::resetAllItemsSelected()
{
	QList<QGraphicsItem*> items = scene->items();
	for (int i = 0;i < items.size(); i++)
	{
		items.at(i)->setSelected(false);
	}
}