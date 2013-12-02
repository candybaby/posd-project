#include "ERD_Connection.h"

ERD_Connection::ERD_Connection(void)
	: ERD_Component()
{
	type = Connection;
}

// clone�غc�l
ERD_Connection::ERD_Connection(ERD_Connection* connectionClone)
	: ERD_Component(connectionClone)
{
	this->cardinality = connectionClone->getCardinality();
	this->nodeId = connectionClone->getNodeId();
	this->otherNodeId = connectionClone->getOtherNodeId();
}

ERD_Connection::ERD_Connection(int id)
{
	this->type = Connection;
	this->id = id;
	this->cardinality = SizeOfCardinality;
}

ERD_Connection::ERD_Connection(int id, ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->type = Connection;
	this->id = id;
	this->text = connectionCardinalityNames[cardinality];
}

// ���A�ഫ
const char* ERD_Connection::connectionCardinalityNames[SizeOfCardinality] = {"1", "N"};

void ERD_Connection::setText(string text)
{
	if (cardinality != SizeOfCardinality)
	{
		if (text == connectionCardinalityNames[one])
		{
			setCardinality(one);
		}
		else if (text == connectionCardinalityNames[n])
		{
			setCardinality(n);
		}
	}
}

bool ERD_Connection::canChangeText(string text)
{
	if (cardinality != SizeOfCardinality)
	{
		if (text == connectionCardinalityNames[one])
		{
			return true;
		}
		else if (text == connectionCardinalityNames[n])
		{
			return true;
		}
	}
	return false;
}

// �]�wcardinality
void ERD_Connection::setCardinality(ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->text = connectionCardinalityNames[cardinality];
}

ERD_Connection::~ERD_Connection(void)
{
}

// �s�u
void ERD_Connection::connectTo(ERD_Component* component)
{
	connections.push_back(component);
	if (connections.size() == 1)
	{
		nodeId = component->getId();
	}
	else
	{
		otherNodeId = component->getId();
	}
}

// ���ocardinality
ERD_Connection::ConnectionCardinality ERD_Connection::getCardinality()
{
	return this->cardinality;
}

// �P�_�O�_����wId���۳s
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

// ���o�Ĥ@�Ӭ۳s��node
int ERD_Connection::getNodeId()
{
	return nodeId;
}

// ���o�ĤG�Ӭ۳s��node
int ERD_Connection::getOtherNodeId()
{
	return otherNodeId;
}

// �J��
ERD_Component* ERD_Connection::clone()
{
	return new ERD_Connection(*this);
}