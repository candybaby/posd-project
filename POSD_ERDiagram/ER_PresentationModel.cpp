#include "ER_PresentationModel.h"
#define CAMMA_SIZE 2
#define CAMMA ", "
#define TABLE_TEXT "Tables:"
#define SEPARATOR_6 "----------------------------------------------------------"
#define TABLE_MENU "  Entity  |  Attribute"
#define SEPARATOR_7 "----------+-----------------------------------------------"
#define SEPARATOR_8 " | "
#define SPACE " "
#define NO_TABLE "It has no table to display. "
#define ENDL "\n"
#define CAMMA_TEXT ','
#define FIND_ENTITY "Find Right Entity"
#define NOT_ENTITY "Not an Entity"
#define ID_NOT_EXIST "Id Not Exist"
#define NOT_BELONG_ENTITY "\' does not belong to Entity \'"
#define THE_NODE "The node \'"
#define APOSTROPHE_TEXT "\'"
#define EMPTY_TEXT ""
#define SET_DONE_PRIMARY_KEY "Setting Success"
#define FULL_STOP_TEXT "."
#define RE_ENTER "Please enter a valid one again."
#define PRIMARY_KEY "PK("
#define FOREIGN_KEY "FK("
#define RIGHT_BRACKET ")"

ER_PresentationModel::ER_PresentationModel(void)
{
}

ER_PresentationModel::ER_PresentationModel(ER_Model* model)
{
	this->model = *model;
}

ER_PresentationModel::~ER_PresentationModel(void)
{
}

const char* ER_PresentationModel::EntityOptionTypeNames[SIZE_OF_EntityOptionType] = { "A", "E", "R", "Attribute", "Entity", "Relation"};

int ER_PresentationModel::option1Mapping(string command)
{
	int result = -1;
	for (int i = 0; i < SIZE_OF_EntityOptionType; i++)
	{
		if(command == EntityOptionTypeNames[i])
		{
			result = i;
		}
	}
	return result;
}

void ER_PresentationModel::addNode(ERD_Component::ComponentType componentType, string nodeName)
{
	model.addNode(componentType, nodeName);
}

int ER_PresentationModel::getCurrentId()
{
	return model.getCurrentId();
}

int ER_PresentationModel::getIdByIndex(int index)
{
	return model.getIdByIndex(index);
}

int ER_PresentationModel::getConnectionNode1ById(int index)
{
	return model.getConnectionNode1ById(index);
}
int ER_PresentationModel::getConnectionNode2ById(int index)
{
	return model.getConnectionNode2ById(index);
}

string ER_PresentationModel::getNameById(int index)
{
	return model.getNameById(index);
}

ERD_Component::ComponentType ER_PresentationModel::getTypeById(int index)
{
	return model.getTypeById(index);
}

string ER_PresentationModel::addConnection(int firstNodeId,int secondNodeId)
{
	return model.addConnection(firstNodeId, secondNodeId);
}

string ER_PresentationModel::addConnection(int firstNodeId,int secondNodeId, ERD_Connection::ConnectionCardinality cardinality)
{
	return model.addConnection(firstNodeId, secondNodeId, cardinality);
}

bool ER_PresentationModel::isConnectCommandValid(string command)
{
	for (vector<ERD_Component *>::iterator it = model.getComponents().begin(); it < model.getComponents().end(); it++)
	{
		int id = ((ERD_Component *)*it)->getId();
		if (Tool_Function::intToString(id) == command)
		{
			return true;
		}
	}
	return false;
}

string ER_PresentationModel::checkEntitySelectedValid(string entityId)
{
	for (vector<ERD_Component *>::iterator it = model.getComponents().begin(); it < model.getComponents().end(); it++)
	{
		int currentId = ((ERD_Component *)*it)->getId();
		if (Tool_Function::intToString(currentId) == entityId)
		{
			if (((ERD_Component *)*it)->getType() == ERD_Component::Entity)
			{
				return FIND_ENTITY;
			}
			else
			{
				return NOT_ENTITY;
			}
		}
	}
	return ID_NOT_EXIST;
}

string ER_PresentationModel::checkAttributesSelectedValid(string queryMessage,int id)
{
	string message;
	vector<string> queryId;
	queryId = Tool_Function::split(queryMessage, CAMMA_TEXT);
	for (vector<string>::iterator it = queryId.begin(); it < queryId.end(); it++) {
		if (isAttributeBelongEntity(std::stoi(*it), id))
		{
			continue;
		}
		else
		{
			message += THE_NODE;
			message += *it;
			message += NOT_BELONG_ENTITY;
			message += Tool_Function::intToString(id);
			message += APOSTROPHE_TEXT;
			message += FULL_STOP_TEXT;
		}
	}
	if (message == EMPTY_TEXT)
	{
		for(vector<string>::iterator it = queryId.begin(); it < queryId.end(); it++) 
		{
			setIsPrimaryKey(std::stoi(*it), true);
		}
		message = SET_DONE_PRIMARY_KEY;
	}
	else
	{
		message += RE_ENTER;
	}
	return message;
}

bool ER_PresentationModel::isAttributeBelongEntity(int attributeId, int entityId)
{
	vector<int> attributesId = findTypeIdByComponentId(ERD_Component::Attribute, entityId);
	for (vector<int>::iterator it = attributesId.begin(); it < attributesId.end(); it++)
	{
		if (attributeId == *it)
		{
			return true;
		}
	}
	return false;
}

void ER_PresentationModel::setIsPrimaryKey(int id, bool flag)
{
	model.setIsPrimaryKey(id, flag);
}

bool ER_PresentationModel::getIsPrimaryKey(int id)
{
	return model.getIsPrimaryKey(id);
}

string ER_PresentationModel::getPrimaryKeyString(int id)
{
	string result;
	vector<int> attributesVector = model.findTypeIdByComponentId(ERD_Component::Attribute, id);
	if (attributesVector.size() == 0)
	{
		return result;
	}

	for (vector<int>::iterator it = attributesVector.begin(); it < attributesVector.end(); it++) 
	{
		if (getIsPrimaryKey(*it))
		{
			result += Tool_Function::intToString(*it);
			result += CAMMA;
		}
	}
	result = result.substr(0,result.size() - CAMMA_SIZE);
	return result;
}

vector<int> ER_PresentationModel::findNode()
{
	vector<int> nodesId;
	for (vector<ERD_Component *>::iterator it = model.getComponents().begin(); it < model.getComponents().end(); it++)
	{
		if (((ERD_Component *)*it)->getType() != ERD_Component::Connection)
		{
			nodesId.push_back(((ERD_Component *)*it)->getId());
		}
	}
	return nodesId;
}

vector<int> ER_PresentationModel::findComponent()
{
	return model.findComponent();
}

vector<int> ER_PresentationModel::findTypeIdByComponentId(ERD_Component::ComponentType type, int id)
{
	return model.findTypeIdByComponentId(type, id);
}

vector<int> ER_PresentationModel::findComponentType(ERD_Component::ComponentType type)
{
	return model.findComponentType(type);
}

bool ER_PresentationModel::isExistTable()
{
	vector<int> entitiesId = findComponentType(ERD_Component::Entity);
	if (entitiesId.size() == 0)
	{
		return false;
	}
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++)
	{
		if (model.findOneByOneRelationEntityId(*it).size() != 0)
		{
			return true;
		}
	}
	return false;
}

string ER_PresentationModel::getForeignKeyResult(int id)
{
	string foreignKeystring;
	vector<vector<int>> foreignKeysVector = model.findForeignKeyByEntityId(id);
	if (foreignKeysVector.size() != 0) // ¦³foreignkeyªº¸Ü
	{
		foreignKeystring = FOREIGN_KEY;
		for (vector<vector<int>>::size_type u = 0; u < foreignKeysVector.size(); u++) 
		{ 
			for (vector<int>::size_type v = 0; v < foreignKeysVector[u].size(); v++) 
			{
				foreignKeystring += getNameById(foreignKeysVector[u][v]);
				foreignKeystring += CAMMA;
			}
			foreignKeystring = foreignKeystring.substr(0,foreignKeystring.size() - CAMMA_SIZE);
			foreignKeystring += RIGHT_BRACKET;
			foreignKeystring = CAMMA + foreignKeystring;
		}
	}
	return foreignKeystring;
}

string ER_PresentationModel::getAttributesForTable(int id)
{
	string result, primaryKeyString = PRIMARY_KEY;
	vector<int> attributesId = findTypeIdByComponentId(ERD_Component::Attribute, id);
	if (attributesId.size() == 0)
	{
		return result;
	}

	int primaryKeyCounter = 0;
	int resultCounter = 0;
	for (vector<int>::iterator it = attributesId.begin(); it < attributesId.end(); it++)
	{
		if (getIsPrimaryKey(*it))
		{
			primaryKeyString += getNameById(*it);
			primaryKeyString += CAMMA;
			primaryKeyCounter++;
		}
		else
		{
			result += getNameById(*it);
			result += CAMMA;
			resultCounter++;
		}
	}
	if (resultCounter > 0)
	{
		result = result.substr(0,result.size() - CAMMA_SIZE); 
	}

	if (primaryKeyCounter > 0)
	{
		primaryKeyString = primaryKeyString.substr(0,primaryKeyString.size() - CAMMA_SIZE);
		primaryKeyString += RIGHT_BRACKET;
	}
	else
	{
		primaryKeyString = EMPTY_TEXT;
	}

	if (resultCounter == 0)
	{
		result = primaryKeyString;
	}
	else
	{
		result = primaryKeyString + CAMMA + result;
	}
	
	result += getForeignKeyResult(id);
	
	return result;
}

vector<int> ER_PresentationModel::findOneByOneEntity()
{
	vector<int> entitiesId = findComponentType(ERD_Component::Entity);
	vector<int> entitiesOneByOneId;
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++)
	{
		if (model.findOneByOneRelationEntityId(*it).size() != 0)
		{
			entitiesOneByOneId.push_back(*it);
		}
	}
	return entitiesOneByOneId;
}

string ER_PresentationModel::getTable()
{
	string message;
	if (isExistTable())
	{
		message += TABLE_TEXT;
		message += ENDL;
		message += SEPARATOR_6;
		message += ENDL;
		message += TABLE_MENU;
		message += ENDL;
		message += SEPARATOR_7;
		message += ENDL;

		vector<int> entitiesId = findOneByOneEntity();
		for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++)
		{
			message += SPACE;
			message += getNameById(*it);
			message += SEPARATOR_8;
			message += getAttributesForTable(*it);
			message += ENDL;
		}

		message += SEPARATOR_6;
	}
	else
	{
		message += NO_TABLE;
	}

	return message;
}

string ER_PresentationModel::loadComponents(string path)
{
	return model.loadComponents(path);
}

string ER_PresentationModel::storeComponents(string path)
{
	return model.storeComponents(path);
}
