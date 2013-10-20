#include "ER_AddCommand.h"
#define EMPTY_TEXT ""

ER_AddCommand::ER_AddCommand(ER_Model* model, ERD_Component::ComponentType type, string name)
{
	this->model = model;
	this->targetType = type;
	this->targetName = name;
	this->targetId = -1;
}


ER_AddCommand::~ER_AddCommand(void)
{
}

// °õ¦æ
string ER_AddCommand::execute()
{
	if (targetId == -1)
	{
		targetId = model->addNode(targetType, targetName);
	}
	else
	{
		model->addNode(targetType, targetName, targetId);
		model->sortComponents();
	}
	model->setHasModify(true);
	return Tool_Function::convertIntToString(targetId);
}

// ¤Ï¾Þ§@
string ER_AddCommand::unexecute()
{
	model->deleteComponent(targetId);
	model->setHasModify(true);
	return EMPTY_TEXT;
}