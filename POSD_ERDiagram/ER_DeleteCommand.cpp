#include "ER_DeleteCommand.h"


ER_DeleteCommand::ER_DeleteCommand(void)
{
}

ER_DeleteCommand::ER_DeleteCommand(ER_Model* m,int id)
{
	this->model = m;
	this->targetId = id;
}


ER_DeleteCommand::~ER_DeleteCommand(void)
{
	//while (.size() > 0)
	//{
	//	* delData = .back();
	//	.pop_back();
	//	delete delData;
	//}

	//delete targetComponent;
}

string ER_DeleteCommand::execute()
{
	bool result;
	result = model->deleteComponent(targetId);
	if (result)
	{
		return Tool_Function::intToString(targetId);
	}
	else
	{
		return "";
	}
}

string ER_DeleteCommand::unexecute()
{

	return "";
}