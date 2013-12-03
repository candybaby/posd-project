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

// 代刚 硈絬
TEST_F(ERD_ConnectionTest, connectTo)
{
	// 代刚
	// 把计:ERD_Component*(component)
	// 肚:礚
	// 爹:礚
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	EXPECT_EQ(entityTest->getId(), connection->getNodeId());
	EXPECT_EQ(attributeTest->getId(), connection->getOtherNodeId());
}

// 代刚 耞琌蛤﹚IdΤ硈
TEST_F(ERD_ConnectionTest, isConnectToId)
{
	// 代刚
	// 把计:int(id)
	// 肚:bool
	// 爹:礚
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

// 代刚 砞﹚ゅ
TEST_F(ERD_ConnectionTest, setText)
{
	// 代刚
	// 把计:礚
	// 肚:礚
	// 爹:礚
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	connectionWithCardinality->connectTo(entityTest);
	connectionWithCardinality->connectTo(relationshipTest);
	string result, except;
	except = "text";
	connection->setText(except);
	result = connection->getText();
	EXPECT_EQ("", result);

	except = "";
	connection->setText(except);
	result = connection->getText();
	EXPECT_EQ("", result);

	except = "1";
	connection->setText(except);
	result = connection->getText();
	EXPECT_EQ("", result);

	except = "N";
	connection->setText(except);
	result = connection->getText();
	EXPECT_EQ("", result);

	except = "text";
	connectionWithCardinality->setText(except);
	result = connectionWithCardinality->getText();
	EXPECT_EQ("1", result);

	except = "";
	connectionWithCardinality->setText(except);
	result = connectionWithCardinality->getText();
	EXPECT_EQ("1", result);

	except = "1";
	connectionWithCardinality->setText(except);
	result = connectionWithCardinality->getText();
	EXPECT_EQ(except, result);

	except = "N";
	connectionWithCardinality->setText(except);
	result = connectionWithCardinality->getText();
	EXPECT_EQ(except, result);
}

// 代刚 эゅ
TEST_F(ERD_ConnectionTest, canChangeText)
{
	// 代刚
	// 把计:礚
	// 肚:bool
	// 爹:礚
	connection->connectTo(entityTest);
	connection->connectTo(attributeTest);
	connectionWithCardinality->connectTo(entityTest);
	connectionWithCardinality->connectTo(relationshipTest);
	EXPECT_EQ(connection->canChangeText("text"), false);
	EXPECT_EQ(connection->canChangeText(""), false);
	EXPECT_EQ(connection->canChangeText("1"), false);
	EXPECT_EQ(connection->canChangeText("N"), false);

	EXPECT_EQ(connectionWithCardinality->canChangeText("text"), false);
	EXPECT_EQ(connectionWithCardinality->canChangeText(""), false);
	EXPECT_EQ(connectionWithCardinality->canChangeText("1"), true);
	EXPECT_EQ(connectionWithCardinality->canChangeText("N"), true);
}

// 代刚 订
TEST_F(ERD_ConnectionTest, clone)
{
	// 代刚
	// 把计:礚
	// 肚:ERD_Component*
	// 爹:礚
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

