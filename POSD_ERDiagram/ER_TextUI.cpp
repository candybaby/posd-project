#include "ER_TextUI.h"
#define MENU_TEXT "1. Load ER diagram file \n2. Save ER diagram file \n3. Add a node \n4. Connect two nodes \n5. Display the current diagram \n6. Set a primary key \n7. Display the table \n8. Delete a component \n9. Undo \n10.Redo \n11.Exit"
#define ERROR_TEXT "You entered an invalid value."
#define RE_ENTER "Please enter a valid one again."
#define ENTER_FIRST_NODE "Please enter the first node ID"
#define ENTER_SECOND_NODE "Please enter the second node ID"
#define BYE_TEXT "Bye Bye!"
#define ADD_NODE_TEXT "What kind of node do you want to add?"
#define ADD_NODE_CHOOSE_TEXT "[A]Attribute [E]Entity [R]Relation"
#define ADD_NODE_NAME_TEXT "Enter the name of this node:"
#define SHIFT_THREE 3
#define CONNECT_MESSAGE "has been connected to the node"
#define NODE_NOT_EXIST "The node ID you entered does not exist."
#define ASK_CARDINALITY "ask cardinality"
#define ASK_CARDINALITY_TEXT "Enter the type of the cardinality:\n [0]1 [1]N"
#define FIND_ENTITY "Find Right Entity"
#define NOT_ENTITY "Not an Entity"
#define ID_NOT_EXIST "Id Not Exist"
#define ID_NOT_EXIST_MESSAGE "The node ID you entered does not exist. "
#define ENTER_ENTITY_ID "Enter the ID of the entity:"
#define IS_NOT_AN_ENTITY "\' is not an entity. "
#define ENTER_ATTRIBUTES_ID "Enter the IDs of the attributes (use a comma to separate two attributes):"
#define SET_DONE_PRIMARY_KEY "Setting Success"
#define THE_NODE "The node \'"
#define APOSTROPHE_TEXT "\'"
#define THE_ENTITY "The entity \'"
#define HAS_PRIMARY_KEY "\' has the primary key ("
#define END_TEXT_KEY ")."
#define A_NODE "A node ["
#define NODE_ADDED "] has been added. ID: "
#define NODE_ADDED_NAME ", Name: \""
#define NODE_ADDED_END "\""
#define CARDINALITY_OPTION_ONE "0"
#define CARDINALITY_OPTION_N "1"
#define INPUT_FILE_PATH "Please input a file path: "
#define INPUT_FILE_NAME "Please input the file name: "
#define NOT_ENOUGH_NODES "Not Enough Nodes To Connect!\n"
#define ENTER_COMPONENT_ID "Please enter the component ID"
#define COMPONENT_NOT_EXIST "The component ID you entered does not exist. "
#define ASK_SAVE_FILE "Save ER diagram file? (Y/N)"
#define ANSWER_YES "Y"
#define ANSWER_NO "N"

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

const char* ER_TextUI::menuCommandNames[SIZE_OF_MenuCommand] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" };

void ER_TextUI::displayMenu()
{
	cout << MENU_TEXT << endl;
	processCommand();
}

void ER_TextUI::processCommand()
{
	string menuCommand;
	cin >> menuCommand;
	if (menuCommand == menuCommandNames[Option_1])  // Load ER diagram file
	{
		loadFile();
	}
	else if (menuCommand == menuCommandNames[Option_2])  // Save ER diagram file
	{
		saveFile();
	}
	else if (menuCommand == menuCommandNames[Option_3])  // Add a node
	{
		addNode();
	}
	else if (menuCommand == menuCommandNames[Option_4])  // Connect two nodes
	{
		tryConnectNodes();
	}
	else if (menuCommand == menuCommandNames[Option_5])  // Display the current diagram
	{
		displayCurrentDiagram();
	}
	else if (menuCommand == menuCommandNames[Option_6])  // Set a primary key
	{
		setPrimaryKey();
	}
	else if (menuCommand == menuCommandNames[Option_7])  // Display the table
	{
		cout << presentationModel.getTable() << endl;
	}
	else if (menuCommand == menuCommandNames[Option_8])  // Delete a component
	{
		deleteComponent();
	}
	else if (menuCommand == menuCommandNames[Option_9])  // Undo
	{
		cout << presentationModel.undo() << endl;
	}
	else if (menuCommand == menuCommandNames[Option_10])  // Redo
	{
		cout << presentationModel.redo() << endl;
	}
	else if (menuCommand == menuCommandNames[Option_11])  // Exit
	{
		exitApplication();
		return;
	}
	else
	{
		cout << ERROR_TEXT << RE_ENTER << endl;
	}
	displayMenu();
}

// 讀檔
void ER_TextUI::loadFile()
{
	cout << INPUT_FILE_PATH;
	string filePath;
	cin >> filePath;
	cout << presentationModel.readComponentsFile(filePath) << endl;
}

// 存檔
void ER_TextUI::saveFile()
{
	cout << INPUT_FILE_NAME;
	string filePath;
	cin >> filePath;
	cout << presentationModel.storeComponents(filePath) << endl;
}

// 新增Node
void ER_TextUI::addNode()
{
	string addNodeCommand, addNodeName, idString;
	int type = -1;
	cout << ADD_NODE_TEXT << endl;
	type = addNodeChooseTypeQuestion(addNodeCommand, type);

	while (type == -1)
	{
		cout << ERROR_TEXT << RE_ENTER << endl;
		type = addNodeChooseTypeQuestion(addNodeCommand, type);
	}
	cout << ADD_NODE_NAME_TEXT << endl;
	cin.ignore();
	getline(cin, addNodeName);
	idString = presentationModel.addNode((ERD_Component::ComponentType)type, addNodeName);
	printAddNodeResult(type, idString, addNodeName);
	cout << presentationModel.getNodesTable();
}

// 嘗試連線
void ER_TextUI::tryConnectNodes()
{
	if (presentationModel.enoughNodesToConnect())
	{
		connectTwoNodes();
	}
	else
	{
		cout << NOT_ENOUGH_NODES << endl;
	}
}

// 連接兩個Nodes
void ER_TextUI::connectTwoNodes()
{
	string connectFirstNode, connectSecondNode;
	cout << ENTER_FIRST_NODE << endl;
	checkNodeExist(connectFirstNode);

	cout << ENTER_SECOND_NODE << endl;
	checkNodeExist(connectSecondNode);

	int firstNodeId, secondNodeId;
	firstNodeId = stoi(connectFirstNode);
	secondNodeId = stoi(connectSecondNode);

	addConnection(firstNodeId, secondNodeId);
}

// 增加連線
void ER_TextUI::addConnection(int firstNodeId, int secondNodeId)
{
	string message, cardinality;
	message = presentationModel.checkAddConnection(firstNodeId, secondNodeId);
	if (message.find(ASK_CARDINALITY) != std::string::npos)
	{
		while (!(message.find(CONNECT_MESSAGE) != std::string::npos))
		{
			cout << ASK_CARDINALITY_TEXT << endl;
			cin >> cardinality;
			if (cardinality == CARDINALITY_OPTION_ONE)
			{
				message = presentationModel.addConnection(firstNodeId, secondNodeId, ERD_Connection::one);
			}
			else if (cardinality == CARDINALITY_OPTION_N)
			{
				message = presentationModel.addConnection(firstNodeId, secondNodeId, ERD_Connection::n);
			}
		}
	}

	cout << message << endl;
	if (message.find(CONNECT_MESSAGE) != std::string::npos)
	{
		cout << presentationModel.getConnectionsTable();
	}
}

// 展示現在的Diagram
void ER_TextUI::displayCurrentDiagram()
{
	cout << presentationModel.getComponentsTable();
	cout << endl;
	cout << presentationModel.getConnectionsTable();
}

// 設定PrimaryKey
void ER_TextUI::setPrimaryKey()
{
	string entityId, messageOfEntity;
	cout << presentationModel.getEntitiesTable();
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
	cout << presentationModel.getAttributesTableById(entityIntId);
	cout << ENTER_ATTRIBUTES_ID << endl;
	checkPrimaryKeySetting(entityIntId);
	printEntityPrimaryKey(entityIntId);
}

// 檢查PrimaryKey的設定
void ER_TextUI::checkPrimaryKeySetting(int entityIntId)
{
	string messageOfAttributes, attributesQuery;
	while (messageOfAttributes != SET_DONE_PRIMARY_KEY)
	{
		cin >> attributesQuery;
		messageOfAttributes = presentationModel.checkAttributesSelectedValid(attributesQuery, entityIntId);
		if (messageOfAttributes.find(RE_ENTER) != std::string::npos)
		{
			cout << messageOfAttributes << endl;
		}
	}
}

//  刪除元件
void ER_TextUI::deleteComponent()
{
	cout << ENTER_COMPONENT_ID << endl;
	string deleteIdString;
	cin >> deleteIdString;
	while (!presentationModel.isExistComponentId(deleteIdString))
	{
		cout << COMPONENT_NOT_EXIST << RE_ENTER << endl;
		cin >> deleteIdString;
	}
	cout << presentationModel.deleteComponent(stoi(deleteIdString)) << endl;
}

// 新增Node的問題
int ER_TextUI::addNodeChooseTypeQuestion(string addNodeCommand, int type)
{
	cout << ADD_NODE_CHOOSE_TEXT << endl;
	cin >> addNodeCommand;
	type = presentationModel.addNodeOptionMapping(addNodeCommand);
	return type;
}

// 印出AddNode結果
void ER_TextUI::printAddNodeResult(int type, string id, string addNodeName)
{
	cout << A_NODE << ER_PresentationModel::entityOptionTypeNames[type + SHIFT_THREE] << NODE_ADDED << id << NODE_ADDED_NAME << addNodeName << NODE_ADDED_END << endl;
}

void ER_TextUI::checkNodeExist(string &connectNode)
{
	cin >> connectNode;
	while (!presentationModel.isExistComponentId(connectNode))
	{
		cout << NODE_NOT_EXIST << RE_ENTER << endl;
		cin >> connectNode;
	}
}

// 印出指定Entity的PrimaryKey
void ER_TextUI::printEntityPrimaryKey(int id)
{
	cout << THE_ENTITY << id << HAS_PRIMARY_KEY << presentationModel.getPrimaryKeyString(id) << END_TEXT_KEY << endl;
}

// 離開程式
void ER_TextUI::exitApplication()
{
	if (presentationModel.getHasModify())
	{
		string answer;
		while (!(answer == ANSWER_YES || answer == ANSWER_NO))
		{
			cout << ASK_SAVE_FILE << endl;
			cin >> answer;
			if (answer == ANSWER_YES)
			{
				saveFile();
			}
		}
	}
	cout << BYE_TEXT << endl;
}