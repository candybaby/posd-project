#pragma once
#ifndef _ER_SAVE_XML_COMPONENT_VISITOR_ 
#define _ER_SAVE_XML_COMPONENT_VISITOR_
#include "ER_ComponentVisitor.h"
#include <string>
using namespace std;

class ER_Model;
class ERD_Attribute;
class ERD_Connection;
class ERD_Entity;
class ERD_Relationship;
class ER_SaveXmlComponentVisitor : public ER_ComponentVisitor
{
public:
	ER_SaveXmlComponentVisitor(ER_Model*);
	~ER_SaveXmlComponentVisitor();
	void visit(ERD_Attribute*);
	void visit(ERD_Connection*);
	void visit(ERD_Entity*);
	void visit(ERD_Relationship*);
	string getComponentXmlInfo();

private:
	string componentXmlInfo;
	ER_Model* model;
};
#endif

