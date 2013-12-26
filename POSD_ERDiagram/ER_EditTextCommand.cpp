#include "ER_EditTextCommand.h"
#define EMPTY_TEXT ""

ER_EditTextCommand::ER_EditTextCommand(ER_Model* model, int id, string text)
{
	this->model = model;
	this->id = id;
	this->text = text;
	this->preText = EMPTY_TEXT;
}


ER_EditTextCommand::~ER_EditTextCommand(void)
{
}

// °õ¦æ
string ER_EditTextCommand::execute()
{
	this->preText = model->getNameById(id);
	model->setComponentText(id, text);
	model->notifyEditText(id, text);
	model->setHasModify(true);
	return EMPTY_TEXT;
}

// ¤Ï¾Þ§@
string ER_EditTextCommand::unexecute()
{
	model->setComponentText(id, preText);
	model->notifyEditText(id, preText);
	model->setHasModify(true);
	return EMPTY_TEXT;
}