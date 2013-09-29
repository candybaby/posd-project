#include "ER_Model.h"
#define MESSAGE_NODE_1 "The node \'"
#define MESSAGE_NODE_2 "\' has been connected to the node \'"
#define MESSAGE_NODE_3 "\'."
#define MESSAGE_NODE_4 "\' cannot be connected to itself."
#define MESSAGE_NODE_5 "\' has already been connected to component \'"
#define MESSAGE_NODE_6 "\' cannot be connected by the node \'"
#define MESSAGE_NODE_7 "\n"
#define MESSAGE_NODE_8 "Its cardinality of the relationship is \'"
#define ASK_CARDINALITY "ask cardinality"
#define EMPTY_TEXT ""

ER_Model::ER_Model(void)
{
	currentId = 0;
}

ER_Model::~ER_Model(void)
{
	while (components.size() > 0)
	{
		ERD_Component* delData = components.back();
		components.pop_back();
		delete delData;
	}
}

const char* ER_Model::ComponentTypeMapNames[SIZE_OF_ComponentTypeMap] = {"A", "E", "R", "C"};

vector<ERD_Component*> ER_Model::getComponents()
{
	return components;
}

void ER_Model::addNode(ERD_Component::ComponentType type, string nodeName)
{
	ERD_Component* component = factory.createNodeComponent(type, nodeName, currentId);
	components.push_back(component);
	currentId++;
}

void ER_Model::addNode(string type, string nodeName)
{
	for (int i = 0; i < SIZE_OF_ComponentTypeMap; i++)
	{
		if (ComponentTypeMapNames[i] == type)
		{
			ERD_Component* component = factory.createNodeComponent((ERD_Component::ComponentType)i, nodeName, currentId);
			components.push_back(component);
			currentId++;
		}
	}
}

ERD_Component* ER_Model::setAttributeTypeConnected(ERD_Component* component)
{
	ERD_Attribute* attribute = (ERD_Attribute*) component;
	attribute->setConnected(true);
	return attribute;
}

string ER_Model::addConnection(int component1Id, int component2Id)
{
	string message;
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	if (isAlreadyConnect(component1, component2)) //已經相連了
	{
		message += MESSAGE_NODE_1;
		message	+= Tool_Function::intToString(component1Id);
		message	+= MESSAGE_NODE_5;
		message	+= Tool_Function::intToString(component2Id);
		message	+= MESSAGE_NODE_3;
		return message;
	}
	if (component1->canConnectTo(component2) && component2->canConnectTo(component1)) //可以連
	{
		if ((component1->getType() == ERD_Component::Entity && component2->getType() == ERD_Component::Relationship) || (component1->getType() == ERD_Component::Relationship && component2->getType() == ERD_Component::Entity))
		{
			message += ASK_CARDINALITY;
			return message;
		}
		message += MESSAGE_NODE_1;
		message	+= Tool_Function::intToString(component1Id);
		message	+= MESSAGE_NODE_2;
		message	+= Tool_Function::intToString(component2Id);
		message	+= MESSAGE_NODE_3;
		if (component1->getType() == ERD_Component::Attribute)
		{
			component1 = setAttributeTypeConnected(component1);
		}
		if (component2->getType() == ERD_Component::Attribute)
		{
			component2 = setAttributeTypeConnected(component2);
		}
		ERD_Component* component = factory.createConnectionComponent(component1, component2, currentId);
		components.push_back(component);
		currentId++;
		return message;
	}
	else if (component1Id == component2Id)
	{
		message += MESSAGE_NODE_1;
		message	+= Tool_Function::intToString(component1Id);
		message	+= MESSAGE_NODE_4;
	}
	else
	{
		message += MESSAGE_NODE_1;
		message	+= Tool_Function::intToString(component2Id);
		message	+= MESSAGE_NODE_6;
		message	+= Tool_Function::intToString(component1Id);
		message	+= MESSAGE_NODE_3;
	}

	return message;
}

string ER_Model::addConnection(int component1Id, int component2Id, ERD_Connection::ConnectionCardinality cardinality)
{
	string message;
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	message += MESSAGE_NODE_1;
	message	+= Tool_Function::intToString(component1Id);
	message	+= MESSAGE_NODE_2;
	message	+= Tool_Function::intToString(component2Id);
	message	+= MESSAGE_NODE_3;
	message	+= MESSAGE_NODE_7;
	message	+= MESSAGE_NODE_8;
	message += ERD_Connection::ConnectionCardinalityNames[cardinality];
	message	+= MESSAGE_NODE_3;
	ERD_Component* component = factory.createConnectionComponent(component1, component2, currentId, cardinality);
	components.push_back(component);
	currentId++;
	return message;
}

void ER_Model::addConnection(int component1Id, int component2Id, int id)
{
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	ERD_Component* component = factory.createConnectionComponent(component1, component2, id);
	components.push_back(component);
}

void ER_Model::addConnection(int component1Id, int component2Id, int id, string cardinalityStr)
{
	ERD_Component* component1 = findComponentById(component1Id);
	ERD_Component* component2 = findComponentById(component2Id);
	ERD_Component* component;
	for (int i = 0; i < ERD_Connection::SIZE_OF_Cardinality; i++)
	{
		if (ERD_Connection::ConnectionCardinalityNames[i] == cardinalityStr)
		{
			component = factory.createConnectionComponent(component1, component2, id, (ERD_Connection::ConnectionCardinality)i);
		}
	}
	components.push_back(component);
}

string ER_Model::getTable()
{
	return EMPTY_TEXT;
}

int ER_Model::getCurrentId()
{
	return currentId;
}

int ER_Model::getIdByIndex(int index)
{
	return components.at(index)->getId();
}

int ER_Model::getConnectionNode1ById(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return ((ERD_Component *)*it)->getConnections().at(0)->getId();
		}
	}
}
int ER_Model::getConnectionNode2ById(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return ((ERD_Component *)*it)->getConnections().at(1)->getId();
		}
	}
}

string ER_Model::getNameById(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return ((ERD_Component *)*it)->getText();
		}
	}
}

ERD_Component::ComponentType ER_Model::getTypeById(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			return ((ERD_Component *)*it)->getType();
		}
	}
}

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

bool ER_Model::isAlreadyConnect(ERD_Component* node1, ERD_Component* node2)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == ERD_Component::Connection)
		{
			if (((ERD_Component *)*it)->getConnections().at(0)->getId() == node1->getId() && ((ERD_Component *)*it)->getConnections().at(1)->getId() == node2->getId())
			{
				return true;
			}
			else if (((ERD_Component *)*it)->getConnections().at(1)->getId() == node1->getId() && ((ERD_Component *)*it)->getConnections().at(0)->getId() == node2->getId())
			{
				return true;
			}
		}
	}
	return false;
}

void ER_Model::setIsPrimaryKey(int id, bool flag)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			ERD_Attribute* att = (ERD_Attribute*)*it;
			att->setPrimaryKey(flag);
		}
	}
}

bool ER_Model::getIsPrimaryKey(int id)
{
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getId() == id)
		{
			ERD_Attribute* att = (ERD_Attribute*)*it;
			return att->getIsPrimaryKey();
		}
	}
	return false;
}


void ER_Model::setIdVector(int sourceId, int targetId, ERD_Component::ComponentType type, vector<int> &idVector)
{
	int id = -1;
	if (getConnectionNode1ById(sourceId) == targetId)
	{
		id = getConnectionNode2ById(sourceId);
	}
	else if (getConnectionNode2ById(sourceId) == targetId)
	{
		id = getConnectionNode1ById(sourceId);
	}
	if (id >= 0 && findComponentById(id)->getType() == type)
	{
		idVector.push_back(id);
	}
}

vector<int> ER_Model::findComponent()
{
	vector<int> entitiesId;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		entitiesId.push_back(((ERD_Component *)*it)->getId());
	}
	return entitiesId;
}

vector<int> ER_Model::findComponentType(ERD_Component::ComponentType type)
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

vector<int> ER_Model::findTypeIdByComponentId(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == ERD_Component::Connection)
		{
			setIdVector(((ERD_Component *)*it)->getId(), targetId, type, idVector);
		}
	}
	return idVector;
}

vector<int> ER_Model::findTypeIdByComponentIdWithCardinality(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector;
	for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
	{
		if (((ERD_Component *)*it)->getType() == ERD_Component::Connection)
		{
			ERD_Connection* connection = (ERD_Connection*)*it;
			if (connection->getCardinality() == ERD_Connection::one)
			{
				setIdVector(((ERD_Component *)*it)->getId(), targetId, type, idVector);
			}
		}
	}
	return idVector;
}

vector<int> ER_Model::findPrimaryKeyByEntityId(int entityId)
{
	vector<int> primaryKeys;
	vector<int> attributesId = findTypeIdByComponentId(ERD_Component::Attribute, entityId);
	for (vector<int>::iterator it = attributesId.begin(); it < attributesId.end(); it++)
	{
		ERD_Attribute* attribute = (ERD_Attribute*)components[*it];
		if (attribute->getIsPrimaryKey())
		{
			primaryKeys.push_back(*it);
		}
	}

	return primaryKeys;
}

vector<vector<int>> ER_Model::findForeignKeyByEntityId(int entityId)
{
	vector<vector<int>> foreignKeysIdVector;
	vector<int> entitiesId = findOneByOneRelationEntityId(entityId);
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++) // 全抓
	{
		ERD_Entity* entity = (ERD_Entity*) findComponentById(entityId);
		ERD_Entity* targetEntity = (ERD_Entity*) findComponentById(*it);
		if (!entity->isContainForeignEntityId(*it))
		{
			entity->addForeignEntityId(*it);
			targetEntity->addForeignEntityId(entityId);
			vector<int> foreignKeysId;
			foreignKeysId = findPrimaryKeyByEntityId(*it);
			foreignKeysIdVector.push_back(foreignKeysId);
		}
	}
	return foreignKeysIdVector;
}

vector<int> ER_Model::findOneByOneRelationEntityId(int targetId)
{
	vector<int> idVector;
	vector<int> relationIdVector;
	relationIdVector = findTypeIdByComponentIdWithCardinality(ERD_Component::Relationship, targetId);
	for (vector<int>::iterator it = relationIdVector.begin(); it < relationIdVector.end(); it++) 
	{
		vector<int> entityIdVector = findTypeIdByComponentIdWithCardinality(ERD_Component::Entity, *it);
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

string ER_Model::loadComponents(string path)
{
	string result;
	ER_FileManager file;

	if (file.openFile(path, ER_FileManager::Read))
	{
		currentId = 0; // init
		string content;
		vector<string> lines;
		int state = 0;
		map<int, string> connectionMap;
		content = file.readFile();
		lines = Tool_Function::split(content, '\n');
		for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
		{
			if (*it == "")
			{
				state++;
			} 
			else
			{
				if (state == 0)
				{
					vector<string> lineParts = Tool_Function::split(*it, ' ');
					if (lineParts.size() > 1)
					{
						string typeStr = lineParts[0].substr(0, 1);
						string text = lineParts[1];
						if (typeStr != ComponentTypeMapNames[Connection])
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
						connectionMap.insert(pair<int, string> (currentId, ""));
						currentId++;
					}
				}
				else if (state == 1)
				{
					vector<string> lineParts = Tool_Function::split(*it, ' ');
					string connectionIdStr = lineParts[0];
					string nodesIdStr = lineParts[1];
					vector<string> nodes = Tool_Function::split(nodesIdStr, ',');
					int node1, node2, connectionId;
					node1 = std::stoi(nodes[0]);
					node2 = std::stoi(nodes[1]);
					connectionId = std::stoi(connectionIdStr);
					string cardinalityStr = connectionMap.at(connectionId);
					if (cardinalityStr != "")
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
					vector<string> lineParts = Tool_Function::split(*it, ' ');
					string primaryKeyIdStr = lineParts[1];
					vector<string> primaryKeysId = Tool_Function::split(primaryKeyIdStr, ',');
					for (vector<string>::iterator it = primaryKeysId.begin(); it < primaryKeysId.end(); it++)
					{
						int primaryKeyId = std::stoi(*it);
						setIsPrimaryKey(primaryKeyId, true);
					}
				}
			}
		}
		file.closeFile();
		result = "Success";
	}
	else
	{
		result = "Fail";
	}
	return result;
}

string ER_Model::storeComponents(string path)
{
	string result;
	ER_FileManager file;
	if (file.openFile(path, ER_FileManager::Write))
	{
		for (vector<ERD_Component *>::iterator it = components.begin(); it < components.end(); it++)
		{
			string line, tmp;
			line = ComponentTypeMapNames[((ERD_Component *)*it)->getType()];
			tmp = ((ERD_Component *)*it)->getText();
			if (tmp.size() > 0)
			{
				line += ", ";
				line += tmp;
			}
			file.writeLine(line);
		}
		file.writeLine("");  // 間隔 以上:存components

		vector<int> connections = findComponentType(ERD_Component::Connection);
		for (vector<int>::iterator it = connections.begin(); it < connections.end(); it++)
		{
			string line, tmp;
			int node1, node2;
			node1 = getConnectionNode1ById(*it);
			node2 = getConnectionNode2ById(*it);
			line = Tool_Function::intToString((int)*it);
			line += " ";
			line += Tool_Function::intToString(node1);
			line += ",";
			line += Tool_Function::intToString(node2);
			file.writeLine(line);
		}
		file.writeLine("");  // 間隔 以上:存connection

		vector<int> entities = findComponentType(ERD_Component::Entity);
		for (vector<int>::iterator it = entities.begin(); it < entities.end(); it++)
		{
			string line;
			vector<int> primaryKeys = findPrimaryKeyByEntityId(*it);
			if (primaryKeys.size() > 0)
			{
				line = Tool_Function::intToString((int)*it);
				line += " ";
				for (vector<int>::iterator pit = primaryKeys.begin(); pit < primaryKeys.end(); pit++)
				{
					line +=  Tool_Function::intToString((int)*pit);
					line += ",";
				}
				line = line.substr(0,line.size() - 1);
				file.writeLine(line);
			}
		}

		file.closeFile();
		result = "Success";
	}
	else
	{
		result = "Fail";
	}
	return result;
}