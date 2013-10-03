#pragma once
#ifndef _ER_DELETE_COMMAND_ 
#define _ER_DELETE_COMMAND_
#include "ER_Command.h"

class ER_DeleteCommand : public ER_Command
{
public:
	ER_DeleteCommand(void);
	~ER_DeleteCommand(void);
	void execute();
	void unexecute();
};
#endif