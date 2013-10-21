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
}

/* ���� �s�W�`�I
TEST_F(ER_PresentationModelTest, addNode)
{
	// ����
	// �Ѽ�:ComponentType(componentType), string(nodeName)
	// �^��:string
	// ����:�L
}*/

/* ���� ���o�{�b��ID
TEST_F(ER_PresentationModelTest, getCurrentId)
{
	// ����
	// �Ѽ�:�L
	// �^��:int
	// ����:�L
}*/

/* ���� ���oID�ǥ�index
TEST_F(ER_PresentationModelTest, getIdByIndex)
{
	// ����
	// �Ѽ�:int(index)
	// �^��:int(id)
	// ����:�L
}*/

/* ���� ���oconnection(by ID)�s����ݪ�ID�HnodeNumber�ӰϤ�0 1
TEST_F(ER_PresentationModelTest, getConnectionNodeById)
{
	// ����
	// �Ѽ�:int(id), int(nodeNumber)
	// �^��:int(id)
	// ����:�L
}*/

/* ���� ���otext�����ǥ�id
TEST_F(ER_PresentationModelTest, getNameById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string(name)
	// ����:�L
}*/

/* ���� ���oType�ǥ�id
TEST_F(ER_PresentationModelTest, getTypeById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:ComponentType
	// ����:�L
}*/

/* ���� �s�u�T��
TEST_F(ER_PresentationModelTest, getAddConnectionMessage)
{
	// ����
	// �Ѽ�:int,int
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �^�Ǥ���s�u���T��
TEST_F(ER_PresentationModelTest, getCannotConnectMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �^�Ǥ@��Node�s�u���~���T��
TEST_F(ER_PresentationModelTest, getSameNodeMessage)
{
	// ����
	// �Ѽ�:string
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �^�ǻݭnCardinary��T���T��
TEST_F(ER_PresentationModelTest, getAskCardinaryStateMessage)
{
	// ����
	// �Ѽ�:�L
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �^�Ǥw�g�s�u���T��
TEST_F(ER_PresentationModelTest, getAlreadyConnectedMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �^�Ǧ��\�s�u���T��
TEST_F(ER_PresentationModelTest, getNodeConnectedMessage)
{
	// ����
	// �Ѽ�:string, string
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �s�W�s�u
TEST_F(ER_PresentationModelTest, addConnection)
{
	// ����
	// �Ѽ�:int, int, ConnectionCardinality
	// �^��:string(message)
	// ����:�L
}*/

/* ���� �P�_idStr�O���O�w�s�b��componentId
TEST_F(ER_PresentationModelTest, isExistComponentId)
{
	// ����
	// �Ѽ�:string
	// �^��:bool
	// ����:�L
}*/

/* ���� �P�_entityId�O���OEntity
TEST_F(ER_PresentationModelTest, checkEntitySelectedValid)
{
	// ����
	// �Ѽ�:string
	// �^��:string
	// ����:�L
}*/

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