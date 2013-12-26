#include "ER_TextView.h"


ER_TextView::ER_TextView(ER_PresentationModel* presentationModel)
{
	this->presentationModel = presentationModel;
	this->presentationModel->registerModelObserver(this);
}


ER_TextView::~ER_TextView(void)
{
}

void ER_TextView::updateItemsFromFile()
{
	updateHtml();
}

void ER_TextView::updateAddComponent(string)
{
	updateHtml();
}

void ER_TextView::updateConnectComponents(string)
{
	updateHtml();
}

void ER_TextView::updateSetPrimaryKey(int, bool)
{
	updateHtml();
}

void ER_TextView::updateDeleteComponents(string)
{
	updateHtml();
}

void ER_TextView::updateUndoEnable(bool)
{
	updateHtml();
}

void ER_TextView::updateRedoEnable(bool)
{
	updateHtml();
}

void ER_TextView::updateEditText(int, string)
{
	updateHtml();
}

void ER_TextView::updateEditTextReject()
{
	updateHtml();
}

void ER_TextView::updateMoveComponents(string)
{
	// do nothing
}

void ER_TextView::updateCanPasteState(bool)
{
	// do nothing
}

void ER_TextView::updateDebugMessage(string)
{
	// do nothing
}

void ER_TextView::updateHtml()
{
	QString qMessage = QString::fromLocal8Bit(presentationModel->getTableHtml().c_str());
	setHtml(qMessage);
}