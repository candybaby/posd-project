#pragma once
#ifndef _ER_ITEMFACTORY_ 
#define _ER_ITEMFACTORY_
#include "ER_ItemEntity.h"
#include "ER_ItemAttribute.h"
#include "ER_ItemRelationship.h"
#include "ER_ItemConnection.h"

class ER_ItemFactory
{
public:
	ER_ItemFactory(void);
	~ER_ItemFactory(void);
	ER_ItemComponent* createItemNodes(QStringList);
	ER_ItemComponent* createItemConnections(QStringList);
	ER_ItemComponent* createItemAttribute(QString);
	ER_ItemComponent* createItemEntity(QString);
	ER_ItemComponent* createItemRelationship(QString);
	ER_ItemComponent* createItemConnection(QString);
};
#endif
