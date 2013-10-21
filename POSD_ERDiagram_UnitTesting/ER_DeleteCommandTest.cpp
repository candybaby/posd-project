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

// ���� ����wid��component
TEST_F(ER_DeleteCommandTest, findComponentById)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	ERD_Component* result = deleteEntityCommand->findComponentById(0);
	EXPECT_EQ(0, result->getId());
	EXPECT_EQ(ERD_Component::Entity, result->getType());
	EXPECT_EQ("Engineer", result->getText());
}

// ���� �R�����wid������
TEST_F(ER_DeleteCommandTest, deleteComponentById)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	EXPECT_EQ(10, model->getComponents().size());
	bool result = deleteEntityCommand->deleteComponentById(0);
	EXPECT_EQ(true, result);
	EXPECT_EQ(9, model->getComponents().size());

	EXPECT_EQ(9, model->getComponents().size());
	result = deleteEntityCommand->deleteComponentById(10);
	EXPECT_EQ(false, result);
	EXPECT_EQ(9, model->getComponents().size());
}

// ���� �M���Ȧs���
TEST_F(ER_DeleteCommandTest, clearTempData)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	deleteEntityCommand->execute();
	EXPECT_EQ(2, deleteEntityCommand->relatedComponents.size());
	deleteEntityCommand->clearTempData();
	EXPECT_EQ(0, deleteEntityCommand->relatedComponents.size());

	deleteSimpleComponentCommand->execute();
	EXPECT_EQ(0, deleteSimpleComponentCommand->relatedComponents.size());
	deleteSimpleComponentCommand->clearTempData();
	EXPECT_EQ(0, deleteSimpleComponentCommand->relatedComponents.size());
}

// ���� ����
TEST_F(ER_DeleteCommandTest, execute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	EXPECT_EQ(10, model->getComponents().size());
	deleteEntityCommand->execute();              //�۳s���s�u�]�R��
	EXPECT_EQ(7, model->getComponents().size());
	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteAttributeCommand->execute();              //�۳s���s�u�]�R��
	EXPECT_EQ(8, model->getComponents().size());
	TearDown();

	SetUp();
	EXPECT_EQ(10, model->getComponents().size());
	deleteRelationshipCommand->execute();              //�۳s���s�u�]�R��
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

// ���� �Ͼާ@
TEST_F(ER_DeleteCommandTest, unexecute)
{
	// ����
	// �Ѽ�:�L
	// �^��:""
	// ����:�L
	EXPECT_EQ(10, model->getComponents().size());//�R��entity�_��
	deleteEntityCommand->execute();              //�۳s���s�u�]�R��
	EXPECT_EQ(7, model->getComponents().size());
	deleteEntityCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());
	deleteEntityCommand->execute(); 
	EXPECT_EQ(7, model->getComponents().size());
	deleteEntityCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());

	EXPECT_EQ(10, model->getComponents().size());//�R��attribute�_��
	deleteAttributeCommand->execute();           //�۳s���s�u�]�R��
	EXPECT_EQ(8, model->getComponents().size());
	deleteAttributeCommand->unexecute();
	EXPECT_EQ(10, model->getComponents().size());
	deleteAttributeCommand->execute();           //�۳s���s�u�]�R��
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //�R��relationship�_��
	deleteRelationshipCommand->execute();         //�۳s���s�u�]�R��
	EXPECT_EQ(5, model->getComponents().size());
	deleteRelationshipCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //�R��simole component �_��
	deleteSimpleComponentCommand->execute();
	EXPECT_EQ(7, model->getComponents().size());
	deleteSimpleComponentCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());

	EXPECT_EQ(8, model->getComponents().size());  //�R��connection �_��
	deleteConnectionCommand->execute();
	EXPECT_EQ(7, model->getComponents().size());
	deleteConnectionCommand->unexecute();
	EXPECT_EQ(8, model->getComponents().size());
}