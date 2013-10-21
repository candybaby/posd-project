#include "ERD_Connection.h"
#include "ERD_Attribute.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "gtest/gtest.h"

using namespace std;
class ERD_ConnectionTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		entityTest = new ERD_Entity("Engineer", 0);
		attributeTest = new ERD_Attribute("Name", 1);
		relationshipTest = new ERD_Relationship("Has", 2);
		connection = new ERD_Connection(3);
		connectionWithCardinality = new ERD_Connection(4, ERD_Connection::one);
		
	}

	virtual void TearDown()
	{
		delete connection;
		delete connectionWithCardinality;
		delete entityTest;
		delete attributeTest;
		delete relationshipTest;
	}

	ERD_Connection* connection;
	ERD_Connection* connectionWithCardinality;
	ERD_Component* entityTest;
	ERD_Component* attributeTest;
	ERD_Component* relationshipTest;
};

// 測試 連線
TEST_F(ERD_ConnectionTest, connectTo)
{
	// 測試
	// 參數:ERD_Component*(component)
	// 回傳:無
	// 附註:無
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	EXPECT_EQ(entityTest->getId(), connection->getNodeId());
	EXPECT_EQ(attributeTest->getId(), connection->getOtherNodeId());
}

// 測試 判斷是否跟指定Id有相連
TEST_F(ERD_ConnectionTest, isConnectToId)
{
	// 測試
	// 參數:int(id)
	// 回傳:bool
	// 附註:無
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	connectionWithCardinality->connectTo(entityTest);
	connectionWithCardinality->connectTo(relationshipTest);

	bool result;
	result = connection->isConnectToId(0);
	EXPECT_EQ(true, result);

	result = connection->isConnectToId(1);
	EXPECT_EQ(true, result);

	result = connection->isConnectToId(2);
	EXPECT_EQ(false, result);

	result = connectionWithCardinality->isConnectToId(0);
	EXPECT_EQ(true, result);

	result = connectionWithCardinality->isConnectToId(2);
	EXPECT_EQ(true, result);

	result = connectionWithCardinality->isConnectToId(1);
	EXPECT_EQ(false, result);

}

// 測試 克隆
TEST_F(ERD_ConnectionTest, clone)
{
	// 測試
	// 參數:無
	// 回傳:ERD_Component*
	// 附註:無
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	ERD_Connection* connectionClone = (ERD_Connection*)connection->clone();
	EXPECT_EQ(connection->getId(), connectionClone->getId());
	EXPECT_EQ(connection->getType(), connectionClone->getType());
	EXPECT_EQ(connection->getText(), connectionClone->getText());
	EXPECT_EQ(connection->getConnections(), connectionClone->getConnections());
	EXPECT_EQ(connection->getCardinality(), connectionClone->getCardinality());
	EXPECT_EQ(connection->getNodeId(), connectionClone->getNodeId());
	EXPECT_EQ(connection->getOtherNodeId(), connectionClone->getOtherNodeId());
}