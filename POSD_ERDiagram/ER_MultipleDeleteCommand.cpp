#include "ER_MultipleDeleteCommand.h"
#define EMPTY_TEXT ""

ER_MultipleDeleteCommand::ER_MultipleDeleteCommand(ER_Model* model,vector<int> ids)
{
	this->model = model;
	this->targetIds = ids;
}

ER_MultipleDeleteCommand::~ER_MultipleDeleteCommand(void)
{
	clearTempData();
}

// 找指定id的component
ERD_Component* ER_MultipleDeleteCommand::findComponentById(int id)
{
	return model->findComponentById(id);
}

void ER_MultipleDeleteCommand::deleteConnectionsByTargetIds(vector<int> ids)
{
	for (vector<int>::iterator it = ids.begin(); it < ids.end(); it++)
	{
		ERD_Component* target = findComponentById(*it);
		if (target->getType() == ERD_Component::Connection)
		{
			relatedComponents.push_back(target->clone());
			deleteComponentById(*it);
			deleteIds.push_back(*it);
		}
	}
}

void ER_MultipleDeleteCommand::deleteRelatedConnectionByTargetId(int id)
{
	vector<int> relatedConnectionId;
	relatedConnectionId = model->findRelatedConnectionById(id);

	for (vector<int>::iterator it = relatedConnectionId.begin(); it < relatedConnectionId.end(); it++)
	{
		relatedComponents.push_back(findComponentById(*it)->clone());
		deleteComponentById(*it);
		deleteIds.push_back(*it);
	}
}

void ER_MultipleDeleteCommand::deleteNodeByTargetIds(vector<int> ids)
{
	for (vector<int>::iterator it = ids.begin(); it < ids.end(); it++)
	{
		ERD_Component* target = findComponentById(*it);
		if (target != NULL && target->getType() != ERD_Component::Connection)
		{
			targetNodes.push_back(target->clone());
			deleteComponentById(*it);
			deleteIds.push_back(*it);
		}
	}
}

// 刪除指定id的物件
bool ER_MultipleDeleteCommand::deleteComponentById(int id)
{
	return model->deleteComponent(id);
}

// 清除暫存資料
void ER_MultipleDeleteCommand::clearTempData()
{
	while (relatedComponents.size() > 0)
	{
		ERD_Component* delData = relatedComponents.back();
		relatedComponents.pop_back();
		delete delData;
	}
	while (targetNodes.size() > 0)
	{
		ERD_Component* delData = targetNodes.back();
		targetNodes.pop_back();
		delete delData;
	}
}

// 執行
string ER_MultipleDeleteCommand::execute()
{
	bool result;
	string deleteList;

	// 刪除給定陣列中的connection 紀錄刪了哪些
	deleteConnectionsByTargetIds(targetIds);

	// 刪除給定陣列中的node的相關connection 紀錄
	for (vector<int>::iterator it = targetIds.begin(); it < targetIds.end(); it++)
	{
		deleteRelatedConnectionByTargetId(*it);
	}

	// 刪除給定陣列中的node
	deleteNodeByTargetIds(targetIds);

	for (vector<int>::iterator it = deleteIds.begin(); it < deleteIds.end(); it++)
	{
		deleteList += Tool_Function::convertIntToString(*it);
		deleteList += ",";
	}
	if (deleteList.size() > 0)
	{
		deleteList = deleteList.substr(0,deleteList.size() - 1);
		model->setHasModify(true);
	}

	model->notifyDeleteComponents(deleteList);

	return EMPTY_TEXT;
}

// 反操作
string ER_MultipleDeleteCommand::unexecute()
{
	for (vector<ERD_Component*>::iterator it = targetNodes.begin(); it < targetNodes.end(); it++)
	{
		model->addComponent((*it)->clone());
		model->notifyAddComponent(model->getNodeInfo((*it)->getId()));
	}

	string addConnectionList;

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
