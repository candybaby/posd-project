#include "ER_PresentationModel.h"
#include "gtest/gtest.h"

using namespace std;
class ER_PresentationModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model();
		presentationModel = new ER_PresentationModel(model);
	}

	virtual void TearDown()
	{
		delete presentationModel;
		delete model;
	}

	void makeTestData()
	{
		presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
		presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
		presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
		presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
		presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
		presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
		presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
		presentationModel->addConnection(0, 4, ERD_Connection::one);
		presentationModel->addConnection(4, 5, ERD_Connection::one);
		presentationModel->addConnection(0, 1, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(0, 2, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(0, 3, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(5, 6, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(5, 7, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->setIsPrimaryKey(1, true);
		presentationModel->setIsPrimaryKey(2, true);
		presentationModel->setIsPrimaryKey(6, true);

	}

	ER_Model* model;
	ER_PresentationModel* presentationModel;
};

// 測試 新增Node時輸入與Type之間的對應
TEST_F(ER_PresentationModelTest, addNodeOptionMapping)
{
	// 測試
	// 參數:string(command)
	// 回傳:int(result)
	// 附註:無
	int result;
	result = presentationModel->addNodeOptionMapping("A");
	EXPECT_EQ(0, result);

	result = presentationModel->addNodeOptionMapping("E");
	EXPECT_EQ(1, result);

	result = presentationModel->addNodeOptionMapping("R");
	EXPECT_EQ(2, result);

	result = presentationModel->addNodeOptionMapping("");  //例外狀況
	EXPECT_EQ(-1, result);
}

// 測試 新增節點
TEST_F(ER_PresentationModelTest, addNode)
{
	// 測試
	// 參數:ComponentType(componentType), string(nodeName)
	// 回傳:string
	// 附註:無
	string result;
	result = presentationModel->addNode(ERD_Component::Entity, "Engineer");
	EXPECT_EQ("0", result);
	result = presentationModel->addNode(ERD_Component::Entity, "PC");
	EXPECT_EQ("1", result);
	EXPECT_EQ(2, presentationModel->getCurrentId());
}

// 測試 取得現在的ID
TEST_F(ER_PresentationModelTest, getCurrentId)
{
	// 測試
	// 參數:無
	// 回傳:int
	// 附註:無
	int result;
	result = presentationModel->getCurrentId();
	EXPECT_EQ(0, result);
	presentationModel->addNode(ERD_Component::Entity, "Engineer");

	result = presentationModel->getCurrentId();
	EXPECT_EQ(1, result);

	presentationModel->addNode(ERD_Component::Entity, "PC");
	result = presentationModel->getCurrentId();
	EXPECT_EQ(2, result);
}

// 測試 取得ID藉由index
TEST_F(ER_PresentationModelTest, getIdByIndex)
{
	// 測試
	// 參數:int(index)
	// 回傳:int(id)
	// 附註:無
	makeTestData();
	int result;
	result = presentationModel->getIdByIndex(0);
	EXPECT_EQ(0, result);

	result = presentationModel->getIdByIndex(14);
	EXPECT_EQ(14, result);

	result = presentationModel->getIdByIndex(15);
	EXPECT_EQ(-1, result);

	result = presentationModel->getIdByIndex(-1);
	EXPECT_EQ(-1, result);
}

// 測試 取得connection(by ID)連接兩端的ID以nodeNumber來區分0 1
TEST_F(ER_PresentationModelTest, getConnectionNodeById)
{
	// 測試
	// 參數:int(id), int(nodeNumber)
	// 回傳:int(id)
	// 附註:無
	makeTestData();
	int result;
	result = presentationModel->getConnectionNodeById(8, 0);
	EXPECT_EQ(0, result);
	result = presentationModel->getConnectionNodeById(8, 1);
	EXPECT_EQ(4, result);

	result = presentationModel->getConnectionNodeById(14, 0);
	EXPECT_EQ(5, result);
	result = presentationModel->getConnectionNodeById(14, 1);
	EXPECT_EQ(7, result);

	result = presentationModel->getConnectionNodeById(15, 0); // 沒有該ID
	EXPECT_EQ(-1, result);
	result = presentationModel->getConnectionNodeById(7, 1);  // 該ID不屬於Connection
	EXPECT_EQ(-1, result);
}

// 測試 取得text的值藉由id
TEST_F(ER_PresentationModelTest, getNameById)
{
	// 測試
	// 參數:int(id)
	// 回傳:string(name)
	// 附註:無
	makeTestData();
	string result;
	result = presentationModel->getNameById(0);
	EXPECT_EQ("Engineer", result);

	result = presentationModel->getNameById(1);
	EXPECT_EQ("EmpID", result);

	result = presentationModel->getNameById(4);
	EXPECT_EQ("Has", result);

	result = presentationModel->getNameById(8);
	EXPECT_EQ("1", result);

	result = presentationModel->getNameById(10);
	EXPECT_EQ("", result);

	result = presentationModel->getNameById(-1);
	EXPECT_EQ("", result);

	result = presentationModel->getNameById(15);
	EXPECT_EQ("", result);
}

// 測試 取得Type藉由id
TEST_F(ER_PresentationModelTest, getTypeById)
{
	// 測試
	// 參數:int(id)
	// 回傳:ComponentType
	// 附註:無
	makeTestData();
	ERD_Component::ComponentType result;
	result = presentationModel->getTypeById(0);
	EXPECT_EQ(ERD_Component::Entity, result);

	result = presentationModel->getTypeById(1);
	EXPECT_EQ(ERD_Component::Attribute, result);

	result = presentationModel->getTypeById(4);
	EXPECT_EQ(ERD_Component::Relationship, result);

	result = presentationModel->getTypeById(8);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = presentationModel->getTypeById(10);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = presentationModel->getTypeById(-1);
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);

	result = presentationModel->getTypeById(15);
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);
}

// 測試 連線訊息
TEST_F(ER_PresentationModelTest, getAddConnectionMessage)
{
	// 測試
	// 參數:int,int
	// 回傳:string(message)
	// 附註:無
	presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
	presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
	presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
	presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
	presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
	presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
	presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
	presentationModel->addConnection(0, 4, ERD_Connection::one);
	string result;
	result = presentationModel->getAddConnectionMessage(0, 4);  //已連線
	EXPECT_EQ("The node '0' has already been connected to component '4'.", result);

	result = presentationModel->getAddConnectionMessage(0, 0);  //同一個Node
	EXPECT_EQ("The node '0' cannot be connected to itself.", result);

	result = presentationModel->getAddConnectionMessage(4, 5);  //ASK_CARDINALITY_STATE
	EXPECT_EQ("ask cardinality", result);

	result = presentationModel->getAddConnectionMessage(6, 7);  //不能連線
	EXPECT_EQ("The node '7' cannot be connected by the node '6'.", result);

	EXPECT_EQ(9, presentationModel->getCurrentId());

	result = presentationModel->getAddConnectionMessage(5, 6);  //可以連線 並連線
	EXPECT_EQ("The node '5' has been connected to the node '6'.", result);
	EXPECT_EQ(10, presentationModel->getCurrentId());
}

// 測試 回傳不能連線的訊息
TEST_F(ER_PresentationModelTest, getCannotConnectMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
	string result;
	result = presentationModel->getCannotConnectMessage("0", "1");
	EXPECT_EQ("The node '0' cannot be connected by the node '1'.", result);
}

// 測試 回傳一樣Node連線錯誤的訊息
TEST_F(ER_PresentationModelTest, getSameNodeMessage)
{
	// 測試
	// 參數:string
	// 回傳:string(message)
	// 附註:無
	string result;
	result = presentationModel->getSameNodeMessage("0");
	EXPECT_EQ("The node '0' cannot be connected to itself.", result);
}

// 測試 回傳需要Cardinary資訊的訊息
TEST_F(ER_PresentationModelTest, getAskCardinaryStateMessage)
{
	// 測試
	// 參數:無
	// 回傳:string(message)
	// 附註:無
	string result;
	result = presentationModel->getAskCardinaryStateMessage();
	EXPECT_EQ("ask cardinality", result);
}

// 測試 回傳已經連線的訊息
TEST_F(ER_PresentationModelTest, getAlreadyConnectedMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
	string result;
	result = presentationModel->getAlreadyConnectedMessage("0", "1");
	EXPECT_EQ("The node '0' has already been connected to component '1'.", result);
}

// 測試 回傳成功連線的訊息
TEST_F(ER_PresentationModelTest, getNodeConnectedMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
	string result;
	result = presentationModel->getNodeConnectedMessage("0", "1");
	EXPECT_EQ("The node '0' has been connected to the node '1'.", result);
}

// 測試 新增連線
TEST_F(ER_PresentationModelTest, addConnection)
{
	// 測試
	// 參數:int, int, ConnectionCardinality
	// 回傳:string(message)
	// 附註:無
	presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
	presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
	presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
	presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
	presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
	presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
	presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
	string result;
	result = presentationModel->addConnection(0, 4, ERD_Connection::one);
	EXPECT_EQ("The node '0' has been connected to the node '4'.\nIts cardinality of the relationship is '1'.", result);
}

// 測試 判斷idStr是不是已存在的componentId
TEST_F(ER_PresentationModelTest, isExistComponentId)
{
	// 測試
	// 參數:string
	// 回傳:bool
	// 附註:無
	makeTestData();
	bool result;
	result = presentationModel->isExistComponentId("0");
	EXPECT_EQ(true, result);

	result = presentationModel->isExistComponentId("14");
	EXPECT_EQ(true, result);

	result = presentationModel->isExistComponentId("15");
	EXPECT_EQ(false, result);
}

// 測試 判斷entityId是不是Entity
TEST_F(ER_PresentationModelTest, checkEntitySelectedValid)
{
	// 測試
	// 參數:string
	// 回傳:string
	// 附註:無
	makeTestData();
	string result;
	result = presentationModel->checkEntitySelectedValid("0");
	EXPECT_EQ("Find Right Entity", result);

	result = presentationModel->checkEntitySelectedValid("1");
	EXPECT_EQ("Not an Entity", result);

	result = presentationModel->checkEntitySelectedValid("15");
	EXPECT_EQ("Id Not Exist", result);
}

/* 測試 處理設定primaryKey的字串
TEST_F(ER_PresentationModelTest, checkAttributesSelectedValid)
{
	// 測試
	// 參數:string, int
	// 回傳:string
	// 附註:無
}*/

/* 測試 判斷Attribute是不是屬於特定Entity的
TEST_F(ER_PresentationModelTest, isAttributeBelongEntity)
{
	// 測試
	// 參數:int, int
	// 回傳:bool
	// 附註:無
}*/

/* 測試 設定id為PrimaryKey
TEST_F(ER_PresentationModelTest, setIsPrimaryKey)
{
	// 測試
	// 參數:int, bool
	// 回傳:無
	// 附註:無
}*/

/* 測試 取得id是否為primaryKey
TEST_F(ER_PresentationModelTest, getIsPrimaryKey)
{
	// 測試
	// 參數:id
	// 回傳:bool
	// 附註:無
}*/

/* 測試 取得primaryKey的顯示字串
TEST_F(ER_PresentationModelTest, getPrimaryKeyString)
{
	// 測試
	// 參數:int(id)
	// 回傳:string
	// 附註:無
}*/

/* 測試 找Node集合(不包含connection)
TEST_F(ER_PresentationModelTest, findNodes)
{
	// 測試
	// 參數:無
	// 回傳:vector<int>
	// 附註:無
}*/

/* 測試 找component集合(全部)
TEST_F(ER_PresentationModelTest, findComponents)
{
	// 測試
	// 參數:無
	// 回傳:vector<int>
	// 附註:無
}*/

/* 測試 找targetId與特定type相連的NodeID(不包含connection)
TEST_F(ER_PresentationModelTest, findIdWithTypeByTargetId)
{
	// 測試
	// 參數:ComponentType(type), int(id)
	// 回傳:vector<int>
	// 附註:無
}*/

/* 測試 找特定型態的component集合
TEST_F(ER_PresentationModelTest, findComponentsByType)
{
	// 測試
	// 參數:ComponentType(type)
	// 回傳:vector<int>
	// 附註:無
}*/

/* 測試 是否存在table
TEST_F(ER_PresentationModelTest, isExistTable)
{
	// 測試
	// 參數:無
	// 回傳:bool
	// 附註:無
}*/

/* 測試 取得特定ID的ForeignKey
TEST_F(ER_PresentationModelTest, getForeignKeyResult)
{
	// 測試
	// 參數:int(id)
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳特定id的Attribute字串
TEST_F(ER_PresentationModelTest, getAttributesForTable)
{
	// 測試
	// 參數:int(id)
	// 回傳:string
	// 附註:無
}*/

/* 測試 製作primaryKey字串
TEST_F(ER_PresentationModelTest, makePrimaryKeyString)
{
	// 測試
	// 參數:int, string
	// 回傳:string
	// 附註:無
}*/

/* 測試 製作result字串
TEST_F(ER_PresentationModelTest, makeResultString)
{
	// 測試
	// 參數:int, string, string
	// 回傳:string
	// 附註:無
}*/

/* 測試 找出有1對1關係的entity
TEST_F(ER_PresentationModelTest, findOneByOneEntity)
{
	// 測試
	// 參數:無
	// 回傳:vector<int>
	// 附註:無
}*/

/* 測試 回傳table字串
TEST_F(ER_PresentationModelTest, getTable)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 讀檔
TEST_F(ER_PresentationModelTest, readComponentsFile)
{
	// 測試
	// 參數:string
	// 回傳:string
	// 附註:無
}*/

/* 測試 存檔
TEST_F(ER_PresentationModelTest, storeComponents)
{
	// 測試
	// 參數:string
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳connection字串
TEST_F(ER_PresentationModelTest, getConnectionsTable)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳node字串
TEST_F(ER_PresentationModelTest, getNodesTable)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳component字串
TEST_F(ER_PresentationModelTest, getComponentsTable)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳entity字串
TEST_F(ER_PresentationModelTest, getEntitiesTable)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 回傳特定id Attribute字串
TEST_F(ER_PresentationModelTest, getAttributesTableById)
{
	// 測試
	// 參數:int
	// 回傳:string
	// 附註:無
}*/

/* 測試 redo
TEST_F(ER_PresentationModelTest, redo)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 undo
TEST_F(ER_PresentationModelTest, undo)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
}*/

/* 測試 刪除特定id的component
TEST_F(ER_PresentationModelTest, deleteComponent)
{
	// 測試
	// 參數:int
	// 回傳:string
	// 附註:無
}*/

/* 測試 判斷是否有足夠的Node可以連接
TEST_F(ER_PresentationModelTest, enoughNodesToConnect)
{
	// 測試
	// 參數:無
	// 回傳:bool
	// 附註:無
}*/

/* 測試 判斷是否有改變
TEST_F(ER_PresentationModelTest, getHasModify)
{
	// 測試
	// 參數:無
	// 回傳:bool
	// 附註:無
}*/