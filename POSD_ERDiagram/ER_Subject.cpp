#include "ER_Subject.h"
#include <algorithm>

ER_Subject::ER_Subject()
{
}

ER_Subject::~ER_Subject()
{
}

void ER_Subject::registerObserver(ER_Observer* observer)
{
	observers.push_back(observer);
}

void ER_Subject::unregisterObserver(ER_Observer* observer)
{
	observers.erase(find(observers.begin(), observers.end(), observer));
}

void ER_Subject::notify()
{
	for (vector<ER_Observer *>::iterator it = observers.begin(); it < observers.end(); it++)
	{
		(*it)->observerUpdate();
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