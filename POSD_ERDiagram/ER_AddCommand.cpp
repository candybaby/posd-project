#include "ER_AddCommand.h"
#define EMPTY_TEXT ""
#define CAMMA_TEXT ","

ER_AddCommand::ER_AddCommand(ER_Model* model, ERD_Component::ComponentType type, string name, int posX, int posY)
{
	this->model = model;
	this->targetType = type;
	this->targetName = name;
	this->targetId = -1;
	this->posX = posX;
	this->posY = posY;
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
	model->setComponentPosition(targetId, posX, posY);
	string message = model->getComponentInfo(targetId);
	model->notifyAddComponent(message);
	return Tool_Function::convertIntToString(targetId);
}

// ¤Ï¾Þ§@
string ER_AddCommand::unexecute()
{
	model->deleteComponent(targetId);
	model->setHasModify(true);
	return EMPTY_TEXT;
}