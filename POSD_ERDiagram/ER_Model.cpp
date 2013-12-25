#include "ER_Model.h"
#include "ER_SaveComponentVisitor.h"
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
#define ZERO_STRING "0";
#define ONE_STRING "1";
#define POS_FILE_TYPE ".pos";

using namespace std;

ER_Model::ER_Model(void)
{
	currentId = 0;
	hasModify = false;
	isStoreFileFail = false;
	pasteCount = 0;
}

ER_Model::~ER_Model(void)
{
	clearCurrentComponents();
	clearClipboard();
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

// 依據id將components重新sort一遍
void ER_Model::sortComponents()
{
	ComponentSorter componentSorter;
	std::sort(components.begin(), components.end(), componentSorter);
}

const char* ER_Model::componentTypeMapNames[SizeOfComponentTypeMap] = {"A", "E", "R", "C"};

// 取得Components
vector<ERD_Component*> ER_Model::getComponents()
{
	return components;
}

// 新增節點(不包含connection)
int ER_Model::addNode(ERD_Component::ComponentType type, string nodeName)
{
	int id = currentId;
	ERD_Component* component = factory.createNodeComponent(type, nodeName, currentId);
	if (component == NULL)
	{
		return -1;
	}
	else
	{
		components.push_back(component);
		currentId++;
		sortComponents();
		return id;
	}
}

// 新增節點(不包含connection) Type為字串
void ER_Model::addNode(string type, string nodeName)
{
	for (int i = 0; i < SizeOfComponentTypeMap; i++)
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
	if (component != NULL)
	{
		components.push_back(component);
	}
}

// 設定Attribute連線狀態
void ER_Model::setAttributeConnected(int componentId, bool flag)
{
	ERD_Component* component = findComponentById(componentId);
	if (component != NULL && component->getType() == ERD_Component::Attribute)//debug
	{
		ERD_Attribute* attribute = (ERD_Attribute*)component;
		attribute->setConnected(flag);
	}
}

// 檢查連線情況 參數為兩個Node要連接的ID 結果 -1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連
int ER_Model::checkAddConnection(int componentId, int otherComponentId)
{
	int result = ALREADY_CONNECTED;
	ERD_Component* component = findComponentById(componentId);
	ERD_Component* otherComponent = findComponentById(otherComponentId);
	if (isAlreadyConnect(componentId, otherComponentId)) //已經相連了
	{
		result = ALREADY_CONNECTED;
		return result;
	}
	if (component->canConnectTo(otherComponent) && otherComponent->canConnectTo(component)) //可以連
	{
		if ((component->getType() == ERD_Component::Entity && otherComponent->getType() == ERD_Component::Relationship) ||
			(component->getType() == ERD_Component::Relationship && otherComponent->getType() == ERD_Component::Entity))
		{
			result = ASK_CARDINALITY;
		}
		else
		{
			result = currentId;
		}
	}
	else if (componentId == otherComponentId)
	{
		result = SAME_NODE;
	}
	else
	{
		result = CANNOT_CONNECT;
	}
	return result;
}

// id並調整為下一個排序
void ER_Model::plusCurrentId()
{
	currentId++;
}

void ER_Model::minusCurrentId()
{
	currentId--;
}

// 新增連線 特定ID位置的新增 主要用於讀檔時的新增
void ER_Model::addConnection(int componentId, int otherComponentId, int id)
{
	ERD_Component* targetComponent = findComponentById(componentId);
	ERD_Component* otherTargetComponent = findComponentById(otherComponentId);
	ERD_Component* component = factory.createConnectionComponent(targetComponent, otherTargetComponent, id);
	setAttributeConnected(componentId, true);
	setAttributeConnected(otherComponentId, true);
	components.push_back(component);
	sortComponents();
}

// 新增連線 特定ID位置的新增包含cardinality屬性
void ER_Model::addConnection(int componentId, int otherComponentId, int id, ERD_Connection::ConnectionCardinality cardinality)
{
	ERD_Component* targetComponent = findComponentById(componentId);
	ERD_Component* otherTargetComponent = findComponentById(otherComponentId);
	ERD_Component* component = factory.createConnectionComponent(targetComponent, otherTargetComponent, id, cardinality);
	setAttributeConnected(componentId, true);
	setAttributeConnected(otherComponentId, true);
	components.push_back(component);
	sortComponents();
}

// 新增連線 特定ID位置的新增包含cardinality屬性 主要用於讀檔時的新增
void ER_Model::addConnection(int componentId, int otherComponentId, int id, string cardinalityStr)
{
	ERD_Component* targetComponent = findComponentById(componentId);
	ERD_Component* otherTargetComponent = findComponentById(otherComponentId);
	ERD_Component* component;
	for (int i = 0; i < ERD_Connection::SizeOfCardinality; i++)
	{
		if (ERD_Connection::connectionCardinalityNames[i] == cardinalityStr)
		{
			component = factory.createConnectionComponent(targetComponent, otherTargetComponent, id, (ERD_Connection::ConnectionCardinality)i);
		}
		else if (cardinalityStr == EMPTY_TEXT)
		{
			component = factory.createConnectionComponent(targetComponent, otherTargetComponent, id);
		}
	}
	setAttributeConnected(componentId, true);
	setAttributeConnected(otherComponentId, true);
	components.push_back(component);
	sortComponents();
}

// 設定目前id
void ER_Model::setCurrentId(int id)
{
	currentId = id;
}

// 回傳目前的ID
int ER_Model::getCurrentId()
{
	return currentId;
}

// 用index找到對應的ID
int ER_Model::getIdByIndex(int index)
{
	if (index >= components.size() || index < 0)
	{
		return -1;
	}
	else
	{
		return components.at(index)->getId();
	}
}

// 取得連線的兩個node 以nodeNumber來分node0與node1
int ER_Model::getConnectionNodeById(int id, int nodeNumber)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id && ((ERD_Component *)*it)->getType() == ERD_Component::Connection)
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
		return ERD_Component::SizeOfComponentType; // exception
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
bool ER_Model::isAlreadyConnect(int nodeId, int otherNodeId)
{
	if (nodeId == otherNodeId)
	{
		return false;
	}
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == ERD_Component::Connection)
		{
			ERD_Connection* connection = (ERD_Connection*)*it;
			if (connection->isConnectToId(nodeId) && connection->isConnectToId(otherNodeId))
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

// 嚐試讀檔
string ER_Model::readComponentsFile(string path)
{
	ER_FileManager file;
	if (file.openFile(path, ER_FileManager::Read))
	{
		loadFileContent(file);
		notifyLoadFile();
		return MESSAGE_SUCCESS;
	}
	else
	{
		return MESSAGE_FAIL;
	}
}

// 讀取檔案內容
void ER_Model::loadFileContent(ER_FileManager &file)
{
	currentId = 0; // init
	clearCurrentComponents();
	vector<string> lines;
	int state = 0;
	map<int, string> connectionMap;
	string content = file.readFile();
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
				loadComponents(it, connectionMap);
			}
			else if (state == 1)
			{
				loadConnections(it, connectionMap);
			}
			else
			{
				loadPrinaryKey(it);
			}
		}
	}
	file.closeFile();
}

// 讀檔第1部分Components
void ER_Model::loadComponents(vector<string>::iterator lineIt, map<int, string> &connectionMap)
{
	vector<string> lineParts = Tool_Function::split(*lineIt, CHAR_SPACE);
	if (lineParts.size() > 1)
	{
		string typeString = lineParts[0].substr(0, 1);
		string text = lineParts[1];
		if (typeString != componentTypeMapNames[Connection])
		{
			addNode(typeString, text);
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

// 讀檔第2部分Connections
void ER_Model::loadConnections(vector<string>::iterator lineIt, map<int, string> &connectionMap)
{
	vector<string> lineParts = Tool_Function::split(*lineIt, CHAR_SPACE);
	string connectionIdString = lineParts[0];
	string nodesIdString = lineParts[1];
	vector<string> nodes = Tool_Function::split(nodesIdString, CHAR_CAMMA);
	int node, otherNode, connectionId;
	node = std::stoi(nodes[0]);
	otherNode = std::stoi(nodes[1]);
	connectionId = std::stoi(connectionIdString);
	string cardinalityString = connectionMap.at(connectionId);
	if (cardinalityString != EMPTY_TEXT)
	{
		addConnection(node, otherNode, connectionId, cardinalityString);
	}
	else
	{
		addConnection(node, otherNode, connectionId);
	}
}

// 讀檔第3部分PrimaryKey
void ER_Model::loadPrinaryKey(vector<string>::iterator lineIt)
{
	vector<string> lineParts = Tool_Function::split(*lineIt, CHAR_SPACE);
	string primaryKeyIdString = lineParts[1];
	vector<string> primaryKeysId = Tool_Function::split(primaryKeyIdString, CHAR_CAMMA);
	for (vector<string>::iterator it = primaryKeysId.begin(); it < primaryKeysId.end(); it++)
	{
		int primaryKeyId = std::stoi(*it);
		setIsPrimaryKey(primaryKeyId, true);
	}
}

// 存檔
string ER_Model::storeComponents(string path)
{
	string result, posPath = path.substr(0,path.size() - 4);
	ER_FileManager file, posFile;
	posPath += POS_FILE_TYPE;
	if (file.openFile(path, ER_FileManager::Write)&&posFile.openFile(posPath, ER_FileManager::Write)&&!isStoreFileFail)
	{
		string componentsInfo, connectionsInfo, positionInfo;
		ER_SaveComponentVisitor* saveVisitor = new ER_SaveComponentVisitor;
		for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
		{
			(*it)->accept(saveVisitor);
			componentsInfo.append(saveVisitor->getComponentInfo());
			connectionsInfo.append(saveVisitor->getConnectionInfo());
			positionInfo.append(saveVisitor->getPositionInfo());
		}

		file.writeLine(componentsInfo);
		file.writeLine(connectionsInfo);
		storeFileAboutPrimaryKey(file);
		file.closeFile();

		posFile.writeLine(positionInfo);
		posFile.closeFile();

		result = MESSAGE_SUCCESS;
		hasModify = false;
	}
	else
	{
		result = MESSAGE_FAIL;
	}
	return result;
}

// 存檔第1部分 Components
//void ER_Model::storeFileAboutComponents(ER_FileManager &file)
//{
//	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
//	{
//		string line, tmp;
//		line = componentTypeMapNames[((ERD_Component *)*it)->getType()];
//		tmp = ((ERD_Component *)*it)->getText();
//		if (tmp.size() > 0)
//		{
//			line += CAMMA;
//			line += tmp;
//		}
//		file.writeLine(line);
//	}
//}

// 存檔第2部分 Connections
//void ER_Model::storeFileAboutConnections(ER_FileManager &file)
//{
//	vector<int> connections = findComponentsByType(ERD_Component::Connection);
//	for (vector<int>::iterator it = connections.begin(); it < connections.end(); it++)
//	{
//		string line, tmp;
//		int node, otherNode;
//		node = getConnectionNodeById(*it, 0);
//		otherNode = getConnectionNodeById(*it, 1);
//		line = Tool_Function::convertIntToString((int)*it);
//		line += SPACE;
//		line += Tool_Function::convertIntToString(node);
//		line += CAMMA_TEXT;
//		line += Tool_Function::convertIntToString(otherNode);
//		file.writeLine(line);
//	}
//}

// 存檔第3部分 PrimaryKey
void ER_Model::storeFileAboutPrimaryKey(ER_FileManager &file)
{
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
}

// 判斷idStr是不是已存在的componentId
bool ER_Model::isExistComponentId(string idString)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		int id = ((ERD_Component *)*it)->getId();
		if (Tool_Function::convertIntToString(id) == idString)
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
		if (delData->getType() == ERD_Component::Connection)
		{
			ERD_Connection* delConnection = (ERD_Connection*) delData;
			setAttributeConnected(delConnection->getNodeId(), false);
			setAttributeConnected(delConnection->getOtherNodeId(), false);
		}
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

// 是否有足夠的node可以連接
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

// 設定有沒有Modify
void ER_Model::setHasModify(bool flag)
{
	hasModify = flag;
}

// 取得有沒有Modify
bool ER_Model::getHasModify()
{
	return hasModify;
}

// 回傳GUI要用到的Node資訊
string ER_Model::getGuiNodes()
{
	string result;
	vector<int> nodesVector = findNodes();
	for (vector<int>::iterator it = nodesVector.begin(); it < nodesVector.end(); it++)
	{
		result += getNodeInfo(*it);
	}
	return result;
}

// 回傳GUI要用到的Connection資訊
string ER_Model::getGuiConnections()
{
	string result;
	vector<int> connectionsVector = findComponentsByType(ERD_Component::Connection);
	for (vector<int>::iterator it = connectionsVector.begin(); it < connectionsVector.end(); it++)
	{
		result += getConnectionInfo(*it);
	}
	return result;
}

// 設定特定component的text
void ER_Model::setComponentText(int id, string text)
{
	ERD_Component* component = findComponentById(id);
	component->setText(text);
}

// 設定指定component postition
void ER_Model::setComponentPosition(int id, int posX, int posY)
{
	ERD_Component* component = findComponentById(id);
	component->setPos(posX, posY);
}

// 取得指定Node的資訊
string ER_Model::getNodeInfo(int id)
{
	ERD_Component* component = findComponentById(id);
	string result;
	int posX = component->getPosX();
	int posY = component->getPosY();
	string name = component->getText();
	string type = componentTypeMapNames[component->getType()];
	result += Tool_Function::convertIntToString(id) + CAMMA_TEXT + name + CAMMA_TEXT + type + CAMMA_TEXT;
	result += Tool_Function::convertIntToString(posX) + CAMMA_TEXT + Tool_Function::convertIntToString(posY);
	if (type == componentTypeMapNames[ERD_Component::Attribute])
	{
		ERD_Attribute* attribute = (ERD_Attribute*)component;
		string primaryString = ZERO_STRING;
		if (attribute->getIsPrimaryKey())
		{
			primaryString = ONE_STRING;
		}
		result += CAMMA_TEXT + primaryString + CHAR_ENDL;
	}
	else
	{
		result += CHAR_ENDL;
	}
	return result;
}

// 取得指定connection的資訊
string ER_Model::getConnectionInfo(int id)
{
	string result;

	ERD_Component* component = findComponentById(id);
	string name = component->getText();
	string type = componentTypeMapNames[component->getType()];
	int node = component->getConnections().at(0)->getId();
	int otherNode = component->getConnections().at(1)->getId();
	result += Tool_Function::convertIntToString(id) + CAMMA_TEXT + name + CAMMA_TEXT + type;
	result += CAMMA_TEXT + Tool_Function::convertIntToString(node) + CAMMA_TEXT;
	result += Tool_Function::convertIntToString(otherNode) + CHAR_ENDL;
	
	return result;
}

void ER_Model::setClipboard(vector<int> ids)
{
	clearClipboard();
	for (vector<int>::iterator it = ids.begin(); it < ids.end(); it++)
	{
		ERD_Component* component = findComponentById(*it);
		clipboard.push_back(component->clone());
	}

	if (ids.size() > 0)
	{
		notifyCanPasteState(true);
	}
	// debug start
	/*int cSize = clipboard.size();
	string message = "(model)clipboard size:" + Tool_Function::convertIntToString(cSize);
	for (vector<ERD_Component*>::iterator it = clipboard.begin(); it < clipboard.end(); it++)
	{
		int id = (*it)->getId();
		message += " id : ";
		message += Tool_Function::convertIntToString(id);
	}
	notifyDebugMessage(message);*/
	// debug end
}

vector<ERD_Component *> ER_Model::getClipboard()
{
	return clipboard;
}

void ER_Model::clearClipboard()
{
	while (clipboard.size() > 0)
	{
		ERD_Component* delData = clipboard.back();
		clipboard.pop_back();
		delete delData;
	}
	notifyCanPasteState(false);
	pasteCount = 0;
}

int ER_Model::getPasteCount()
{
	return pasteCount;
}

void ER_Model::addPasteCount()
{
	pasteCount++;
}

void ER_Model::minusPasteCount()
{
	pasteCount--;
}

void ER_Model::deDugFunction()
{
	string message;
	message.append("CurrentId:");
	message.append(Tool_Function::convertIntToString(currentId));

	notifyDebugMessage(message);
}