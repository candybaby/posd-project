#pragma once
#ifndef _ERD_CONNECTION_ 
#define _ERD_CONNECTION_
#include "ERD_Component.h"

class ER_ComponentVisitor;
class ERD_Connection : public ERD_Component
{
public:
	enum ConnectionCardinality
	{
		one,
		n,
		SizeOfCardinality 
	};
	static const char* connectionCardinalityNames[SizeOfCardinality];
	ERD_Connection(void);
	ERD_Connection(ERD_Connection*);
	ERD_Connection(int);
	ERD_Connection(int, ConnectionCardinality);
	~ERD_Connection(void);
	void connectTo(ERD_Component*);
	ConnectionCardinality getCardinality();
	void setText(string);
	void setCardinality(ConnectionCardinality);
	bool isConnectToId(int);
	bool canChangeText(string);
	int getNodeId();
	int getOtherNodeId();
	ERD_Component* clone();
	void accept(ER_ComponentVisitor*);

private:
	ConnectionCardinality cardinality;
	int nodeId;
	int otherNodeId;
};
#endif
