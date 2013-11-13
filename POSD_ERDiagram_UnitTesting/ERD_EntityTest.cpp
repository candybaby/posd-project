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

// ���� �غc�l
TEST_F(ERD_EntityTest, ERD_Entity)
{
	// ����
	// �Ѽ�:�L
	// �^��:�L
	// ����:�L
	entity = new ERD_Entity();
	EXPECT_EQ(ERD_Component::Entity, entity->getType());
}

// ���� �P�_�O�_�i�s
TEST_F(ERD_EntityTest, canConnectTo)
{
	// ����
	// �Ѽ�:ERD_Component*(entity)
	// �^��:bool
	// ����:�L
	bool result;
	result = entity->canConnectTo(entityTest);
	EXPECT_EQ(false, result);

	result = entity->canConnectTo(attributeTest);
	EXPECT_EQ(true, result);

	result = entity->canConnectTo(relationshipTest);
	EXPECT_EQ(true, result);
}

// ���� ���o�O�_���]�t�P��entity��foreignKey���Y��EntityID
TEST_F(ERD_EntityTest, isContainForeignEntityId)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:bool
	// ����:�L
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

// ���� �s�W��foreignKey���Y��EntityID
TEST_F(ERD_EntityTest, addForeignEntityId)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:�L
	// ����:�L
	entity->addForeignEntityId(1);
	entity->addForeignEntityId(3);
	vector<int> resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(2, resultVector.size());
}

// ���� ���oforeignKey���Y��EntityID Vector
TEST_F(ERD_EntityTest, getForeignEntityIdVector)
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>
	// ����:�L
	entity->addForeignEntityId(1);
	vector<int> resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(1, resultVector.size());
	entity->addForeignEntityId(3);
	resultVector = entity->getForeignEntityIdVector();
	EXPECT_EQ(2, resultVector.size());
}

// ���� �J��
TEST_F(ERD_EntityTest, clone)
{
	// ����
	// �Ѽ�:�L
	// �^��:ERD_Component*
	// ����:�L
	ERD_Entity* entityClone = (ERD_Entity*)entity->clone();
	EXPECT_EQ(entity->getId(), entityClone->getId());
	EXPECT_EQ(entity->getType(), entityClone->getType());
	EXPECT_EQ(entity->getText(), entityClone->getText());
	EXPECT_EQ(entity->getConnections(), entityClone->getConnections());
	EXPECT_EQ(entity->getForeignEntityIdVector(), entityClone->getForeignEntityIdVector());
}