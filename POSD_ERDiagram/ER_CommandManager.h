#pragma once
#ifndef _ER_COMMANDMANAGER_ 
#define _ER_COMMANDMANAGER_
#include "ER_Command.h"
#include <stack>

using namespace std;

class ER_CommandManager
{
public:
	ER_CommandManager(void);
	virtual ~ER_CommandManager(void);
	string execute(ER_Command*);
	bool redo();
	bool undo();
	int getUndoStackCount();
	int getRedoStackCount();

private:
	stack<ER_Command*> undoCmds;
	stack<ER_Command*> redoCmds;
};
#endif
