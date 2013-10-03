#pragma once
#ifndef _ER_DELETE_COMMAND_ 
#define _ER_DELETE_COMMAND_
#include "ER_Command.h"
#include "ERD_ConnectionData.h"

class ER_DeleteCommand : public ER_Command
{
public:
	ER_DeleteCommand(void);
	ER_DeleteCommand(ER_Model*, int);
	~ER_DeleteCommand(void);
	string execute();
	string unexecute();
private:
	ER_Model* model;
	bool isConnection;
	int targetId;
	ERD_Component* targetComponent;
	vector<ERD_ConnectionData*> relatedConnectionsData;

};
#endif