#include "ERD_Connection.h"

ERD_Connection::ERD_Connection(void)
{
	type = Connection;
}

ERD_Connection::ERD_Connection(ERD_Connection* rhs)
{
	this->id = rhs->getId();
	this->type = rhs->getType();
	this->text = rhs->getText();
	this->connections = rhs->getConnections();
	this->cardinality = rhs->getCardinality();
	this->node1Id = rhs->getNode1Id();
	this->node2Id = rhs->getNode2Id();
}

ERD_Connection::ERD_Connection(int id)
{
	this->type = Connection;
	this->id = id;
	this->cardinality = SIZE_OF_Cardinality;
}

ERD_Connection::ERD_Connection(int id, ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->type = Connection;
	this->id = id;
	this->text = connectionCardinalityNames[cardinality];
}

const char* ERD_Connection::connectionCardinalityNames[SIZE_OF_Cardinality] = {"1", "N"};

void ERD_Connection::setCardinality(ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->text = connectionCardinalityNames[cardinality];
}

ERD_Connection::~ERD_Connection(void)
{
}

void ERD_Connection::connectTo(ERD_Component* component)
{
	connections.push_back(component);
	if (connections.size() == 1)
	{
		node1Id = component->getId();
	}
	else
	{
		node2Id = component->getId();
	}
}

ERD_Connection::ConnectionCardinality ERD_Connection::getCardinality()
{
	return this->cardinality;
}

bool ERD_Connection::isConnectToId(int id)
{
	for (vector<ERD_Component *>::iterator it = connections.begin(); it < connections.end(); it++)
	{
		ERD_Component* target = *it;
		if (target->getId() == id)
		{
			return true;
		}
	}
	return false;
}

int ERD_Connection::getNode1Id()
{
	return node1Id;
}

int ERD_Connection::getNode2Id()
{
	return node2Id;
}

ERD_Component* ERD_Connection::clone()
{
	return new ERD_Connection(*this);
}