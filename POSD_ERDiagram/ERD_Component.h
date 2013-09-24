#pragma once
#ifndef _ERD_COMPONENT_ 
#define _ERD_COMPONENT_

#include <string>
#include <vector>
#include "ER_Enum.h"
using namespace std;

class ERD_Component
{
public:
	ERD_Component(void);
	virtual ~ERD_Component(void);
	int getId();
	ComponentType getType();
	string getText();
	virtual void connectTo(ERD_Component*);
	virtual bool canConnectTo(ERD_Component*);
	vector<ERD_Component*> getConnections();

protected:
	vector<ERD_Component*> connections;
	int id;
	ComponentType type;
	string text;
};
#endif
