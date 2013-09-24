#include "ER_ComponentFactory.h"

ER_ComponentFactory::ER_ComponentFactory(void)
{
}

ER_ComponentFactory::~ER_ComponentFactory(void)
{
}

ERD_Component* ER_ComponentFactory::createNodeComponent(ComponentType type, string nodeName, int id)
{
	if (type == Attribute)
	{
		return new ERD_Attribute(nodeName, id);
	}
	else if (type == Entity)
	{
		return new ERD_Entity(nodeName, id);
	}
	else if (type == Relationship)
	{
		return new ERD_Relationship(nodeName, id);
	}
	else
	{
		return NULL;
	}
}

ERD_Component* ER_ComponentFactory::createConnectionComponent(ERD_Component* component1, ERD_Component* component2, int id)
{
	ERD_Component* connection = new ERD_Connection(id);
	connection->connectTo(component1);
	connection->connectTo(component2);
	return connection;
}

ERD_Component* ER_ComponentFactory::createConnectionComponent(ERD_Component* component1, ERD_Component* component2, int id, ConnectionCardinality cardinality)
{
	ERD_Component* connection = new ERD_Connection(id, cardinality);
	connection->connectTo(component1);
	connection->connectTo(component2);
	return connection;
}