#include "ERD_Attribute.h"

ERD_Attribute::ERD_Attribute(void)
{
	this->type = Attribute;
	this->isPrimaryKey = false;
	this->isConnected = false;
}

ERD_Attribute::ERD_Attribute(string name, int id)
{
	this->type = Attribute;
	this->text = name;
	this->id = id;
	this->isPrimaryKey = false;
	this->isConnected = false;
}

ERD_Attribute::~ERD_Attribute(void)
{
}

bool ERD_Attribute::canConnectTo(ERD_Component* entity)
{
	if (entity->getType() == Entity && this->isConnected == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ERD_Attribute::getIsPrimaryKey()
{
	return this->isPrimaryKey;
}

void ERD_Attribute::setPrimaryKey(bool flag)
{
	this->isPrimaryKey = flag;
}

void ERD_Attribute::setConnected(bool flag)
{
	this->isConnected = flag;
}