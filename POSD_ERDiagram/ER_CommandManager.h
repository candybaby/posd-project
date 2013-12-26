#pragma once
#ifndef _ER_COMMANDMANAGER_ 
#define _ER_COMMANDMANAGER_
#include "ER_Command.h"
#include <stack>
#include "ER_Model.h"

using namespace std;

class ER_CommandManager
{
public:
	ER_CommandManager(ER_Model*);
	virtual ~ER_CommandManager(void);
	string execute(ER_Command*);
	bool redo();
	bool undo();
	int getUndoStackCount();
	int getRedoStackCount();
	void reset();
	void clear();

private:
	stack<ER_Command*> undoCommands;
	stack<ER_Command*> redoCommands;
	ER_Model* model;
};
#endif
