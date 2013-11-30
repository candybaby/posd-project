#pragma once
#ifndef _ER_OBSERVER_ 
#define _ER_OBSERVER_
#include <string>

using namespace std;

class ER_Observer
{
public:
	ER_Observer();
	virtual ~ER_Observer();
	virtual void observerUpdate() = 0;
	virtual void updateAddComponent(string) = 0;
	virtual void updateConnectComponents(string) = 0;
	virtual void updateSetPrimaryKey(int, bool) = 0;
	virtual void updateDeleteComponents(string) = 0;
	virtual void updateUndoEnable(bool) = 0;
	virtual void updateRedoEnable(bool) = 0;
};
#endif

