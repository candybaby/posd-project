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

	ER_Model* model;
};

// 測試清除目前model內的components
TEST_F(ER_ModelTest, clearCurrentComponents) {
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
TEST_F(ER_ModelTest, sortComponents) {
	// 建立id沒有順序的資料在作排序測式
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試新增節點(不包含connection) case多
TEST_F(ER_ModelTest, addNode) {
	// 測試
	// 參數:ComponentType(type), string(name)
	// 回傳:int (id)
	// 附註:id為目前model依序新增的id(遞增)
	EXPECT_EQ(0, model->getComponents().size());

	// 測試
	// 參數:string(type), string(name)
	// 回傳:無
	// 附註:id為目前model依序新增的id(遞增)
	EXPECT_EQ(0, model->getComponents().size());

	// 測試
	// 參數:ComponentType(type), string(name), int(id)
	// 回傳:無
	// 附註:id為目前model依序新增的id(遞增)
	EXPECT_EQ(0, model->getComponents().size());

}

// 測試 設定Attribute為已連線狀態
TEST_F(ER_ModelTest, setAttributeTypeConnected) {
	// 測試
	// 參數:ERD_Component*(component)
	// 回傳:ERD_Component*
	// 附註:無
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 檢查連線情況 參數為兩個Node要連接的ID 結果 -1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連
TEST_F(ER_ModelTest, checkAddConnection) {
	// 測試
	// 參數:int(component1Id), int(component2Id)
	// 回傳:int(-1:已經相連 -2:Cardinality -3:兩點相同 -4:不能連 >=0:連線的id)
	// 附註:
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得現在model的排序id並調整為下一個排序
TEST_F(ER_ModelTest, getAddConnectionId) {
	// 測試
	// 參數:無
	// 回傳:int(id)
	// 附註:新增連線時用到
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 新增連線 case多
TEST_F(ER_ModelTest, addConnection) {
	// 測試
	// 參數:int(component1Id), int(component2Id), int(id)
	// 回傳:無
	// 附註:特定ID位置的新增 主要用於讀檔時的新增
	EXPECT_EQ(0, model->getComponents().size());

	// 測試
	// 參數:int(component1Id), int(component2Id), int(id), ConnectionCardinality(cardinality)
	// 回傳:無
	// 附註:特定ID位置的新增包含cardinality屬性
	EXPECT_EQ(0, model->getComponents().size());

	// 測試
	// 參數:int(component1Id), int(component2Id), int(id), string(cardinalityStr)
	// 回傳:無
	// 附註:特定ID位置的新增包含cardinality屬性 主要用於讀檔時的新增
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 用index找到對應的ID
TEST_F(ER_ModelTest, getIdByIndex) {
	// 測試
	// 參數:int(index)
	// 回傳:int(id)
	// 附註:無
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得連線的兩個node 以nodeNumber來分node0與node1
TEST_F(ER_ModelTest, getConnectionNodeById) {
	// 測試
	// 參數:int(id), int(nodeNumber)
	// 回傳:int(id)
	// 附註:回傳值為-1的狀況為例外狀況例:無連線
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得名稱藉由ID
TEST_F(ER_ModelTest, getNameById) {
	// 測試
	// 參數:int(id)
	// 回傳:string(name)
	// 附註:回傳空字串為該id的text為空或沒有指定id的component存在
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得型態藉由ID
TEST_F(ER_ModelTest, getTypeById) {
	// 測試
	// 參數:int(id)
	// 回傳:ComponentType(type)
	// 附註:回傳值等於SIZE_OF_ComponentType為沒有指定id的component存在
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得ERD_Component藉由ID
TEST_F(ER_ModelTest, findComponentById) {
	// 測試
	// 參數:int(id)
	// 回傳:ERD_Component*(component)
	// 附註:找不到為NULL
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 兩個node是否已經連線
TEST_F(ER_ModelTest, isAlreadyConnect) {
	// 測試
	// 參數:ERD_Component*(node1), ERD_Component*(node2)
	// 回傳:bool
	// 附註:無
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 設定特定的ID為PrimaryKey(Attribute)
TEST_F(ER_ModelTest, setIsPrimaryKey) {
	// 測試
	// 參數:int(id), bool(flag)
	// 回傳:無
	// 附註:無
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 取得特定的ID(Attribute)是否為PrimaryKey
TEST_F(ER_ModelTest, getIsPrimaryKey) {
	// 測試
	// 參數:int(id)
	// 回傳:bool
	// 附註:回傳值等於false可能為沒有指定id的component存在
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 sourceId為connection找連線為targetId的點將與targetId相連的ID且形態等於type的點記錄起來
TEST_F(ER_ModelTest, setRelatedIdVector) {
	// 測試
	// 參數:int(sourceId), int(targetId), ComponentType(type), vector<int>&(idVector)
	// 回傳:無
	// 附註:找條件相符的點並記錄該id
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 找Node集合(不包含connection)
TEST_F(ER_ModelTest, findNodes) {
	// 測試
	// 參數:無
	// 回傳:vector<int>(nodesId)
	// 附註:回傳目前model中所有的Node
	EXPECT_EQ(0, model->getComponents().size());
}

// 測試 找component集合(全部)
TEST_F(ER_ModelTest, findComponents) {
	// 測試
	// 參數:無
	// 回傳:vector<int>(componentsId)
	// 附註:回傳目前model中所有的Components
	EXPECT_EQ(0, model->getComponents().size());
}

/* 測試
TEST_F(ER_ModelTest, functionName) {
	// 測試
	// 參數:
	// 回傳:
	// 附註:
	EXPECT_EQ(0, model->getComponents().size());
}*/

/* 測試
TEST_F(ER_ModelTest, functionName) {
	// 測試
	// 參數:
	// 回傳:
	// 附註:
	EXPECT_EQ(0, model->getComponents().size());
}*/

/* 測試
TEST_F(ER_ModelTest, functionName) {
	// 測試
	// 參數:
	// 回傳:
	// 附註:
	EXPECT_EQ(0, model->getComponents().size());
}*/