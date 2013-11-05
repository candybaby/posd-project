#include "ER_ItemFactory.h"
#define TWO 2
#define THREE 3
#define TYPE_ENTITY "E"
#define TYPE_ATTRIBUTE "A"
#define TYPE_RELATIONSHIP "R"
#define ONE_STRING "1"


ER_ItemFactory::ER_ItemFactory(void)
{
}


ER_ItemFactory::~ER_ItemFactory(void)
{
}

// 製作node
ER_ItemComponent* ER_ItemFactory::createItemNodes(QStringList componentString)
{
	ER_ItemComponent *item;
	if (componentString.at(TWO) == TYPE_ENTITY)
	{
		item = new ER_ItemEntity(componentString.at(1));
		item->setId(componentString.at(0).toInt());
	}
	else if (componentString.at(TWO) == TYPE_ATTRIBUTE)
	{
		bool primaryFlag = (componentString.at(THREE) == ONE_STRING ? true : false);
		item = new ER_ItemAttribute(componentString.at(1), primaryFlag);
		item->setId(componentString.at(0).toInt());
	}
	else if (componentString.at(TWO) == TYPE_RELATIONSHIP)
	{
		item = new ER_ItemRelationship(componentString.at(1));
		item->setId(componentString.at(0).toInt());
	}
	return item;
}

// 製作connection
ER_ItemComponent* ER_ItemFactory::createItemConnections(QStringList componentString)
{
	ER_ItemComponent *item;
	item = new ER_ItemConnection(componentString.at(1));
	item->setId(componentString.at(0).toInt());
	return item;
}