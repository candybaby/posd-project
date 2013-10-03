#include "ER_CommandManager.h"


ER_CommandManager::ER_CommandManager(void)
{
}


ER_CommandManager::~ER_CommandManager(void)
{
	while (!undoCmds.empty()) {
		ER_Command* c = undoCmds.top();
		undoCmds.pop();
		delete c;
	}
	while (!redoCmds.empty()) {
		ER_Command* c = redoCmds.top();
		redoCmds.pop();
		delete c;
	}
}

void ER_CommandManager::execute(ER_Command* cmd) {
	cmd->execute();
	undoCmds.push(cmd);

	// cleanup and release redoable commands
	while (!redoCmds.empty()) {
		ER_Command* c = redoCmds.top();
		redoCmds.pop();
		delete c;
	}
}

bool ER_CommandManager::redo() {
	if (redoCmds.size() == 0)
	{
		return false; // or throw exception
	}
	else
	{
		ER_Command* c = redoCmds.top();
		redoCmds.pop();
		c->execute(); // redo the command
		undoCmds.push(c);
		return true;
	}
}

bool ER_CommandManager::undo() {
	if (undoCmds.size() == 0)
	{
		return false;
	}
	else
	{
		ER_Command* c = undoCmds.top();
		undoCmds.pop();
		c->unexecute(); // undo the command
		redoCmds.push(c);
		return true;
	}
}