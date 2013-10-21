#include "ER_Model.h"
#include "ER_ConnectCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_ConnectCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		model->addNode(ERD_Component::Entity, "Engineer", 0);
		model->addNode(ERD_Component::Attribute, "Engineer_ID", 1);
		model->addNode(ERD_Component::Entity, "PC", 2);
		model->addNode(ERD_Component::Attribute, "PC_ID", 3);
		model->addNode(ERD_Component::Relationship, "Has", 4);
		connectCommand = new ER_ConnectCommand(model, 0, 1, 5);
		connectWithCardinalityCommand = new ER_ConnectCommand(model, 2, 4, 6, ERD_Connection::one);
	}

	virtual void TearDown()
	{
		delete connectWithCardinalityCommand;
		delete connectCommand;
		delete model;
	}

	ER_Model* model;
	ER_ConnectCommand* connectCommand;
	ER_ConnectCommand* connectWithCardinalityCommand;
};

// ���� ����
TEST_F(ER_ConnectCommandTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	connectCommand->execute();
	EXPECT_EQ(6, model->getComponents().size());
	EXPECT_EQ(ERD_Connection::Connection, model->findComponentById(5)->getType());//5 is id
	EXPECT_EQ("", model->findComponentById(5)->getText());  

	connectWithCardinalityCommand->execute();
	EXPECT_EQ(7, model->getComponents().size());
	EXPECT_EQ(ERD_Connection::Connection, model->findComponentById(6)->getType());//6 is id
	EXPECT_EQ("1", model->findComponentById(6)->getText());
}

// ���� �Ͼާ@
TEST_F(ER_ConnectCommandTest, unexecute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	connectCommand->execute();
	connectWithCardinalityCommand->execute();

	connectWithCardinalityCommand->unexecute();
	EXPECT_EQ(6, model->getComponents().size());
	EXPECT_EQ(NULL, model->findComponentById(6));//6 is id

	connectCommand->unexecute();
	EXPECT_EQ(5, model->getComponents().size());
	EXPECT_EQ(NULL, model->findComponentById(5));//5 is id
}