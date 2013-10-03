#pragma once
#ifndef _ER_COMMAND_ 
#define _ER_COMMAND_
#include "ER_Model.h"

class ER_Command
{
public:
	ER_Command(void);
	virtual ~ER_Command(void);
	virtual string execute() = 0;
	virtual string unexecute() = 0;
};
#endif
