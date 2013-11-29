#pragma once
#ifndef _ER_OBSERVER_ 
#define _ER_OBSERVER_

class ER_Observer
{
public:
	ER_Observer();
	virtual ~ER_Observer();
	virtual void observerUpdate() = 0;
};
#endif

