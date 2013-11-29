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
	void notify();
private:
	vector<ER_Observer*> observers;
};
#endif
