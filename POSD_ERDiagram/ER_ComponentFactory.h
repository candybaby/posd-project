#pragma once
#ifndef _ER_COMPONMENTFACTORY_ 
#define _ER_COMPONMENTFACTORY_
#include "ERD_Entity.h"
#include "ERD_Attribute.h"
#include "ERD_Relationship.h"
#include "ERD_Connection.h"

class ER_ComponentFactory
{
public:
	ER_ComponentFactory(void);
	~ER_ComponentFactory(void);
	ERD_Component* createNodeComponent(ERD_Component::ComponentType, string, int);
	ERD_Component* createConnectionComponent(ERD_Component*, ERD_Component*, int);
	ERD_Component* createConnectionComponent(ERD_Component*, ERD_Component*, int, ERD_Connection::ConnectionCardinality);
};

#endif
