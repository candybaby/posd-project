#pragma once
#ifndef _ER_ADD_COMMAND_ 
#define _ER_ADD_COMMAND_
#include "ER_Command.h"

class ER_AddCommand : public ER_Command
{
public:
	ER_AddCommand(void);
	~ER_AddCommand(void);
	string execute();
	string unexecute();
};
#endif