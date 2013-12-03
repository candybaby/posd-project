#include "ER_Model.h"
#include "ER_SetPrimaryKeyCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_SetPrimaryKeyCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		model->addNode(ERD_Component::Attribute, "Name", 0);
		setPrimaryKeyCommand = new ER_SetPrimaryKeyCommand(model, 0, true);
	}

	virtual void TearDown()
	{
		delete setPrimaryKeyCommand;
		delete model;
	}

	ER_Model* model;
	ER_SetPrimaryKeyCommand* setPrimaryKeyCommand;
};

// 測試 執行
TEST_F(ER_SetPrimaryKeyCommandTest, execute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	ERD_Attribute* attrubite = (ERD_Attribute*)model->findComponentById(0);
	EXPECT_EQ(false, attrubite->getIsPrimaryKey());
	setPrimaryKeyCommand->execute();
	EXPECT_EQ(true, attrubite->getIsPrimaryKey());
}

// 測試 反操作
TEST_F(ER_SetPrimaryKeyCommandTest, unexecute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	ERD_Attribute* attrubite = (ERD_Attribute*)model->findComponentById(0);
	EXPECT_EQ(false, attrubite->getIsPrimaryKey());
	setPrimaryKeyCommand->execute();
	EXPECT_EQ(true, attrubite->getIsPrimaryKey());
	setPrimaryKeyCommand->unexecute();
	EXPECT_EQ(false, attrubite->getIsPrimaryKey());
}