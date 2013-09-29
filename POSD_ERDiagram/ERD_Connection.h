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
	static const char* ConnectionCardinalityNames[SIZE_OF_Cardinality];

	ERD_Connection(void);
	ERD_Connection(int);
	ERD_Connection(int, ConnectionCardinality);
	~ERD_Connection(void);
	ConnectionCardinality getCardinality();
	void setCardinality(ConnectionCardinality);

private:
	ConnectionCardinality cardinality;
};
#endif
