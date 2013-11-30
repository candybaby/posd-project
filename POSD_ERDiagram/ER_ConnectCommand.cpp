#include "ER_ConnectCommand.h"
#define EMPTY_TEXT ""

ER_ConnectCommand::ER_ConnectCommand(ER_Model* model,int nodeId, int otherNodeId, int id)
{
	this->model = model;
	this->firstNodeId = nodeId;
	this->secondNodeId = otherNodeId;
	this->targetId = id;
	this->targetCardinality = ERD_Connection::SizeOfCardinality;
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* model,int nodeId, int otherNodeId, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	this->model = model;
	this->firstNodeId = nodeId;
	this->secondNodeId = otherNodeId;
	this->targetId = id;
	this->targetCardinality = cardinality;
}

ER_ConnectCommand::~ER_ConnectCommand(void)
{
}

// °õ¦æ
string ER_ConnectCommand::execute()
{
	model->addConnection(firstNodeId, secondNodeId, targetId, targetCardinality);
	model->plusCurrentId();
	model->setHasModify(true);
	string message = model->getConnectionInfo(targetId);
	model->notifyConnectComponents(message);
	return EMPTY_TEXT;
}

// ¤Ï¾Þ§@
string ER_ConnectCommand::unexecute()
{
	model->setAttributeConnected(firstNodeId, false);
	model->setAttributeConnected(secondNodeId, false);
	model->deleteComponent(targetId);
	model->setHasModify(true);
	return EMPTY_TEXT;
}