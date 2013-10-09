#include "ER_ConnectCommand.h"
#define EMPTY_TEXT ""

ER_ConnectCommand::ER_ConnectCommand(void)
{
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* model,int node1Id, int node2Id, int id)
{
	this->model = model;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
	this->targetId = id;
	this->targetCardinality = ERD_Connection::SIZE_OF_Cardinality;
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* model,int node1Id, int node2Id, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	this->model = model;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
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
	model->setHasModify(true);
	return EMPTY_TEXT;
}

// ¤Ï¾Þ§@
string ER_ConnectCommand::unexecute()
{
	model->deleteComponent(targetId);
	model->setHasModify(true);
	return EMPTY_TEXT;
}