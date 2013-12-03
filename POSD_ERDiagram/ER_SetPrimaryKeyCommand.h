#pragma once
#ifndef _ER_SET_PRIMARYKEY_COMMAND_ 
#define _ER_SET_PRIMARYKEY_COMMAND_
#include "ER_Command.h"
#include "ER_Model.h"

class ER_SetPrimaryKeyCommand : public ER_Command
{
public:
	ER_SetPrimaryKeyCommand(ER_Model*, int, bool);
	~ER_SetPrimaryKeyCommand(void);
	string execute();
	string unexecute();

private:
	ER_Model* model;
	int id;
	bool flag;
};
#endif
