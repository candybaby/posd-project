#include "ER_PresentationModel.h"
#define CAMMA_SIZE 2
#define CAMMA ", "
#define TABLE_TEXT "Tables:"
#define CONNECTION_TEXT "Connections:"
#define ENTITY_TEXT "Entities:"
#define COMPONENTS_TEXT "The ER diagram is displayed as follows:\nComponents:"
#define ATTRIBUTE_TEXT "Attributes of the entity \'"
#define CONNECTION_MENU "Connection | node | node"
#define NODES_TEXT "Nodes:"
#define COMPONENT_MENU " Type |  ID  |  Name "
#define SEPARATOR_1 "------------------------------------"
#define SEPARATOR_2 "------+------+----------------------"
#define SEPARATOR_3 "   |  "
#define SEPARATOR_4 "-----------+------+-----------------"
#define SEPARATOR_5 "   |   "
#define SEPARATOR_6 "----------------------------------------------------------"
#define TABLE_MENU "  Entity  |  Attribute"
#define SEPARATOR_7 "----------+-----------------------------------------------"
#define SEPARATOR_8 " | "
#define SPACE " "
#define SPACE_TEXT_1 "  "
#define SPACE_TEXT_2 "       "
#define NO_TABLE "It has no table to display. "
#define ENDL "\n"
#define CAMMA_TEXT ','
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

const char* ER_PresentationModel::entityOptionTypeNames[SIZE_OF_EntityOptionType] = { "A", "E", "R", "Attribute", "Entity", "Relation"};

int ER_PresentationModel::option1Mapping(string command)
{
	int result = -1;
	for (int i = 0; i < SIZE_OF_EntityOptionType; i++)
	{
		if(command == entityOptionTypeNames[i])
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
	return model.isConnectCommandValid(command);
}

string ER_PresentationModel::checkEntitySelectedValid(string entityId)
{
	return model.checkEntitySelectedValid(entityId);
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

vector<int> ER_PresentationModel::findNodes()
{
	return model.findNodes();
}

vector<int> ER_PresentationModel::findComponents()
{
	return model.findComponents();
}

vector<int> ER_PresentationModel::findTypeIdByComponentId(ERD_Component::ComponentType type, int id)
{
	return model.findTypeIdByComponentId(type, id);
}

vector<int> ER_PresentationModel::findComponentsByType(ERD_Component::ComponentType type)
{
	return model.findComponentsByType(type);
}

bool ER_PresentationModel::isExistTable()
{
	vector<int> entitiesId = findComponentsByType(ERD_Component::Entity);
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
	vector<int> entitiesId = findComponentsByType(ERD_Component::Entity);
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
	message += ENDL;
	return message;
}

string ER_PresentationModel::loadComponents(string path)
{
	string message = model.loadComponents(path);
	if (message.find("Success") != std::string::npos)
	{
		string result;
		result += getComponentsTable();
		result += ENDL;
		result += getConnectionsTable();
		return result;
	}
	else
	{
		return "File not found!!\n";
	}
}

string ER_PresentationModel::storeComponents(string path)
{
	string message = model.storeComponents(path);
	if (message.find("Success") != std::string::npos)
	{
		return "\n";
	}
	else
	{
		return "Fail to Save!!\n";
	}
}

string ER_PresentationModel::getConnectionsTable()
{
	string result;
	result += CONNECTION_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += CONNECTION_MENU;
	result += ENDL;
	result += SEPARATOR_4;
	result += ENDL;
	vector<int> connectionsId = findComponentsByType(ERD_Component::Connection);
	sort(connectionsId.begin(), connectionsId.end());
	for (vector<int>::iterator it = connectionsId.begin(); it < connectionsId.end(); it++) 
	{
		int id = *it, node1Id = getConnectionNode1ById(id), node2Id = getConnectionNode2ById(id);
		result += SPACE_TEXT_2;
		result += Tool_Function::intToString(id);
		result += SEPARATOR_3;
		result += Tool_Function::intToString(node1Id);
		result += SEPARATOR_3;
		result += Tool_Function::intToString(node2Id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

string ER_PresentationModel::getNodesTable()
{
	string result;
	result += NODES_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += COMPONENT_MENU;
	result += ENDL;
	result += SEPARATOR_2;
	result += ENDL;
	vector<int> nodesId = findNodes();
	sort(nodesId.begin(), nodesId.end());
	for (vector<int>::iterator it = nodesId.begin(); it < nodesId.end(); it++)
	{
		int id = *it;
		result += SPACE_TEXT_1;
		result += ERD_Component::componentTypeNames[getTypeById(id)];
		result += SEPARATOR_5;
		result += Tool_Function::intToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

string ER_PresentationModel::getComponentsTable()
{
	string result;
	result += COMPONENTS_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += COMPONENT_MENU;
	result += ENDL;
	result += SEPARATOR_2;
	result += ENDL;
	vector<int> componentsId = findComponents();
	sort(componentsId.begin(), componentsId.end());
	for (vector<int>::iterator it = componentsId.begin(); it < componentsId.end(); it++)
	{
		int id = *it;
		result += SPACE_TEXT_1;
		result += ERD_Component::componentTypeNames[getTypeById(id)];
		result += SEPARATOR_5;
		result += Tool_Function::intToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

string ER_PresentationModel::getEntitiesTable()
{
	string result;
	result += ENTITY_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += COMPONENT_MENU;
	result += ENDL;
	result += SEPARATOR_2;
	result += ENDL;
	vector<int> entitiesId = findComponentsByType(ERD_Component::Entity);
	sort(entitiesId.begin(), entitiesId.end());
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++) 
	{
		int id = *it;
		result += SPACE_TEXT_1;
		result += ERD_Component::componentTypeNames[getTypeById(id)];
		result += SEPARATOR_5;
		result += Tool_Function::intToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

string ER_PresentationModel::getAttributesTableById(int id)
{
	string result;
	result += ATTRIBUTE_TEXT;
	result += Tool_Function::intToString(id);
	result += APOSTROPHE_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += COMPONENT_MENU;
	result += ENDL;
	result += SEPARATOR_2;
	result += ENDL;
	vector<int> attributesList = findTypeIdByComponentId(ERD_Component::Attribute, id);
	sort(attributesList.begin(), attributesList.end());
	for (vector<int>::iterator it = attributesList.begin(); it < attributesList.end(); it++) 
	{
		int id = *it;
		result += SPACE_TEXT_1;
		result += ERD_Component::componentTypeNames[getTypeById(id)];
		result += SEPARATOR_5;
		result += Tool_Function::intToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

string ER_PresentationModel::redo()
{
	string message;
	bool redoResult;
	redoResult = cmdManager.redo();
	if (redoResult)
	{
		message += "Redo Succeed!";
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
	}
	else
	{
		message += "Cannot redo.";
		message += ENDL;
	}
	return message;
}

string ER_PresentationModel::undo()
{
	string message;
	bool undoResult;
	undoResult = cmdManager.undo();
	if (undoResult)
	{
		message += "Undo Succeed!";
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
	}
	else
	{
		message += "Cannot undo.";
		message += ENDL;
	}
	return message;
}

string ER_PresentationModel::deleteComponent(int id)
{
	string cmdResult = cmdManager.execute(new ER_DeleteCommand(&model, id));
	if (cmdResult != "")
	{
		string message;
		message += "The component \"";
		message += cmdResult;
		message += "\" has been deleted.";
		message += ENDL;
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
		return message;
	}
	else
	{
		return "fail to delete!";
	}
}