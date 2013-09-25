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
	this->text = ConnectionCardinalityNames[cardinality];
}

void ERD_Connection::setCardinality(ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->text = ConnectionCardinalityNames[cardinality];
}

ERD_Connection::~ERD_Connection(void)
{
}

ConnectionCardinality ERD_Connection::getCardinality()
{
	return this->cardinality;
}

