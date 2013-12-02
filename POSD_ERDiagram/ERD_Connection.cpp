#include "ERD_Connection.h"

ERD_Connection::ERD_Connection(void)
	: ERD_Component()
{
	type = Connection;
}

// clone建構子
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

// 型態轉換
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

// 設定cardinality
void ERD_Connection::setCardinality(ConnectionCardinality cardinality)
{
	this->cardinality = cardinality;
	this->text = connectionCardinalityNames[cardinality];
}

ERD_Connection::~ERD_Connection(void)
{
}

// 連線
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

// 取得cardinality
ERD_Connection::ConnectionCardinality ERD_Connection::getCardinality()
{
	return this->cardinality;
}

// 判斷是否跟指定Id有相連
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

// 取得第一個相連的node
int ERD_Connection::getNodeId()
{
	return nodeId;
}

// 取得第二個相連的node
int ERD_Connection::getOtherNodeId()
{
	return otherNodeId;
}

// 克隆
ERD_Component* ERD_Connection::clone()
{
	return new ERD_Connection(*this);
}