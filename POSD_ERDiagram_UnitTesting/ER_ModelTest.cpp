#include "ER_Model.h"
#include "gtest/gtest.h"

using namespace std;
class ER_ModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		model = new ER_Model;
	}

	ER_Model* model;
};

// ���ղM���ثemodel����components
TEST_F(ER_ModelTest, clearCurrentComponents) {
	// �b�S��component���ɫ�M��
	EXPECT_EQ(0, model->getComponents().size());  // �T�{components���Ū�
	model->clearCurrentComponents();              // �M��(���ը禡)
	EXPECT_EQ(0, model->getComponents().size());  // ���G���Ū�
	// �s�W�@��components�b�M��
	ERD_Component* testComponent = new ERD_Component;
	model->addComponent(testComponent);           // �[�J1��component
	EXPECT_EQ(1, model->getComponents().size());  // ���G���Ū�
	model->clearCurrentComponents();              // �M��(���ը禡)
	EXPECT_EQ(0, model->getComponents().size());  // ���G���Ū�
}

// ���ը̾�id�ƧǱƧ�components
TEST_F(ER_ModelTest, sortComponents) {
	// �إ�id�S�����Ǫ���Ʀb�@�ƧǴ���
	EXPECT_EQ(0, model->getComponents().size());
}

// ���շs�W�`�I(���]�tconnection) case�h
TEST_F(ER_ModelTest, addNode) {
	// ����
	// �Ѽ�:ComponentType(type), string(name)
	// �^��:int (id)
	// ����:id���ثemodel�̧Ƿs�W��id(���W)
	EXPECT_EQ(0, model->getComponents().size());

	// ����
	// �Ѽ�:string(type), string(name)
	// �^��:�L
	// ����:id���ثemodel�̧Ƿs�W��id(���W)
	EXPECT_EQ(0, model->getComponents().size());

	// ����
	// �Ѽ�:ComponentType(type), string(name), int(id)
	// �^��:�L
	// ����:id���ثemodel�̧Ƿs�W��id(���W)
	EXPECT_EQ(0, model->getComponents().size());

}

// ���� �]�wAttribute���w�s�u���A
TEST_F(ER_ModelTest, setAttributeTypeConnected) {
	// ����
	// �Ѽ�:ERD_Component*(component)
	// �^��:ERD_Component*
	// ����:�L
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� �ˬd�s�u���p �ѼƬ����Node�n�s����ID ���G -1:�w�g�۳s -2:Cardinality -3:���I�ۦP -4:����s
TEST_F(ER_ModelTest, checkAddConnection) {
	// ����
	// �Ѽ�:int(component1Id), int(component2Id)
	// �^��:int(-1:�w�g�۳s -2:Cardinality -3:���I�ۦP -4:����s >=0:�s�u��id)
	// ����:
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���o�{�bmodel���Ƨ�id�ýվ㬰�U�@�ӱƧ�
TEST_F(ER_ModelTest, getAddConnectionId) {
	// ����
	// �Ѽ�:�L
	// �^��:int(id)
	// ����:�s�W�s�u�ɥΨ�
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� �s�W�s�u case�h
TEST_F(ER_ModelTest, addConnection) {
	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id)
	// �^��:�L
	// ����:�S�wID��m���s�W �D�n�Ω�Ū�ɮɪ��s�W
	EXPECT_EQ(0, model->getComponents().size());

	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id), ConnectionCardinality(cardinality)
	// �^��:�L
	// ����:�S�wID��m���s�W�]�tcardinality�ݩ�
	EXPECT_EQ(0, model->getComponents().size());

	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id), string(cardinalityStr)
	// �^��:�L
	// ����:�S�wID��m���s�W�]�tcardinality�ݩ� �D�n�Ω�Ū�ɮɪ��s�W
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ��index��������ID
TEST_F(ER_ModelTest, getIdByIndex) {
	// ����
	// �Ѽ�:int(index)
	// �^��:int(id)
	// ����:�L
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���o�s�u�����node �HnodeNumber�Ӥ�node0�Pnode1
TEST_F(ER_ModelTest, getConnectionNodeById) {
	// ����
	// �Ѽ�:int(id), int(nodeNumber)
	// �^��:int(id)
	// ����:�^�ǭȬ�-1�����p���ҥ~���p��:�L�s�u
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���o�W���ǥ�ID
TEST_F(ER_ModelTest, getNameById) {
	// ����
	// �Ѽ�:int(id)
	// �^��:string(name)
	// ����:�^�ǪŦr�ꬰ��id��text���ũΨS�����wid��component�s�b
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���o���A�ǥ�ID
TEST_F(ER_ModelTest, getTypeById) {
	// ����
	// �Ѽ�:int(id)
	// �^��:ComponentType(type)
	// ����:�^�ǭȵ���SIZE_OF_ComponentType���S�����wid��component�s�b
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���oERD_Component�ǥ�ID
TEST_F(ER_ModelTest, findComponentById) {
	// ����
	// �Ѽ�:int(id)
	// �^��:ERD_Component*(component)
	// ����:�䤣�쬰NULL
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���node�O�_�w�g�s�u
TEST_F(ER_ModelTest, isAlreadyConnect) {
	// ����
	// �Ѽ�:ERD_Component*(node1), ERD_Component*(node2)
	// �^��:bool
	// ����:�L
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� �]�w�S�w��ID��PrimaryKey(Attribute)
TEST_F(ER_ModelTest, setIsPrimaryKey) {
	// ����
	// �Ѽ�:int(id), bool(flag)
	// �^��:�L
	// ����:�L
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ���o�S�w��ID(Attribute)�O�_��PrimaryKey
TEST_F(ER_ModelTest, getIsPrimaryKey) {
	// ����
	// �Ѽ�:int(id)
	// �^��:bool
	// ����:�^�ǭȵ���false�i�ର�S�����wid��component�s�b
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� sourceId��connection��s�u��targetId���I�N�PtargetId�۳s��ID�B�κA����type���I�O���_��
TEST_F(ER_ModelTest, setRelatedIdVector) {
	// ����
	// �Ѽ�:int(sourceId), int(targetId), ComponentType(type), vector<int>&(idVector)
	// �^��:�L
	// ����:�����۲Ū��I�ðO����id
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ��Node���X(���]�tconnection)
TEST_F(ER_ModelTest, findNodes) {
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>(nodesId)
	// ����:�^�ǥثemodel���Ҧ���Node
	EXPECT_EQ(0, model->getComponents().size());
}

// ���� ��component���X(����)
TEST_F(ER_ModelTest, findComponents) {
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>(componentsId)
	// ����:�^�ǥثemodel���Ҧ���Components
	EXPECT_EQ(0, model->getComponents().size());
}

/* ����
TEST_F(ER_ModelTest, functionName) {
	// ����
	// �Ѽ�:
	// �^��:
	// ����:
	EXPECT_EQ(0, model->getComponents().size());
}*/

/* ����
TEST_F(ER_ModelTest, functionName) {
	// ����
	// �Ѽ�:
	// �^��:
	// ����:
	EXPECT_EQ(0, model->getComponents().size());
}*/

/* ����
TEST_F(ER_ModelTest, functionName) {
	// ����
	// �Ѽ�:
	// �^��:
	// ����:
	EXPECT_EQ(0, model->getComponents().size());
}*/