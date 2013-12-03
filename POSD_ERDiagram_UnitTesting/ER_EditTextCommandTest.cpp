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

// 測試 執行
TEST_F(ER_EditTextCommandTest, execute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());

	editTextCommand->unexecute();
	EXPECT_EQ("Engineer", model->findComponentById(0)->getText());

	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());
}

// 測試 反操作
TEST_F(ER_EditTextCommandTest, unexecute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());

	editTextCommand->unexecute();
	EXPECT_EQ("Engineer", model->findComponentById(0)->getText());

	editTextCommand->execute();
	EXPECT_EQ("PC", model->findComponentById(0)->getText());
}