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

// 代刚 篶
TEST_F(ERD_RelationshipTest, ERD_Relationship)
{
	// 代刚
	// 把计:礚
	// 肚:礚
	// 爹:礚
	relationship = new ERD_Relationship();
	EXPECT_EQ(ERD_Component::Relationship, relationship->getType());
}

// 代刚 耞琌硈
TEST_F(ERD_RelationshipTest, canConnectTo)
{
	// 代刚
	// 把计:ERD_Component*(entity)
	// 肚:bool
	// 爹:礚
	bool result;
	result = relationship->canConnectTo(entityTest);
	EXPECT_EQ(true, result);

	result = relationship->canConnectTo(attributeTest);
	EXPECT_EQ(false, result);
}

// 代刚 订
TEST_F(ERD_RelationshipTest, clone)
{
	// 代刚
	// 把计:礚
	// 肚:ERD_Component*
	// 爹:礚
	ERD_Relationship* relationshipClone = (ERD_Relationship*)relationship->clone();
	EXPECT_EQ(relationship->getId(), relationshipClone->getId());
	EXPECT_EQ(relationship->getType(), relationshipClone->getType());
	EXPECT_EQ(relationship->getText(), relationshipClone->getText());
	EXPECT_EQ(relationship->getConnections(), relationshipClone->getConnections());
}