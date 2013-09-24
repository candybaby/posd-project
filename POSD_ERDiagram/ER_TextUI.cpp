#include "ER_TextUI.h"
#define MENU_TEXT "1. Add a node \n2. Connect two nodes \n3. Display the current diagram \n4. Set a primary key \n5. Display the table \n6. Exit"
#define ERROR_TEXT "You entered an invalid value."
#define RE_ENTER "Please enter a valid one again."
#define ENTER_FIRST_NODE "Please enter the first node ID"
#define ENTER_SECOND_NODE "Please enter the second node ID"
#define BYE_TEXT "Bye Bye!"
#define ADD_NODE_TEXT "What kind of node do you want to add?"
#define ADD_NODE_CHOOSE_TEXT "[A]Attribute [E]Entity [R]Relation"
#define ADD_NODE_NAME_TEXT "Enter the name of this node:"
#define SHIFT_THREE 3
#define SEPARATOR_1 "------------------------------------"
#define SEPARATOR_2 "------+------+----------------------"
#define SEPARATOR_3 "   |  "
#define SEPARATOR_4 "-----------+------+-----------------"
#define SEPARATOR_5 "   |   "
#define SPACE_TEXT_1 "  "
#define SPACE_TEXT_2 "       "
#define NODES_TEXT "Nodes:"
#define COMPONENT_MENU " Type |  ID  |  Name "
#define CONNECTION_TEXT "Connections:"
#define CONNECTION_MENU "Connection | node | node"
#define CONNECT_MESSAGE "has been connected to the node"
#define NODE_NOT_EXIST "The node ID you entered does not exist."
#define ASK_CARDINALITY "ask cardinality"
#define ASK_CARDINALITY_TEXT "Enter the type of the cardinality:\n [0]1 [1]N"
#define COMPONENTS_TEXT "The ER diagram is displayed as follows:\n Components:"
#define FIND_ENTITY "Find Right Entity"
#define NOT_ENTITY "Not an Entity"
#define ID_NOT_EXIST "Id Not Exist"
#define ENTITY_TEXT "Entities:"
#define ID_NOT_EXIST_MESSAGE "The node ID you entered does not exist. "
#define ENTER_ENTITY_ID "Enter the ID of the entity:"
#define IS_NOT_AN_ENTITY "\' is not an entity. "
#define ENTER_ATTRIBUTES_ID "Enter the IDs of the attributes (use a comma to separate two attributes):"
#define SET_DONE_PRIMARY_KEY "Setting Success"
#define THE_NODE "The node \'"
#define APOSTROPHE_TEXT "\'"
#define ATTRIBUTE_TEXT "Attributes of the entity \'"
#define THE_ENTITY "The entity \'"
#define HAS_PRIMARY_KEY "\' has the primary key ("
#define END_TEXT_KEY ")."
#define A_NODE "A node ["
#define NODE_ADDED "] has been added. ID: "
#define NODE_ADDED_NAME ", Name: \""
#define NODE_ADDED_END "\""


using namespace std;

ER_TextUI::ER_TextUI(void)
{
}

ER_TextUI::ER_TextUI(ER_PresentationModel* presentationModel)
{
	this->presentationModel = *presentationModel;
}

ER_TextUI::~ER_TextUI(void)
{
}

void ER_TextUI::displayMenu()
{
	cout << MENU_TEXT << endl;
	processCommand();
}

void ER_TextUI::processCommand()
{
	string menuCommand;
	cin >> menuCommand;
	if (menuCommand == MenuCommandNames[Option_1])
	{
		string addNodeCommand, addNodeName;
		int type = -1, id = 0;
		cout << ADD_NODE_TEXT << endl;
		type = option1Question(addNodeCommand, type);

		while (type == -1)
		{
			cout << ERROR_TEXT << RE_ENTER << endl;
			type = option1Question(addNodeCommand, type);
		}
		cout << ADD_NODE_NAME_TEXT << endl;
		cin >> addNodeName;
		presentationModel.addNode((ComponentType)type, addNodeName);
		id = presentationModel.getCurrentId() - 1;
		printAddNodeResult(type, id, addNodeName);
		printNodes();
	}
	else if (menuCommand == MenuCommandNames[Option_2])
	{
		string connectFirstNode, connectSecondNode;
		cout << ENTER_FIRST_NODE << endl;
		option2Question(connectFirstNode);

		cout << ENTER_SECOND_NODE << endl;
		option2Question(connectSecondNode);

		int firstNodeId, secondNodeId;
		string message, cardinality;
		firstNodeId = stoi(connectFirstNode);
		secondNodeId = stoi(connectSecondNode);
		message = presentationModel.addConnection(firstNodeId, secondNodeId);
		if (message.find(ASK_CARDINALITY) != std::string::npos)
		{
			while (!(message.find(CONNECT_MESSAGE) != std::string::npos))
			{
				cout << ASK_CARDINALITY_TEXT << endl;
				cin >> cardinality;
				if (cardinality == "0")
				{
					message = presentationModel.addConnection(firstNodeId, secondNodeId, one);
				}
				else if (cardinality == "1")
				{
					message = presentationModel.addConnection(firstNodeId, secondNodeId, n);
				}
			}
		}

		cout << message << endl;
		if (message.find(CONNECT_MESSAGE) != std::string::npos)
		{
			printConnections();
		}
	}
	else if (menuCommand == MenuCommandNames[Option_3])
	{
		printComponents();
		cout << endl;
		printConnections();
	}
	else if (menuCommand == MenuCommandNames[Option_4])
	{
		string entityId, messageOfEntity, attributesQuery, messageOfAttributes;
		printEntities();
		cout << ENTER_ENTITY_ID << endl;
		while (messageOfEntity != FIND_ENTITY)
		{
			cin >> entityId;
			messageOfEntity = presentationModel.checkEntitySelectedValid(entityId);
			if (messageOfEntity.find(NOT_ENTITY) != std::string::npos)
			{
				cout << THE_NODE << entityId << IS_NOT_AN_ENTITY << RE_ENTER << endl;
			}
			else if (messageOfEntity.find(ID_NOT_EXIST) != std::string::npos)
			{
				cout << ID_NOT_EXIST_MESSAGE << RE_ENTER << endl;
			}
		}
		int entityIntId = std::stoi(entityId);
		printAttributesById(entityIntId); 
		cout << ENTER_ATTRIBUTES_ID << endl;
		while (messageOfAttributes != SET_DONE_PRIMARY_KEY)
		{
			cin >> attributesQuery;
			messageOfAttributes = presentationModel.checkAttributesSelectedValid(attributesQuery, entityIntId);
			if (messageOfAttributes.find(RE_ENTER) != std::string::npos)
			{
				cout << messageOfAttributes << endl;
			}
		}
		printEntityPrimaryKey(entityIntId);
	}
	else if (menuCommand == MenuCommandNames[Option_5])
	{
		printTables();
	}
	else if (menuCommand == MenuCommandNames[Option_6])
	{
		cout << BYE_TEXT << endl;
		return ;
	}
	else
	{
		cout << ERROR_TEXT << RE_ENTER << endl;
	}
	displayMenu();
}

int ER_TextUI::option1Question(string addNodeCommand, int type)
{
	cout << ADD_NODE_CHOOSE_TEXT << endl;
	cin >> addNodeCommand;
	type = presentationModel.option1Mapping(addNodeCommand);
	return type;
}

void ER_TextUI::printAddNodeResult(int type, int id, string addNodeName)
{
	cout << A_NODE << Option1TypeNames[type + SHIFT_THREE] << NODE_ADDED << id << NODE_ADDED_NAME << addNodeName << NODE_ADDED_END << endl;
}

void ER_TextUI::printNodes()  // without Connection
{
	cout << NODES_TEXT << endl;
	cout << SEPARATOR_1 << endl;
	cout << COMPONENT_MENU << endl;
	cout << SEPARATOR_2 << endl;
	vector<int> nodesId = presentationModel.findNode();
	for (vector<int>::iterator it = nodesId.begin(); it < nodesId.end(); it++)
	{
		cout << SPACE_TEXT_1 << ComponentTypeNames[presentationModel.getType(*it)] << SEPARATOR_5 << presentationModel.getId(*it) << SEPARATOR_5 << presentationModel.getName(*it) << endl;
	}
	cout << SEPARATOR_1 << endl;
}

void ER_TextUI::printConnections()
{
	cout << CONNECTION_TEXT << endl;
	cout << SEPARATOR_1 << endl;
	cout << CONNECTION_MENU << endl;
	cout << SEPARATOR_4 << endl;
	vector<int> connectionsId = presentationModel.findComponentType(Connection);
	for (vector<int>::iterator it = connectionsId.begin(); it < connectionsId.end(); it++) 
	{
		cout << SPACE_TEXT_2 << presentationModel.getId(*it) << SEPARATOR_3 << presentationModel.getConnectionNode1(*it) << SEPARATOR_3 << presentationModel.getConnectionNode2(*it) << endl;
	}
	cout << SEPARATOR_1 << endl;
}

void ER_TextUI::printComponents()
{
	cout << COMPONENTS_TEXT << endl;
	cout << SEPARATOR_1 << endl;
	cout << COMPONENT_MENU << endl;
	cout << SEPARATOR_2 << endl;
	for (int i = 0; i < presentationModel.getCurrentId(); i++)
	{
		cout << SPACE_TEXT_1 << ComponentTypeNames[presentationModel.getType(i)] << SEPARATOR_5 << presentationModel.getId(i) << SEPARATOR_5 << presentationModel.getName(i) << endl;
	}
	cout << SEPARATOR_1 << endl;
}

void ER_TextUI::printEntities()
{
	cout << ENTITY_TEXT << endl;
	cout << SEPARATOR_1 << endl;
	cout << COMPONENT_MENU << endl;
	cout << SEPARATOR_2 << endl;
	vector<int> entitiesId = presentationModel.findComponentType(Entity);
	for (vector<int>::iterator it = entitiesId.begin(); it < entitiesId.end(); it++) 
	{
		cout << SPACE_TEXT_1 << ComponentTypeNames[presentationModel.getType(*it)] << SEPARATOR_5 << presentationModel.getId(*it) << SEPARATOR_5 << presentationModel.getName(*it) << endl;
	}
	cout << SEPARATOR_1 << endl;
}

void ER_TextUI::option2Question(string &connectNode)
{
	cin >> connectNode;
	while (!presentationModel.isConnectCommandValid(connectNode))
	{
		cout << NODE_NOT_EXIST << RE_ENTER << endl;
		cin >> connectNode;
	}
}

void ER_TextUI::printAttributesById(int id)
{
	cout << ATTRIBUTE_TEXT << id << APOSTROPHE_TEXT << endl;
	cout << SEPARATOR_1 << endl;
	cout << COMPONENT_MENU << endl;
	cout << SEPARATOR_2 << endl;
	vector<int> attributesList = findAttributes(id);
	for (vector<int>::iterator it = attributesList.begin(); it < attributesList.end(); it++) 
	{
		cout << SPACE_TEXT_1 << ComponentTypeNames[presentationModel.getType(*it)] << SEPARATOR_5 << presentationModel.getId(*it) << SEPARATOR_5 << presentationModel.getName(*it) << endl;
	}
	cout << SEPARATOR_1 << endl;
}

vector<int> ER_TextUI::findAttributes(int id)
{
	return presentationModel.findTypeIdByComponentId(Attribute, id);
}

void ER_TextUI::printEntityPrimaryKey(int id)
{
	cout << THE_ENTITY << id << HAS_PRIMARY_KEY << presentationModel.getPrimaryKeyString(id) << END_TEXT_KEY << endl;
}

void ER_TextUI::printTables()
{
	cout << presentationModel.getTable() << endl;
}