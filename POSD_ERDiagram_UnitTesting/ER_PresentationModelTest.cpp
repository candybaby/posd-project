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
}

/* 測試 新增節點
TEST_F(ER_PresentationModelTest, addNode)
{
	// 測試
	// 參數:ComponentType(componentType), string(nodeName)
	// 回傳:string
	// 附註:無
}*/

/* 測試 取得現在的ID
TEST_F(ER_PresentationModelTest, getCurrentId)
{
	// 測試
	// 參數:無
	// 回傳:int
	// 附註:無
}*/

/* 測試 取得ID藉由index
TEST_F(ER_PresentationModelTest, getIdByIndex)
{
	// 測試
	// 參數:int(index)
	// 回傳:int(id)
	// 附註:無
}*/

/* 測試 取得connection(by ID)連接兩端的ID以nodeNumber來區分0 1
TEST_F(ER_PresentationModelTest, getConnectionNodeById)
{
	// 測試
	// 參數:int(id), int(nodeNumber)
	// 回傳:int(id)
	// 附註:無
}*/

/* 測試 取得text的值藉由id
TEST_F(ER_PresentationModelTest, getNameById)
{
	// 測試
	// 參數:int(id)
	// 回傳:string(name)
	// 附註:無
}*/

/* 測試 取得Type藉由id
TEST_F(ER_PresentationModelTest, getTypeById)
{
	// 測試
	// 參數:int(id)
	// 回傳:ComponentType
	// 附註:無
}*/

/* 測試 連線訊息
TEST_F(ER_PresentationModelTest, getAddConnectionMessage)
{
	// 測試
	// 參數:int,int
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 回傳不能連線的訊息
TEST_F(ER_PresentationModelTest, getCannotConnectMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 回傳一樣Node連線錯誤的訊息
TEST_F(ER_PresentationModelTest, getSameNodeMessage)
{
	// 測試
	// 參數:string
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 回傳需要Cardinary資訊的訊息
TEST_F(ER_PresentationModelTest, getAskCardinaryStateMessage)
{
	// 測試
	// 參數:無
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 回傳已經連線的訊息
TEST_F(ER_PresentationModelTest, getAlreadyConnectedMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 回傳成功連線的訊息
TEST_F(ER_PresentationModelTest, getNodeConnectedMessage)
{
	// 測試
	// 參數:string, string
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 新增連線
TEST_F(ER_PresentationModelTest, addConnection)
{
	// 測試
	// 參數:int, int, ConnectionCardinality
	// 回傳:string(message)
	// 附註:無
}*/

/* 測試 判斷idStr是不是已存在的componentId
TEST_F(ER_PresentationModelTest, isExistComponentId)
{
	// 測試
	// 參數:string
	// 回傳:bool
	// 附註:無
}*/

/* 測試 判斷entityId是不是Entity
TEST_F(ER_PresentationModelTest, checkEntitySelectedValid)
{
	// 測試
	// 參數:string
	// 回傳:string
	// 附註:無
}*/

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