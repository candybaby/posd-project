#include "ER_SaveComponentVisitor.h"
#include "ER_Model.h"
#include "ERD_Component.h"
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

// visit attribute
void ER_SaveComponentVisitor::visit(ERD_Attribute* attribute)
{
	if (mappingSaveId.find(attribute->getId()) == mappingSaveId.end())
	{
		mappingSaveId.insert(pair<int, int> (attribute->getId(), newId));
		components.push_back(attribute);
		newId++;
	}
	else
	{
		componentInfo.append(TYPE_ATTRIBUTE).append(CAMMA).append(attribute->getText()).append(ENDL);

		int posX, posY;
		posX = attribute->getPosX();
		posY = attribute->getPosY();
		positionInfo.append(Tool_Function::convertIntToString(posX));
		positionInfo.append(SPACE);
		positionInfo.append(Tool_Function::convertIntToString(posY)).append(ENDL);
	}
}

// visit connection
void ER_SaveComponentVisitor::visit(ERD_Connection* connection)
{
	if (mappingSaveId.find(connection->getId()) == mappingSaveId.end())
	{
		mappingSaveId.insert(pair<int, int> (connection->getId(), newId));
		components.push_back(connection);
		newId++;
	}
	else
	{
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
	}
}

// visit entity
void ER_SaveComponentVisitor::visit(ERD_Entity* entity)
{
	if (mappingSaveId.find(entity->getId()) == mappingSaveId.end())
	{
		mappingSaveId.insert(pair<int, int> (entity->getId(), newId));
		components.push_back(entity);
		newId++;
	}
	else
	{
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
	}
}

// visit relationship
void ER_SaveComponentVisitor::visit(ERD_Relationship* relationship)
{
	if (mappingSaveId.find(relationship->getId()) == mappingSaveId.end())
	{
		mappingSaveId.insert(pair<int, int> (relationship->getId(), newId));
		components.push_back(relationship);
		newId++;
	}
	else
	{
		componentInfo.append(TYPE_RELATIONSHIP).append(CAMMA).append(relationship->getText()).append(ENDL);

		int posX, posY;
		posX = relationship->getPosX();
		posY = relationship->getPosY();
		positionInfo.append(Tool_Function::convertIntToString(posX));
		positionInfo.append(SPACE);
		positionInfo.append(Tool_Function::convertIntToString(posY)).append(ENDL);
	}
}

// visit all components
void ER_SaveComponentVisitor::visitAllComponents()
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		(*it)->accept(this);
	}
}

// ¾켹component info
string ER_SaveComponentVisitor::getComponentInfo()
{
	return componentInfo;
}

// ¾켹connection info
string ER_SaveComponentVisitor::getConnectionInfo()
{
	return connectionInfo;
}

// ¾켹primary key info
string ER_SaveComponentVisitor::getPrimaryKeyInfo()
{
	return primaryKeyInfo;
}

// ¾켹position info
string ER_SaveComponentVisitor::getPositionInfo()
{
	return positionInfo;
}