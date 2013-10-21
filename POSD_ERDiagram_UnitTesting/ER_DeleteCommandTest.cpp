#include "ER_Model.h"
#include "ER_DeleteCommand.h"
#include "gtest/gtest.h"

using namespace std;
class ER_DeleteCommandTest : public ::testing::Test
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
		model->addConnection(0, 1, 5);
		model->addConnection(2, 3, 6);
		model->addConnection(0, 4, 7, ERD_Connection::one);
		model->addConnection(2, 4, 8, ERD_Connection::one);
		model->addNode(ERD_Component::Entity, "Simple", 9);

		deleteEntityCommand = new ER_DeleteCommand(model, 2);
		deleteAttributeCommand = new ER_DeleteCommand(model, 3);
		deleteRelationshipCommand = new ER_DeleteCommand(model, 4);
		deleteConnectionCommand = new ER_DeleteCommand(model, 5);
		deleteSimpleComponentCommand = new ER_DeleteCommand(model, 9);
		deleteNullComponentCommand = new ER_DeleteCommand(model, 10);
	}

	virtual void TearDown()
	{
		delete deleteEntityCommand;
		delete deleteAttributeCommand;
		delete deleteRelationshipCommand;
		delete deleteConnectionCommand;
		delete deleteSimpleComponentCommand;
		delete deleteNullComponentCommand;
		delete model;
	}

	ER_Model* model;
	ER_DeleteCommand* deleteEntityCommand;
	ER_DeleteCommand* deleteAttributeCommand;
	ER_DeleteCommand* deleteRelationshipCommand;
	ER_DeleteCommand* deleteConnectionCommand;
	ER_DeleteCommand* deleteSimpleComponentCommand;
	ER_DeleteCommand* deleteNullComponentCommand;
};

// 測試 找指定id的component
TEST_F(ER_DeleteCommandTest, findComponentById)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	ERD_Component* result = deleteEntityCommand->findComponentById(0);
	EXPECT_EQ(0, result->getId());
	EXPECT_EQ(ERD_Component::Entity, result->getType());
	EXPECT_EQ("Engineer", result->getText());
}

// 測試 刪除指定id的物件
TEST_F(ER_DeleteCommandTest, deleteComponentById)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	EXPECT_EQ(10, model->getComponents().size());
	bool result = deleteEntityCommand->deleteComponentById(0);
	EXPECT_EQ(true, result);
	EXPECT_EQ(9, model->getComponents().size());

	EXPECT_EQ(9, model->getComponents().size());
	result = deleteEntityCommand->deleteComponentById(10);
	EXPECT_EQ(false, result);
	EXPECT_EQ(9, model->getComponents().size());
}

// 測試 清除暫存資料
TEST_F(ER_DeleteCommandTest, clearTempData)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	deleteEntityCommand->execute();
	EXPECT_EQ(2, deleteEntityCommand->relatedComponents.size());
	deleteEntityCommand->clearTempData();
	EXPECT_EQ(0, deleteEntityCommand->relatedComponents.size());

	deleteSimpleComponentCommand->execute();
	EXPECT_EQ(0, deleteSimpleComponentCommand->relatedComponents.size());
	deleteSimpleComponentCommand->clearTempData();
	EXPECT_EQ(0, deleteSimpleComponentCommand->relatedComponents.size());
}

// 測試 執行
TEST_F(ER_DeleteCommandTest, execute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	EXPECT_EQ(10, model->getComponents().size());
	deleteEntityCommand->execute();              //相連的連線也刪除
	EXPECT_EQ(7, model->getComponents().size());
	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteAttributeCommand->execute();              //相連的連線也刪除
	EXPECT_EQ(8, model->getComponents().size());
	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteRelationshipCommand->execute();              //相連的連線也刪除
	EXPECT_EQ(7, model->getComponents().size());

	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteSimpleComponentCommand->execute();   
	EXPECT_EQ(9, model->getComponents().size());
	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteNullComponentCommand->execute();   
	EXPECT_EQ(10, model->getComponents().size());
}

// 測試 反操作
TEST_F(ER_DeleteCommandTest, unexecute)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	EXPECT_EQ(10, model->getComponents().size());//刪除entity復原
	deleteEntityCommand->execute();              //相連的連線也刪除
	EXPECT_EQ(7, model->getComponents().size());
	deleteEntityCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());
	deleteEntityCommand->execute(); 
	EXPECT_EQ(7, model->getComponents().size());
	deleteEntityCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());

	EXPECT_EQ(10, model->getComponents().size());//刪除attribute復原
	deleteAttributeCommand->execute();           //相連的連線也刪除
	EXPECT_EQ(8, model->getComponents().size());
	deleteAttributeCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());
	deleteAttributeCommand->execute();           //相連的連線也刪除
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //刪除relationship復原
	deleteRelationshipCommand->execute();         //相連的連線也刪除
	EXPECT_EQ(5, model->getComponents().size());
	deleteRelationshipCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //刪除simole component 復原
	deleteSimpleComponentCommand->execute();
	EXPECT_EQ(7, model->getComponents().size());
	deleteSimpleComponentCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //刪除connection 復原
	deleteConnectionCommand->execute();
	EXPECT_EQ(7, model->getComponents().size());
	deleteConnectionCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());
}