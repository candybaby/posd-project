#pragma once
#ifndef _ERD_COMPONENT_ 
#define _ERD_COMPONENT_

#include <string>
#include <vector>
using namespace std;

class ERD_Component
{
public:
	enum ComponentType
	{
		Attribute,
		Entity,
		Relationship,
		Connection,
		SIZE_OF_ComponentType
	};
	static const char* ComponentTypeNames[SIZE_OF_ComponentType];
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
