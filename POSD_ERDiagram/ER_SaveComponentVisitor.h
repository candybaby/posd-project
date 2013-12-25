#pragma once
#ifndef _ER_SAVE_COMPONENT_VISITOR_ 
#define _ER_SAVE_COMPONENT_VISITOR_
#include "ER_ComponentVisitor.h"
#include <string>
using namespace std;

class ER_Model;
class ERD_Attribute;
class ERD_Connection;
class ERD_Entity;
class ERD_Relationship;
class ER_SaveComponentVisitor : public ER_ComponentVisitor
{
public:
	ER_SaveComponentVisitor(ER_Model*);
	~ER_SaveComponentVisitor();
	void visit(ERD_Attribute*);
	void visit(ERD_Connection*);
	void visit(ERD_Entity*);
	void visit(ERD_Relationship*);
	string getComponentInfo();
	string getConnectionInfo();
	string getPrimaryKeyInfo();
	string getPositionInfo();

private:
	string componentInfo;
	string connectionInfo;
	string primaryKeyInfo;
	string positionInfo;
	ER_Model* model;
};
#endif