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
			qDebug() << "item Press pos" << item->pos();
			pressPosX = item->pos().x();
			pressPosY = item->pos().y();
			scene->sendEvent(item, pressEvent);
		}
		else
		{
			resetAllItemsSelected();
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
			qDebug() << "item Release pos" << item->pos();
			int deltaX = item->pos().x() - pressPosX;
			int deltaY = item->pos().y() - pressPosY;
			qDebug() << "Delta pos (" << deltaX << ", " << deltaY << ")";
			scene->moveSelectedItem(deltaX, deltaY);
			scene->sendEvent(item, releaseEvent);
		}
	}
	scene->checkCanDeleteStatus();
	item = NULL;
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