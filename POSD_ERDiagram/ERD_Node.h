#pragma once
#ifndef _ERD_NODE_ 
#define _ERD_NODE_
#include "ERD_Component.h"

class ER_ComponentVisitor;
class ERD_Node : public ERD_Component
{
public:
	ERD_Node(void);
	~ERD_Node(void);
	ERD_Node(ERD_Node*);
	virtual bool canConnectTo(ERD_Component*);
	virtual ERD_Component* clone();
	virtual void accept(ER_ComponentVisitor*);
};
#endif
