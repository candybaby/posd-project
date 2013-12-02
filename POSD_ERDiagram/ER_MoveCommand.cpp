#include "ER_MoveCommand.h"
#define EMPTY_TEXT ""
#define CAMMA ','

ER_MoveCommand::ER_MoveCommand(ER_Model* model, string idString, int deltaX, int deltaY)
{
	this->model = model;
	this->idString = idString;
	vector<string> idStringList = Tool_Function::split(idString, CAMMA);
	for (int i = 0; i < idStringList.size(); i++)
	{
		idVector.push_back(stoi(idStringList.at(i)));
	}
	this->deltaX = deltaX;
	this->deltaY = deltaY;
}


ER_MoveCommand::~ER_MoveCommand(void)
{
}

void ER_MoveCommand::moveCommand(int localDeltaX, int localDeltaY)
{
	ERD_Component* component;
	for (int i = 0; i < idVector.size(); i++)
	{
		component = model->findComponentById(idVector.at(i));
		component->setPos(component->getPosX() + localDeltaX, component->getPosY() + localDeltaY);
	}
	model->notifyMoveComponent(idString);
}

// °õ¦æ
string ER_MoveCommand::execute()
{
	moveCommand(deltaX, deltaY);
	return EMPTY_TEXT;
}

// ¤Ï¾Þ§@
string ER_MoveCommand::unexecute()
{
	moveCommand(-deltaX, -deltaY);
	return EMPTY_TEXT;
}