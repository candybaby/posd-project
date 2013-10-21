#include "ER_ComponentFactory.h"
#include "gtest/gtest.h"

using namespace std;
class ER_ComponentFactoryTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
	ER_ComponentFactory componentFactory;
};

// ���� �s�@Node
TEST_F(ER_ComponentFactoryTest, createNodeComponent) {
	// ����
	// �Ѽ�:ComponentType(type), string(nodeName), int id
	// �^��:ERD_Component*
	// ����:
	ERD_Component* result = componentFactory.createNodeComponent(ERD_Component::Entity, "Engineer", 0);
	EXPECT_EQ(0, result->getId());
	EXPECT_EQ("Engineer", result->getText());
	EXPECT_EQ(ERD_Component::Entity, result->getType());

	result = componentFactory.createNodeComponent(ERD_Component::Attribute, "Name", 1);
	EXPECT_EQ(1, result->getId());
	EXPECT_EQ("Name", result->getText());
	EXPECT_EQ(ERD_Component::Attribute, result->getType());

	result = componentFactory.createNodeComponent(ERD_Component::Relationship, "Has", 2);
	EXPECT_EQ(2, result->getId());
	EXPECT_EQ("Has", result->getText());
	EXPECT_EQ(ERD_Component::Relationship, result->getType());

	result = componentFactory.createNodeComponent(ERD_Component::Connection, "", 3);
	EXPECT_EQ(NULL, result);
}

// ���� �s�@Connection
TEST_F(ER_ComponentFactoryTest, createConnectionComponent) {
	// ����
	// �Ѽ�:ERD_Component*(component1), ERD_Component*(component2), int(id)
	// �^��:ERD_Component*
	// ����:
	ERD_Component* component1 = componentFactory.createNodeComponent(ERD_Component::Entity, "Engineer", 0);
	ERD_Component* component2 = componentFactory.createNodeComponent(ERD_Component::Attribute, "Name", 1);
	ERD_Component* result = componentFactory.createConnectionComponent(component1, component2, 2);
	EXPECT_EQ(2, result->getId());
	EXPECT_EQ("", result->getText());
	EXPECT_EQ(ERD_Component::Connection, result->getType());

	// ����
	// �Ѽ�:ERD_Component*(component1), ERD_Component*(component2), int(id), ConnectionCardinality(cardinality)
	// �^��:ERD_Component*
	// ����:
	result = componentFactory.createConnectionComponent(component1, component2, 2, ERD_Connection::one);
	EXPECT_EQ(2, result->getId());
	EXPECT_EQ("1", result->getText());
	EXPECT_EQ(ERD_Component::Connection, result->getType());
}