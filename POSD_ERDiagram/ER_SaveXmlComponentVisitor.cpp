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

ER_SaveXmlComponentVisitor::ER_SaveXmlComponentVisitor(ER_Model* model)
{
	this->model = model;
}


ER_SaveXmlComponentVisitor::~ER_SaveXmlComponentVisitor()
{
}

void ER_SaveXmlComponentVisitor::visit(ERD_Attribute* attribute)
{
	int id = attribute->getId();
	int posX = attribute->getPosX();
	int posY = attribute->getPosY();
	string idString = Tool_Function::convertIntToString(id);
	string text = attribute->getText();
	string posXString = Tool_Function::convertIntToString(posX);
	string posYString = Tool_Function::convertIntToString(posY);
	componentXmlInfo.append(TAB).append("<Attribute>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Id>").append(idString).append("</Id>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Text>").append(text).append("</Text>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<postionX>").append(posXString).append("</postionX>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<postionY>").append(posYString).append("</postionY>").append(ENDL);
	componentXmlInfo.append(TAB).append("</Attribute>").append(ENDL);
}

void ER_SaveXmlComponentVisitor::visit(ERD_Connection* connection)
{
	int id = connection->getId();
	int sourceId = connection->getNodeId();
	int targetId = connection->getOtherNodeId();
	string idString = Tool_Function::convertIntToString(id);
	string text = connection->getText();
	string sourceIdString = Tool_Function::convertIntToString(sourceId);
	string targetIdString = Tool_Function::convertIntToString(targetId);
	componentXmlInfo.append(TAB).append("<Connector>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Id>").append(idString).append("</Id>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Text>").append(text).append("</Text>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Source>").append(sourceIdString).append("</Source>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Target>").append(targetIdString).append("</Target>").append(ENDL);
	componentXmlInfo.append(TAB).append("</Connector>").append(ENDL);
}

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
	componentXmlInfo.append(TAB).append("<Entity>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Id>").append(idString).append("</Id>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Text>").append(text).append("</Text>").append(ENDL);
	if (primaryKeys.size() > 0)
	{
		componentXmlInfo.append(TAB).append(TAB).append("<PrimaryKey>");
		for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
		{
			int primaryKeyId = *pit;
			componentXmlInfo.append(Tool_Function::convertIntToString(primaryKeyId));
			componentXmlInfo.append(CAMMA_TEXT);
		}
		componentXmlInfo = componentXmlInfo.substr(0,componentXmlInfo.size() - 1);
		componentXmlInfo.append("</PrimaryKey>").append(ENDL);
	}
	componentXmlInfo.append(TAB).append(TAB).append("<postionX>").append(posXString).append("</postionX>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<postionY>").append(posYString).append("</postionY>").append(ENDL);
	componentXmlInfo.append(TAB).append("</Entity>").append(ENDL);
}

void ER_SaveXmlComponentVisitor::visit(ERD_Relationship* relationship)
{
	int id = relationship->getId();
	int posX = relationship->getPosX();
	int posY = relationship->getPosY();
	string idString = Tool_Function::convertIntToString(id);
	string text = relationship->getText();
	string posXString = Tool_Function::convertIntToString(posX);
	string posYString = Tool_Function::convertIntToString(posY);
	componentXmlInfo.append(TAB).append("<Relation>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Id>").append(idString).append("</Id>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<Text>").append(text).append("</Text>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<postionX>").append(posXString).append("</postionX>").append(ENDL);
	componentXmlInfo.append(TAB).append(TAB).append("<postionY>").append(posYString).append("</postionY>").append(ENDL);
	componentXmlInfo.append(TAB).append("</Relation>").append(ENDL);
}

string ER_SaveXmlComponentVisitor::getComponentXmlInfo()
{
	return componentXmlInfo;
}