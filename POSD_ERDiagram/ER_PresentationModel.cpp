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
#define MESSAGE_NODE_1 "The node \'"
#define MESSAGE_NODE_2 "\' has been connected to the node \'"
#define MESSAGE_NODE_3 "\'."
#define MESSAGE_NODE_4 "\' cannot be connected to itself."
#define MESSAGE_NODE_5 "\' has already been connected to component \'"
#define MESSAGE_NODE_6 "\' cannot be connected by the node \'"
#define MESSAGE_NODE_7 "\n"
#define MESSAGE_NODE_8 "Its cardinality of the relationship is \'"
#define ASK_CARDINALITY "ask cardinality"
#define MESSAGE_SUCCESS "Success"
#define MESSAGE_FAIL "Fail"
#define FILE_NOT_FOUND "File not found!!\n"
#define FAIL_TO_SAVE "Fail to Save!!"
#define REDO_SUCCEED "Redo Succeed!"
#define CANNOT_REDO "Cannot redo."
#define UNDO_SUCCEED "Undo Succeed!"
#define CANNOT_UNDO "Cannot undo."
#define COMPONENT_TEXT "The component \""
#define DELETED_TEXT "\" has been deleted."
#define FAIL_DELETED_TEXT "fail to delete!"
#define ALREADY_CONNECTED -1
#define ASK_CARDINALITY_STATE -2
#define SAME_NODE -3
#define CANNOT_CONNECT -4

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

const char* ER_PresentationModel::entityOptionTypeNames[SizeOfEntityOptionType] = { "A", "E", "R", "Attribute", "Entity", "Relation"};

// 新增Node時輸入與Type之間的對應
int ER_PresentationModel::addNodeOptionMapping(string command)
{
	int result = -1;
	for (int i = 0; i < SizeOfEntityOptionType; i++)
	{
		if(command == entityOptionTypeNames[i])
		{
			result = i;
		}
	}
	return result;
}

// 新增節點
string ER_PresentationModel::addNode(ERD_Component::ComponentType componentType, string nodeName, int posX, int posY)
{
	return cmdManager.execute(new ER_AddCommand(&model, componentType, nodeName, posX, posY));
}

// 取得現在的ID
int ER_PresentationModel::getCurrentId()
{
	return model.getCurrentId();
}

// 取得ID藉由index
int ER_PresentationModel::getIdByIndex(int index)
{
	return model.getIdByIndex(index);
}

// 取得connection(by ID)連接兩端的ID以nodeNumber來區分0 1
int ER_PresentationModel::getConnectionNodeById(int id, int nodeNumber)
{
	return model.getConnectionNodeById(id, nodeNumber);
}

// 取得text的值藉由id
string ER_PresentationModel::getNameById(int id)
{
	return model.getNameById(id);
}

// 取得Type藉由id
ERD_Component::ComponentType ER_PresentationModel::getTypeById(int id)
{
	return model.getTypeById(id);
}

// 連線訊息
string ER_PresentationModel::getAddConnectionMessage(int firstNodeId,int secondNodeId)
{
	string message, componentIdString, otherComponentIdString;
	componentIdString = Tool_Function::convertIntToString(firstNodeId);
	otherComponentIdString = Tool_Function::convertIntToString(secondNodeId);
	int result = model.checkAddConnection(firstNodeId, secondNodeId);
	if (result == CANNOT_CONNECT)
	{
		message = getCannotConnectMessage(otherComponentIdString, componentIdString);
	}
	else if (result == SAME_NODE)
	{
		message = getSameNodeMessage(componentIdString);
	}
	else if (result == ASK_CARDINALITY_STATE)
	{
		message = getAskCardinaryStateMessage();
	}
	else if (result == ALREADY_CONNECTED)
	{
		message = getAlreadyConnectedMessage(componentIdString, otherComponentIdString);
	}
	else
	{
		cmdManager.execute(new ER_ConnectCommand(&model, firstNodeId, secondNodeId, result));
		message = getNodeConnectedMessage(componentIdString, otherComponentIdString);
	}
	return message;
}

// 回傳不能連線的訊息
string ER_PresentationModel::getCannotConnectMessage(string componentIdString, string otherComponentIdString )
{
	string message;
	message += MESSAGE_NODE_1;
	message	+= componentIdString;
	message	+= MESSAGE_NODE_6;
	message	+= otherComponentIdString;
	message	+= MESSAGE_NODE_3;	
	return message;
}

// 回傳一樣Node連線錯誤的訊息
string ER_PresentationModel::getSameNodeMessage(string componentIdString)
{
	string message;
	message += MESSAGE_NODE_1;
	message	+= componentIdString;
	message	+= MESSAGE_NODE_4;
	return message;
}

// 回傳需要Cardinary資訊的訊息
string ER_PresentationModel::getAskCardinaryStateMessage()
{
	return ASK_CARDINALITY;
}

// 回傳已經連線的訊息
string ER_PresentationModel::getAlreadyConnectedMessage(string componentIdString, string otherComponentIdString)
{
	string message;
	message += MESSAGE_NODE_1;
	message	+= componentIdString;
	message	+= MESSAGE_NODE_5;
	message	+= otherComponentIdString;
	message	+= MESSAGE_NODE_3;
	return message;
}

// 回傳成功連線的訊息
string ER_PresentationModel::getNodeConnectedMessage(string componentIdString, string otherComponentIdString)
{
	string message;
	message += MESSAGE_NODE_1;
	message	+= componentIdString;
	message	+= MESSAGE_NODE_2;
	message	+= otherComponentIdString;
	message	+= MESSAGE_NODE_3;
	return message;
}

// 新增連線
string ER_PresentationModel::addConnection(int firstNodeId,int secondNodeId, ERD_Connection::ConnectionCardinality cardinality)
{
	string message, componentIdString, otherComponentIdString;
	componentIdString = Tool_Function::convertIntToString(firstNodeId);
	otherComponentIdString = Tool_Function::convertIntToString(secondNodeId);
	int connectionId = model.getCurrentId();
	message += MESSAGE_NODE_1;
	message	+= componentIdString;
	message	+= MESSAGE_NODE_2;
	message	+= otherComponentIdString;
	message	+= MESSAGE_NODE_3;
	message	+= MESSAGE_NODE_7;
	message	+= MESSAGE_NODE_8;
	message += ERD_Connection::connectionCardinalityNames[cardinality];
	message	+= MESSAGE_NODE_3;
	cmdManager.execute(new ER_ConnectCommand(&model, firstNodeId, secondNodeId, connectionId, cardinality));
	return message;
}

// 判斷idStr是不是已存在的componentId
bool ER_PresentationModel::isExistComponentId(string idString)
{
	return model.isExistComponentId(idString);
}

// 判斷entityId是不是Entity
string ER_PresentationModel::checkEntitySelectedValid(string entityId)
{
	return model.checkEntitySelectedValid(entityId);
}

// 處理設定primaryKey的字串
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
			message += Tool_Function::convertIntToString(id);
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

// 判斷Attribute是不是屬於特定Entity的
bool ER_PresentationModel::isAttributeBelongEntity(int attributeId, int entityId)
{
	vector<int> attributesId = findIdWithTypeByTargetId(ERD_Component::Attribute, entityId);
	for (vector<int>::iterator it = attributesId.begin(); it < attributesId.end(); it++)
	{
		if (attributeId == *it)
		{
			return true;
		}
	}
	return false;
}

// 設定id為PrimaryKey
void ER_PresentationModel::setIsPrimaryKey(int id)
{
	ERD_Component* component = model.findComponentById(id);
	if (component->getType() == ERD_Component::Attribute)
	{
		ERD_Attribute* attribute = (ERD_Attribute*) component;
		bool keyFlag = attribute->getIsPrimaryKey();
		cmdManager.execute(new ER_SetPrimaryKeyCommand(&model, id, !keyFlag));
	}
}

// 設定id為PrimaryKey
void ER_PresentationModel::setIsPrimaryKey(int id, bool flag)
{
	cmdManager.execute(new ER_SetPrimaryKeyCommand(&model, id, flag));
}

// 取得id是否為primaryKey
bool ER_PresentationModel::getIsPrimaryKey(int id)
{
	return model.getIsPrimaryKey(id);
}

// 取得primaryKey的顯示字串
string ER_PresentationModel::getPrimaryKeyString(int id)
{
	string result;
	vector<int> attributesVector = model.findIdWithTypeByTargetId(ERD_Component::Attribute, id);
	if (attributesVector.size() == 0)
	{
		return result;
	}
	for (vector<int>::iterator it = attributesVector.begin(); it < attributesVector.end(); it++) 
	{
		if (getIsPrimaryKey(*it))
		{
			result += Tool_Function::convertIntToString(*it);
			result += CAMMA;
		}
	}
	result = result.substr(0,result.size() - CAMMA_SIZE);
	return result;
}

// 找Node集合(不包含connection)
vector<int> ER_PresentationModel::findNodes()
{
	return model.findNodes();
}

// 找component集合(全部)
vector<int> ER_PresentationModel::findComponents()
{
	return model.findComponents();
}

// 找targetId與特定type相連的NodeID(不包含connection)
vector<int> ER_PresentationModel::findIdWithTypeByTargetId(ERD_Component::ComponentType type, int id)
{
	return model.findIdWithTypeByTargetId(type, id);
}

// 找特定型態的component集合
vector<int> ER_PresentationModel::findComponentsByType(ERD_Component::ComponentType type)
{
	return model.findComponentsByType(type);
}

// 是否存在table
bool ER_PresentationModel::isExistTable()
{
	vector<int> entitiesId = findComponentsByType(ERD_Component::Entity);
	if (entitiesId.size() == 0)
	{
		return false;
	}
	else
	{
		for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++)
		{
			vector<int> oneByOneRelationEntityId = model.findOneByOneRelationEntityId(*it);
			if (oneByOneRelationEntityId.size() != 0) // 有1對1的Entity
			{
				for (vector<int>::iterator entityIt = oneByOneRelationEntityId.begin(); entityIt < oneByOneRelationEntityId.end(); entityIt++)
				{
					if (model.findPrimaryKeyByEntityId(*entityIt).size() == 0 || model.findPrimaryKeyByEntityId(*it).size() == 0) // 判斷有沒有primaryKey
					{
						return false;
					}
					return true;
				}
			}
		}
		return false;
	}
	
}

// 取得特定ID的ForeignKey
string ER_PresentationModel::getForeignKeyResult(int id)
{
	string foreignKeystring;
	vector<vector<int>> foreignKeysVector = model.findForeignKeyByEntityId(id);
	vector<string> foreignKeyStringVector;
	if (foreignKeysVector.size() != 0) // 有foreignkey的話
	{
		for (vector<vector<int>>::size_type u = 0; u < foreignKeysVector.size(); u++) 
		{ 
			foreignKeystring = FOREIGN_KEY;
			for (vector<int>::size_type v = 0; v < foreignKeysVector[u].size(); v++) 
			{
				foreignKeystring += getNameById(foreignKeysVector[u][v]);
				foreignKeystring += CAMMA;
			}
			foreignKeystring = foreignKeystring.substr(0,foreignKeystring.size() - CAMMA_SIZE);
			foreignKeystring += RIGHT_BRACKET;
			foreignKeystring = CAMMA + foreignKeystring;
			foreignKeyStringVector.push_back(foreignKeystring);
		}
	}
	foreignKeystring = "";
	for (vector<string>::iterator it = foreignKeyStringVector.begin(); it < foreignKeyStringVector.end(); it++)
	{
		foreignKeystring += *it;
	}
	return foreignKeystring;
}

// 回傳特定id的Attribute字串
string ER_PresentationModel::getAttributesForTable(int id)
{
	string result, primaryKeyString = PRIMARY_KEY;
	vector<int> attributesId = findIdWithTypeByTargetId(ERD_Component::Attribute, id);
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
	primaryKeyString = makePrimaryKeyString(primaryKeyCounter, primaryKeyString);
	result = makeResultString(resultCounter, result, primaryKeyString);
	result += getForeignKeyResult(id);
	return result;
}

// 製作primaryKey字串
string ER_PresentationModel::makePrimaryKeyString(int primaryKeyCounter, string primaryKeyString)
{
	if (primaryKeyCounter > 0)
	{
		primaryKeyString = primaryKeyString.substr(0,primaryKeyString.size() - CAMMA_SIZE);
		primaryKeyString += RIGHT_BRACKET;
	}
	else
	{
		primaryKeyString = EMPTY_TEXT;
	}
	return primaryKeyString;
}

// 製作result字串
string ER_PresentationModel::makeResultString(int resultCounter, string result, string primaryKeyString)
{
	if (resultCounter == 0)
	{
		result = primaryKeyString;
	}
	else
	{
		result = primaryKeyString + CAMMA + result;
	}
	return result;
}

// 找出有1對1關係的entity
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

// 回傳table字串
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

// 讀檔
string ER_PresentationModel::readComponentsFile(string path)
{
	string message = model.readComponentsFile(path);
	if (message.find(MESSAGE_SUCCESS) != std::string::npos)
	{
		string result;
		result += getComponentsTable();
		result += ENDL;
		result += getConnectionsTable();
		return result;
	}
	else
	{
		return FILE_NOT_FOUND;
	}
}

// 存檔
string ER_PresentationModel::storeComponents(string path)
{
	string message = model.storeComponents(path);
	if (message.find(MESSAGE_SUCCESS) != std::string::npos)
	{
		return EMPTY_TEXT;
	}
	else
	{
		return FAIL_TO_SAVE;
	}
}

// 回傳connection字串
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
		int id = *it, nodeId = getConnectionNodeById(id, 0), otherNodeId = getConnectionNodeById(id, 1);
		result += SPACE_TEXT_2;
		result += Tool_Function::convertIntToString(id);
		result += SEPARATOR_3;
		result += Tool_Function::convertIntToString(nodeId);
		result += SEPARATOR_3;
		result += Tool_Function::convertIntToString(otherNodeId);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

// 回傳node字串
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
		result += Tool_Function::convertIntToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

// 回傳component字串
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
		result += Tool_Function::convertIntToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

// 回傳entity字串
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
		result += Tool_Function::convertIntToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

// 回傳特定id Attribute字串
string ER_PresentationModel::getAttributesTableById(int id)
{
	string result;
	result += ATTRIBUTE_TEXT;
	result += Tool_Function::convertIntToString(id);
	result += APOSTROPHE_TEXT;
	result += ENDL;
	result += SEPARATOR_1;
	result += ENDL;
	result += COMPONENT_MENU;
	result += ENDL;
	result += SEPARATOR_2;
	result += ENDL;
	vector<int> attributesList = findIdWithTypeByTargetId(ERD_Component::Attribute, id);
	sort(attributesList.begin(), attributesList.end());
	for (vector<int>::iterator it = attributesList.begin(); it < attributesList.end(); it++) 
	{
		int id = *it;
		result += SPACE_TEXT_1;
		result += ERD_Component::componentTypeNames[getTypeById(id)];
		result += SEPARATOR_5;
		result += Tool_Function::convertIntToString(id);
		result += SEPARATOR_5;
		result += getNameById(id);
		result += ENDL;
	}
	result += SEPARATOR_1;
	result += ENDL;
	return result;
}

// redo
string ER_PresentationModel::redo()
{
	string message;
	bool redoResult;
	redoResult = cmdManager.redo();
	if (redoResult)
	{
		message += REDO_SUCCEED;
		message += ENDL;
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
	}
	else
	{
		message += CANNOT_REDO;
		message += ENDL;
	}
	return message;
}

// undo
string ER_PresentationModel::undo()
{
	string message;
	bool undoResult;
	undoResult = cmdManager.undo();
	if (undoResult)
	{
		message += UNDO_SUCCEED;
		message += ENDL;
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
	}
	else
	{
		message += CANNOT_UNDO;
		message += ENDL;
	}
	return message;
}

// 刪除特定id的component
string ER_PresentationModel::deleteComponent(int id)
{
	string cmdResult = cmdManager.execute(new ER_DeleteCommand(&model, id));
	if (cmdResult != EMPTY_TEXT)
	{
		string message;
		message += COMPONENT_TEXT;
		message += cmdResult;
		message += DELETED_TEXT;
		message += ENDL;
		message += getComponentsTable();
		message += ENDL;
		message += getConnectionsTable();
		return message;
	}
	else
	{
		return FAIL_DELETED_TEXT;
	}
}

// 判斷是否有足夠的Node可以連接
bool ER_PresentationModel::enoughNodesToConnect()
{
	return model.enoughNodesToConnect();
}

//判斷是否有改變
bool ER_PresentationModel::getHasModify()
{
	return model.getHasModify();
}

// 回傳GUI要用到的Node資訊
string ER_PresentationModel::getGuiNodes()
{
	return model.getGuiNodes();
}

// 回傳GUI要用到的Connection資訊
string ER_PresentationModel::getGuiConnections()
{
	return model.getGuiConnections();
}

// 設定某個component的位置
void ER_PresentationModel::setComponentPos(int id, int posX, int posY)
{
	model.setComponentPosition(id, posX, posY);
}

// 取得某個component的x座標
int ER_PresentationModel::getComponentPosXById(int id)
{
	ERD_Component* component = model.findComponentById(id);
	return component->getPosX();
}

// 取得某個component的y座標
int ER_PresentationModel::getComponentPosYById(int id)
{
	ERD_Component* component = model.findComponentById(id);
	return component->getPosY();
}

// 設定某個component的text
void ER_PresentationModel::setComponentText(int id, string text)
{
	string cmdResult = cmdManager.execute(new ER_EditTextCommand(&model, id, text));
}

void ER_PresentationModel::modelRegisterObserver(ER_Observer* observer)
{
	model.registerObserver(observer);
}
