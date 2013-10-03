#include "ERD_Connection.h"

ERD_Connection::ERD_Connection(void)
{
	type = Connection;
}

ERD_Connection::ERD_Connection(int id)
{
	this->type = Connection;
	this->id = id;
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

