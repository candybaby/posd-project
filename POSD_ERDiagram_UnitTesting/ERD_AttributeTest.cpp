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

// 測試 判斷是否可連
TEST_F(ERD_AttributeTest, canConnectTo)
{
	// 測試
	// 參數:ERD_Component*(entity)
	// 回傳:bool
	// 附註:無
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

// 測試 克隆
TEST_F(ERD_AttributeTest, clone)
{
	// 測試
	// 參數:無
	// 回傳:ERD_Component*
	// 附註:無
	ERD_Attribute* attributeClone = (ERD_Attribute*)attribute->clone();
	EXPECT_EQ(attribute->getId(), attributeClone->getId());
	EXPECT_EQ(attribute->getType(), attributeClone->getType());
	EXPECT_EQ(attribute->getText(), attributeClone->getText());
	EXPECT_EQ(attribute->getConnections(), attributeClone->getConnections());
	EXPECT_EQ(attribute->getIsPrimaryKey(), attributeClone->getIsPrimaryKey());
	EXPECT_EQ(attribute->getIsConnected(), attributeClone->getIsConnected());
}