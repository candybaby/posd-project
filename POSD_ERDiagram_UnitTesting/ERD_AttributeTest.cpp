#include "ERD_Attribute.h"
#include "ERD_Entity.h"
#include "gtest/gtest.h"

using namespace std;
class ERD_AttributeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		attribute = new ERD_Attribute("Name", 0);
	}

	virtual void TearDown()
	{
		delete attribute;
	}

	ERD_Attribute* attribute;
};

// 代刚 篶
TEST_F(ERD_AttributeTest, ERD_Attribute)
{
	// 代刚
	// 把计:礚
	// 肚:礚
	// 爹:礚
	attribute = new ERD_Attribute();
	EXPECT_EQ(ERD_Component::Attribute, attribute->getType());
	EXPECT_EQ(false, attribute->getIsPrimaryKey());
	EXPECT_EQ(false, attribute->getIsConnected());
}

// 代刚 耞琌硈
TEST_F(ERD_AttributeTest, canConnectTo)
{
	// 代刚
	// 把计:ERD_Component*(entity)
	// 肚:bool
	// 爹:礚
	ERD_Component* entityTest = new ERD_Entity("Engineer", 1);
	bool result;
	result = attribute->canConnectTo(entityTest);
	EXPECT_EQ(true, result);
	delete entityTest;
	TearDown();

	SetUp();
	ERD_Component* attributeTest = new ERD_Attribute("EMP_ID", 1);
	result = attribute->canConnectTo(attributeTest);
	EXPECT_EQ(false, result);
	delete attributeTest;
	TearDown();

	SetUp();
	entityTest = new ERD_Entity("Engineer", 1);
	attribute->setConnected(true);
	result = attribute->canConnectTo(entityTest);
	EXPECT_EQ(false, result);
	delete entityTest;
}

// 代刚 订
TEST_F(ERD_AttributeTest, clone)
{
	// 代刚
	// 把计:礚
	// 肚:ERD_Component*
	// 爹:礚
	ERD_Attribute* attributeClone = (ERD_Attribute*)attribute->clone();
	EXPECT_EQ(attribute->getId(), attributeClone->getId());
	EXPECT_EQ(attribute->getType(), attributeClone->getType());
	EXPECT_EQ(attribute->getText(), attributeClone->getText());
	EXPECT_EQ(attribute->getConnections(), attributeClone->getConnections());
	EXPECT_EQ(attribute->getIsPrimaryKey(), attributeClone->getIsPrimaryKey());
	EXPECT_EQ(attribute->getIsConnected(), attributeClone->getIsConnected());
}