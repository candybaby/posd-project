#pragma once
#ifndef _ER_CONNECT_COMMAND_ 
#define _ER_CONNECT_COMMAND_
#include "ER_Command.h"

class ER_ConnectCommand : public ER_Command
{
public:
	ER_ConnectCommand(void);
	ER_ConnectCommand(ER_Model*, int, int, int);
	ER_ConnectCommand(ER_Model*, int, int, int, ERD_Connection::ConnectionCardinality);
	~ER_ConnectCommand(void);
	string execute();
	string unexecute();

private:
	ER_Model* model;
	int targetId;
	int firstNodeId;
	int secondNodeId;
	ERD_Connection::ConnectionCardinality targetCardinality;
};
#endif