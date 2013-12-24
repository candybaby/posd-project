#include "ERD_Node.h"
#include "ER_ComponentVisitor.h"

ERD_Node::ERD_Node(void)
	: ERD_Component()
{
}

ERD_Node::~ERD_Node(void)
{
}

ERD_Node::ERD_Node(ERD_Node* nodeClone)
	: ERD_Component(nodeClone)
{

}

bool ERD_Node::canConnectTo(ERD_Component* entity)
{
	// virtual method
	return false;
}

ERD_Component* ERD_Node::clone()
{
	// virtual method
	return NULL;
}

void ERD_Node::accept(ER_ComponentVisitor* componentVisitor)
{
	// virtual method
}
