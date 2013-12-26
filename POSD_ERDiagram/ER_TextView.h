#pragma once
#ifndef _ER_TABLE_VIEWL_ 
#define _ER_TABLE_VIEW_
#include <QTextEdit>
#include "ER_PresentationModel.h"
#include "ER_Observer.h"

class ER_TextView : public QTextEdit, public ER_Observer
{
public:
	ER_TextView(ER_PresentationModel*);
	~ER_TextView(void);
	void updateItemsFromFile();
	void updateAddComponent(string);
	void updateConnectComponents(string);
	void updateSetPrimaryKey(int, bool);
	void updateDeleteComponents(string);
	void updateUndoEnable(bool);
	void updateRedoEnable(bool);
	void updateEditText(int, string);
	void updateEditTextReject();
	void updateMoveComponents(string);
	void updateCanPasteState(bool);
	void updateDebugMessage(string);
	void updateHtml();

private:
	ER_PresentationModel* presentationModel;
};
#endif