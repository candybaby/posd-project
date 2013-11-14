#include "ER_GUIAddNodeState.h"
#include <QInputDialog>

ER_GUIAddNodeState::ER_GUIAddNodeState(ER_DiagramScene* scene)
	: ER_GUIState(scene)
{
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
