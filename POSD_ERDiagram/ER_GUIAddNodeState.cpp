#include "ER_GUIAddNodeState.h"
#include <QInputDialog>

ER_GUIAddNodeState::ER_GUIAddNodeState(ER_DiagramScene* scene, QGraphicsItem* preViewItem)
	: ER_GUIState(scene)
{
	this->preViewItem = preViewItem;
	scene->addItem(preViewItem);
}

ER_GUIAddNodeState::~ER_GUIAddNodeState()
{
	scene->removeItem(preViewItem);
}

void ER_GUIAddNodeState::mousePressEvent(QGraphicsSceneMouseEvent* pressEvent)
{
	if (pressEvent->button() == Qt::LeftButton)
	{
		bool okFlag;
		QString text = QInputDialog::getText(0, "Enter Text","Please enter the text:", QLineEdit::Normal,"", &okFlag, Qt::Dialog);
		if (okFlag && !text.isEmpty())
		{
			nodeName = text;
		}
	}
}

void ER_GUIAddNodeState::mouseMoveEvent(QGraphicsSceneMouseEvent* moveEvent)
{
	preViewItem->setPos(moveEvent->scenePos());
}
