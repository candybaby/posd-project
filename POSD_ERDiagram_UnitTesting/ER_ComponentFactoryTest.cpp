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

// 代刚 籹Node
TEST_F(ER_ComponentFactoryTest, createNodeComponent) {
	// 代刚
	// 把计:ComponentType(type), string(nodeName), int id
	// 肚:ERD_Component*
	// 爹:
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

// 代刚 籹Connection
TEST_F(ER_ComponentFactoryTest, createConnectionComponent) {
	// 代刚
	// 把计:ERD_Component*(component1), ERD_Component*(component2), int(id)
	// 肚:ERD_Component*
	// 爹:
	ERD_Component* component1 = componentFactory.createNodeComponent(ERD_Component::Entity, "Engineer", 0);
	ERD_Component* component2 = componentFactory.createNodeComponent(ERD_Component::Attribute, "Name", 1);
	ERD_Component* result = componentFactory.createConnectionComponent(component1, component2, 2);
	EXPECT_EQ(2, result->getId());
	EXPECT_EQ("", result->getText());
	EXPECT_EQ(ERD_Component::Connection, result->getType());

	// 代刚
	// 把计:ERD_Component*(component1), ERD_Component*(component2), int(id), ConnectionCardinality(cardinality)
	// 肚:ERD_Component*
	// 爹:
	result = componentFactory.createConnectionComponent(component1, component2, 2, ERD_Connection::one);
	EXPECT_EQ(2, result->getId());
	EXPECT_EQ("1", result->getText());
	EXPECT_EQ(ERD_Component::Connection, result->getType());
}