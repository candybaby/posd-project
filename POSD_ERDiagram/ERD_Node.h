#pragma once
#ifndef _ERD_NODE_ 
#define _ERD_NODE_
#include "ERD_Component.h"
class ERD_Node : public ERD_Component
{
public:
	ERD_Node(void);
	~ERD_Node(void);
	virtual bool canConnectTo(ERD_Component*);
	virtual ERD_Component* clone();
};
#endif
