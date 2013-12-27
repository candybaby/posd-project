#include "ER_SaveXmlComponentVisitor.h"
#include "ER_Model.h"
#include "ERD_Attribute.h"
#include "ERD_Connection.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "Tool_Function.h"

#define ENDL "\n"
#define TAB "    "
#define CAMMA_TEXT ","
#define ATTRIBUTE_TAG "<Attribute>"
#define ATTRIBUTE_TAG_END "</Attribute>"
#define CONNECTOR_TAG "<Connector>"
#define CONNECTOR_TAG_END "</Connector>"
#define ENTITY_TAG "<Entity>"
#define ENTITY_TAG_END "</Entity>"
#define RELATION_TAG "<Relation>"
#define RELATION_TAG_END "</Relation>"
#define ID_TAG "<Id>"
#define ID_TAG_END "</Id>"
#define TEXT_TAG "<Text>"
#define TEXT_TAG_END "</Text>"
#define POSITION_X_TAG "<PositionX>"
#define POSITION_X_TAG_END "</PositionX>"
#define POSITION_Y_TAG "<PositionY>"
#define POSITION_Y_TAG_END "</PositionY>"
#define SOURCE_TAG "<Source>"
#define SOURCE_TAG_END "</Source>"
#define TARGET_TAG "<Target>"
#define TARGET_TAG_END "</Target>"
#define PRIMARY_KEY_TAG "<PrimaryKey>"
#define PRIMARY_KEY_TAG_END "</PrimaryKey>"

ER_SaveXmlComponentVisitor::ER_SaveXmlComponentVisitor(ER_Model* model)
{
	this->model = model;
}


ER_SaveXmlComponentVisitor::~ER_SaveXmlComponentVisitor()
{
}

// visit attribute
void ER_SaveXmlComponentVisitor::visit(ERD_Attribute* attribute)
{
	int id = attribute->getId();
	int posX = attribute->getPosX();
	int posY = attribute->getPosY();
	string idString = Tool_Function::convertIntToString(id);
	string text = attribute->getText();
	string posXString = Tool_Function::convertIntToString(posX);
	string posYString = Tool_Function::convertIntToString(posY);
	componentXmlInfo.append(TAB).append(ATTRIBUTE_TAG).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(ID_TAG).append(idString).append(ID_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(TEXT_TAG).append(text).append(TEXT_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_X_TAG).append(posXString).append(POSITION_X_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_Y_TAG).append(posYString).append(POSITION_Y_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(ATTRIBUTE_TAG_END).append(ENDL);
}

// visit connection
void ER_SaveXmlComponentVisitor::visit(ERD_Connection* connection)
{
	int id = connection->getId();
	int sourceId = connection->getNodeId();
	int targetId = connection->getOtherNodeId();
	string idString = Tool_Function::convertIntToString(id);
	string text = connection->getText();
	string sourceIdString = Tool_Function::convertIntToString(sourceId);
	string targetIdString = Tool_Function::convertIntToString(targetId);
	componentXmlInfo.append(TAB).append(CONNECTOR_TAG).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(ID_TAG).append(idString).append(ID_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(TEXT_TAG).append(text).append(TEXT_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(SOURCE_TAG).append(sourceIdString).append(SOURCE_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(TARGET_TAG).append(targetIdString).append(TARGET_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(CONNECTOR_TAG_END).append(ENDL);
}

// visit entity
void ER_SaveXmlComponentVisitor::visit(ERD_Entity* entity)
{
	int id = entity->getId();
	int posX = entity->getPosX();
	int posY = entity->getPosY();
	vector<int> primaryKeys = model->findPrimaryKeyByEntityId(entity->getId());
	string idString = Tool_Function::convertIntToString(id);
	string text = entity->getText();
	string posXString = Tool_Function::convertIntToString(posX);
	string posYString = Tool_Function::convertIntToString(posY);
	componentXmlInfo.append(TAB).append(ENTITY_TAG).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(ID_TAG).append(idString).append(ID_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(TEXT_TAG).append(text).append(TEXT_TAG_END).append(ENDL);
	if (primaryKeys.size() > 0)
	{
		componentXmlInfo.append(TAB).append(TAB).append(PRIMARY_KEY_TAG);
		for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
		{
			int primaryKeyId = *pit;
			componentXmlInfo.append(Tool_Function::convertIntToString(primaryKeyId));
			componentXmlInfo.append(CAMMA_TEXT);
		}
		componentXmlInfo = componentXmlInfo.substr(0,componentXmlInfo.size() - 1);
		componentXmlInfo.append(PRIMARY_KEY_TAG_END).append(ENDL);
	}
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_X_TAG).append(posXString).append(POSITION_X_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_Y_TAG).append(posYString).append(POSITION_Y_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(ENTITY_TAG_END).append(ENDL);
}

// visit relationship
void ER_SaveXmlComponentVisitor::visit(ERD_Relationship* relationship)
{
	int id = relationship->getId();
	int posX = relationship->getPosX();
	int posY = relationship->getPosY();
	string idString = Tool_Function::convertIntToString(id);
	string text = relationship->getText();
	string posXString = Tool_Function::convertIntToString(posX);
	string posYString = Tool_Function::convertIntToString(posY);
	componentXmlInfo.append(TAB).append(RELATION_TAG).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(ID_TAG).append(idString).append(ID_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(TEXT_TAG).append(text).append(TEXT_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_X_TAG).append(posXString).append(POSITION_X_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append(POSITION_Y_TAG).append(posYString).append(POSITION_Y_TAG_END).append(ENDL);
	componentXmlInfo.append(TAB).append(RELATION_TAG_END).append(ENDL);
}

// ¨ú±o components info
string ER_SaveXmlComponentVisitor::getComponentXmlInfo()
{
	return componentXmlInfo;
}