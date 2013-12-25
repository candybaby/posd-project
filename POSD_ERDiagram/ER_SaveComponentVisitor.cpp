#include "ER_SaveComponentVisitor.h"
#include "ER_Model.h"
#include "ERD_Attribute.h"
#include "ERD_Connection.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "Tool_Function.h"

#define ENDL "\n"
#define TYPE_ATTRIBUTE "A"
#define TYPE_ENTITY "E"
#define TYPE_CONNECTION "C"
#define TYPE_RELATIONSHIP "R"
#define CAMMA ", "
#define CAMMA_TEXT ","
#define SPACE " "

ER_SaveComponentVisitor::ER_SaveComponentVisitor(ER_Model* model)
{
	this->model = model;
	this->newId = 0;
}


ER_SaveComponentVisitor::~ER_SaveComponentVisitor()
{
}

void ER_SaveComponentVisitor::visit(ERD_Attribute* attribute)
{
	mappingSaveId.insert(pair<int, int> (attribute->getId(), newId));
	componentInfo.append(TYPE_ATTRIBUTE).append(CAMMA).append(attribute->getText()).append(ENDL);

	int posX, posY;
	posX = attribute->getPosX();
	posY = attribute->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(SPACE);
	positionInfo.append(Tool_Function::convertIntToString(posY)).append(ENDL);
	newId++;
}

void ER_SaveComponentVisitor::visit(ERD_Connection* connection)
{
	mappingSaveId.insert(pair<int, int> (connection->getId(), newId));
	componentInfo.append(TYPE_CONNECTION);
	if (connection->getText().size() > 0)
	{
		componentInfo.append(CAMMA).append(connection->getText());
	}
	componentInfo.append(ENDL);

	int id, sourceId, targetId;
	id = mappingSaveId[connection->getId()];
	sourceId = mappingSaveId[connection->getNodeId()];
	targetId = mappingSaveId[connection->getOtherNodeId()];
	connectionInfo.append(Tool_Function::convertIntToString(id));
	connectionInfo.append(SPACE).append(Tool_Function::convertIntToString(sourceId));
	connectionInfo.append(CAMMA_TEXT).append(Tool_Function::convertIntToString(targetId)).append(ENDL);
	newId++;
}

void ER_SaveComponentVisitor::visit(ERD_Entity* entity)
{
	mappingSaveId.insert(pair<int, int> (entity->getId(), newId));
	componentInfo.append(TYPE_ENTITY).append(CAMMA).append(entity->getText()).append(ENDL);

	vector<int> primaryKeys = model->findPrimaryKeyByEntityId(entity->getId());
	int id = mappingSaveId[entity->getId()];
	if (primaryKeys.size() > 0)
	{
		primaryKeyInfo.append(Tool_Function::convertIntToString(id));
		primaryKeyInfo.append(SPACE);
		for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
		{
			int primaryKeyId = mappingSaveId[(int)*pit];
			primaryKeyInfo.append(Tool_Function::convertIntToString(primaryKeyId));
			primaryKeyInfo.append(CAMMA_TEXT);
		}
		primaryKeyInfo = primaryKeyInfo.substr(0,primaryKeyInfo.size() - 1);
	}
	primaryKeyInfo.append(ENDL);

	int posX, posY;
	posX = entity->getPosX();
	posY = entity->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(SPACE);
	positionInfo.append(Tool_Function::convertIntToString(posY)).append(ENDL);
	newId++;
}

void ER_SaveComponentVisitor::visit(ERD_Relationship* relationship)
{
	mappingSaveId.insert(pair<int, int> (relationship->getId(), newId));
	componentInfo.append(TYPE_RELATIONSHIP).append(CAMMA).append(relationship->getText()).append(ENDL);

	int posX, posY;
	posX = relationship->getPosX();
	posY = relationship->getPosY();
	positionInfo.append(Tool_Function::convertIntToString(posX));
	positionInfo.append(SPACE);
	positionInfo.append(Tool_Function::convertIntToString(posY)).append(ENDL);
	newId++;
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