#pragma once
#ifndef _ER_COMMAND_ 
#define _ER_COMMAND_
class ER_Command
{
public:
	ER_Command(void);
	virtual ~ER_Command(void);
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};
#endif
