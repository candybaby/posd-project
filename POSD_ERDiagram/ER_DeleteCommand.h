#pragma once
#ifndef _ER_DELETE_COMMAND_ 
#define _ER_DELETE_COMMAND_
#include "ER_Command.h"

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
	int targetId;
};
#endif