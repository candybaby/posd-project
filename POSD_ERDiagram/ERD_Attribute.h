#pragma once
#ifndef _ERD_ATTRIBUTE_ 
#define _ERD_ATTRIBUTE_
#include "ERD_Node.h"
class ERD_Attribute : public ERD_Node
{
public:
	ERD_Attribute(void);
	ERD_Attribute(string, int);
	~ERD_Attribute(void);
	virtual bool canConnectTo(ERD_Component*);
	bool getIsPrimaryKey();
	void setPrimaryKey(bool);
	void setConnected(bool);

private:
	bool isPrimaryKey;
	bool isConnected;
};
#endif
