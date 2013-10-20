#pragma once
#ifndef _ER_ADD_COMMAND_ 
#define _ER_ADD_COMMAND_
#include "ER_Command.h"

class ER_AddCommand : public ER_Command
{
public:
	ER_AddCommand(ER_Model*, ERD_Component::ComponentType, string);
	~ER_AddCommand(void);
	string execute();
	string unexecute();

private:
	ER_Model* model;
	ERD_Component::ComponentType targetType;
	string targetName;
	int targetId;
};
#endif