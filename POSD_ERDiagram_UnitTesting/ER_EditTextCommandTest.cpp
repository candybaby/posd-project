#include "ER_Model.h"
#include "ER_EditTextCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_EditTextCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		model->addNode(ERD_Component::Entity, "Engineer", 0);
		editTextCommand = new ER_EditTextCommand(model, 0, "PC");
	}

	virtual void TearDown()
	{
		delete editTextCommand;
		delete model;
	}

	ER_Model* model;
	ER_EditTextCommand* editTextCommand;
};

// ���� ����
TEST_F(ER_EditTextCommandTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());

	editTextCommand->unexecute();
	EXPECT_EQ("Engineer", model->findComponentById(0)->getText());

	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());
}

// ���� �Ͼާ@
TEST_F(ER_EditTextCommandTest, unexecute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());

	editTextCommand->unexecute();
	EXPECT_EQ("Engineer", model->findComponentById(0)->getText());

	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());
}