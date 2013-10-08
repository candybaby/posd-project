#include "ERD_Relationship.h"

ERD_Relationship::ERD_Relationship(void)
{
	this->type = Relationship;
}

// clone建構子
ERD_Relationship::ERD_Relationship(ERD_Relationship* relationshipClone)
{
	this->id = relationshipClone->getId();
	this->type = relationshipClone->getType();
	this->text = relationshipClone->getText();
	this->connections = relationshipClone->getConnections();
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

// 判斷是否可以連接
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

// 克隆
ERD_Component* ERD_Relationship::clone()
{
	return new ERD_Relationship(*this);
}