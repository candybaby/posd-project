#pragma once
#ifndef _ER_COMPONENT_VISITOR_ 
#define _ER_COMPONENT_VISITOR_
#include <string>
using namespace std;

class ERD_Attribute;
class ERD_Connection;
class ERD_Entity;
class ERD_Relationship;
class ER_ComponentVisitor
{
public:
	ER_ComponentVisitor();
	~ER_ComponentVisitor();
	virtual void visit(ERD_Attribute*) = 0;
	virtual void visit(ERD_Connection*) = 0;
	virtual void visit(ERD_Entity*) = 0;
	virtual void visit(ERD_Relationship*) = 0;
	virtual string getComponentInfo();
	virtual string getConnectionInfo();
	virtual string getPositionInfo();

protected:
	string componentInfo;
	string connectionInfo;
	string positionInfo;
};
#endif
