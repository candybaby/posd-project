#include "ER_Model.h"
#include "gtest/gtest.h"

using namespace std;
class ER_ModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
	}

	virtual void TearDown()
	{
		delete model;
	}

	void testDataInit()
	{
		model->addNode(ERD_Component::Entity, "Engineer");  //id=0
		model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		model->addNode(ERD_Component::Attribute, "Name");   //id=2
		model->addNode(ERD_Component::Relationship, "Has");   //id=3
		model->addNode(ERD_Component::Entity, "PC");  //id=4
	}

	void testDataInitWithConnection()
	{
		model->addNode(ERD_Component::Entity, "Engineer");  //id=0
		model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		model->addNode(ERD_Component::Attribute, "Name");   //id=2
		model->addNode(ERD_Component::Attribute, "Department");   //id=3
		model->addNode(ERD_Component::Relationship, "Has");   //id=4
		model->addNode(ERD_Component::Entity, "PC");  //id=5
		model->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
		model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
		model->addConnection(0, 4, 8, ERD_Connection::one);
		model->addConnection(4, 5, 9, ERD_Connection::one);
		model->addConnection(0, 1, 10, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(0, 2, 11, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(0, 3, 12, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(5, 6, 13, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(5, 7, 14, ERD_Connection::SIZE_OF_Cardinality);
		model->setIsPrimaryKey(1, true);
		model->setIsPrimaryKey(2, true);
		model->setIsPrimaryKey(6, true);
	}

	ER_Model* model;
};



// 測試清除目前model內的components
TEST_F(ER_ModelTest, clearCurrentComponents) 
{
	// 在沒有component的時後清除
	EXPECT_EQ(0, model->getComponents().size());  // 確認components為空的
	model->clearCurrentComponents();              // 清除(測試函式)
	EXPECT_EQ(0, model->getComponents().size());  // 結果為空的
	// 新增一些components在清除
	ERD_Component* testComponent = new ERD_Component;
	model->addComponent(testComponent);           // 加入1個component
	EXPECT_EQ(1, model->getComponents().size());  // 結果為空的
	model->clearCurrentComponents();              // 清除(測試函式)
	EXPECT_EQ(0, model->getComponents().size());  // 結果為空的
}

// 測試依據id排序排序components
TEST_F(ER_ModelTest, sortComponents) 
{
	// 建立id沒有順序的資料在作排序測式
	model->addNode(ERD_Component::Entity, "ID2", 2);
	model->addNode(ERD_Component::Attribute, "ID1", 1);
	model->addNode(ERD_Component::Entity, "ID0", 0);
	EXPECT_EQ(0, model->getIdByIndex(2));        // 加入順序2 Id為0
	EXPECT_EQ(2, model->getIdByIndex(0));        // 加入順序0 Id為2
	model->sortComponents();
	for (unsigned i = 0;i < model->getComponents().size(); i++)
	{
		EXPECT_EQ(i, model->getIdByIndex(i));        // 加入順序i Id為i
	}
}

// 測試新增節點(不包含connection)
TEST_F(ER_ModelTest, addNode) 
{
	// 測試
	// 參數:ComponentType(type), string(name)
	// 回傳:int (id)
	// 附註:id為目前model依序新增的id(遞增)
	int addNodeId;
	EXPECT_EQ(0, model->getComponents().size());         // 初始為0

	addNodeId = model->addNode(ERD_Component::Entity, "E:ID_0");
	EXPECT_EQ(0, addNodeId);                             //Id = 0;
	EXPECT_EQ(1, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Attribute, "A:ID_1");
	EXPECT_EQ(1, addNodeId);                             //Id = 1;
	EXPECT_EQ(2, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Relationship, "R:ID_2");
	EXPECT_EQ(2, addNodeId);                             //Id = 2;
	EXPECT_EQ(3, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Connection, "C:ID_3"); //addNode不能新增Connection 回傳-1
	EXPECT_EQ(-1, addNodeId);                             //不能新增回傳-1
	EXPECT_EQ(3, model->getComponents().size());          //數量沒變

	TearDown();
	// 測試
	// 參數:string(type), string(name)
	// 回傳:無
	// 附註:id為目前model依序新增的id(遞增)
	SetUp();
	model->addNode("E", "E:ID_0");
	EXPECT_EQ(1, model->getComponents().size());

	model->addNode("A", "E:ID_1");
	EXPECT_EQ(2, model->getComponents().size());

	model->addNode("R", "E:ID_2");
	EXPECT_EQ(3, model->getComponents().size());

	model->addNode("C", "C:ID_3");                //addNode不能新增Connection
	EXPECT_EQ(3, model->getComponents().size());  //數量沒變

	TearDown();
	// 測試
	// 參數:ComponentType(type), string(name), int(id)
	// 回傳:無
	// 附註:特定ID位置的新增
	SetUp();
	model->addNode(ERD_Component::Entity, "E:ID_2", 2);
	EXPECT_EQ(1, model->getComponents().size());
	EXPECT_EQ("E:ID_2", model->getNameById(2));

	model->addNode(ERD_Component::Connection, "E:ID_3", 3);//addNode不能新增Connection
	EXPECT_EQ(1, model->getComponents().size());           //數量沒變

	model->addNode(ERD_Component::Attribute, "A:ID_0", 0);
	EXPECT_EQ(2, model->getComponents().size());
	EXPECT_EQ("A:ID_0", model->getNameById(0));

	model->addNode(ERD_Component::Relationship, "R:ID_1", 1);
	EXPECT_EQ(3, model->getComponents().size());
	EXPECT_EQ("R:ID_1", model->getNameById(1));
}

// 測試 設定Attribute連線狀態
TEST_F(ER_ModelTest, setAttributeConnected)
{
	// 測試
	// 參數:ERD_Component*(component)
	// 回傳:ERD_Component*
	// 附註:無
	model->addNode(ERD_Component::Attribute, "A:ID_0", 0);
	ERD_Component* component = model->findComponentById(0);
	ERD_Attribute* attribute = (ERD_Attribute*) component;
	EXPECT_EQ(false, attribute->getIsConnected());
	model->setAttributeConnected(0, true);
	EXPECT_EQ(true, attribute->getIsConnected());

	model->addNode(ERD_Component::Entity, "E:ID_1", 1);
	model->setAttributeConnected(1, true);                 //不是connection不做事
	EXPECT_EQ(2, model->getComponents().size());
}

// 測試 檢查連線情況 參數為兩個Node要連接的ID 結果 -1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連
TEST_F(ER_ModelTest, checkAddConnection)
{
	// 測試
	// 參數:int(component1Id), int(component2Id)
	// 回傳:int(-1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連 >=0:連線的id)
	// 附註:
	testDataInit();

	int result;
	result = model->checkAddConnection(0, 1);
	EXPECT_EQ(5, result);                      //可以連回傳連線的id
	model->addConnection(0, 1, result);

	result = model->checkAddConnection(0, 1);
	EXPECT_EQ(-1, result);                     //-1:已經相連

	result = model->checkAddConnection(0, 3);
	EXPECT_EQ(-2, result);                     //-2:Cardinality

	result = model->checkAddConnection(3, 4);
	EXPECT_EQ(-2, result);                     //-2:Cardinality

	result = model->checkAddConnection(0, 0);
	EXPECT_EQ(-3, result);                     //-3:兩點相同

	result = model->checkAddConnection(1, 2);  //同為Attrubute
	EXPECT_EQ(-4, result);                     //-4:不能連

	result = model->checkAddConnection(1, 3);  //Attribute與Relationship
	EXPECT_EQ(-4, result);                     //-4:不能連

	result = model->checkAddConnection(0, 4);  //同為Entity
	EXPECT_EQ(-4, result);                     //-4:不能連
}

// 測試 id並調整為下一個排序
TEST_F(ER_ModelTest, plusCurrentId)
{
	// 測試
	// 參數:無
	// 回傳:int(id)
	// 附註:新增連線時用到
	EXPECT_EQ(0, model->getCurrentId());
	model->plusCurrentId();
	EXPECT_EQ(1, model->getCurrentId());
	model->plusCurrentId();
	EXPECT_EQ(2, model->getCurrentId());
}

// 測試 新增連線
TEST_F(ER_ModelTest, addConnection) 
{
	// 測試
	// 參數:int(component1Id), int(component2Id), int(id)
	// 回傳:無
	// 附註:特定ID位置的新增 主要用於讀檔時的新增
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 1, 5);
	EXPECT_EQ(6, model->getComponents().size());

	TearDown();
	// 測試
	// 參數:int(component1Id), int(component2Id), int(id), ConnectionCardinality(cardinality)
	// 回傳:無
	// 附註:特定ID位置的新增包含cardinality屬性
	SetUp();
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 3, 5, ERD_Connection::one);
	EXPECT_EQ(6, model->getComponents().size());
	model->addConnection(4, 3, 6, ERD_Connection::n);
	EXPECT_EQ(7, model->getComponents().size());
	model->addConnection(0, 1, 7, ERD_Connection::SIZE_OF_Cardinality);
	EXPECT_EQ(8, model->getComponents().size());

	TearDown();
	// 測試
	// 參數:int(component1Id), int(component2Id), int(id), string(cardinalityStr)
	// 回傳:無
	// 附註:特定ID位置的新增包含cardinality屬性 主要用於讀檔時的新增
	SetUp();
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 3, 5, "1");
	EXPECT_EQ(6, model->getComponents().size());
	model->addConnection(4, 3, 6, "N");
	EXPECT_EQ(7, model->getComponents().size());
	model->addConnection(0, 1, 7, "");
	EXPECT_EQ(8, model->getComponents().size());

}

// 測試 用index找到對應的ID
TEST_F(ER_ModelTest, getIdByIndex) 
{
	// 測試
	// 參數:int(index)
	// 回傳:int(id)
	// 附註:無
    testDataInit();
	int result;
	result = model->getIdByIndex(0);
	EXPECT_EQ(0, result);
	result = model->getIdByIndex(4);
	EXPECT_EQ(4, result);
}

// 測試 取得連線的兩個node 以nodeNumber來分node0與node1
TEST_F(ER_ModelTest, getConnectionNodeById)
{
	// 測試
	// 參數:int(id), int(nodeNumber)
	// 回傳:int(id)
	// 附註:回傳值為-1的狀況為例外狀況例:無連線
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料

	int result;
	result = model->getConnectionNodeById(5, 0);  //拿第一個Id
	EXPECT_EQ(0, result);
	result = model->getConnectionNodeById(5, 1);  //拿第二個Id
	EXPECT_EQ(3, result);

	//例外
	result = model->getConnectionNodeById(4, 0);  //不是connection
	EXPECT_EQ(-1, result);
}

// 測試 取得名稱藉由ID
TEST_F(ER_ModelTest, getNameById)
{
	// 測試
	// 參數:int(id)
	// 回傳:string(name)
	// 附註:回傳空字串為該id的text為空或沒有指定id的component存在
	testDataInit();
	string result;
	result = model->getNameById(0);
	EXPECT_EQ("Engineer", result);

	result = model->getNameById(4);
	EXPECT_EQ("PC", result);
	
	result = model->getNameById(5); // id不存在
	EXPECT_EQ("", result);
}

// 測試 取得型態藉由ID
TEST_F(ER_ModelTest, getTypeById)
{
	// 測試
	// 參數:int(id)
	// 回傳:ComponentType(type)
	// 附註:回傳值等於SIZE_OF_ComponentType為沒有指定id的component存在
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料

	ERD_Component::ComponentType result;
	result = model->getTypeById(0);
	EXPECT_EQ(ERD_Component::Entity, result);

	result = model->getTypeById(1);
	EXPECT_EQ(ERD_Component::Attribute, result);

	result = model->getTypeById(3);
	EXPECT_EQ(ERD_Component::Relationship, result);

	result = model->getTypeById(5);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = model->getTypeById(6); // id不存在
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);
}

// 測試 取得ERD_Component藉由ID
TEST_F(ER_ModelTest, findComponentById) 
{
	// 測試
	// 參數:int(id)
	// 回傳:ERD_Component*(component)
	// 附註:找不到為NULL
	testDataInit();

	ERD_Component* result;
	result = model->findComponentById(0);
	EXPECT_EQ("Engineer", result->getText());
	EXPECT_EQ(0, result->getId());
	EXPECT_EQ(ERD_Component::Entity, result->getType());

	result = model->findComponentById(6); // id不存在
	EXPECT_EQ(NULL, result);
}

// 測試 兩個node是否已經連線
TEST_F(ER_ModelTest, isAlreadyConnect) 
{
	// 測試
	// 參數:ERD_Component*(node1), ERD_Component*(node2)
	// 回傳:bool
	// 附註:無
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料
	
	bool result;
	result = model->isAlreadyConnect(1, 2);
	EXPECT_EQ(false, result);

	result = model->isAlreadyConnect(1, 1);
	EXPECT_EQ(false, result);

	result = model->isAlreadyConnect(0, 3);
	EXPECT_EQ(true, result);
}

// 測試 設定特定的ID為PrimaryKey(Attribute)
TEST_F(ER_ModelTest, setIsPrimaryKey)
{
	// 測試
	// 參數:int(id), bool(flag)
	// 回傳:無
	// 附註:無
	testDataInit();
	model->setIsPrimaryKey(1, true);
	EXPECT_EQ(true, model->getIsPrimaryKey(1));
	model->setIsPrimaryKey(1, false);
	EXPECT_EQ(false, model->getIsPrimaryKey(1));
}

// 測試 取得特定的ID(Attribute)是否為PrimaryKey
TEST_F(ER_ModelTest, getIsPrimaryKey) 
{
	// 測試
	// 參數:int(id)
	// 回傳:bool
	// 附註:回傳值等於false可能為沒有指定id的component存在
	testDataInit();
	model->setIsPrimaryKey(1, true);
	bool result;
	result = model->getIsPrimaryKey(1);
	EXPECT_EQ(true, result);

	result = model->getIsPrimaryKey(5); //不存在
	EXPECT_EQ(false, result);
}

// 測試 sourceId為connection找連線為targetId的點將與targetId相連的ID且形態等於type的點記錄起來
TEST_F(ER_ModelTest, setRelatedIdVector) 
{
	// 測試
	// 參數:int(sourceId), int(targetId), ComponentType(type), vector<int>&(idVector)
	// 回傳:無
	// 附註:找條件相符的點並記錄該id
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料

	vector<int> result;
	model->setRelatedIdVector(5, 0, ERD_Component::Relationship, result);

	vector<int> expected;
	expected.push_back(3);
	EXPECT_EQ(expected, result);

	result.clear();
	expected.clear();
	model->setRelatedIdVector(5, 3, ERD_Component::Entity, result);
	expected.push_back(0);
	EXPECT_EQ(expected, result);

	result.clear();
	expected.clear();
	model->setRelatedIdVector(5, 3, ERD_Component::Attribute, result);  //找不到
	EXPECT_EQ(expected, result);
}

// 測試 找Node集合(不包含connection)
TEST_F(ER_ModelTest, findNodes) 
{
	// 測試
	// 參數:無
	// 回傳:vector<int>(nodesId)
	// 附註:回傳目前model中所有的Node
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料
	vector<int> result = model->findNodes();
	vector<int> expected;
	expected.push_back(0);
	expected.push_back(1);
	expected.push_back(2);
	expected.push_back(3);
	expected.push_back(4);
	EXPECT_EQ(expected, result);
}

// 測試 找component集合(全部)
TEST_F(ER_ModelTest, findComponents) 
{
	// 測試
	// 參數:無
	// 回傳:vector<int>(componentsId)
	// 附註:回傳目前model中所有的Components
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料
	vector<int> result = model->findComponents();
	vector<int> expected;
	expected.push_back(0);
	expected.push_back(1);
	expected.push_back(2);
	expected.push_back(3);
	expected.push_back(4);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// 測試 找特定型態的component集合
TEST_F(ER_ModelTest, findComponentsByType) 
{
	// 測試
	// 參數:ComponentType(type)
	// 回傳:vector<int>(componentsId)
	// 附註:回傳目前model中所有的為指定type的Components
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料
	vector<int> result = model->findComponentsByType(ERD_Component::Attribute);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(2);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Entity);
	expected.push_back(0);
	expected.push_back(4);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Relationship);
	expected.push_back(3);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Connection);
	expected.push_back(5);

}

// 測試 找targetId與特定type相連的NodeID(不包含connection)
TEST_F(ER_ModelTest, findIdWithTypeByTargetId)
{
	// 測試
	// 參數:ComponentType(type), int(targetId)
	// 回傳:vector<int>(componentsId)
	// 附註:回傳與指定Component相連的Component其type為指定的type
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //建立連線測試資料
	vector<int> result = model->findIdWithTypeByTargetId(ERD_Component::Relationship, 0);
	vector<int> expected;
	expected.push_back(3);
	EXPECT_EQ(expected, result);
}

// 測試 找targetId與特定type相連的NodeID且Cardinality性質為one的(不包含connection)
TEST_F(ER_ModelTest, findIdWithTypeByTargetIdWithCardinality)
{
	// 測試
	// 參數:ComponentType(type), int(targetId)
	// 回傳:vector<int>(NodesId)
	// 附註:回傳與指定Component相連的Component其type為指定的type連線屬性Cardinality為one
	testDataInitWithConnection();
	vector<int> result = model->findIdWithTypeByTargetIdWithCardinality(ERD_Component::Relationship, 0);
	vector<int> expected;
	expected.push_back(4);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findIdWithTypeByTargetIdWithCardinality(ERD_Component::Entity, 4);
	expected.push_back(0);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// 測試 找特定entity的primaryKey
TEST_F(ER_ModelTest, findPrimaryKeyByEntityId) 
{
	// 測試
	// 參數:int(entityId)
	// 回傳:vector<int>(attributeId)
	// 附註:無
	testDataInitWithConnection();
	
	vector<int> result = model->findPrimaryKeyByEntityId(0);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(2);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findPrimaryKeyByEntityId(5);
	expected.push_back(6);
	EXPECT_EQ(expected, result);
}

// 測試 給定entityId找他的foreignKeys
TEST_F(ER_ModelTest, findForeignKeyByEntityId) 
{
	// 測試
	// 參數:int(entityId)
	// 回傳:vector<vector<int>>(foreignKeysIdVector)
	// 附註:回傳foreignkeyIdVector
	testDataInitWithConnection();
	vector<vector<int>> result = model->findForeignKeyByEntityId(0);
	vector<vector<int>> expected;
	expected.push_back(model->findPrimaryKeyByEntityId(5));
	EXPECT_EQ(expected, result);
	TearDown();

	SetUp();
	testDataInitWithConnection();
	expected.clear();
	result = model->findForeignKeyByEntityId(5);
	expected.push_back(model->findPrimaryKeyByEntityId(0));
	EXPECT_EQ(expected, result);
}

// 測試 給定entity找1對1關係的entity
TEST_F(ER_ModelTest, findOneByOneRelationEntityId)
{
	// 測試
	// 參數:int(targetId)
	// 回傳:vector<int>(entitiesId)
	// 附註:找1對1關係的entity
	testDataInitWithConnection();
	vector<int> result = model->findOneByOneRelationEntityId(0);
	vector<int> expected;
	expected.push_back(5);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findOneByOneRelationEntityId(5);
	expected.push_back(0);
	EXPECT_EQ(expected, result);
}

// 測試 嚐試讀檔
TEST_F(ER_ModelTest, readComponentsFile)
{
	// 測試
	// 參數:string(path)
	// 回傳:string(message)
	// 附註:
	string result;
	result = model->readComponentsFile("unittest//test_file1.erd");
	EXPECT_EQ("Success", result);
	result = model->readComponentsFile("unittest//file_not_found.erd");
	EXPECT_EQ("Fail", result);
}

// 測試 讀取檔案內容
TEST_F(ER_ModelTest, loadFileContent)
{
	// 測試
	// 參數:ER_FileManager &(file)
	// 回傳:無
	// 附註:讀檔
	ER_FileManager file;
	file.openFile("unittest//test_file1.erd", ER_FileManager::Read);
	model->loadFileContent(file);
	EXPECT_EQ(15, model->getComponents().size());
}

// 測試 讀檔第1部分Components
TEST_F(ER_ModelTest, loadComponents) 
{
	// 測試
	// 參數:vector<string>::iterator(linIt), map<int, string> &(connectionMap)
	// 回傳:無
	// 附註:建置model內容
	ER_FileManager file;
	file.openFile("unittest//test_file1_part1.erd", ER_FileManager::Read);
	vector<string> lines;
	map<int, string> resultMap;
	string content = file.readFile();
	lines = Tool_Function::split(content, '\n');
	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadComponents(it, resultMap);
	}
	file.closeFile();
	map<int, string> expectedMap;
	expectedMap.insert(pair<int, string> (7, ""));
	expectedMap.insert(pair<int, string> (8, ""));
	expectedMap.insert(pair<int, string> (9, ""));
	expectedMap.insert(pair<int, string> (10, ""));
	expectedMap.insert(pair<int, string> (11, "1"));
	expectedMap.insert(pair<int, string> (12, "1"));
	expectedMap.insert(pair<int, string> (14, ""));
	EXPECT_EQ(expectedMap, resultMap);
	EXPECT_EQ(8, model->getComponents().size());
}

// 測試 讀檔第2部分Connections
TEST_F(ER_ModelTest, loadConnections) 
{
	// 測試
	// 參數:vector<string>::iterator(linIt), map<int, string> &(connectionMap)
	// 回傳:無
	// 附註:建置model內容
	ER_FileManager file;
	file.openFile("unittest//test_file1_part2.erd", ER_FileManager::Read);
	string content = file.readFile();
	vector<string> lines;
	lines = Tool_Function::split(content, '\n');
	// 建立資料
	map<int, string> connectionMap;
	connectionMap.insert(pair<int, string> (7, ""));
	connectionMap.insert(pair<int, string> (8, ""));
	connectionMap.insert(pair<int, string> (9, ""));
	connectionMap.insert(pair<int, string> (10, ""));
	connectionMap.insert(pair<int, string> (11, "1"));
	connectionMap.insert(pair<int, string> (12, "1"));
	connectionMap.insert(pair<int, string> (14, ""));

	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	model->addNode(ERD_Component::Relationship, "Has");   //id=2
	model->addNode(ERD_Component::Attribute, "Name");   //id=3
	model->addNode(ERD_Component::Entity, "PC");  //id=4
	model->addNode(ERD_Component::Attribute, "PC_ID");   //id=5
	model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=6
	model->addNode(ERD_Component::Attribute, "Department", 13);   //id=13
	// 建立資料end

	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadConnections(it, connectionMap);
	}
	file.closeFile();
	EXPECT_EQ(15, model->getComponents().size());
}

// 測試 讀檔第3部分PrimaryKey
TEST_F(ER_ModelTest, loadPrinaryKey) 
{
	// 測試
	// 參數:vector<string>::iterator(linIt)
	// 回傳:無
	// 附註:建置model內容
	ER_FileManager file;
	file.openFile("unittest//test_file1_part3.erd", ER_FileManager::Read);
	string content = file.readFile();
	vector<string> lines;
	lines = Tool_Function::split(content, '\n');
	// 建立資料
	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	model->addNode(ERD_Component::Relationship, "Has");   //id=2
	model->addNode(ERD_Component::Attribute, "Name");   //id=3
	model->addNode(ERD_Component::Entity, "PC");  //id=4
	model->addNode(ERD_Component::Attribute, "PC_ID");   //id=5
	model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=6
	model->addNode(ERD_Component::Attribute, "Department", 13);   //id=13

	model->addConnection(0, 1, 7, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(0, 3, 8, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(4, 5, 9, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(4, 6, 10, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(0, 2, 11, ERD_Connection::one);
	model->addConnection(2, 4, 12, ERD_Connection::one);
	model->addConnection(0, 13, 14, ERD_Connection::SIZE_OF_Cardinality);
	// 建立資料end

	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadPrinaryKey(it);
	}
	file.closeFile();

	vector<int> result = model->findPrimaryKeyByEntityId(0);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(3);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findPrimaryKeyByEntityId(4);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// 測試 存檔
TEST_F(ER_ModelTest, storeComponents) 
{
	// 測試
	// 參數:string(path)
	// 回傳:string(message)
	// 附註:
	testDataInitWithConnection();
	string result;
	result = model->storeComponents("unittest//test_store_file.erd");
	EXPECT_EQ("Success", result);
}

// 測試 判斷idStr是不是已存在的componentId
TEST_F(ER_ModelTest, isExistComponentId)
{
	// 測試
	// 參數:string(idStr)
	// 回傳:bool(result)
	// 附註:無
	testDataInitWithConnection();
	bool result;
	result = model->isExistComponentId("0");
	EXPECT_EQ(true, result);

	result = model->isExistComponentId("14");
	EXPECT_EQ(true, result);

	result = model->isExistComponentId("15");
	EXPECT_EQ(false, result);
}

// 測試 判斷entityId是不是Entity
TEST_F(ER_ModelTest, checkEntitySelectedValid) 
{
	// 測試
	// 參數:string(entityId)
	// 回傳:string(message)
	// 附註:無
	testDataInitWithConnection();
	string result;
	result = model->checkEntitySelectedValid("0");
	EXPECT_EQ("Find Right Entity", result);

	result = model->checkEntitySelectedValid("14");
	EXPECT_EQ("Not an Entity", result);

	result = model->checkEntitySelectedValid("15");
	EXPECT_EQ("Id Not Exist", result);
}

// 測試 刪除component
TEST_F(ER_ModelTest, deleteComponent) 
{
	// 測試
	// 參數:int(id)
	// 回傳:bool(result)
	// 附註:
	testDataInitWithConnection();
	bool result;
	result = model->deleteComponent(0);
	EXPECT_EQ(true, result);

	result = model->deleteComponent(14);
	EXPECT_EQ(true, result);

	result = model->deleteComponent(15);
	EXPECT_EQ(false, result);
}

// 測試 找出與給定ID(targetId)有關的所有Connection的ID
TEST_F(ER_ModelTest, findRelatedConnectionById) 
{
	// 測試
	// 參數:int(targetId)
	// 回傳:vector<int>(connectionId)
	// 附註:
	testDataInitWithConnection();
	vector<int> result = model->findRelatedConnectionById(0);
	vector<int> expected;
	expected.push_back(8);
	expected.push_back(10);
	expected.push_back(11);
	expected.push_back(12);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findRelatedConnectionById(5);
	expected.push_back(9);
	expected.push_back(13);
	expected.push_back(14);
	EXPECT_EQ(expected, result);
}

// 測試 新增component
TEST_F(ER_ModelTest, addComponent) 
{
	// 測試
	// 參數:ERD_Component*(component)
	// 回傳:無
	// 附註:
	ERD_Component* testComponent = new ERD_Component;
	model->addComponent(testComponent);           // 加入1個component
	EXPECT_EQ(1, model->getComponents().size());
}

// 測試 是否有足夠的node可以連接
TEST_F(ER_ModelTest, enoughNodesToConnect) 
{
	// 測試
	// 參數:無
	// 回傳:bool(result)
	// 附註:
	EXPECT_EQ(false, model->enoughNodesToConnect());
	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	EXPECT_EQ(true, model->enoughNodesToConnect());
}

/* 測試
TEST_F(ER_ModelTest, functionName)
{
	// 測試
	// 參數:
	// 回傳:
	// 附註:
	EXPECT_EQ(0, model->getComponents().size());
}*/