#include "ER_ComponentVisitor.h"
#include "ERD_Attribute.h"
#include "ERD_Connection.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"


ER_ComponentVisitor::ER_ComponentVisitor()
{
}


ER_ComponentVisitor::~ER_ComponentVisitor()
{
}

string ER_ComponentVisitor::getComponentInfo()
{
	return componentInfo;
}

string ER_ComponentVisitor::getConnectionInfo()
{
	return connectionInfo;
}

string ER_ComponentVisitor::getPositionInfo()
{
	return positionInfo;
}