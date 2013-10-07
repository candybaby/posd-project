#include "ER_CommandManager.h"

ER_CommandManager::ER_CommandManager(void)
{
}

ER_CommandManager::~ER_CommandManager(void)
{
	while (!undoCmds.empty()) 
	{
		ER_Command* command = undoCmds.top();
		undoCmds.pop();
		delete command;
	}
	while (!redoCmds.empty()) 
	{
		ER_Command* command = redoCmds.top();
		redoCmds.pop();
		delete command;
	}
}

string ER_CommandManager::execute(ER_Command* cmd) 
{
	string result;
	result = cmd->execute();
	undoCmds.push(cmd);

	// cleanup and release redoable commands
	while (!redoCmds.empty()) 
	{
		ER_Command* command = redoCmds.top();
		redoCmds.pop();
		delete command;
	}
	return result;
}

bool ER_CommandManager::redo() 
{
	if (redoCmds.size() == 0)
	{
		return false; // or throw exception
	}
	else
	{
		ER_Command* command = redoCmds.top();
		redoCmds.pop();
		command->execute(); // redo the command
		undoCmds.push(command);
		return true;
	}
}

bool ER_CommandManager::undo() 
{
	if (undoCmds.size() == 0)
	{
		return false;
	}
	else
	{
		ER_Command* command = undoCmds.top();
		undoCmds.pop();
		command->unexecute(); // undo the command
		redoCmds.push(command);
		return true;
	}
}