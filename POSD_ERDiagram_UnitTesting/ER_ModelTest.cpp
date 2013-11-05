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

	virtual void TearDown()
	{
		delete model;
	}

	void testDataInit()
	{
		model->addNode(ERD_Component::Entity, "Engineer");  //id=0
		model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		model->addNode(ERD_Component::Attribute, "Name");   //id=2
		model->addNode(ERD_Component::Relationship, "Has");   //id=3
		model->addNode(ERD_Component::Entity, "PC");  //id=4
	}

	void testDataInitWithConnection()
	{
		model->addNode(ERD_Component::Entity, "Engineer");  //id=0
		model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
		model->addNode(ERD_Component::Attribute, "Name");   //id=2
		model->addNode(ERD_Component::Attribute, "Department");   //id=3
		model->addNode(ERD_Component::Relationship, "Has");   //id=4
		model->addNode(ERD_Component::Entity, "PC");  //id=5
		model->addNode(ERD_Component::Attribute, "PC_ID");   //id=6
		model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=7
		model->addConnection(0, 4, 8, ERD_Connection::one);
		model->addConnection(4, 5, 9, ERD_Connection::one);
		model->addConnection(0, 1, 10, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(0, 2, 11, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(0, 3, 12, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(5, 6, 13, ERD_Connection::SIZE_OF_Cardinality);
		model->addConnection(5, 7, 14, ERD_Connection::SIZE_OF_Cardinality);
		model->setIsPrimaryKey(1, true);
		model->setIsPrimaryKey(2, true);
		model->setIsPrimaryKey(6, true);
	}

	ER_Model* model;
};



// ���ղM���ثemodel����components
TEST_F(ER_ModelTest, clearCurrentComponents) 
{
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
TEST_F(ER_ModelTest, sortComponents) 
{
	// �إ�id�S�����Ǫ���Ʀb�@�ƧǴ���
	model->addNode(ERD_Component::Entity, "ID2", 2);
	model->addNode(ERD_Component::Attribute, "ID1", 1);
	model->addNode(ERD_Component::Entity, "ID0", 0);
	EXPECT_EQ(0, model->getIdByIndex(2));        // �[�J����2 Id��0
	EXPECT_EQ(2, model->getIdByIndex(0));        // �[�J����0 Id��2
	model->sortComponents();
	for (unsigned i = 0;i < model->getComponents().size(); i++)
	{
		EXPECT_EQ(i, model->getIdByIndex(i));        // �[�J����i Id��i
	}
}

// ���շs�W�`�I(���]�tconnection)
TEST_F(ER_ModelTest, addNode) 
{
	// ����
	// �Ѽ�:ComponentType(type), string(name)
	// �^��:int (id)
	// ����:id���ثemodel�̧Ƿs�W��id(���W)
	int addNodeId;
	EXPECT_EQ(0, model->getComponents().size());         // ��l��0

	addNodeId = model->addNode(ERD_Component::Entity, "E:ID_0");
	EXPECT_EQ(0, addNodeId);                             //Id = 0;
	EXPECT_EQ(1, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Attribute, "A:ID_1");
	EXPECT_EQ(1, addNodeId);                             //Id = 1;
	EXPECT_EQ(2, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Relationship, "R:ID_2");
	EXPECT_EQ(2, addNodeId);                             //Id = 2;
	EXPECT_EQ(3, model->getComponents().size());

	addNodeId = model->addNode(ERD_Component::Connection, "C:ID_3"); //addNode����s�WConnection �^��-1
	EXPECT_EQ(-1, addNodeId);                             //����s�W�^��-1
	EXPECT_EQ(3, model->getComponents().size());          //�ƶq�S��

	TearDown();
	// ����
	// �Ѽ�:string(type), string(name)
	// �^��:�L
	// ����:id���ثemodel�̧Ƿs�W��id(���W)
	SetUp();
	model->addNode("E", "E:ID_0");
	EXPECT_EQ(1, model->getComponents().size());

	model->addNode("A", "E:ID_1");
	EXPECT_EQ(2, model->getComponents().size());

	model->addNode("R", "E:ID_2");
	EXPECT_EQ(3, model->getComponents().size());

	model->addNode("C", "C:ID_3");                //addNode����s�WConnection
	EXPECT_EQ(3, model->getComponents().size());  //�ƶq�S��

	TearDown();
	// ����
	// �Ѽ�:ComponentType(type), string(name), int(id)
	// �^��:�L
	// ����:�S�wID��m���s�W
	SetUp();
	model->addNode(ERD_Component::Entity, "E:ID_2", 2);
	EXPECT_EQ(1, model->getComponents().size());
	EXPECT_EQ("E:ID_2", model->getNameById(2));

	model->addNode(ERD_Component::Connection, "E:ID_3", 3);//addNode����s�WConnection
	EXPECT_EQ(1, model->getComponents().size());           //�ƶq�S��

	model->addNode(ERD_Component::Attribute, "A:ID_0", 0);
	EXPECT_EQ(2, model->getComponents().size());
	EXPECT_EQ("A:ID_0", model->getNameById(0));

	model->addNode(ERD_Component::Relationship, "R:ID_1", 1);
	EXPECT_EQ(3, model->getComponents().size());
	EXPECT_EQ("R:ID_1", model->getNameById(1));
}

// ���� �]�wAttribute�s�u���A
TEST_F(ER_ModelTest, setAttributeConnected)
{
	// ����
	// �Ѽ�:ERD_Component*(component)
	// �^��:ERD_Component*
	// ����:�L
	model->addNode(ERD_Component::Attribute, "A:ID_0", 0);
	ERD_Component* component = model->findComponentById(0);
	ERD_Attribute* attribute = (ERD_Attribute*) component;
	EXPECT_EQ(false, attribute->getIsConnected());
	model->setAttributeConnected(0, true);
	EXPECT_EQ(true, attribute->getIsConnected());

	model->addNode(ERD_Component::Entity, "E:ID_1", 1);
	model->setAttributeConnected(1, true);                 //���Oconnection������
	EXPECT_EQ(2, model->getComponents().size());
}

// ���� �ˬd�s�u���p �ѼƬ����Node�n�s����ID ���G -1:�w�g�۳s -2:Cardinality -3:���I�ۦP -4:����s
TEST_F(ER_ModelTest, checkAddConnection)
{
	// ����
	// �Ѽ�:int(component1Id), int(component2Id)
	// �^��:int(-1:�w�g�۳s -2:Cardinality -3:���I�ۦP -4:����s >=0:�s�u��id)
	// ����:
	testDataInit();

	int result;
	result = model->checkAddConnection(0, 1);
	EXPECT_EQ(5, result);                      //�i�H�s�^�ǳs�u��id
	model->addConnection(0, 1, result);

	result = model->checkAddConnection(0, 1);
	EXPECT_EQ(-1, result);                     //-1:�w�g�۳s

	result = model->checkAddConnection(0, 3);
	EXPECT_EQ(-2, result);                     //-2:Cardinality

	result = model->checkAddConnection(3, 4);
	EXPECT_EQ(-2, result);                     //-2:Cardinality

	result = model->checkAddConnection(0, 0);
	EXPECT_EQ(-3, result);                     //-3:���I�ۦP

	result = model->checkAddConnection(1, 2);  //�P��Attrubute
	EXPECT_EQ(-4, result);                     //-4:����s

	result = model->checkAddConnection(1, 3);  //Attribute�PRelationship
	EXPECT_EQ(-4, result);                     //-4:����s

	result = model->checkAddConnection(0, 4);  //�P��Entity
	EXPECT_EQ(-4, result);                     //-4:����s
}

// ���� id�ýվ㬰�U�@�ӱƧ�
TEST_F(ER_ModelTest, plusCurrentId)
{
	// ����
	// �Ѽ�:�L
	// �^��:int(id)
	// ����:�s�W�s�u�ɥΨ�
	EXPECT_EQ(0, model->getCurrentId());
	model->plusCurrentId();
	EXPECT_EQ(1, model->getCurrentId());
	model->plusCurrentId();
	EXPECT_EQ(2, model->getCurrentId());
}

// ���� �s�W�s�u
TEST_F(ER_ModelTest, addConnection) 
{
	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id)
	// �^��:�L
	// ����:�S�wID��m���s�W �D�n�Ω�Ū�ɮɪ��s�W
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 1, 5);
	EXPECT_EQ(6, model->getComponents().size());

	TearDown();
	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id), ConnectionCardinality(cardinality)
	// �^��:�L
	// ����:�S�wID��m���s�W�]�tcardinality�ݩ�
	SetUp();
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 3, 5, ERD_Connection::one);
	EXPECT_EQ(6, model->getComponents().size());
	model->addConnection(4, 3, 6, ERD_Connection::n);
	EXPECT_EQ(7, model->getComponents().size());
	model->addConnection(0, 1, 7, ERD_Connection::SIZE_OF_Cardinality);
	EXPECT_EQ(8, model->getComponents().size());

	TearDown();
	// ����
	// �Ѽ�:int(component1Id), int(component2Id), int(id), string(cardinalityStr)
	// �^��:�L
	// ����:�S�wID��m���s�W�]�tcardinality�ݩ� �D�n�Ω�Ū�ɮɪ��s�W
	SetUp();
	testDataInit();
	EXPECT_EQ(5, model->getComponents().size());
	model->addConnection(0, 3, 5, "1");
	EXPECT_EQ(6, model->getComponents().size());
	model->addConnection(4, 3, 6, "N");
	EXPECT_EQ(7, model->getComponents().size());
	model->addConnection(0, 1, 7, "");
	EXPECT_EQ(8, model->getComponents().size());

}

// ���� ��index��������ID
TEST_F(ER_ModelTest, getIdByIndex) 
{
	// ����
	// �Ѽ�:int(index)
	// �^��:int(id)
	// ����:�L
    testDataInit();
	int result;
	result = model->getIdByIndex(0);
	EXPECT_EQ(0, result);
	result = model->getIdByIndex(4);
	EXPECT_EQ(4, result);
}

// ���� ���o�s�u�����node �HnodeNumber�Ӥ�node0�Pnode1
TEST_F(ER_ModelTest, getConnectionNodeById)
{
	// ����
	// �Ѽ�:int(id), int(nodeNumber)
	// �^��:int(id)
	// ����:�^�ǭȬ�-1�����p���ҥ~���p��:�L�s�u
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��

	int result;
	result = model->getConnectionNodeById(5, 0);  //���Ĥ@��Id
	EXPECT_EQ(0, result);
	result = model->getConnectionNodeById(5, 1);  //���ĤG��Id
	EXPECT_EQ(3, result);

	//�ҥ~
	result = model->getConnectionNodeById(4, 0);  //���Oconnection
	EXPECT_EQ(-1, result);
}

// ���� ���o�W���ǥ�ID
TEST_F(ER_ModelTest, getNameById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:string(name)
	// ����:�^�ǪŦr�ꬰ��id��text���ũΨS�����wid��component�s�b
	testDataInit();
	string result;
	result = model->getNameById(0);
	EXPECT_EQ("Engineer", result);

	result = model->getNameById(4);
	EXPECT_EQ("PC", result);
	
	result = model->getNameById(5); // id���s�b
	EXPECT_EQ("", result);
}

// ���� ���o���A�ǥ�ID
TEST_F(ER_ModelTest, getTypeById)
{
	// ����
	// �Ѽ�:int(id)
	// �^��:ComponentType(type)
	// ����:�^�ǭȵ���SIZE_OF_ComponentType���S�����wid��component�s�b
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��

	ERD_Component::ComponentType result;
	result = model->getTypeById(0);
	EXPECT_EQ(ERD_Component::Entity, result);

	result = model->getTypeById(1);
	EXPECT_EQ(ERD_Component::Attribute, result);

	result = model->getTypeById(3);
	EXPECT_EQ(ERD_Component::Relationship, result);

	result = model->getTypeById(5);
	EXPECT_EQ(ERD_Component::Connection, result);

	result = model->getTypeById(6); // id���s�b
	EXPECT_EQ(ERD_Component::SIZE_OF_ComponentType, result);
}

// ���� ���oERD_Component�ǥ�ID
TEST_F(ER_ModelTest, findComponentById) 
{
	// ����
	// �Ѽ�:int(id)
	// �^��:ERD_Component*(component)
	// ����:�䤣�쬰NULL
	testDataInit();

	ERD_Component* result;
	result = model->findComponentById(0);
	EXPECT_EQ("Engineer", result->getText());
	EXPECT_EQ(0, result->getId());
	EXPECT_EQ(ERD_Component::Entity, result->getType());

	result = model->findComponentById(6); // id���s�b
	EXPECT_EQ(NULL, result);
}

// ���� ���node�O�_�w�g�s�u
TEST_F(ER_ModelTest, isAlreadyConnect) 
{
	// ����
	// �Ѽ�:ERD_Component*(node1), ERD_Component*(node2)
	// �^��:bool
	// ����:�L
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��
	
	bool result;
	result = model->isAlreadyConnect(1, 2);
	EXPECT_EQ(false, result);

	result = model->isAlreadyConnect(1, 1);
	EXPECT_EQ(false, result);

	result = model->isAlreadyConnect(0, 3);
	EXPECT_EQ(true, result);
}

// ���� �]�w�S�w��ID��PrimaryKey(Attribute)
TEST_F(ER_ModelTest, setIsPrimaryKey)
{
	// ����
	// �Ѽ�:int(id), bool(flag)
	// �^��:�L
	// ����:�L
	testDataInit();
	model->setIsPrimaryKey(1, true);
	EXPECT_EQ(true, model->getIsPrimaryKey(1));
	model->setIsPrimaryKey(1, false);
	EXPECT_EQ(false, model->getIsPrimaryKey(1));
}

// ���� ���o�S�w��ID(Attribute)�O�_��PrimaryKey
TEST_F(ER_ModelTest, getIsPrimaryKey) 
{
	// ����
	// �Ѽ�:int(id)
	// �^��:bool
	// ����:�^�ǭȵ���false�i�ର�S�����wid��component�s�b
	testDataInit();
	model->setIsPrimaryKey(1, true);
	bool result;
	result = model->getIsPrimaryKey(1);
	EXPECT_EQ(true, result);

	result = model->getIsPrimaryKey(5); //���s�b
	EXPECT_EQ(false, result);
}

// ���� sourceId��connection��s�u��targetId���I�N�PtargetId�۳s��ID�B�κA����type���I�O���_��
TEST_F(ER_ModelTest, setRelatedIdVector) 
{
	// ����
	// �Ѽ�:int(sourceId), int(targetId), ComponentType(type), vector<int>&(idVector)
	// �^��:�L
	// ����:�����۲Ū��I�ðO����id
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��

	vector<int> result;
	model->setRelatedIdVector(5, 0, ERD_Component::Relationship, result);

	vector<int> expected;
	expected.push_back(3);
	EXPECT_EQ(expected, result);

	result.clear();
	expected.clear();
	model->setRelatedIdVector(5, 3, ERD_Component::Entity, result);
	expected.push_back(0);
	EXPECT_EQ(expected, result);

	result.clear();
	expected.clear();
	model->setRelatedIdVector(5, 3, ERD_Component::Attribute, result);  //�䤣��
	EXPECT_EQ(expected, result);
}

// ���� ��Node���X(���]�tconnection)
TEST_F(ER_ModelTest, findNodes) 
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>(nodesId)
	// ����:�^�ǥثemodel���Ҧ���Node
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��
	vector<int> result = model->findNodes();
	vector<int> expected;
	expected.push_back(0);
	expected.push_back(1);
	expected.push_back(2);
	expected.push_back(3);
	expected.push_back(4);
	EXPECT_EQ(expected, result);
}

// ���� ��component���X(����)
TEST_F(ER_ModelTest, findComponents) 
{
	// ����
	// �Ѽ�:�L
	// �^��:vector<int>(componentsId)
	// ����:�^�ǥثemodel���Ҧ���Components
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��
	vector<int> result = model->findComponents();
	vector<int> expected;
	expected.push_back(0);
	expected.push_back(1);
	expected.push_back(2);
	expected.push_back(3);
	expected.push_back(4);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// ���� ��S�w���A��component���X
TEST_F(ER_ModelTest, findComponentsByType) 
{
	// ����
	// �Ѽ�:ComponentType(type)
	// �^��:vector<int>(componentsId)
	// ����:�^�ǥثemodel���Ҧ��������wtype��Components
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��
	vector<int> result = model->findComponentsByType(ERD_Component::Attribute);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(2);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Entity);
	expected.push_back(0);
	expected.push_back(4);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Relationship);
	expected.push_back(3);

	expected.clear();
	result = model->findComponentsByType(ERD_Component::Connection);
	expected.push_back(5);

}

// ���� ��targetId�P�S�wtype�۳s��NodeID(���]�tconnection)
TEST_F(ER_ModelTest, findIdWithTypeByTargetId)
{
	// ����
	// �Ѽ�:ComponentType(type), int(targetId)
	// �^��:vector<int>(componentsId)
	// ����:�^�ǻP���wComponent�۳s��Component��type�����w��type
	testDataInit();
	model->addConnection(0, 3, 5, ERD_Connection::one);  //�إ߳s�u���ո��
	vector<int> result = model->findIdWithTypeByTargetId(ERD_Component::Relationship, 0);
	vector<int> expected;
	expected.push_back(3);
	EXPECT_EQ(expected, result);
}

// ���� ��targetId�P�S�wtype�۳s��NodeID�BCardinality�ʽ謰one��(���]�tconnection)
TEST_F(ER_ModelTest, findIdWithTypeByTargetIdWithCardinality)
{
	// ����
	// �Ѽ�:ComponentType(type), int(targetId)
	// �^��:vector<int>(NodesId)
	// ����:�^�ǻP���wComponent�۳s��Component��type�����w��type�s�u�ݩ�Cardinality��one
	testDataInitWithConnection();
	vector<int> result = model->findIdWithTypeByTargetIdWithCardinality(ERD_Component::Relationship, 0);
	vector<int> expected;
	expected.push_back(4);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findIdWithTypeByTargetIdWithCardinality(ERD_Component::Entity, 4);
	expected.push_back(0);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// ���� ��S�wentity��primaryKey
TEST_F(ER_ModelTest, findPrimaryKeyByEntityId) 
{
	// ����
	// �Ѽ�:int(entityId)
	// �^��:vector<int>(attributeId)
	// ����:�L
	testDataInitWithConnection();
	
	vector<int> result = model->findPrimaryKeyByEntityId(0);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(2);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findPrimaryKeyByEntityId(5);
	expected.push_back(6);
	EXPECT_EQ(expected, result);
}

// ���� ���wentityId��L��foreignKeys
TEST_F(ER_ModelTest, findForeignKeyByEntityId) 
{
	// ����
	// �Ѽ�:int(entityId)
	// �^��:vector<vector<int>>(foreignKeysIdVector)
	// ����:�^��foreignkeyIdVector
	testDataInitWithConnection();
	vector<vector<int>> result = model->findForeignKeyByEntityId(0);
	vector<vector<int>> expected;
	expected.push_back(model->findPrimaryKeyByEntityId(5));
	EXPECT_EQ(expected, result);
	TearDown();

	SetUp();
	testDataInitWithConnection();
	expected.clear();
	result = model->findForeignKeyByEntityId(5);
	expected.push_back(model->findPrimaryKeyByEntityId(0));
	EXPECT_EQ(expected, result);
}

// ���� ���wentity��1��1���Y��entity
TEST_F(ER_ModelTest, findOneByOneRelationEntityId)
{
	// ����
	// �Ѽ�:int(targetId)
	// �^��:vector<int>(entitiesId)
	// ����:��1��1���Y��entity
	testDataInitWithConnection();
	vector<int> result = model->findOneByOneRelationEntityId(0);
	vector<int> expected;
	expected.push_back(5);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findOneByOneRelationEntityId(5);
	expected.push_back(0);
	EXPECT_EQ(expected, result);
}

// ���� �|��Ū��
TEST_F(ER_ModelTest, readComponentsFile)
{
	// ����
	// �Ѽ�:string(path)
	// �^��:string(message)
	// ����:
	string result;
	result = model->readComponentsFile("unittest//test_file1.erd");
	EXPECT_EQ("Success", result);
	result = model->readComponentsFile("unittest//file_not_found.erd");
	EXPECT_EQ("Fail", result);
}

// ���� Ū���ɮפ��e
TEST_F(ER_ModelTest, loadFileContent)
{
	// ����
	// �Ѽ�:ER_FileManager &(file)
	// �^��:�L
	// ����:Ū��
	ER_FileManager file;
	file.openFile("unittest//test_file1.erd", ER_FileManager::Read);
	model->loadFileContent(file);
	EXPECT_EQ(15, model->getComponents().size());
}

// ���� Ū�ɲ�1����Components
TEST_F(ER_ModelTest, loadComponents) 
{
	// ����
	// �Ѽ�:vector<string>::iterator(linIt), map<int, string> &(connectionMap)
	// �^��:�L
	// ����:�ظmmodel���e
	ER_FileManager file;
	file.openFile("unittest//test_file1_part1.erd", ER_FileManager::Read);
	vector<string> lines;
	map<int, string> resultMap;
	string content = file.readFile();
	lines = Tool_Function::split(content, '\n');
	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadComponents(it, resultMap);
	}
	file.closeFile();
	map<int, string> expectedMap;
	expectedMap.insert(pair<int, string> (7, ""));
	expectedMap.insert(pair<int, string> (8, ""));
	expectedMap.insert(pair<int, string> (9, ""));
	expectedMap.insert(pair<int, string> (10, ""));
	expectedMap.insert(pair<int, string> (11, "1"));
	expectedMap.insert(pair<int, string> (12, "1"));
	expectedMap.insert(pair<int, string> (14, ""));
	EXPECT_EQ(expectedMap, resultMap);
	EXPECT_EQ(8, model->getComponents().size());
}

// ���� Ū�ɲ�2����Connections
TEST_F(ER_ModelTest, loadConnections) 
{
	// ����
	// �Ѽ�:vector<string>::iterator(linIt), map<int, string> &(connectionMap)
	// �^��:�L
	// ����:�ظmmodel���e
	ER_FileManager file;
	file.openFile("unittest//test_file1_part2.erd", ER_FileManager::Read);
	string content = file.readFile();
	vector<string> lines;
	lines = Tool_Function::split(content, '\n');
	// �إ߸��
	map<int, string> connectionMap;
	connectionMap.insert(pair<int, string> (7, ""));
	connectionMap.insert(pair<int, string> (8, ""));
	connectionMap.insert(pair<int, string> (9, ""));
	connectionMap.insert(pair<int, string> (10, ""));
	connectionMap.insert(pair<int, string> (11, "1"));
	connectionMap.insert(pair<int, string> (12, "1"));
	connectionMap.insert(pair<int, string> (14, ""));

	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	model->addNode(ERD_Component::Relationship, "Has");   //id=2
	model->addNode(ERD_Component::Attribute, "Name");   //id=3
	model->addNode(ERD_Component::Entity, "PC");  //id=4
	model->addNode(ERD_Component::Attribute, "PC_ID");   //id=5
	model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=6
	model->addNode(ERD_Component::Attribute, "Department", 13);   //id=13
	// �إ߸��end

	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadConnections(it, connectionMap);
	}
	file.closeFile();
	EXPECT_EQ(15, model->getComponents().size());
}

// ���� Ū�ɲ�3����PrimaryKey
TEST_F(ER_ModelTest, loadPrinaryKey) 
{
	// ����
	// �Ѽ�:vector<string>::iterator(linIt)
	// �^��:�L
	// ����:�ظmmodel���e
	ER_FileManager file;
	file.openFile("unittest//test_file1_part3.erd", ER_FileManager::Read);
	string content = file.readFile();
	vector<string> lines;
	lines = Tool_Function::split(content, '\n');
	// �إ߸��
	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	model->addNode(ERD_Component::Relationship, "Has");   //id=2
	model->addNode(ERD_Component::Attribute, "Name");   //id=3
	model->addNode(ERD_Component::Entity, "PC");  //id=4
	model->addNode(ERD_Component::Attribute, "PC_ID");   //id=5
	model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=6
	model->addNode(ERD_Component::Attribute, "Department", 13);   //id=13

	model->addConnection(0, 1, 7, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(0, 3, 8, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(4, 5, 9, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(4, 6, 10, ERD_Connection::SIZE_OF_Cardinality);
	model->addConnection(0, 2, 11, ERD_Connection::one);
	model->addConnection(2, 4, 12, ERD_Connection::one);
	model->addConnection(0, 13, 14, ERD_Connection::SIZE_OF_Cardinality);
	// �إ߸��end

	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadPrinaryKey(it);
	}
	file.closeFile();

	vector<int> result = model->findPrimaryKeyByEntityId(0);
	vector<int> expected;
	expected.push_back(1);
	expected.push_back(3);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findPrimaryKeyByEntityId(4);
	expected.push_back(5);
	EXPECT_EQ(expected, result);
}

// ���� �s��
TEST_F(ER_ModelTest, storeComponents) 
{
	// ����
	// �Ѽ�:string(path)
	// �^��:string(message)
	// ����:
	testDataInitWithConnection();
	string result;
	result = model->storeComponents("unittest//test_store_file.erd");
	EXPECT_EQ("Success", result);
}

// ���� �P�_idStr�O���O�w�s�b��componentId
TEST_F(ER_ModelTest, isExistComponentId)
{
	// ����
	// �Ѽ�:string(idStr)
	// �^��:bool(result)
	// ����:�L
	testDataInitWithConnection();
	bool result;
	result = model->isExistComponentId("0");
	EXPECT_EQ(true, result);

	result = model->isExistComponentId("14");
	EXPECT_EQ(true, result);

	result = model->isExistComponentId("15");
	EXPECT_EQ(false, result);
}

// ���� �P�_entityId�O���OEntity
TEST_F(ER_ModelTest, checkEntitySelectedValid) 
{
	// ����
	// �Ѽ�:string(entityId)
	// �^��:string(message)
	// ����:�L
	testDataInitWithConnection();
	string result;
	result = model->checkEntitySelectedValid("0");
	EXPECT_EQ("Find Right Entity", result);

	result = model->checkEntitySelectedValid("14");
	EXPECT_EQ("Not an Entity", result);

	result = model->checkEntitySelectedValid("15");
	EXPECT_EQ("Id Not Exist", result);
}

// ���� �R��component
TEST_F(ER_ModelTest, deleteComponent) 
{
	// ����
	// �Ѽ�:int(id)
	// �^��:bool(result)
	// ����:
	testDataInitWithConnection();
	bool result;
	result = model->deleteComponent(0);
	EXPECT_EQ(true, result);

	result = model->deleteComponent(14);
	EXPECT_EQ(true, result);

	result = model->deleteComponent(15);
	EXPECT_EQ(false, result);
}

// ���� ��X�P���wID(targetId)�������Ҧ�Connection��ID
TEST_F(ER_ModelTest, findRelatedConnectionById) 
{
	// ����
	// �Ѽ�:int(targetId)
	// �^��:vector<int>(connectionId)
	// ����:
	testDataInitWithConnection();
	vector<int> result = model->findRelatedConnectionById(0);
	vector<int> expected;
	expected.push_back(8);
	expected.push_back(10);
	expected.push_back(11);
	expected.push_back(12);
	EXPECT_EQ(expected, result);

	expected.clear();
	result = model->findRelatedConnectionById(5);
	expected.push_back(9);
	expected.push_back(13);
	expected.push_back(14);
	EXPECT_EQ(expected, result);
}

// ���� �s�Wcomponent
TEST_F(ER_ModelTest, addComponent) 
{
	// ����
	// �Ѽ�:ERD_Component*(component)
	// �^��:�L
	// ����:
	ERD_Component* testComponent = new ERD_Component;
	model->addComponent(testComponent);           // �[�J1��component
	EXPECT_EQ(1, model->getComponents().size());
}

// ���� �O�_��������node�i�H�s��
TEST_F(ER_ModelTest, enoughNodesToConnect) 
{
	// ����
	// �Ѽ�:�L
	// �^��:bool(result)
	// ����:
	EXPECT_EQ(false, model->enoughNodesToConnect());
	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	EXPECT_EQ(true, model->enoughNodesToConnect());
}

/* ����
TEST_F(ER_ModelTest, functionName)
{
	// ����
	// �Ѽ�:
	// �^��:
	// ����:
	EXPECT_EQ(0, model->getComponents().size());
}*/