#include "ERD_Component.h"

ERD_Component::ERD_Component(void)
{
	id = 0;
	type = Attribute;
	text = "";
}

ERD_Component::~ERD_Component(void)
{
}

int ERD_Component::getId()
{
	return id;
}

ComponentType ERD_Component::getType()
{
	return type;
}

string ERD_Component::getText()
{
	return text;
}

void ERD_Component::connectTo(ERD_Component* component)
{
	// virtual method
	connections.push_back(component);
}

bool ERD_Component::canConnectTo(ERD_Component* component)
{
	// virtual method
	return false;
}

vector<ERD_Component*> ERD_Component::getConnections()
{
	return connections;
}
