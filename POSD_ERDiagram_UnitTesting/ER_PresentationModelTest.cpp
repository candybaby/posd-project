#include "ER_PresentationModel.h"
#include "gtest/gtest.h"

using namespace std;
class ER_PresentationModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model();
		presentationModel = new ER_PresentationModel(model);
	}

	virtual void TearDown()
	{
		delete presentationModel;
		delete model;
	}

	void makeTestData()
	{
		presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
		presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
		presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
		presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
		presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
		presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
		presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
		presentationModel->addConnection(0, 4, ERD_Connection::one);
		presentationModel->addConnection(4, 5, ERD_Connection::one);
		presentationModel->addConnection(0, 1, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(0, 2, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(0, 3, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(5, 6, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->addConnection(5, 7, ERD_Connection::SIZE_OF_Cardinality);
		presentationModel->setIsPrimaryKey(1, true);
		presentationModel->setIsPrimaryKey(2, true);
		presentationModel->setIsPrimaryKey(6, true);

	}

	ER_Model* model;
	ER_PresentationModel* presentationModel;
};

// ���� �s�WNode�ɿ�J�PType����������
TEST_F(ER_PresentationModelTest, addNodeOptionMapping)
{
	// ����
	// �Ѽ�:string(command)
	// �^��:int(result)
	// ����:�L
	int result;
	result = presentationModel->addNodeOptionMapping("A");
	EXPECT_EQ(0, result);

	result = presentationModel->addNodeOptionMapping("E");
	EXPECT_EQ(1, result);

	result = presentationModel->addNodeOptionMapping("R");
	EXPECT_EQ(2, result);

	result = presentationModel->addNodeOptionMapping("");  //�ҥ~���p
	EXPECT_EQ(-1, result);
}

// ���� �s�W�`�I
TEST_F(ER_PresentationModelTest, addNode)
{
	// ����
	// �Ѽ�:ComponentType(componentType), string(nodeName)
	// �^��:string
	// ����:�L
	string result;
	result = presentationModel->addNode(ERD_Component::Entity, "Engineer");
	EXPECT_EQ("0", result);
	result = presentationModel->addNode(ERD_Component::Entity, "PC");
	EXPECT_EQ("1", result);
	EXPECT_EQ(2, presentationModel->getCurrentId());
}

// ���� ���o�{�b��ID
TEST_F(ER_PresentationModelTest, getCurrentId)
{
	// ����
	// �Ѽ�:�L
	// �^��:int
	// ����:�L
	int result;
	result = presentationModel->getCurrentId();
	EXPECT_EQ(0, result);
	presentationModel->addNode(ERD_Component::Entity, "Engineer");

	result = presentationModel->getCurrentId();
	EXPECT_EQ(1, result);

	presentationModel->addNode(ERD_Component::Entity, "PC");
	result = presentationModel->getCurrentId();
	EXPECT_EQ(2, result);
}

// ���� ���oID�ǥ�index
TEST_F(ER_PresentationModelTest, getIdByIndex)
{
	// ����
	// �Ѽ�:int(index)
	// �^��:int(id)
	// ����:�L
	makeTestData();
	int result;
	result = presentationModel->getIdByIndex(0);
	EXPECT_EQ(0, result);

	result = presentationModel->getIdByIndex(14);
	EXPECT_EQ(14, result);

	result = presentationModel->getIdByIndex(15);
	EXPECT_EQ(-1, result);

	result = presentationModel->getIdByIndex(-1);
	EXPECT_EQ(-1, result);
}

// ���� ���oconnection(by ID)�s����ݪ�ID�HnodeNumber�ӰϤ�0 1
TEST_F(ER_PresentationModelTest, getConnectionNodeById)
{
	// ����
	// �Ѽ�:int(id), int(nodeNumber)
	// �^��:int(id)
	// ����:�L
	makeTestData();
	int result;
	result = presentationModel->getConnectionNodeById(8, 0);
	EXPECT_EQ(0, result);
	result = presentationModel->getConnectionNodeById(8, 1);
	EXPECT_EQ(4, result);

	result = presentationModel->getConnectionNodeById(14, 0);
	EXPECT_EQ(5, result);
	result = presentationModel->getConnectionNodeById(14, 1);
	EXPECT_EQ(7, result);

	result = presentationModel->getConnectionNodeById(15, 0); // �S����ID
	EXPECT_EQ(-1, result);
	result = presentationModel->getConnectionNodeById(7, 1);  // ��ID���ݩ�Connection
	EXPECT_EQ(-1, result);
}

// ���� ���otext�����ǥ�id
TEST_F(ER_PresentationModelTest, getNameById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string(name)
	// ����:�L
	makeTestData();
	string result;
	result = presentationModel->getNameById(0);
	EXPECT_EQ("Engineer", result);

	result = presentationModel->getNameById(1);
	EXPECT_EQ("EmpID", result);

	result = presentationModel->getNameById(4);
	EXPECT_EQ("Has", result);

	result = presentationModel->getNameById(8);
	EXPECT_EQ("1", result);

	result = presentationModel->getNameById(10);
	EXPECT_EQ("", result);

	result = presentationModel->getNameById(-1);
	EXPECT_EQ("", result);

	result = presentationModel->getNameById(15);
	EXPECT_EQ("", result);
}

// ���� ���oType�ǥ�id
TEST_F(ER_PresentationModelTest, getTypeById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:ComponentType
	// ����:�L
	makeTestData();
	ERD_Component::ComponentType result;
	result = presentationModel->getTypeById(0);
	EXPECT_EQ(ERD_Component::Entity, result);

	result = presentationModel->getTypeById(1);
	EXPECT_EQ(ERD_Component::Attribute, result);

	result = presentationModel->getTypeById(4);
	EXPECT_EQ(ERD_Component::Relationship, result);

	result = presentationModel->getTypeById(8);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = presentationModel->getTypeById(10);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = presentationModel->getTypeById(-1);
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);

	result = presentationModel->getTypeById(15);
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);
}

// ���� �s�u�T��
TEST_F(ER_PresentationModelTest, getAddConnectionMessage)
{
	// ����
	// �Ѽ�:int,int
	// �^��:string(message)
	// ����:�L
	presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
	presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
	presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
	presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
	presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
	presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
	presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
	presentationModel->addConnection(0, 4, ERD_Connection::one);
	string result;
	result = presentationModel->getAddConnectionMessage(0, 4);  //�w�s�u
	EXPECT_EQ("The node '0' has already been connected to component '4'.", result);

	result = presentationModel->getAddConnectionMessage(0, 0);  //�P�@��Node
	EXPECT_EQ("The node '0' cannot be connected to itself.", result);

	result = presentationModel->getAddConnectionMessage(4, 5);  //ASK_CARDINALITY_STATE
	EXPECT_EQ("ask cardinality", result);

	result = presentationModel->getAddConnectionMessage(6, 7);  //����s�u
	EXPECT_EQ("The node '7' cannot be connected by the node '6'.", result);

	EXPECT_EQ(9, presentationModel->getCurrentId());

	result = presentationModel->getAddConnectionMessage(5, 6);  //�i�H�s�u �ós�u
	EXPECT_EQ("The node '5' has been connected to the node '6'.", result);
	EXPECT_EQ(10, presentationModel->getCurrentId());
}

// ���� �^�Ǥ���s�u���T��
TEST_F(ER_PresentationModelTest, getCannotConnectMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
	string result;
	result = presentationModel->getCannotConnectMessage("0", "1");
	EXPECT_EQ("The node '0' cannot be connected by the node '1'.", result);
}

// ���� �^�Ǥ@��Node�s�u���~���T��
TEST_F(ER_PresentationModelTest, getSameNodeMessage)
{
	// ����
	// �Ѽ�:string
	// �^��:string(message)
	// ����:�L
	string result;
	result = presentationModel->getSameNodeMessage("0");
	EXPECT_EQ("The node '0' cannot be connected to itself.", result);
}

// ���� �^�ǻݭnCardinary��T���T��
TEST_F(ER_PresentationModelTest, getAskCardinaryStateMessage)
{
	// ����
	// �Ѽ�:�L
	// �^��:string(message)
	// ����:�L
	string result;
	result = presentationModel->getAskCardinaryStateMessage();
	EXPECT_EQ("ask cardinality", result);
}

// ���� �^�Ǥw�g�s�u���T��
TEST_F(ER_PresentationModelTest, getAlreadyConnectedMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
	string result;
	result = presentationModel->getAlreadyConnectedMessage("0", "1");
	EXPECT_EQ("The node '0' has already been connected to component '1'.", result);
}

// ���� �^�Ǧ��\�s�u���T��
TEST_F(ER_PresentationModelTest, getNodeConnectedMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
	string result;
	result = presentationModel->getNodeConnectedMessage("0", "1");
	EXPECT_EQ("The node '0' has been connected to the node '1'.", result);
}

// ���� �s�W�s�u
TEST_F(ER_PresentationModelTest, addConnection)
{
	// ����
	// �Ѽ�:int, int, ConnectionCardinality
	// �^��:string(message)
	// ����:�L
	presentationModel->addNode(ERD_Component::Entity, "Engineer");  //id=0
	presentationModel->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	presentationModel->addNode(ERD_Component::Attribute, "Name");   //id=2
	presentationModel->addNode(ERD_Component::Attribute, "Department");   //id=3
	presentationModel->addNode(ERD_Component::Relationship, "Has");   //id=4
	presentationModel->addNode(ERD_Component::Entity, "PC");  //id=5
	presentationModel->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
	presentationModel->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
	string result;
	result = presentationModel->addConnection(0, 4, ERD_Connection::one);
	EXPECT_EQ("The node '0' has been connected to the node '4'.\nIts cardinality of the relationship is '1'.", result);
}

// ���� �P�_idStr�O���O�w�s�b��componentId
TEST_F(ER_PresentationModelTest, isExistComponentId)
{
	// ����
	// �Ѽ�:string
	// �^��:bool
	// ����:�L
	makeTestData();
	bool result;
	result = presentationModel->isExistComponentId("0");
	EXPECT_EQ(true, result);

	result = presentationModel->isExistComponentId("14");
	EXPECT_EQ(true, result);

	result = presentationModel->isExistComponentId("15");
	EXPECT_EQ(false, result);
}

// ���� �P�_entityId�O���OEntity
TEST_F(ER_PresentationModelTest, checkEntitySelectedValid)
{
	// ����
	// �Ѽ�:string
	// �^��:string
	// ����:�L
	makeTestData();
	string result;
	result = presentationModel->checkEntitySelectedValid("0");
	EXPECT_EQ("Find Right Entity", result);

	result = presentationModel->checkEntitySelectedValid("1");
	EXPECT_EQ("Not an Entity", result);

	result = presentationModel->checkEntitySelectedValid("15");
	EXPECT_EQ("Id Not Exist", result);
}

/* ���� �B�z�]�wprimaryKey���r��
TEST_F(ER_PresentationModelTest, checkAttributesSelectedValid)
{
	// ����
	// �Ѽ�:string, int
	// �^��:string
	// ����:�L
}*/

/* ���� �P�_Attribute�O���O�ݩ�S�wEntity��
TEST_F(ER_PresentationModelTest, isAttributeBelongEntity)
{
	// ����
	// �Ѽ�:int, int
	// �^��:bool
	// ����:�L
}*/

/* ���� �]�wid��PrimaryKey
TEST_F(ER_PresentationModelTest, setIsPrimaryKey)
{
	// ����
	// �Ѽ�:int, bool
	// �^��:�L
	// ����:�L
}*/

/* ���� ���oid�O�_��primaryKey
TEST_F(ER_PresentationModelTest, getIsPrimaryKey)
{
	// ����
	// �Ѽ�:id
	// �^��:bool
	// ����:�L
}*/

/* ���� ���oprimaryKey����ܦr��
TEST_F(ER_PresentationModelTest, getPrimaryKeyString)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string
	// ����:�L
}*/

/* ���� ��Node���X(���]�tconnection)
TEST_F(ER_PresentationModelTest, findNodes)
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>
	// ����:�L
}*/

/* ���� ��component���X(����)
TEST_F(ER_PresentationModelTest, findComponents)
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>
	// ����:�L
}*/

/* ���� ��targetId�P�S�wtype�۳s��NodeID(���]�tconnection)
TEST_F(ER_PresentationModelTest, findIdWithTypeByTargetId)
{
	// ����
	// �Ѽ�:ComponentType(type), int(id)
	// �^��:vector<int>
	// ����:�L
}*/

/* ���� ��S�w���A��component���X
TEST_F(ER_PresentationModelTest, findComponentsByType)
{
	// ����
	// �Ѽ�:ComponentType(type)
	// �^��:vector<int>
	// ����:�L
}*/

/* ���� �O�_�s�btable
TEST_F(ER_PresentationModelTest, isExistTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:bool
	// ����:�L
}*/

/* ���� ���o�S�wID��ForeignKey
TEST_F(ER_PresentationModelTest, getForeignKeyResult)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string
	// ����:�L
}*/

/* ���� �^�ǯS�wid��Attribute�r��
TEST_F(ER_PresentationModelTest, getAttributesForTable)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string
	// ����:�L
}*/

/* ���� �s�@primaryKey�r��
TEST_F(ER_PresentationModelTest, makePrimaryKeyString)
{
	// ����
	// �Ѽ�:int, string
	// �^��:string
	// ����:�L
}*/

/* ���� �s�@result�r��
TEST_F(ER_PresentationModelTest, makeResultString)
{
	// ����
	// �Ѽ�:int, string, string
	// �^��:string
	// ����:�L
}*/

/* ���� ��X��1��1���Y��entity
TEST_F(ER_PresentationModelTest, findOneByOneEntity)
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>
	// ����:�L
}*/

/* ���� �^��table�r��
TEST_F(ER_PresentationModelTest, getTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� Ū��
TEST_F(ER_PresentationModelTest, readComponentsFile)
{
	// ����
	// �Ѽ�:string
	// �^��:string
	// ����:�L
}*/

/* ���� �s��
TEST_F(ER_PresentationModelTest, storeComponents)
{
	// ����
	// �Ѽ�:string
	// �^��:string
	// ����:�L
}*/

/* ���� �^��connection�r��
TEST_F(ER_PresentationModelTest, getConnectionsTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� �^��node�r��
TEST_F(ER_PresentationModelTest, getNodesTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� �^��component�r��
TEST_F(ER_PresentationModelTest, getComponentsTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� �^��entity�r��
TEST_F(ER_PresentationModelTest, getEntitiesTable)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� �^�ǯS�wid Attribute�r��
TEST_F(ER_PresentationModelTest, getAttributesTableById)
{
	// ����
	// �Ѽ�:int
	// �^��:string
	// ����:�L
}*/

/* ���� redo
TEST_F(ER_PresentationModelTest, redo)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� undo
TEST_F(ER_PresentationModelTest, undo)
{
	// ����
	// �Ѽ�:�L
	// �^��:string
	// ����:�L
}*/

/* ���� �R���S�wid��component
TEST_F(ER_PresentationModelTest, deleteComponent)
{
	// ����
	// �Ѽ�:int
	// �^��:string
	// ����:�L
}*/

/* ���� �P�_�O�_��������Node�i�H�s��
TEST_F(ER_PresentationModelTest, enoughNodesToConnect)
{
	// ����
	// �Ѽ�:�L
	// �^��:bool
	// ����:�L
}*/

/* ���� �P�_�O�_������
TEST_F(ER_PresentationModelTest, getHasModify)
{
	// ����
	// �Ѽ�:�L
	// �^��:bool
	// ����:�L
}*/