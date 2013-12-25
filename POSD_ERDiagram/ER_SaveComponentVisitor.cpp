#include "ER_SaveComponentVisitor.h"
#include "ER_Model.h"
#include "ERD_Attribute.h"
#include "ERD_Connection.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "Tool_Function.h"


ER_SaveComponentVisitor::ER_SaveComponentVisitor(ER_Model* model)
{
	this->model = model;
}


ER_SaveComponentVisitor::~ER_SaveComponentVisitor()
{
}

void ER_SaveComponentVisitor::visit(ERD_Attribute* attribute)
{
	componentInfo = "";
	componentInfo.append("A").append(", ").append(attribute->getText()).append("\n");

	connectionInfo = "";

	primaryKeyInfo = "";

	positionInfo = "";
	int posX, posY;
	posX = attribute->getPosX();
	posY = attribute->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(" ");
	positionInfo.append(Tool_Function::convertIntToString(posY)).append("\n");
}

void ER_SaveComponentVisitor::visit(ERD_Connection* connection)
{
	componentInfo = "";
	componentInfo.append("C");
	if (connection->getText().size() > 0)
	{
		componentInfo.append(", ").append(connection->getText());
	}
	componentInfo.append("\n");

	connectionInfo = "";
	int id, sourceId, targetId;
	id = connection->getId();
	sourceId = connection->getNodeId();
	targetId = connection->getOtherNodeId();
	connectionInfo.append(Tool_Function::convertIntToString(id));
	connectionInfo.append(" ").append(Tool_Function::convertIntToString(sourceId));
	connectionInfo.append(",").append(Tool_Function::convertIntToString(targetId)).append("\n");

	primaryKeyInfo = "";

	positionInfo = "";
}

void ER_SaveComponentVisitor::visit(ERD_Entity* entity)
{
	componentInfo = "";
	componentInfo.append("E").append(", ").append(entity->getText()).append("\n");

	connectionInfo = "";

	primaryKeyInfo = "";
	int id = entity->getId();
	vector<int> primaryKeys = model->findPrimaryKeyByEntityId(id);
	if (primaryKeys.size() > 0)
	{
		primaryKeyInfo.append(Tool_Function::convertIntToString(id));
		primaryKeyInfo.append(" ");
		for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
		{
			primaryKeyInfo.append(Tool_Function::convertIntToString((int)*pit));
			primaryKeyInfo.append(",");
		}
		primaryKeyInfo = primaryKeyInfo.substr(0,primaryKeyInfo.size() - 1);
	}
	primaryKeyInfo.append("\n");

	positionInfo = "";
	int posX, posY;
	posX = entity->getPosX();
	posY = entity->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(" ");
	positionInfo.append(Tool_Function::convertIntToString(posY)).append("\n");
}

void ER_SaveComponentVisitor::visit(ERD_Relationship* relationship)
{
	componentInfo = "";
	componentInfo.append("R").append(", ").append(relationship->getText()).append("\n");

	connectionInfo = "";

	primaryKeyInfo = "";

	positionInfo = "";
	int posX, posY;
	posX = relationship->getPosX();
	posY = relationship->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(" ");
	positionInfo.append(Tool_Function::convertIntToString(posY)).append("\n");
}

string ER_SaveComponentVisitor::getComponentInfo()
{
	return componentInfo;
}

string ER_SaveComponentVisitor::getConnectionInfo()
{
	return connectionInfo;
}

string ER_SaveComponentVisitor::getPrimaryKeyInfo()
{
	return primaryKeyInfo;
}

string ER_SaveComponentVisitor::getPositionInfo()
{
	return positionInfo;
}