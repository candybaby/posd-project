#include "ERD_Connection.h"

ERD_Connection::ERD_Connection(void)
{
	type = Connection;
}

// clone建構子
ERD_Connection::ERD_Connection(ERD_Connection* connectionClone)
{
	this->id = connectionClone->getId();
	this->type = connectionClone->getType();
	this->text = connectionClone->getText();
	this->connections = connectionClone->getConnections();
	this->cardinality = connectionClone->getCardinality();
	this->node1Id = connectionClone->getNode1Id();
	this->node2Id = connectionClone->getNode2Id();
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

// 型態轉換
const char* ERD_Connection::connectionCardinalityNames[SIZE_OF_Cardinality] = {"1", "N"};

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
		node1Id = component->getId();
	}
	else
	{
		node2Id = component->getId();
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
int ERD_Connection::getNode1Id()
{
	return node1Id;
}

// 取得第二個相連的node
int ERD_Connection::getNode2Id()
{
	return node2Id;
}

// 克隆
ERD_Component* ERD_Connection::clone()
{
	return new ERD_Connection(*this);
}