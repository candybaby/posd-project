#include "ER_Model.h"
#include "ER_MoveCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_MoveCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		model->addNode(ERD_Component::Entity, "Engineer", 0);
		model->addNode(ERD_Component::Attribute, "Name", 1);
		moveCommand = new ER_MoveCommand(model, "0", 100, 50);
		moveCommandMoreNodes = new ER_MoveCommand(model, "0,1", 200, 400);
	}

	virtual void TearDown()
	{
		delete moveCommand;
		delete moveCommandMoreNodes;
		delete model;
	}

	ER_Model* model;
	ER_MoveCommand* moveCommand;
	ER_MoveCommand* moveCommandMoreNodes;
};

// ���� ����
TEST_F(ER_MoveCommandTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	EXPECT_EQ(0, model->findComponentById(0)->getPosX());
	EXPECT_EQ(0, model->findComponentById(0)->getPosY());

	moveCommand->execute();
	EXPECT_EQ(100, model->findComponentById(0)->getPosX());
	EXPECT_EQ(50, model->findComponentById(0)->getPosY());

	EXPECT_EQ(0, model->findComponentById(1)->getPosX());
	EXPECT_EQ(0, model->findComponentById(1)->getPosY());

	moveCommandMoreNodes->execute();
	EXPECT_EQ(300, model->findComponentById(0)->getPosX());
	EXPECT_EQ(450, model->findComponentById(0)->getPosY());

	EXPECT_EQ(200, model->findComponentById(1)->getPosX());
	EXPECT_EQ(400, model->findComponentById(1)->getPosY());
}

// ���� �Ͼާ@
TEST_F(ER_MoveCommandTest, unexecute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	EXPECT_EQ(0, model->findComponentById(0)->getPosX());
	EXPECT_EQ(0, model->findComponentById(0)->getPosY());

	moveCommand->execute();
	EXPECT_EQ(100, model->findComponentById(0)->getPosX());
	EXPECT_EQ(50, model->findComponentById(0)->getPosY());

	moveCommand->unexecute();
	EXPECT_EQ(0, model->findComponentById(0)->getPosX());
	EXPECT_EQ(0, model->findComponentById(0)->getPosY());

	moveCommandMoreNodes->execute();
	EXPECT_EQ(200, model->findComponentById(0)->getPosX());
	EXPECT_EQ(400, model->findComponentById(0)->getPosY());
	EXPECT_EQ(200, model->findComponentById(1)->getPosX());
	EXPECT_EQ(400, model->findComponentById(1)->getPosY());

	moveCommandMoreNodes->unexecute();
	EXPECT_EQ(0, model->findComponentById(0)->getPosX());
	EXPECT_EQ(0, model->findComponentById(0)->getPosY());
	EXPECT_EQ(0, model->findComponentById(1)->getPosX());
	EXPECT_EQ(0, model->findComponentById(1)->getPosY());
}