#include "ERD_Attribute.h"
#include "ERD_Entity.h"
#include "ERD_Relationship.h"
#include "gtest/gtest.h"

using namespace std;
class ERD_EntityTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		entity = new ERD_Entity("Engineer", 0);
		entityTest = new ERD_Entity("PC", 1);
		attributeTest = new ERD_Attribute("Name", 2);
		relationshipTest = new ERD_Relationship("Has", 3);
	}

	virtual void TearDown()
	{
		delete entity;
		delete entityTest;
		delete attributeTest;
		delete relationshipTest;
	}

	ERD_Entity* entity;
	ERD_Component* entityTest;
	ERD_Component* attributeTest;
	ERD_Component* relationshipTest;
};

// 測試 建構子
TEST_F(ERD_EntityTest, ERD_Entity)
{
	// 測試
	// 參數:無
	// 回傳:無
	// 附註:無
	entity = new ERD_Entity();
	EXPECT_EQ(ERD_Component::Entity, entity->getType());
}

// 測試 判斷是否可連
TEST_F(ERD_EntityTest, canConnectTo)
{
	// 測試
	// 參數:ERD_Component*(entity)
	// 回傳:bool
	// 附註:無
	bool result;
	result = entity->canConnectTo(entityTest);
	EXPECT_EQ(false, result);

	result = entity->canConnectTo(attributeTest);
	EXPECT_EQ(true, result);

	result = entity->canConnectTo(relationshipTest);
	EXPECT_EQ(true, result);
}

// 測試 取得是否有包含與該entity有foreignKey關係的EntityID
TEST_F(ERD_EntityTest, isContainForeignEntityId)
{
	// 測試
	// 參數:int(id)
	// 回傳:bool
	// 附註:無
	entity->addForeignEntityId(1);
	entity->addForeignEntityId(3);
	bool result;
	result = entity->isContainForeignEntityId(1);
	EXPECT_EQ(true, result);

	result = entity->isContainForeignEntityId(3);
	EXPECT_EQ(true, result);

	result = entity->isContainForeignEntityId(5);
	EXPECT_EQ(false, result);
}

// 測試 新增有foreignKey關係的EntityID
TEST_F(ERD_EntityTest, addForeignEntityId)
{
	// 測試
	// 參數:int(id)
	// 回傳:無
	// 附註:無
	entity->addForeignEntityId(1);
	entity->addForeignEntityId(3);
	vector<int> resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(2, resultVector.size());
}

// 測試 取得foreignKey關係的EntityID Vector
TEST_F(ERD_EntityTest, getForeignEntityIdVector)
{
	// 測試
	// 參數:無
	// 回傳:vector<int>
	// 附註:無
	entity->addForeignEntityId(1);
	vector<int> resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(1, resultVector.size());
	entity->addForeignEntityId(3);
	resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(2, resultVector.size());
}

// 測試 克隆
TEST_F(ERD_EntityTest, clone)
{
	// 測試
	// 參數:無
	// 回傳:ERD_Component*
	// 附註:無
	ERD_Entity* entityClone = (ERD_Entity*)entity->clone();
	EXPECT_EQ(entity->getId(), entityClone->getId());
	EXPECT_EQ(entity->getType(), entityClone->getType());
	EXPECT_EQ(entity->getText(), entityClone->getText());
	EXPECT_EQ(entity->getConnections(), entityClone->getConnections());
	EXPECT_EQ(entity->getForeignEntityIdVector(), entityClone->getForeignEntityIdVector());
}