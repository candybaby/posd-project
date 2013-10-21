#include "ER_CommandManager.h"

ER_CommandManager::ER_CommandManager(void)
{
}

ER_CommandManager::~ER_CommandManager(void)
{
	while (!undoCommands.empty()) 
	{
		ER_Command* command = undoCommands.top();
		undoCommands.pop();
		delete command;
	}
	while (!redoCommands.empty()) 
	{
		ER_Command* command = redoCommands.top();
		redoCommands.pop();
		delete command;
	}
}

// °õ¦æ
string ER_CommandManager::execute(ER_Command* command) 
{
	string result;
	result = command->execute();
	undoCommands.push(command);

	// cleanup and release redoable commands
	while (!redoCommands.empty()) 
	{
		ER_Command* command = redoCommands.top();
		redoCommands.pop();
		delete command;
	}
	return result;
}

// redo
bool ER_CommandManager::redo() 
{
	if (redoCommands.size() == 0)
	{
		return false; // or throw exception
	}
	else
	{
		ER_Command* command = redoCommands.top();
		redoCommands.pop();
		command->execute(); // redo the command
		undoCommands.push(command);
		return true;
	}
}

// undo
bool ER_CommandManager::undo() 
{
	if (undoCommands.size() == 0)
	{
		return false;
	}
	else
	{
		ER_Command* command = undoCommands.top();
		undoCommands.pop();
		command->unexecute(); // undo the command
		redoCommands.push(command);
		return true;
	}
}

// getter
int ER_CommandManager::getUndoStackCount()
{
	return undoCommands.size();
}

// getter
int ER_CommandManager::getRedoStackCount()
{
	return redoCommands.size();
}