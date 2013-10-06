#pragma once
#ifndef _ERD_CONNECTION_ 
#define _ERD_CONNECTION_
#include "ERD_Component.h"

class ERD_Connection : public ERD_Component
{
public:
	enum ConnectionCardinality
	{
		one,
		n,
		SIZE_OF_Cardinality 
	};
	static const char* connectionCardinalityNames[SIZE_OF_Cardinality];

	ERD_Connection(void);
	ERD_Connection(ERD_Connection* rhs);
	ERD_Connection(int);
	ERD_Connection(int, ConnectionCardinality);
	~ERD_Connection(void);
	void connectTo(ERD_Component*);
	ConnectionCardinality getCardinality();
	void setCardinality(ConnectionCardinality);
	bool isConnectToId(int);
	int getNode1Id();
	int getNode2Id();
	ERD_Component* clone();

private:
	ConnectionCardinality cardinality;
	int node1Id;
	int node2Id;
};
#endif
