#include "ERD_Component.h"

ERD_Component::ERD_Component(void)
{
	id = 0;
	type = Attribute;
}

ERD_Component::ERD_Component(ERD_Component* rhs)
{
	// virtual method
	this->id = rhs->getId();
	this->type = rhs->getType();
	this->text = rhs->getText();
	this->connections = rhs->getConnections();
}

ERD_Component::~ERD_Component(void)
{
}

int ERD_Component::getId()
{
	return id;
}

const char* ERD_Component::componentTypeNames[SIZE_OF_ComponentType] = { "A", "E", "R", "C"};

ERD_Component::ComponentType ERD_Component::getType()
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

ERD_Component* ERD_Component::clone()
{
	return new ERD_Component(*this);
}