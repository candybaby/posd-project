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

// ���� �غc�l
TEST_F(ERD_RelationshipTest, ERD_Relationship)
{
	// ����
	// �Ѽ�:�L
	// �^��:�L
	// ����:�L
	relationship = new ERD_Relationship();
	EXPECT_EQ(ERD_Component::Relationship, relationship->getType());
}

// ���� �P�_�O�_�i�s
TEST_F(ERD_RelationshipTest, canConnectTo)
{
	// ����
	// �Ѽ�:ERD_Component*(entity)
	// �^��:bool
	// ����:�L
	bool result;
	result = relationship->canConnectTo(entityTest);
	EXPECT_EQ(true, result);

	result = relationship->canConnectTo(attributeTest);
	EXPECT_EQ(false, result);
}

// ���� �J��
TEST_F(ERD_RelationshipTest, clone)
{
	// ����
	// �Ѽ�:�L
	// �^��:ERD_Component*
	// ����:�L
	ERD_Relationship* relationshipClone = (ERD_Relationship*)relationship->clone();
	EXPECT_EQ(relationship->getId(), relationshipClone->getId());
	EXPECT_EQ(relationship->getType(), relationshipClone->getType());
	EXPECT_EQ(relationship->getText(), relationshipClone->getText());
	EXPECT_EQ(relationship->getConnections(), relationshipClone->getConnections());
}