#pragma once
#ifndef _ERD_ENTITY_ 
#define _ERD_ENTITY_
#include "ERD_Node.h"

class ERD_Entity : public ERD_Node
{
public:
	ERD_Entity(void);
	ERD_Entity(ERD_Entity*);
	ERD_Entity(string, int);
	~ERD_Entity(void);
	virtual bool canConnectTo(ERD_Component*);
	bool isContainForeignEntityId(int);
	void addForeignEntityId(int);
	vector<int> getForeignEntityIdVector();
	ERD_Component* clone();

private:
	vector<int> foreignEntityIdVector;
};
#endif
