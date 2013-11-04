#include "ER_ItemFactory.h"


ER_ItemFactory::ER_ItemFactory(void)
{
}


ER_ItemFactory::~ER_ItemFactory(void)
{
}

ER_ItemComponent* ER_ItemFactory::createItemNodes(QStringList componentString)
{
	//componentList.at(0);//ID
	//componentList.at(1);//Name
	//componentList.at(2);//Type
	ER_ItemComponent *item;
	if (componentString.at(2) == "E")
	{
		item = new ER_ItemEntity(componentString.at(1));
		item->setId(componentString.at(0).toInt());
	}
	else if (componentString.at(2) == "A")
	{
		bool primaryFlag = (componentString.at(3) == "1" ? true : false);
		item = new ER_ItemAttribute(componentString.at(1), primaryFlag);
		item->setId(componentString.at(0).toInt());
	}
	else if (componentString.at(2) == "R")
	{
		item = new ER_ItemRelationship(componentString.at(1));
		item->setId(componentString.at(0).toInt());
	}
	//else if (componentString.at(2) == "C")
	//{
	//	item = new ER_ItemConnection(componentString.at(1));
	//	item->setId(componentString.at(0).toInt());
	//	//ER_ItemComponent *item = new ER_ItemConnection(componentList.at(1));
	//	//item->setId(componentList.at(0).toInt());
	//	//addItem(item);
	//}
	return item;
}

ER_ItemComponent* ER_ItemFactory::createItemConnections(QStringList componentString)
{
	//componentList.at(0);//ID
	//componentList.at(1);//Name
	//componentList.at(2);//Type
	ER_ItemComponent *item;
	item = new ER_ItemConnection(componentString.at(1));
	item->setId(componentString.at(0).toInt());
	//	//ER_ItemComponent *item = new ER_ItemConnection(componentList.at(1));
	//	//item->setId(componentList.at(0).toInt());
	//	//addItem(item);
	return item;
}