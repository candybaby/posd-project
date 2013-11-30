#include "ER_GUISetPrimaryKeyState.h"


ER_GUISetPrimaryKeyState::ER_GUISetPrimaryKeyState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
	item = NULL;
}

ER_GUISetPrimaryKeyState::~ER_GUISetPrimaryKeyState(void)
{

}

void ER_GUISetPrimaryKeyState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	qDebug() << "SetPrimaryKeyState press event";
	if (pressEvent->button() == Qt::LeftButton)
	{
		item = scene->itemAt(pressEvent->scenePos());
		if (item != NULL)
		{
			ER_ItemComponent* component = (ER_ItemComponent*)item;
			int id;
			id = component->getId();
			scene->tryToSetPrimaryKey(id);
		}
	}
}