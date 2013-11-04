#include "ERD_Component.h"

ERD_Component::ERD_Component(void)
{
	id = 0;
	type = Attribute;
}

// clone�غc�l
ERD_Component::ERD_Component(ERD_Component* componentClone)
{
	// virtual method
	this->id = componentClone->getId();
	this->type = componentClone->getType();
	this->text = componentClone->getText();
	this->connections = componentClone->getConnections();
}

ERD_Component::~ERD_Component(void)
{
}

void ERD_Component::setId(int value)
{
	this->id = value;
}

// ���oid
int ERD_Component::getId()
{
	return id;
}

// ���A�ഫ
const char* ERD_Component::componentTypeNames[SIZE_OF_ComponentType] = { "A", "E", "R", "C"};

// ���o���A
ERD_Component::ComponentType ERD_Component::getType()
{
	return type;
}

// ���otext  (name)
string ERD_Component::getText()
{
	return text;
}

// �s�u
void ERD_Component::connectTo(ERD_Component* component)
{
	// virtual method
	connections.push_back(component);
}

// �P�_�O�_�i�H�s�u
bool ERD_Component::canConnectTo(ERD_Component* component)
{
	// virtual method
	return false;
}

// ���o�s�uVector
vector<ERD_Component*> ERD_Component::getConnections()
{
	return connections;
}

// �J��
ERD_Component* ERD_Component::clone()
{
	return new ERD_Component(*this);
}