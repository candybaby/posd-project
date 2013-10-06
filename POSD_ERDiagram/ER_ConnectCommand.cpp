#include "ER_ConnectCommand.h"


ER_ConnectCommand::ER_ConnectCommand(void)
{
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* m,int node1Id, int node2Id)
{
	this->model = m;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
	this->targetId = -1;
}

ER_ConnectCommand::ER_ConnectCommand(ER_Model* m,int node1Id, int node2Id, ERD_Connection::ConnectionCardinality cardinality)
{
	this->model = m;
	this->firstNodeId = node1Id;
	this->secondNodeId = node2Id;
	this->targetId = -1;
	this->targetCardinality = cardinality;
}


ER_ConnectCommand::~ER_ConnectCommand(void)
{
}

string ER_ConnectCommand::execute()
{
	//if (targetId == -1)
	//{
	//	targetId = model->addConnection(firstNodeId, secondNodeId);
	//}
	//else
	//{
	//	model->addNode(targetType, targetName, targetId);
	//}
	return "";
}
string ER_ConnectCommand::unexecute()
{
	return "";
}