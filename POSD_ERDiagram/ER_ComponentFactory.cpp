#include "ER_ComponentFactory.h"

ER_ComponentFactory::ER_ComponentFactory(void)
{
}

ER_ComponentFactory::~ER_ComponentFactory(void)
{
}

// 製作Node
ERD_Component* ER_ComponentFactory::createNodeComponent(ERD_Component::ComponentType type, string nodeName, int id)
{
	if (type == ERD_Component::Attribute)
	{
		return new ERD_Attribute(nodeName, id);
	}
	else if (type == ERD_Component::Entity)
	{
		return new ERD_Entity(nodeName, id);
	}
	else if (type == ERD_Component::Relationship)
	{
		return new ERD_Relationship(nodeName, id);
	}
	else
	{
		return NULL;
	}
}

// 製作Connection
ERD_Component* ER_ComponentFactory::createConnectionComponent(ERD_Component* component, ERD_Component* otherComponent, int id)
{
	ERD_Component* connection = new ERD_Connection(id);
	connection->connectTo(component);
	connection->connectTo(otherComponent);
	return connection;
}

// 製作Connection
ERD_Component* ER_ComponentFactory::createConnectionComponent(ERD_Component* component, ERD_Component* otherComponent, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	if (cardinality == ERD_Connection::SizeOfCardinality)
	{
		return createConnectionComponent(component, otherComponent, id);
	}
	else
	{
		ERD_Component* connection = new ERD_Connection(id, cardinality);
		connection->connectTo(component);
		connection->connectTo(otherComponent);
		return connection;
	}
}