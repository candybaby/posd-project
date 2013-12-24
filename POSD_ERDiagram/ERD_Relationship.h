#pragma once
#ifndef _ERD_RELATIONSHIP_ 
#define _ERD_RELATIONSHIP_
#include "ERD_Node.h"

class ER_ComponentVisitor;
class ERD_Relationship : public ERD_Node
{
public:
	ERD_Relationship(void);
	ERD_Relationship(ERD_Relationship*);
	ERD_Relationship(string, int);
	~ERD_Relationship(void);
	virtual bool canConnectTo(ERD_Component*);
	ERD_Component* clone();
	void accept(ER_ComponentVisitor*);
};
#endif
