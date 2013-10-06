#include "ER_AddCommand.h"


ER_AddCommand::ER_AddCommand(void)
{
}

ER_AddCommand::ER_AddCommand(ER_Model* m, ERD_Component::ComponentType type, string name)
{
	this->model = m;
	this->targetType = type;
	this->targetName = name;
	this->targetId = -1;
}


ER_AddCommand::~ER_AddCommand(void)
{
}

string ER_AddCommand::execute()
{
	if (targetId == -1)
	{
		targetId = model->addNode(targetType, targetName);
	}
	else
	{
		model->addNode(targetType, targetName, targetId);
	}
	return Tool_Function::intToString(targetId);
}

string ER_AddCommand::unexecute()
{
	model->deleteComponent(targetId);
	return "";
}