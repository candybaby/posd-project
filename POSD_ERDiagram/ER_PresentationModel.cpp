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

int ER_PresentationModel::option1Mapping(string command)
{
	int result = -1;
	for (int i = 0; i < SIZE_OF_Option1Type; i++)
	{
		if(command == Option1TypeNames[i])
		{
			result = i;
		}
	}
	return result;
}

void ER_PresentationModel::addNode(ComponentType componentType, string nodeName)
{
	model.addNode(componentType, nodeName);
}

int ER_PresentationModel::getCurrentId()
{
	return model.getCurrentId();
}

int ER_PresentationModel::getId(int index)
{
	return model.getId(index);
}

int ER_PresentationModel::getConnectionNode1(int index)
{
	return model.getConnectionNode1(index);
}
int ER_PresentationModel::getConnectionNode2(int index)
{
	return model.getConnectionNode2(index);
}

string ER_PresentationModel::getName(int index)
{
	return model.getName(index);
}

ComponentType ER_PresentationModel::getType(int index)
{
	return model.getType(index);
}

string ER_PresentationModel::addConnection(int firstNodeId,int secondNodeId)
{
	return model.addConnection(firstNodeId, secondNodeId);
}

string ER_PresentationModel::addConnection(int firstNodeId,int secondNodeId, ConnectionCardinality cardinality)
{
	return model.addConnection(firstNodeId, secondNodeId, cardinality);
}

bool ER_PresentationModel::isConnectCommandValid(string command)
{
	for (int i = 0; i < getCurrentId(); i++)
	{
		int id = getId(i);
		if (Tool_Function::intToString(id) == command)
		{
			return true;
		}
	}
	return false;
}

string ER_PresentationModel::checkEntitySelectedValid(string entityId)
{
	for (int i = 0; i < getCurrentId(); i++)
	{
		int currentId = getId(i);
		if (Tool_Function::intToString(currentId) == entityId)
		{
			if (getType(i) == Entity)
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
	vector<int> attributesId = findTypeIdByComponentId(Attribute, entityId);
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
	vector<int> attributesVector = model.findTypeIdByComponentId(Attribute, id);
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
	for (int i = 0; i < getCurrentId(); i++)
	{
		if (getType(i) != Connection)
		{
			nodesId.push_back(getId(i));
		}
	}
	return nodesId;
}

vector<int> ER_PresentationModel::findTypeIdByComponentId(ComponentType type, int id)
{
	return model.findTypeIdByComponentId(type, id);
}

vector<int> ER_PresentationModel::findComponentType(ComponentType type)
{
	vector<int> entitiesId;
	for (int i = 0; i < getCurrentId(); i++)
	{
		if (getType(i) == type)
		{
			entitiesId.push_back(getId(i));
		}
	}
	return entitiesId;
}

bool ER_PresentationModel::isExistTable()
{
	vector<int> entitiesId = findComponentType(Entity);
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
				foreignKeystring += getName(foreignKeysVector[u][v]);
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
	vector<int> attributesId = findTypeIdByComponentId(Attribute, id);
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
			primaryKeyString += getName(*it);
			primaryKeyString += CAMMA;
			primaryKeyCounter++;
		}
		else
		{
			result += getName(*it);
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
	vector<int> entitiesId = findComponentType(Entity);
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
			message += getName(*it);
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
