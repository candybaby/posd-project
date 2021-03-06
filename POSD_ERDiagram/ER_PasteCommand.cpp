#include "ER_PasteCommand.h"
#include <algorithm>


ER_PasteCommand::ER_PasteCommand(ER_Model* model, vector<ERD_Component*> components, int pasteCount)
{
	this->model = model;
	for (vector<ERD_Component*>::iterator it = components.begin(); it < components.end(); it++) 
	{
		this->candidatePasteComponents.push_back((*it)->clone());
	}
	this->modelCurrentId = model->getCurrentId();
	this->continuePasteCommandCount = pasteCount;
	this->pasteComponentCount = 0;
}

ER_PasteCommand::~ER_PasteCommand(void)
{
	clearConnections();
	while (candidatePasteComponents.size() > 0)
	{
		ERD_Component* delData = candidatePasteComponents.back();
		candidatePasteComponents.pop_back();
		delete delData;
	}
}

// 在候選貼上物件中 是否存在給定ID的node
bool ER_PasteCommand::isExistNode(int id)
{
	bool result = false;
	for (vector<ERD_Component*>::iterator it = candidatePasteComponents.begin(); it < candidatePasteComponents.end(); it++) 
	{
		ERD_Component* component = *it;
		if (component->getId() == id)
		{
			result = true;
		}
	}
	return result;
}

// 執行
string ER_PasteCommand::execute()
{
	pasteNodes();
	pasteConnections();
	model->setCurrentId(modelCurrentId + pasteComponentCount);
	
	model->setHasModify(true);
	model->addPasteCount();
	return "";
}

// 反操作
string ER_PasteCommand::unexecute()
{
	reverse(pastedComponentIds.begin(), pastedComponentIds.end());
	for (vector<int>::iterator it = pastedComponentIds.begin(); it < pastedComponentIds.end(); it++) 
	{
		model->deleteComponent(*it);
		model->notifyDeleteComponents(Tool_Function::convertIntToString(*it));
	}
	pastedComponentIds.clear();
	clearConnections();
	mappingCloneId.clear();
	model->minusPasteCount();
	model->setHasModify(true);
	model->setCurrentId(modelCurrentId);
	pasteComponentCount = 0;
	return "";
}

// 貼上nodes
void ER_PasteCommand::pasteNodes()
{
	for (vector<ERD_Component*>::iterator it = candidatePasteComponents.begin(); it < candidatePasteComponents.end(); it++) 
	{
		ERD_Component* component = (*it)->clone();
		if (component->getType() == ERD_Component::Connection)
		{
			connections.push_back((ERD_Connection*)component);
		}
		else
		{
			if (component->getType() == ERD_Component::Attribute)
			{
				((ERD_Attribute*)component)->setConnected(false);
			}
			int id = modelCurrentId + pasteComponentCount;
			mappingCloneId.insert(pair<int, int> (component->getId(), id));
			component->setId(id);
			int modifyWeight = continuePasteCommandCount + 1;
			component->setPos(component->getPosX() + (10 * modifyWeight), component->getPosY() + (10 * modifyWeight));
			model->addComponent(component->clone());
			pastedComponentIds.push_back(id);
			string message = model->getNodeInfo(id);
			model->notifyAddComponent(message);
			pasteComponentCount++;
		}
	}
}

// 貼上 connections
void ER_PasteCommand::pasteConnections()
{
	for (vector<ERD_Connection*>::iterator it = connections.begin(); it < connections.end(); it++) 
	{
		ERD_Connection* connection = *it;
		int nodeId = connection->getNodeId();
		int otherNodeId = connection->getOtherNodeId();
		if (isExistNode(nodeId) && isExistNode(otherNodeId))
		{
			int id = modelCurrentId + pasteComponentCount;
			model->addConnection(mappingCloneId.at(nodeId), mappingCloneId.at(otherNodeId), id, connection->getCardinality());
			pastedComponentIds.push_back(id);
			string message = model->getConnectionInfo(id);
			model->notifyConnectComponents(message);
			pasteComponentCount++;
		}
	}
}

// 清空connections
void ER_PasteCommand::clearConnections()
{
	while (connections.size() > 0)
	{
		ERD_Component* delData = connections.back();
		connections.pop_back();
		delete delData;
	}
}