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
	while (relatedConnectionsData.size() > 0)
	{
		ERD_ConnectionData* delData = relatedConnectionsData.back();
		relatedConnectionsData.pop_back();
		delete delData;
	}

	delete targetComponent;
}

string ER_DeleteCommand::execute()
{
	bool result;
	ERD_Component* target = model->findComponentById(targetId);
	if (target->getType() == ERD_Component::Connection)
	{
		isConnection = true;
	}
	else
	{
		isConnection = false;
	}
	targetComponent = target->clone();

	vector<int> relatedConnectionId = model->findRelatedConnectionById(targetId);
	for (vector<int>::iterator it = relatedConnectionId.begin(); it < relatedConnectionId.end(); it++)
	{
		ERD_Connection* tmp = (ERD_Connection*)model->findComponentById(*it);
		ERD_ConnectionData* data = new ERD_ConnectionData(tmp->getId(), tmp->getText(), model->getConnectionNode1ById(tmp->getId()), model->getConnectionNode2ById(tmp->getId()));

		relatedConnectionsData.push_back(data);
		model->deleteComponent(*it);
	}

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
	if (isConnection)
	{
		ERD_Connection* tmp = (ERD_Connection*)targetComponent;
		model->addConnection(tmp->getNode1(), tmp->getNode2(), tmp->getId(), tmp->getText());
	}
	else
	{
		model->addComponent(targetComponent->clone());
	}
	
	for (vector<ERD_ConnectionData *>::iterator it = relatedConnectionsData.begin(); it < relatedConnectionsData.end(); it++)
	{
		ERD_ConnectionData* data = (ERD_ConnectionData*)*it;
		model->addConnection(data->node1, data->node2, data->id, data->text);
		cout << "ID:" << data->id << ", text:" << data->text << ", node1:" << data->node1 << " ,node2:" << data->node2 << endl;
	}
	return "";
}