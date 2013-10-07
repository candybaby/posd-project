#include "ER_Model.h"
#define EMPTY_TEXT ""
#define FIND_ENTITY "Find Right Entity"
#define NOT_ENTITY "Not an Entity"
#define ID_NOT_EXIST "Id Not Exist"
#define MESSAGE_SUCCESS "Success"
#define MESSAGE_FAIL "Fail"
#define CAMMA_TEXT ","
#define CAMMA ", "
#define SPACE " "
#define CHAR_ENDL '\n'
#define CHAR_SPACE ' '
#define CHAR_CAMMA ','
#define ALREADY_CONNECTED -1
#define ASK_CARDINALITY -2
#define SAME_NODE -3
#define CANNOT_CONNECT -4

using namespace std;

ER_Model::ER_Model(void)
{
	currentId = 0;
}

ER_Model::~ER_Model(void)
{
	clearCurrentComponents();
}

// 清除components
void ER_Model::clearCurrentComponents()
{
	while (components.size() > 0)
	{
		ERD_Component* delData = components.back();
		components.pop_back();
		delete delData;
	}
}

// 依據id將components重新sort一遍 (未測試)
void ER_Model::sortComponents()
{
	ComponentSorter componentSorter;
	std::sort(components.begin(), components.end(), componentSorter);
}

const char* ER_Model::componentTypeMapNames[SIZE_OF_ComponentTypeMap] = {"A", "E", "R", "C"};

vector<ERD_Component*> ER_Model::getComponents()
{
	return components;
}

// 新增節點(不包含connection)
int ER_Model::addNode(ERD_Component::ComponentType type, string nodeName)
{
	int id = currentId;
	ERD_Component* component = factory.createNodeComponent(type, nodeName, currentId);
	components.push_back(component);
	currentId++;
	sortComponents();
	return id;
}

// 新增節點(不包含connection) Type為字串
void ER_Model::addNode(string type, string nodeName)
{
	for (int i = 0; i < SIZE_OF_ComponentTypeMap; i++)
	{
		if (componentTypeMapNames[i] == type)
		{
			addNode((ERD_Component::ComponentType)i, nodeName);
		}
	}
}

// 新增節點 特定ID位置的新增
void ER_Model::addNode(ERD_Component::ComponentType type, string nodeName, int id)
{
	ERD_Component* component = factory.createNodeComponent(type, nodeName, id);
	components.push_back(component);
	sortComponents();
}

// 設定Attribute為以連線狀態
ERD_Component* ER_Model::setAttributeTypeConnected(ERD_Component* component)
{
	ERD_Attribute* attribute = (ERD_Attribute*) component;
	attribute->setConnected(true);
	return attribute;
}

// 新增連線 參數為兩個Node要連接的ID 結果 -1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連
int ER_Model::checkAddConnection(int component1Id, int component2Id)
{
	int result = ALREADY_CONNECTED;
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	if (isAlreadyConnect(component1, component2)) //已經相連了
	{
		result = ALREADY_CONNECTED;
		return result;
	}
	if (component1->canConnectTo(component2) && component2->canConnectTo(component1)) //可以連
	{
		if ((component1->getType() == ERD_Component::Entity && component2->getType() == ERD_Component::Relationship) ||
			(component1->getType() == ERD_Component::Relationship && component2->getType() == ERD_Component::Entity))
		{
			result = ASK_CARDINALITY;
		}
		else
		{
			if (component1->getType() == ERD_Component::Attribute)
			{
				component1 = setAttributeTypeConnected(component1);
			}
			if (component2->getType() == ERD_Component::Attribute)
			{
				component2 = setAttributeTypeConnected(component2);
			}
			result = currentId;
			currentId++;
		}
	}
	else if (component1Id == component2Id)
	{
		result = SAME_NODE;
	}
	else
	{
		result = CANNOT_CONNECT;
	}
	return result;
}


int ER_Model::getAddConnectionId()
{
	int result;
	result = currentId;
	currentId++;
	return result;
}

// 新增連線 特定ID位置的新增 主要用於讀檔時的新增
void ER_Model::addConnection(int component1Id, int component2Id, int id)
{
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	ERD_Component* component = factory.createConnectionComponent(component1, component2, id);
	components.push_back(component);
	sortComponents();
}

// 新增連線 特定ID位置的新增包含cardinality屬性
void ER_Model::addConnection(int component1Id, int component2Id, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	ERD_Component* component;
	component = factory.createConnectionComponent(component1, component2, id, cardinality);
	components.push_back(component);
	sortComponents();
}

// 新增連線 特定ID位置的新增包含cardinality屬性 主要用於讀檔時的新增
void ER_Model::addConnection(int component1Id, int component2Id, int id, string cardinalityStr)
{
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	ERD_Component* component;
	for (int i = 0; i < ERD_Connection::SIZE_OF_Cardinality; i++)
	{
		if (ERD_Connection::connectionCardinalityNames[i] == cardinalityStr)
		{
			component = factory.createConnectionComponent(component1, component2, id, (ERD_Connection::ConnectionCardinality)i);
		}
		else if (cardinalityStr == EMPTY_TEXT)
		{
			component = factory.createConnectionComponent(component1, component2, id);
		}
	}
	components.push_back(component);
	sortComponents();
}

// 回傳目前的ID
int ER_Model::getCurrentId()
{
	return currentId;
}

// 用index找到對應的ID
int ER_Model::getIdByIndex(int index)
{
	return components.at(index)->getId();
}

// 取得連線的兩個node 以nodeNumber來分node0與node1
int ER_Model::getConnectionNodeById(int id, int nodeNumber)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return ((ERD_Component *)*it)->getConnections().at(nodeNumber)->getId();
		}
	}
	return -1; // exception
}

// 取得名稱藉由ID
string ER_Model::getNameById(int id)
{
	ERD_Component* target = findComponentById(id);
	if (target != NULL)
	{
		return target->getText();
	}
	else
	{
		return EMPTY_TEXT; // exception
	}
}

// 取得型態藉由ID
ERD_Component::ComponentType ER_Model::getTypeById(int id)
{
	ERD_Component* target = findComponentById(id);
	if (target != NULL)
	{
		return target->getType();
	}
	else
	{
		return ERD_Component::SIZE_OF_ComponentType; // exception
	}
}

// 取得ERD_Component藉由ID
ERD_Component* ER_Model::findComponentById(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return *it;
		}
	}
	return NULL;
}

// 兩個node是否已經連線
bool ER_Model::isAlreadyConnect(ERD_Component* node1, ERD_Component* node2)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == ERD_Component::Connection)
		{
			ERD_Connection* connection = (ERD_Connection*)*it;
			if (connection->isConnectToId(node1->getId()) && connection->isConnectToId(node2->getId()))
			{
				return true;
			}
		}
	}
	return false;
}

// 設定特定的ID為PrimaryKey(Attribute)
void ER_Model::setIsPrimaryKey(int id, bool flag)
{
	ERD_Attribute* att = (ERD_Attribute*)findComponentById(id);
	att->setPrimaryKey(flag);
}

// 取得特定的ID(Attribute)是否為PrimaryKey
bool ER_Model::getIsPrimaryKey(int id)
{
	ERD_Attribute* att = (ERD_Attribute*)findComponentById(id);
	if (att != NULL)
	{
		return att->getIsPrimaryKey();
	}
	else
	{
		return false; // exception
	}
}

// sourceId為connection找連線為targetId的點將與targetId相連的ID且形態等於type的點記錄起來
void ER_Model::setRelatedIdVector(int sourceId, int targetId, ERD_Component::ComponentType type, vector<int> &idVector)
{
	int id = -1;
	if (getConnectionNodeById(sourceId, 0) == targetId)
	{
		id = getConnectionNodeById(sourceId, 1);
	}
	else if (getConnectionNodeById(sourceId, 1) == targetId)
	{
		id = getConnectionNodeById(sourceId, 0);
	}
	if (id >= 0 && findComponentById(id)->getType() == type)
	{
		idVector.push_back(id);
	}
}

// 找Node集合(不包含connection)
vector<int> ER_Model::findNodes()
{
	vector<int> nodesId;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() != ERD_Component::Connection)
		{
			nodesId.push_back(((ERD_Component *)*it)->getId());
		}
	}
	return nodesId;
}

// 找component集合(全部)
vector<int> ER_Model::findComponents()
{
	vector<int> entitiesId;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		entitiesId.push_back(((ERD_Component *)*it)->getId());
	}
	return entitiesId;
}

// 找特定型態的component集合
vector<int> ER_Model::findComponentsByType(ERD_Component::ComponentType type)
{
	vector<int> entitiesId;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == type)
		{
			entitiesId.push_back(((ERD_Component *)*it)->getId());
		}
	}
	return entitiesId;
}

// 找targetId與特定type相連的NodeID(不包含connection)
vector<int> ER_Model::findIdWithTypeByTargetId(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector, connectionIds;
	connectionIds = findComponentsByType(ERD_Component::Connection);
	for (vector<int>::iterator it = connectionIds.begin(); it < connectionIds.end(); it++)
	{
		setRelatedIdVector(*it, targetId, type, idVector);
	}
	return idVector;
}

// 找targetId與特定type相連的NodeID且Cardinality性質為one的(不包含connection)
vector<int> ER_Model::findIdWithTypeByTargetIdWithCardinality(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector, connectionIds;
	connectionIds = findComponentsByType(ERD_Component::Connection);
	for (vector<int>::iterator it = connectionIds.begin(); it < connectionIds.end(); it++)
	{
		ERD_Connection* connection = (ERD_Connection*)findComponentById(*it);
		if (connection->getCardinality() == ERD_Connection::one)
		{
			setRelatedIdVector(*it, targetId, type, idVector);
		}
	}
	return idVector;
}

// 找特定entity的primaryKey
vector<int> ER_Model::findPrimaryKeyByEntityId(int entityId)
{
	vector<int> primaryKeys;
	vector<int> attributesId = findIdWithTypeByTargetId(ERD_Component::Attribute, entityId);
	for (vector<int>::iterator it = attributesId.begin(); it < attributesId.end(); it++)
	{
		ERD_Attribute* attribute = (ERD_Attribute*)findComponentById(*it);
		if (attribute->getIsPrimaryKey())
		{
			primaryKeys.push_back(*it);
		}
	}
	return primaryKeys;
}

// 給定entityId找他的foreignKeys
vector<vector<int>> ER_Model::findForeignKeyByEntityId(int entityId)
{
	vector<vector<int>> foreignKeysIdVector;
	vector<int> entitiesId = findOneByOneRelationEntityId(entityId);
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++) // 全抓
	{
		ERD_Entity* entity = (ERD_Entity*) findComponentById(entityId);
		ERD_Entity* targetEntity = (ERD_Entity*) findComponentById(*it);
		if (!targetEntity->isContainForeignEntityId(entityId))
		{
			entity->addForeignEntityId(*it);
			vector<int> foreignKeysId;
			foreignKeysId = findPrimaryKeyByEntityId(*it);
			foreignKeysIdVector.push_back(foreignKeysId);
		}
	}
	return foreignKeysIdVector;
}

// 給定entity找1對1關係的entity
vector<int> ER_Model::findOneByOneRelationEntityId(int targetId)
{
	vector<int> idVector;
	vector<int> relationIdVector;
	relationIdVector = findIdWithTypeByTargetIdWithCardinality(ERD_Component::Relationship, targetId);
	for (vector<int>::iterator it = relationIdVector.begin(); it < relationIdVector.end(); it++) 
	{
		vector<int> entityIdVector = findIdWithTypeByTargetIdWithCardinality(ERD_Component::Entity, *it);
		for (vector<int>::iterator entityIt = entityIdVector.begin(); entityIt < entityIdVector.end(); entityIt++)
		{
			if (*entityIt != targetId)
			{
				idVector.push_back(*entityIt);
			}
		}
	}
	return idVector;
}

// 讀檔
string ER_Model::loadComponents(string path)
{
	string result;
	ER_FileManager file;

	if (file.openFile(path, ER_FileManager::Read))
	{
		currentId = 0; // init
		clearCurrentComponents();
		string content;
		vector<string> lines;
		int state = 0;
		map<int, string> connectionMap;
		content = file.readFile();
		lines = Tool_Function::split(content, CHAR_ENDL);
		for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
		{
			if (*it == EMPTY_TEXT)
			{
				state++;
			} 
			else
			{
				if (state == 0)
				{
					vector<string> lineParts = Tool_Function::split(*it, CHAR_SPACE);
					if (lineParts.size() > 1)
					{
						string typeStr = lineParts[0].substr(0, 1);
						string text = lineParts[1];
						if (typeStr != componentTypeMapNames[Connection])
						{
							addNode(typeStr, text);
						}
						else
						{
							connectionMap.insert(pair<int, string> (currentId, text));
							currentId++;
						}
					}
					else
					{
						connectionMap.insert(pair<int, string> (currentId, EMPTY_TEXT));
						currentId++;
					}
				}
				else if (state == 1)
				{
					vector<string> lineParts = Tool_Function::split(*it, CHAR_SPACE);
					string connectionIdStr = lineParts[0];
					string nodesIdStr = lineParts[1];
					vector<string> nodes = Tool_Function::split(nodesIdStr, CHAR_CAMMA);
					int node1, node2, connectionId;
					node1 = std::stoi(nodes[0]);
					node2 = std::stoi(nodes[1]);
					connectionId = std::stoi(connectionIdStr);
					string cardinalityStr = connectionMap.at(connectionId);
					if (cardinalityStr != EMPTY_TEXT)
					{
						addConnection(node1, node2, connectionId, cardinalityStr);
					}
					else
					{
						addConnection(node1, node2, connectionId);
					}
				}
				else
				{
					vector<string> lineParts = Tool_Function::split(*it, CHAR_SPACE);
					string primaryKeyIdStr = lineParts[1];
					vector<string> primaryKeysId = Tool_Function::split(primaryKeyIdStr, CHAR_CAMMA);
					for (vector<string>::iterator it = primaryKeysId.begin(); it < primaryKeysId.end(); it++)
					{
						int primaryKeyId = std::stoi(*it);
						setIsPrimaryKey(primaryKeyId, true);
					}
				}
			}
		}
		file.closeFile();
		result = MESSAGE_SUCCESS;
	}
	else
	{
		result = MESSAGE_FAIL;
	}
	return result;
}

// 存檔
string ER_Model::storeComponents(string path)
{
	string result;
	ER_FileManager file;
	if (file.openFile(path, ER_FileManager::Write))
	{
		for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
		{
			string line, tmp;
			line = componentTypeMapNames[((ERD_Component *)*it)->getType()];
			tmp = ((ERD_Component *)*it)->getText();
			if (tmp.size() > 0)
			{
				line += CAMMA;
				line += tmp;
			}
			file.writeLine(line);
		}
		file.writeLine(EMPTY_TEXT);  // 間隔 以上:存components
		vector<int> connections = findComponentsByType(ERD_Component::Connection);
		for (vector<int>::iterator it = connections.begin(); it < connections.end(); it++)
		{
			string line, tmp;
			int node1, node2;
			node1 = getConnectionNodeById(*it, 0);
			node2 = getConnectionNodeById(*it, 1);
			line = Tool_Function::convertIntToString((int)*it);
			line += SPACE;
			line += Tool_Function::convertIntToString(node1);
			line += CAMMA_TEXT;
			line += Tool_Function::convertIntToString(node2);
			file.writeLine(line);
		}
		file.writeLine(EMPTY_TEXT);  // 間隔 以上:存connection
		vector<int> entities = findComponentsByType(ERD_Component::Entity);
		for (vector<int>::iterator it = entities.begin(); it < entities.end(); it++)
		{
			string line;
			vector<int> primaryKeys = findPrimaryKeyByEntityId(*it);
			if (primaryKeys.size() > 0)
			{
				line = Tool_Function::convertIntToString((int)*it);
				line += SPACE;
				for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
				{
					line +=  Tool_Function::convertIntToString((int)*pit);
					line += CAMMA_TEXT;
				}
				line = line.substr(0,line.size() - 1);
				file.writeLine(line);
			}
		}
		file.closeFile();
		result = MESSAGE_SUCCESS;
	}
	else
	{
		result = MESSAGE_FAIL;
	}
	return result;
}

// 判斷idStr是不是已存在的componentId
bool ER_Model::isExistComponentId(string idStr)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		int id = ((ERD_Component *)*it)->getId();
		if (Tool_Function::convertIntToString(id) == idStr)
		{
			return true;
		}
	}
	return false;
}

// 判斷entityId是不是Entity
string ER_Model::checkEntitySelectedValid(string entityId)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		int currentId = ((ERD_Component *)*it)->getId();
		if (Tool_Function::convertIntToString(currentId) == entityId)
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

// 刪除component
bool ER_Model::deleteComponent(int id)
{
	ERD_Component* delData = findComponentById(id);
	if (delData == NULL)
	{
		return false;
	}
	else
	{
		components.erase(find(components.begin(), components.end(), delData));
		delete delData;
		return true;
	}
}

// 找出與給定ID(targetId)有關的所有Connection的ID
vector<int> ER_Model::findRelatedConnectionById(int targetId) 
{
	vector<int> connectsId = findComponentsByType(ERD_Component::Connection);
	vector<int> resultVector;
	for (vector<int>::iterator it = connectsId.begin(); it < connectsId.end(); it++)
	{
		if (((ERD_Connection *)findComponentById(*it))->isConnectToId(targetId))
		{
			resultVector.push_back(*it);
		}
	}
	return resultVector;
}

// 新增component
void ER_Model::addComponent(ERD_Component* component)
{
	components.push_back(component);
	sortComponents();
}

bool ER_Model::enoughNodesToConnect()
{
	if (findNodes().size() > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}