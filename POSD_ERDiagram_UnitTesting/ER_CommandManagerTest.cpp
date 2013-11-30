#include "ER_CommandManager.h"
#include "gtest/gtest.h"
#include "ER_AddCommand.h"

using namespace std;
class ER_CommandManagerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
		cmdManager = new ER_CommandManager(model);
	}

	virtual void TearDown()
	{
		cmdManager->~ER_CommandManager();
	}
	ER_Model* model;
	ER_CommandManager* cmdManager;
};

// ���� ����
TEST_F(ER_CommandManagerTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:string(id)
	// ����:�L

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Entity, "Engineer", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Attribute, "Name", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());

	cmdManager->undo();
	EXPECT_EQ(1, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Attribute, "Emp_Id", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());

	
}

// ���� redo
TEST_F(ER_CommandManagerTest, redo)
{
	// ����
	// �Ѽ�:�L
	// �^��:bool
	// ����:�L
	bool result;
	result = cmdManager->redo();
	EXPECT_EQ(false, result);

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Entity, "Engineer", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Attribute, "Name", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());

	cmdManager->undo();
	EXPECT_EQ(1, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	result = cmdManager->redo();
	EXPECT_EQ(true, result);
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());

	result = cmdManager->redo();
	EXPECT_EQ(false, result);
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());
}

// ���� undo
TEST_F(ER_CommandManagerTest, undo)
{
	// ����
	// �Ѽ�:�L
	// �^��:bool
	// ����:�L
	bool result;
	result = cmdManager->undo();
	EXPECT_EQ(false, result);

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Entity, "Engineer", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	cmdManager->execute(new ER_AddCommand(model, ERD_Component::Attribute, "Name", 0, 0));
	EXPECT_EQ(0, cmdManager->getRedoStackCount());
	EXPECT_EQ(2, cmdManager->getUndoStackCount());

	result = cmdManager->undo();
	EXPECT_EQ(true, result);
	EXPECT_EQ(1, cmdManager->getRedoStackCount());
	EXPECT_EQ(1, cmdManager->getUndoStackCount());

	result = cmdManager->undo();
	EXPECT_EQ(true, result);
	EXPECT_EQ(2, cmdManager->getRedoStackCount());
	EXPECT_EQ(0, cmdManager->getUndoStackCount());

	result = cmdManager->undo();
	EXPECT_EQ(false, result);
	EXPECT_EQ(2, cmdManager->getRedoStackCount());
	EXPECT_EQ(0, cmdManager->getUndoStackCount());

}