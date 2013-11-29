#include "ERD_Entity.h"

ERD_Entity::ERD_Entity(void)
	: ERD_Node()
{
	this->type = Entity;
}

// clone�غc�l
ERD_Entity::ERD_Entity(ERD_Entity* entityClone)
	: ERD_Node(entityClone)
{
	this->foreignEntityIdVector = entityClone->getForeignEntityIdVector();
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

// �P�_�O�_�i�H�s��
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

// ���o�O�_���]�t�P��entity��foreignKey���Y��EntityID
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

// �s�W��foreignKey���Y��EntityID
void ERD_Entity::addForeignEntityId(int id)
{
	foreignEntityIdVector.push_back(id);
}

// ���oforeignKey���Y��EntityID Vector
vector<int> ERD_Entity::getForeignEntityIdVector()
{
	return foreignEntityIdVector;
}

// �J��
ERD_Component* ERD_Entity::clone()
{
	return new ERD_Entity(*this);
}