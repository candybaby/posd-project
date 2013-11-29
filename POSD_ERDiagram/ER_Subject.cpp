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