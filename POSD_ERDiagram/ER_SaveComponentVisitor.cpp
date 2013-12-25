#include "ER_SaveComponentVisitor.h"
#include "ERD_Attribute.h"
#include "ERD_Connection.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"


ER_SaveComponentVisitor::ER_SaveComponentVisitor()
{
}


ER_SaveComponentVisitor::~ER_SaveComponentVisitor()
{
}

void ER_SaveComponentVisitor::visit(ERD_Attribute* )
{
	componentInfo = "ERD_Attribute";
}

void ER_SaveComponentVisitor::visit(ERD_Connection*)
{
	componentInfo = "ERD_Connection";
}

void ER_SaveComponentVisitor::visit(ERD_Entity*)
{
	componentInfo = "ERD_Entity";
}

void ER_SaveComponentVisitor::visit(ERD_Relationship*)
{
	componentInfo = "ERD_Relationship";
}

string ER_SaveComponentVisitor::getComponentInfo()
{
	return componentInfo;
}