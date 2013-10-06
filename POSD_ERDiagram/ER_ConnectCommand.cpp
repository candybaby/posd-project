#include "ER_ConnectCommand.h"


ER_ConnectCommand::ER_ConnectCommand(void)
{
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* m,int node1Id, int node2Id, int id)
{
	this->model = m;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
	this->targetId = id;
	this->targetCardinality = ERD_Connection::SIZE_OF_Cardinality;
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* m,int node1Id, int node2Id, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	this->model = m;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
	this->targetId = id;
	this->targetCardinality = cardinality;
}


ER_ConnectCommand::~ER_ConnectCommand(void)
{
}

string ER_ConnectCommand::execute()
{
	model->addConnection(firstNodeId, secondNodeId, targetId, targetCardinality);
	return "";
}

string ER_ConnectCommand::unexecute()
{
	model->deleteComponent(targetId);
	return "";
}