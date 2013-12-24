#include "ERD_Attribute.h"
#include "ER_ComponentVisitor.h"

ERD_Attribute::ERD_Attribute(void)
	: ERD_Node()
{
	this->type = Attribute;
	this->isPrimaryKey = false;
	this->isConnected = false;
}

// clone建構子
ERD_Attribute::ERD_Attribute(ERD_Attribute* attributeClone)
	: ERD_Node(attributeClone)
{
	this->isPrimaryKey = attributeClone->getIsPrimaryKey();
	this->isConnected = attributeClone->getIsConnected();
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

// 判斷是否可連
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

// 取得isPrimaryKey
bool ERD_Attribute::getIsPrimaryKey()
{
	return this->isPrimaryKey;
}

// 設定isPrimaryKey
void ERD_Attribute::setPrimaryKey(bool flag)
{
	this->isPrimaryKey = flag;
}

// 取得isConnected
bool ERD_Attribute::getIsConnected()
{
	return isConnected;
}

// 設定isConnected
void ERD_Attribute::setConnected(bool flag)
{
	this->isConnected = flag;
}

// 克隆
ERD_Component* ERD_Attribute::clone()
{
	return new ERD_Attribute(*this);
}

void ERD_Attribute::accept(ER_ComponentVisitor* componentVisitor)
{
	componentVisitor->visit(this);
}