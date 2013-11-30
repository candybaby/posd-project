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

// ����
string ER_EditTextCommand::execute()
{
	this->preText = model->getNameById(id);
	model->setComponentText(id, text);
	return EMPTY_TEXT;
}

// �Ͼާ@
string ER_EditTextCommand::unexecute()
{
	model->setComponentText(id, preText);
	return EMPTY_TEXT;
}