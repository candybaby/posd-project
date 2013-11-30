#include "ER_DeleteCommand.h"
#define EMPTY_TEXT ""

ER_DeleteCommand::ER_DeleteCommand(ER_Model* model,int id)
{
	this->model = model;
	this->targetId = id;
	this->target = NULL;
}

ER_DeleteCommand::~ER_DeleteCommand(void)
{
	clearTempData();
	if (target != NULL)
	{
		delete target;
	}
}

// 找指定id的component
ERD_Component* ER_DeleteCommand::findComponentById(int id)
{
	return model->findComponentById(id);
}

// 刪除指定id的物件
bool ER_DeleteCommand::deleteComponentById(int id)
{
	return model->deleteComponent(id);
}

// 清除暫存資料
void ER_DeleteCommand::clearTempData()
{
	while (relatedComponents.size() > 0)
	{
		ERD_Component* delData = relatedComponents.back();
		relatedComponents.pop_back();
		delete delData;
	}
}

// 執行
string ER_DeleteCommand::execute()
{
	bool result;
	string deleteList;
	vector<int> relatedConnectionId;
	relatedConnectionId = model->findRelatedConnectionById(targetId);

	for (vector<int>::iterator it = relatedConnectionId.begin(); it < relatedConnectionId.end(); it++)
	{
		relatedComponents.push_back(findComponentById(*it)->clone());
		deleteComponentById(*it);
		deleteList += Tool_Function::convertIntToString(*it);
		deleteList += ',';
	}
	target = findComponentById(targetId);
	if (target == NULL)
	{
		return EMPTY_TEXT;
	}
	else
	{
		target = target->clone();
		result = deleteComponentById(targetId);
		model->setHasModify(true);
		deleteList += Tool_Function::convertIntToString(targetId);
		model->notifyDeleteComponents(deleteList);
		return Tool_Function::convertIntToString(targetId);
	}
}

// 反操作
string ER_DeleteCommand::unexecute()
{
	string addConnectionList;
	if (target->getType() != ERD_Component::Connection)
	{
		model->addComponent(target->clone());
		model->notifyAddComponent(model->getNodeInfo(targetId));
	}
	else
	{
		ERD_Connection* connection = (ERD_Connection*)target;
		model->addConnection(connection->getNodeId(), connection->getOtherNodeId(), connection->getId(), connection->getCardinality());
		addConnectionList += model->getConnectionInfo(connection->getId());
	}

	for (vector<ERD_Component*>::iterator it = relatedComponents.begin(); it < relatedComponents.end(); it++)
	{
		ERD_Connection* connection = (ERD_Connection*)*it;
		model->addConnection(connection->getNodeId(), connection->getOtherNodeId(), connection->getId(), connection->getCardinality());
		addConnectionList += model->getConnectionInfo(connection->getId());
	}

	model->notifyConnectComponents(addConnectionList);

	clearTempData();
	model->setHasModify(true);
	return EMPTY_TEXT;
}