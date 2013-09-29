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


string ER_Model::getTable()
{
	return EMPTY_TEXT;
}

int ER_Model::getCurrentId()
{
	return currentId;
}

int ER_Model::getId(int index)
{
	return components.at(index)->getId();
}

int ER_Model::getConnectionNode1(int index)
{
	return components.at(index)->getConnections().at(0)->getId();
}
int ER_Model::getConnectionNode2(int index)
{
	return components.at(index)->getConnections().at(1)->getId();
}

string ER_Model::getName(int index)
{
	return components.at(index)->getText();
}

ERD_Component::ComponentType ER_Model::getType(int index)
{
	return components.at(index)->getType();
}

ERD_Component* ER_Model::findComponentById(int id)
{
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getId() == id)
		{
			return components[i];
		}
	}
	return NULL;
}

bool ER_Model::isAlreadyConnect(ERD_Component* node1, ERD_Component* node2)
{
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getType() == ERD_Component::Connection)
		{
			if (components[i]->getConnections().at(0)->getId() == node1->getId() && components[i]->getConnections().at(1)->getId() == node2->getId())
			{
				return true;
			}
			else if (components[i]->getConnections().at(1)->getId() == node1->getId() && components[i]->getConnections().at(0)->getId() == node2->getId())
			{
				return true;
			}
		}
	}
	return false;
}

void ER_Model::setIsPrimaryKey(int id, bool flag)
{
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getId() == id)
		{
			ERD_Attribute* att = (ERD_Attribute*)components[i];
			att->setPrimaryKey(flag);
		}
	}
}

bool ER_Model::getIsPrimaryKey(int id)
{
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getId() == id)
		{
			ERD_Attribute* att = (ERD_Attribute*)components[i];
			return att->getIsPrimaryKey();
		}
	}
	return false;
}


void ER_Model::setIdVector(int i, int targetId, ERD_Component::ComponentType type, vector<int> &idVector)
{
	int id = -1;
	if (getConnectionNode1(components[i]->getId()) == targetId)
	{
		id = getConnectionNode2(components[i]->getId());
	}
	else if (getConnectionNode2(components[i]->getId()) == targetId)
	{
		id = getConnectionNode1(components[i]->getId());
	}
	if (id >= 0 && findComponentById(id)->getType() == type)
	{
		idVector.push_back(id);
	}
}

vector<int> ER_Model::findTypeIdByComponentId(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector;
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getType() == ERD_Component::Connection)
		{
			setIdVector(i, targetId, type, idVector);
		}
	}
	return idVector;
}

vector<int> ER_Model::findTypeIdByComponentIdWithCardinality(ERD_Component::ComponentType type, int targetId)
{
	vector<int> idVector;
	for (int i = 0; i< components.size(); i++)
	{
		if (components[i]->getType() == ERD_Component::Connection)
		{
			ERD_Connection* connection = (ERD_Connection*)components[i];
			if (connection->getCardinality() == ERD_Connection::one)
			{
				setIdVector(i, targetId, type, idVector);
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
