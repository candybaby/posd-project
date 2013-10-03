#pragma once
#ifndef _ER_CONNECT_COMMAND_ 
#define _ER_CONNECT_COMMAND_
#include "ER_Command.h"
class ER_ConnectCommand : public ER_Command
{
public:
	ER_ConnectCommand(void);
	~ER_ConnectCommand(void);
	string execute();
	string unexecute();
};
#endif