#include "ERD_Relationship.h"

ERD_Relationship::ERD_Relationship(void)
{
	this->type = Relationship;
}

ERD_Relationship::ERD_Relationship(ERD_Relationship* rhs)
{
	this->id = rhs->getId();
	this->type = rhs->getType();
	this->text = rhs->getText();
	this->connections = rhs->getConnections();
}

ERD_Relationship::ERD_Relationship(string name, int id)
{
	this->type = Relationship;
	this->text = name;
	this->id = id;
}

ERD_Relationship::~ERD_Relationship(void)
{
}

bool ERD_Relationship::canConnectTo(ERD_Component* entity)
{
	if (entity->getType() == Entity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ERD_Component* ERD_Relationship::clone()
{
	return new ERD_Relationship(*this);
}