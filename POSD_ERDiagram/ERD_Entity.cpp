#include "ERD_Entity.h"

ERD_Entity::ERD_Entity(void)
{
	this->type = Entity;
}

ERD_Entity::ERD_Entity(string name, int id)
{
	this->type = Entity;
	this->text = name;
	this->id = id;
}

ERD_Entity::~ERD_Entity(void)
{
}

bool ERD_Entity::canConnectTo(ERD_Component* entity)
{
	if (entity->getType() == Entity)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool ERD_Entity::isContainForeignEntityId(int id)
{
	for (vector<int>::iterator it = foreignEntityIdVector.begin(); it < foreignEntityIdVector.end(); it++)
	{
		if (*it == id)
		{
			return true;
		}
	}
	return false;
}

void ERD_Entity::addForeignEntityId(int id)
{
	foreignEntityIdVector.push_back(id);
}