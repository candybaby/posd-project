#pragma once
#ifndef _ER_SUBJECT_ 
#define _ER_SUBJECT_
#include "ER_Observer.h"
#include "vector"

using namespace std;

class ER_Subject
{
public:
	ER_Subject();
	virtual ~ER_Subject();
	void registerObserver(ER_Observer*);
	void unregisterObserver(ER_Observer*);
	void notifyLoadFile();
	void notifyAddComponent(string);
	void notifyConnectComponents(string);
	void notifySetPrimaryKey(int, bool);
	void notifyDeleteComponents(string);
	void notifyUndoEnable(bool);
	void notifyRedoEnable(bool);
	void notifyEditText(int, string);
	void notifyEditTextReject();
	void notifyMoveComponent(string);

private:
	vector<ER_Observer*> observers;
};
#endif
