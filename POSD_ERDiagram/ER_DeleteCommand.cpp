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
	clearTempData();

	delete target;
}

ERD_Component* ER_DeleteCommand::findComponentById(int id)
{
	return model->findComponentById(id);
}

bool ER_DeleteCommand::deleteComponentById(int id)
{
	return model->deleteComponent(id);
}

void ER_DeleteCommand::clearTempData()
{
	while (relatedComponents.size() > 0)
	{
		ERD_Component* delData = relatedComponents.back();
		relatedComponents.pop_back();
		delete delData;
	}
}

string ER_DeleteCommand::execute()
{
	bool result;
	vector<int> relatedConnectionId;
	relatedConnectionId = model->findRelatedConnectionById(targetId);
	for (vector<int>::iterator it = relatedConnectionId.begin(); it < relatedConnectionId.end(); it++)
	{
		relatedComponents.push_back(findComponentById(*it)->clone());
		deleteComponentById(*it);
	}
	target = findComponentById(targetId)->clone();
	result = deleteComponentById(targetId);
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
	if (target->getType() != ERD_Component::Connection)
	{
		model->addComponent(target->clone());
	}
	else
	{
		ERD_Connection* connection = (ERD_Connection*)target;
		model->addConnection(connection->getNode1Id(), connection->getNode2Id(), connection->getId(), connection->getCardinality());
	}

	for (vector<ERD_Component*>::iterator it = relatedComponents.begin(); it < relatedComponents.end(); it++)
	{
		ERD_Connection* connection = (ERD_Connection*)*it;
		model->addConnection(connection->getNode1Id(), connection->getNode2Id(), connection->getId(), connection->getCardinality());
	}

	clearTempData();
	
	return "";
}