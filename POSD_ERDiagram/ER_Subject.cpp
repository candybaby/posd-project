#include "ER_Subject.h"
#include <algorithm>

ER_Subject::ER_Subject()
{
}

ER_Subject::~ER_Subject()
{
}

// µù¥U
void ER_Subject::registerObserver(ER_Observer* observer)
{
	observers.push_back(observer);
}

// µù¥U®ø°£
void ER_Subject::unregisterObserver(ER_Observer* observer)
{
	observers.erase(find(observers.begin(), observers.end(), observer));
}

// Invoke Load File
void ER_Subject::notifyLoadFile()
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateItemsFromFile();
	}
}

// Invoke Add Component
void ER_Subject::notifyAddComponent(string message)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateAddComponent(message);
	}
}

// Invoke Connect Components
void ER_Subject::notifyConnectComponents(string message)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateConnectComponents(message);
	}
}

// Invoke Set Primary Key
void ER_Subject::notifySetPrimaryKey(int id, bool flag)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateSetPrimaryKey(id, flag);
	}
}

// Invoke Delete Components
void ER_Subject::notifyDeleteComponents(string message)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateDeleteComponents(message);
	}
}

// undo
void ER_Subject::notifyUndoEnable(bool flag)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateUndoEnable(flag);
	}
}

// redo
void ER_Subject::notifyRedoEnable(bool flag)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateRedoEnable(flag);
	}
}

// Invoke Edit Text
void ER_Subject::notifyEditText(int id, string text)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateEditText(id, text);
	}
}

// Invoke Edit Text Reject
void ER_Subject::notifyEditTextReject()
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateEditTextReject();
	}
}

// Invoke Move Components
void ER_Subject::notifyMoveComponent(string message)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateMoveComponents(message);
	}
}

// Invoke Can Paste State
void ER_Subject::notifyCanPasteState(bool flag)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateCanPasteState(flag);
	}
}

// Invoke Paste Components
void ER_Subject::notifyDebugMessage(string message)
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->updateDebugMessage(message);
	}
}
