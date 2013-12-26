#include "ER_CommandManager.h"

ER_CommandManager::ER_CommandManager(ER_Model* model)
{
	this->model = model;
}

ER_CommandManager::~ER_CommandManager(void)
{
	clear();
}

void ER_CommandManager::clear()
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

void ER_CommandManager::reset()
{
	clear();
	model->notifyUndoEnable(false);
	model->notifyRedoEnable(false);
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
	model->notifyUndoEnable(true);
	model->notifyRedoEnable(false);
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
		model->notifyUndoEnable(true);
		if (redoCommands.size() == 0)
		{
			model->notifyRedoEnable(false);
		}
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
		model->notifyRedoEnable(true);
		if (undoCommands.size() == 0)
		{
			model->notifyUndoEnable(false);
		}
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