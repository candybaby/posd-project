#include "ER_Model.h"
#include "ER_AddCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_AddCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		addCommand = new ER_AddCommand(model, ERD_Component::Entity, "Engineer", 0, 0);
	}

	virtual void TearDown()
	{
		delete addCommand;
		delete model;
	}

	ER_Model* model;
	ER_AddCommand* addCommand;
};

// ���� ����
TEST_F(ER_AddCommandTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:string(id)
	// ����:�L
	string result;
	result = addCommand->execute();
	EXPECT_EQ(1, model->getComponents().size());
	EXPECT_EQ(ERD_Component::Entity, model->findComponentById(0)->getType());
	EXPECT_EQ("0", result);

	addCommand->unexecute();
	EXPECT_EQ(0, model->getComponents().size());

	addCommand->execute();
	EXPECT_EQ(1, model->getComponents().size());
	EXPECT_EQ(ERD_Component::Entity, model->findComponentById(0)->getType());
	EXPECT_EQ("0", result);
}

// ���� �Ͼާ@
TEST_F(ER_AddCommandTest, unexecute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	addCommand->execute();
	EXPECT_EQ(1, model->getComponents().size());

	addCommand->unexecute();
	EXPECT_EQ(0, model->getComponents().size());

	addCommand->execute();
	EXPECT_EQ(1, model->getComponents().size());

	addCommand->unexecute();
	EXPECT_EQ(0, model->getComponents().size());
}