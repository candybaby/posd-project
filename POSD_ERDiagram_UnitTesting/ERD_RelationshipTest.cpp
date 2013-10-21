#include "ERD_Attribute.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "gtest/gtest.h"

using namespace std;
class ERD_RelationshipTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		relationship = new ERD_Relationship("Has", 0);
		entityTest = new ERD_Entity("Engineer", 1);
		attributeTest = new ERD_Attribute("Name", 2);
	}

	virtual void TearDown()
	{
		delete relationship;
		delete entityTest;
		delete attributeTest;
	}

	ERD_Relationship* relationship;
	ERD_Component* entityTest;
	ERD_Component* attributeTest;
};

// 測試 判斷是否可連
TEST_F(ERD_RelationshipTest, canConnectTo)
{
	// 測試
	// 參數:ERD_Component*(entity)
	// 回傳:bool
	// 附註:無
	bool result;
	result = relationship->canConnectTo(entityTest);
	EXPECT_EQ(true, result);

	result = relationship->canConnectTo(attributeTest);
	EXPECT_EQ(false, result);
}

// 測試 克隆
TEST_F(ERD_RelationshipTest, clone)
{
	// 測試
	// 參數:無
	// 回傳:ERD_Component*
	// 附註:無
	ERD_Relationship* relationshipClone = (ERD_Relationship*)relationship->clone();
	EXPECT_EQ(relationship->getId(), relationshipClone->getId());
	EXPECT_EQ(relationship->getType(), relationshipClone->getType());
	EXPECT_EQ(relationship->getText(), relationshipClone->getText());
	EXPECT_EQ(relationship->getConnections(), relationshipClone->getConnections());
}