#include "ER_ItemFactory.h"
#define TWO 2
#define THREE 3
#define FIVE 5
#define TYPE_ENTITY "E"
#define TYPE_ATTRIBUTE "A"
#define TYPE_RELATIONSHIP "R"
#define TYPE_CONNECTOR "C"
#define ONE_STRING "1"


ER_ItemFactory::ER_ItemFactory(void)
{
}


ER_ItemFactory::~ER_ItemFactory(void)
{
}

// �s�@node
ER_ItemComponent* ER_ItemFactory::createItemNodes(QStringList componentString)
{
	ER_ItemComponent *item;
	if (componentString.at(TWO) == TYPE_ENTITY)
	{
		item = new ER_ItemEntity(componentString.at(1));
		
	}
	else if (componentString.at(TWO) == TYPE_ATTRIBUTE)
	{
		bool primaryFlag = (componentString.at(FIVE) == ONE_STRING ? true : false);
		item = new ER_ItemAttribute(componentString.at(1), primaryFlag);
	}
	else if (componentString.at(TWO) == TYPE_RELATIONSHIP)
	{
		item = new ER_ItemRelationship(componentString.at(1));
	}
	item->setId(componentString.at(0).toInt());
	item->setPos(componentString.at(3).toInt(), componentString.at(4).toInt());
	return item;
}

// �s�@connection
ER_ItemComponent* ER_ItemFactory::createItemConnections(QStringList componentString)
{
	ER_ItemComponent *item;
	item = new ER_ItemConnection(componentString.at(1));
	item->setId(componentString.at(0).toInt());
	return item;
}

// �s�@attribute
ER_ItemComponent* ER_ItemFactory::createItemAttribute(QString entityName)
{
	ER_ItemComponent *item;
	item = new ER_ItemAttribute(entityName);
	return item;
}

// �s�@entity
ER_ItemComponent* ER_ItemFactory::createItemEntity(QString entityName)
{
	ER_ItemComponent *item;
	item = new ER_ItemEntity(entityName);
	return item;
}

// �s�@relationship
ER_ItemComponent* ER_ItemFactory::createItemRelationship(QString entityName)
{
	ER_ItemComponent *item;
	item = new ER_ItemRelationship(entityName);
	return item;
}

// �s�@connection
ER_ItemComponent* ER_ItemFactory::createItemConnection(QString cardinary)
{
	ER_ItemComponent *item;
	item = new ER_ItemConnection(cardinary);
	return item;
}

// �s�@table item
ER_TableViewItem* ER_ItemFactory::createTableItem(QStringList componentString)
{
	ER_TableViewItem *item;
	QString itemType;
	if (componentString.at(TWO) == TYPE_ENTITY)
	{
		itemType = "Entity";
	}
	else if (componentString.at(TWO) == TYPE_ATTRIBUTE)
	{
		itemType = "Attribute";
	}
	else if (componentString.at(TWO) == TYPE_RELATIONSHIP)
	{
		itemType = "Relation";
	}
	else if (componentString.at(TWO) == TYPE_CONNECTOR)
	{
		itemType = "Connector";
	}
	item = new ER_TableViewItem(componentString.at(0).toInt(), componentString.at(1), itemType);
	return item;
}