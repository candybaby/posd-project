#include "ERD_Node.h"

ERD_Node::ERD_Node(void)
{
}

ERD_Node::~ERD_Node(void)
{
}

bool ERD_Node::canConnectTo(ERD_Component* entity)
{
	// virtual method
	return false;
}
