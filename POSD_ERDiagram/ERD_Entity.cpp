#include "ERD_Entity.h"

ERD_Entity::ERD_Entity(void)
	: ERD_Node()
{
	this->type = Entity;
}

// clone建構子
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

// 判斷是否可以連接
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

// 取得是否有包含與該entity有foreignKey關係的EntityID
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

// 新增有foreignKey關係的EntityID
void ERD_Entity::addForeignEntityId(int id)
{
	foreignEntityIdVector.push_back(id);
}

// 取得foreignKey關係的EntityID Vector
vector<int> ERD_Entity::getForeignEntityIdVector()
{
	return foreignEntityIdVector;
}

// 克隆
ERD_Component* ERD_Entity::clone()
{
	return new ERD_Entity(*this);
}