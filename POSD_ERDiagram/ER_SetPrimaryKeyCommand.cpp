#include "ER_SetPrimaryKeyCommand.h"
#define EMPTY_TEXT ""

ER_SetPrimaryKeyCommand::ER_SetPrimaryKeyCommand(ER_Model* model, int id, bool flag)
{
	this->model = model;
	this->id = id;
	this->flag = flag;
}


ER_SetPrimaryKeyCommand::~ER_SetPrimaryKeyCommand(void)
{
}

// °õ¦æ
string ER_SetPrimaryKeyCommand::execute()
{
	model->setIsPrimaryKey(id, flag);
	return EMPTY_TEXT;
}

// ¤Ï¾Þ§@
string ER_SetPrimaryKeyCommand::unexecute()
{
	model->setIsPrimaryKey(id, !flag);
	return EMPTY_TEXT;
}