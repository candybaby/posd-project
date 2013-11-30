#include "ER_Model.h"
#include "ER_PresentationModel.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace std;
class ER_IntegrationTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_mkdir("testdata");
		ofstream outputFile("testdata/test_file1.erd");
		outputFile << "E, Engineer" << endl;
		outputFile << "A, Emp_ID" << endl;
		outputFile << "R, Has" << endl;
		outputFile << "A, Name" << endl;
		outputFile << "E, PC" << endl;
		outputFile << "A, PC_ID" << endl;
		outputFile << "A, Purchase_Date" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C, 1" << endl;
		outputFile << "C, 1" << endl;
		outputFile << "A, Department" << endl;
		outputFile << "C" << endl;
		outputFile << endl;
		outputFile << "7 0,1" << endl;
		outputFile << "8 0,3" << endl;
		outputFile << "9 4,5" << endl;
		outputFile << "10 4,6" << endl;
		outputFile << "11 0,2" << endl;
		outputFile << "12 2,4" << endl;
		outputFile << "14 0,13" << endl;
		outputFile << endl;
		outputFile << "0 1,3" << endl;
		outputFile << "4 5" << endl;
		outputFile.close();

		model = new ER_Model();
		presentationModel = new ER_PresentationModel(model);
	}

	virtual void TearDown()
	{
		remove("testdata/test_file1.erd");
		_rmdir("testdata");
		delete presentationModel;
		delete model;
	}

	ER_Model* model;
	ER_PresentationModel* presentationModel;
};

// 代刚 testLoadFileNotExist 
TEST_F(ER_IntegrationTest, testLoadFileNotExist)
{
	string result;
	result = presentationModel->readComponentsFile("testdata//file_not_exist.erd");
	EXPECT_EQ("File not found!!\n", result);
}

// 代刚 testIsPrimaryExist 
TEST_F(ER_IntegrationTest, testIsPrimaryExist)
{
	string message;
	// Load the ¨test_file1.erd〃 under the ¨testdata〃 directory
	message = presentationModel->readComponentsFile("testdata//test_file1.erd");
	
	// Assert the diagram is loaded correctly 
	EXPECT_EQ("The ER diagram is displayed as follows:\nComponents:\n------------------------------------\n Type |  ID  |  Name \n------+------+----------------------\n  E   |   0   |   Engineer\n  A   |   1   |   Emp_ID\n  R   |   2   |   Has\n  A   |   3   |   Name\n  E   |   4   |   PC\n  A   |   5   |   PC_ID\n  A   |   6   |   Purchase_Date\n  C   |   7   |   \n  C   |   8   |   \n  C   |   9   |   \n  C   |   10   |   \n  C   |   11   |   1\n  C   |   12   |   1\n  A   |   13   |   Department\n  C   |   14   |   \n------------------------------------\n\nConnections:\n------------------------------------\nConnection | node | node\n-----------+------+-----------------\n       7   |  0   |  1\n       8   |  0   |  3\n       9   |  4   |  5\n       10   |  4   |  6\n       11   |  0   |  2\n       12   |  2   |  4\n       14   |  0   |  13\n------------------------------------\n", message);
	
	// Display the table
	message = presentationModel->getTable();
	EXPECT_EQ("Tables:\n----------------------------------------------------------\n  Entity  |  Attribute\n----------+-----------------------------------------------\n Engineer | PK(Emp_ID, Name), Department, FK(PC_ID)\n PC | PK(PC_ID), Purchase_Date\n----------------------------------------------------------\n", message);
	
	// Assert Engineerˇs primary key is ¨Name〃 and ¨Emp_ID〃
	message = presentationModel->getPrimaryKeyString(0);
	EXPECT_EQ("1, 3", message);  // 1: Name 3: Emp_ID

	// Assert PCˇs primary key is ¨PC_ID〃 Assert PCˇs primary key is not ¨Purchase_Date〃 
	message = presentationModel->getPrimaryKeyString(4);
	EXPECT_EQ("5", message);  // 5: PC_ID Τ5 ┮6: Purchase_Date ぃ琌PCprimary key
}

// 代刚 testUndoDeleteComponent 
TEST_F(ER_IntegrationTest, testUndoDeleteComponent)
{
	string message;
	// Load the ¨test_file1.erd〃 under the ¨testdata〃 directory
	message = presentationModel->readComponentsFile("testdata//test_file1.erd");

	// Assert the diagram is loaded correctly 
	EXPECT_EQ("The ER diagram is displayed as follows:\nComponents:\n------------------------------------\n Type |  ID  |  Name \n------+------+----------------------\n  E   |   0   |   Engineer\n  A   |   1   |   Emp_ID\n  R   |   2   |   Has\n  A   |   3   |   Name\n  E   |   4   |   PC\n  A   |   5   |   PC_ID\n  A   |   6   |   Purchase_Date\n  C   |   7   |   \n  C   |   8   |   \n  C   |   9   |   \n  C   |   10   |   \n  C   |   11   |   1\n  C   |   12   |   1\n  A   |   13   |   Department\n  C   |   14   |   \n------------------------------------\n\nConnections:\n------------------------------------\nConnection | node | node\n-----------+------+-----------------\n       7   |  0   |  1\n       8   |  0   |  3\n       9   |  4   |  5\n       10   |  4   |  6\n       11   |  0   |  2\n       12   |  2   |  4\n       14   |  0   |  13\n------------------------------------\n", message);

	// Add an entity with text ¨Test〃
	EXPECT_EQ(15, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Entity, "Test", 0, 0);

	// Assert the entity is added correctly
	EXPECT_EQ(16, presentationModel->findComponents().size());
	EXPECT_EQ("Test", presentationModel->getNameById(15));

	// Delete the entity added above
	presentationModel->deleteComponent(15);

	// Assert the entity has been deleted
	EXPECT_EQ(15, presentationModel->findComponents().size());

	// Undo
	presentationModel->undo();

	// Assert there is an entity with text ¨Test〃 
	EXPECT_EQ(16, presentationModel->findComponents().size());
	EXPECT_EQ("Test", presentationModel->getNameById(15));
}

// 代刚 testRedoConnectComponent 
TEST_F(ER_IntegrationTest, testRedoConnectComponent)
{
	string message;
	// Load the ¨test_file1.erd〃 under the ¨testdata〃 directory
	message = presentationModel->readComponentsFile("testdata//test_file1.erd");

	// Assert the diagram is loaded correctly 
	EXPECT_EQ("The ER diagram is displayed as follows:\nComponents:\n------------------------------------\n Type |  ID  |  Name \n------+------+----------------------\n  E   |   0   |   Engineer\n  A   |   1   |   Emp_ID\n  R   |   2   |   Has\n  A   |   3   |   Name\n  E   |   4   |   PC\n  A   |   5   |   PC_ID\n  A   |   6   |   Purchase_Date\n  C   |   7   |   \n  C   |   8   |   \n  C   |   9   |   \n  C   |   10   |   \n  C   |   11   |   1\n  C   |   12   |   1\n  A   |   13   |   Department\n  C   |   14   |   \n------------------------------------\n\nConnections:\n------------------------------------\nConnection | node | node\n-----------+------+-----------------\n       7   |  0   |  1\n       8   |  0   |  3\n       9   |  4   |  5\n       10   |  4   |  6\n       11   |  0   |  2\n       12   |  2   |  4\n       14   |  0   |  13\n------------------------------------\n", message);

	// Add an entity with text ¨Test〃
	EXPECT_EQ(15, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Entity, "Test", 0, 0);

	// Assert the entity is added correctly
	EXPECT_EQ(16, presentationModel->findComponents().size());
	EXPECT_EQ("Test", presentationModel->getNameById(15));

	// Add an attribute with text ¨Test Attr〃 
	EXPECT_EQ(16, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Attribute, "TestAttr", 0, 0);

	// Assert the attribute is added correctly 
	EXPECT_EQ(17, presentationModel->findComponents().size());
	EXPECT_EQ("TestAttr", presentationModel->getNameById(16));

	// Connect node 15 and 16 Assert there is a connection between node 15 and 16
	EXPECT_EQ(17, presentationModel->findComponents().size());
	string connectionMessage = presentationModel->getAddConnectionMessage(15, 16);
	EXPECT_EQ("The node '15' has been connected to the node '16'.", connectionMessage);
	EXPECT_EQ(18, presentationModel->findComponents().size());
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(17, 0));
	EXPECT_EQ(16, presentationModel->getConnectionNodeById(17, 1));

	// Undo
	presentationModel->undo();

	// Assert there is no connection between node 15 and 16
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(17, 0));
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(17, 1));

	// Redo
	presentationModel->redo();

	// Assert node 15 and 16 are connected
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(17, 0));
	EXPECT_EQ(16, presentationModel->getConnectionNodeById(17, 1));
}

// 代刚 testRedoConnectComponent 
TEST_F(ER_IntegrationTest, testCommonUsage)
{
	string message;
	// Load the ¨test_file1.erd〃 under the ¨testdata〃 directory
	message = presentationModel->readComponentsFile("testdata//test_file1.erd");

	// Assert the diagram is loaded correctly 
	EXPECT_EQ("The ER diagram is displayed as follows:\nComponents:\n------------------------------------\n Type |  ID  |  Name \n------+------+----------------------\n  E   |   0   |   Engineer\n  A   |   1   |   Emp_ID\n  R   |   2   |   Has\n  A   |   3   |   Name\n  E   |   4   |   PC\n  A   |   5   |   PC_ID\n  A   |   6   |   Purchase_Date\n  C   |   7   |   \n  C   |   8   |   \n  C   |   9   |   \n  C   |   10   |   \n  C   |   11   |   1\n  C   |   12   |   1\n  A   |   13   |   Department\n  C   |   14   |   \n------------------------------------\n\nConnections:\n------------------------------------\nConnection | node | node\n-----------+------+-----------------\n       7   |  0   |  1\n       8   |  0   |  3\n       9   |  4   |  5\n       10   |  4   |  6\n       11   |  0   |  2\n       12   |  2   |  4\n       14   |  0   |  13\n------------------------------------\n", message);

	// Add an entity with text ¨Work Diary〃
	EXPECT_EQ(15, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Entity, "Work Diary", 0, 0);

	// Assert the entity is added correctly
	EXPECT_EQ(16, presentationModel->findComponents().size());
	EXPECT_EQ("Work Diary", presentationModel->getNameById(15));

	// Add a Relationship with text "Write"  
	EXPECT_EQ(16, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Relationship, "Write", 0, 0);

	// Assert the Relationship is added correctly  
	EXPECT_EQ(17, presentationModel->findComponents().size());
	EXPECT_EQ("Write", presentationModel->getNameById(16));

	// Connect node 0 and 16, and set its cardinality as "1"
	presentationModel->addConnection(0, 16, ERD_Connection::one);

	// Assert node 0 and 16 are connected
	EXPECT_EQ(18, presentationModel->findComponents().size());
	EXPECT_EQ(0, presentationModel->getConnectionNodeById(17, 0));
	EXPECT_EQ(16, presentationModel->getConnectionNodeById(17, 1));

	// Connect node 15 and 16
	presentationModel->addConnection(15, 16, ERD_Connection::one);

	// Assert node 15 and 16 are connected 
	EXPECT_EQ(19, presentationModel->findComponents().size());
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(18, 0));
	EXPECT_EQ(16, presentationModel->getConnectionNodeById(18, 1));

	// Add an Attribute with text "Content" 
	EXPECT_EQ(19, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Attribute, "Content", 0, 0); //id:19

	// Assert the Attribute is added correctly 
	EXPECT_EQ(20, presentationModel->findComponents().size());
	EXPECT_EQ("Content", presentationModel->getNameById(19));

	// Add an Attribute with text "WD_ID" 
	EXPECT_EQ(20, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Attribute, "WD_ID", 0, 0); //id:20

	// Assert the Attribute is added correctly 
	EXPECT_EQ(21, presentationModel->findComponents().size());
	EXPECT_EQ("WD_ID", presentationModel->getNameById(20));

	// Add an Attribute with text "WD_date" 
	EXPECT_EQ(21, presentationModel->findComponents().size());
	presentationModel->addNode(ERD_Component::Attribute, "WD_date", 0, 0); //id:21

	// Assert the Attribute is added correctly 
	EXPECT_EQ(22, presentationModel->findComponents().size());
	EXPECT_EQ("WD_date", presentationModel->getNameById(21));

	// Connect node 15 and 19 
	EXPECT_EQ(22, presentationModel->findComponents().size());
	string connectionMessage = presentationModel->getAddConnectionMessage(15, 19);
	EXPECT_EQ("The node '15' has been connected to the node '19'.", connectionMessage);
	
	// Assert node 15 and 19 are connected 
	EXPECT_EQ(23, presentationModel->findComponents().size());
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(22, 0));
	EXPECT_EQ(19, presentationModel->getConnectionNodeById(22, 1));

	// Connect node 15 and 20 
	EXPECT_EQ(23, presentationModel->findComponents().size());
	connectionMessage = presentationModel->getAddConnectionMessage(15, 20);
	EXPECT_EQ("The node '15' has been connected to the node '20'.", connectionMessage);

	// Assert node 15 and 20 are connected 
	EXPECT_EQ(24, presentationModel->findComponents().size());
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(23, 0));
	EXPECT_EQ(20, presentationModel->getConnectionNodeById(23, 1));

	// Connect node 15 and 21 
	EXPECT_EQ(24, presentationModel->findComponents().size());
	connectionMessage = presentationModel->getAddConnectionMessage(15, 21);
	EXPECT_EQ("The node '15' has been connected to the node '21'.", connectionMessage);

	// Assert node 15 and 21 are connected 
	EXPECT_EQ(25, presentationModel->findComponents().size());
	EXPECT_EQ(15, presentationModel->getConnectionNodeById(24, 0));
	EXPECT_EQ(21, presentationModel->getConnectionNodeById(24, 1));

	// Set "Work Diary" primary key "WD_ID" 
	presentationModel->setIsPrimaryKey(20, true);

	// Assert "Work Diary" has the primary key "WD_ID"  
	EXPECT_EQ(true, presentationModel->getIsPrimaryKey(20));

	// Display the table 
	message = presentationModel->getTable(); //notice
	EXPECT_EQ("Tables:\n----------------------------------------------------------\n  Entity  |  Attribute\n----------+-----------------------------------------------\n Engineer | PK(Emp_ID, Name), Department, FK(PC_ID), FK(WD_ID)\n PC | PK(PC_ID), Purchase_Date\n Work Diary | PK(WD_ID), Content, WD_date\n----------------------------------------------------------\n", message);
	
	// Assert the Entity "Work Diary" exists 
	EXPECT_EQ("Work Diary", presentationModel->getNameById(15));

	// Assert Work Diary's primary key is "WD_ID" 
	string primaryKeyString = presentationModel->getPrimaryKeyString(15);
	EXPECT_EQ("20", primaryKeyString);

	// Delete the Entity he/she added above 
	presentationModel->deleteComponent(15);

	// Assert the Entity has been deleted 
	EXPECT_EQ("", presentationModel->getNameById(15));

	// Assert there is no connection between node 15 and 16  
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(18, 0));
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(18, 1));

	// Assert there is no connection between node 15 and 19  
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(22, 0));
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(22, 1));

	// Assert there is no connection between node 15 and 20  
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(23, 0));
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(23, 1));

	// Assert there is no connection between node 15 and 21  

	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(24, 0));
	EXPECT_EQ(-1, presentationModel->getConnectionNodeById(24, 1));

	// Display the table
	message = presentationModel->getTable();
	EXPECT_EQ("Tables:\n----------------------------------------------------------\n  Entity  |  Attribute\n----------+-----------------------------------------------\n Engineer | PK(Emp_ID, Name), Department, FK(PC_ID)\n PC | PK(PC_ID), Purchase_Date\n----------------------------------------------------------\n", message);
	
	// Assert the Entity "Work Diary" does not exist 
	EXPECT_EQ("", presentationModel->getNameById(15));

	// Assert Engineer's primary key is "Name" and "Emp_ID" 
	primaryKeyString = presentationModel->getPrimaryKeyString(0);
	EXPECT_EQ("1, 3", primaryKeyString);  // 1: Name 3: Emp_ID

	// Undo 
	presentationModel->undo();
	// Display the table 
	message = presentationModel->getTable(); //notice
	EXPECT_EQ("Tables:\n----------------------------------------------------------\n  Entity  |  Attribute\n----------+-----------------------------------------------\n Engineer | PK(Emp_ID, Name), Department, FK(PC_ID), FK(WD_ID)\n PC | PK(PC_ID), Purchase_Date\n Work Diary | PK(WD_ID), Content, WD_date\n----------------------------------------------------------\n", message);

	// Assert Work Diary's primary key is "WD_ID" 
	primaryKeyString = presentationModel->getPrimaryKeyString(15);
	EXPECT_EQ("20", primaryKeyString);

	// Redo 
	presentationModel->redo();

	// Assert the Entity "Work Diary" does not exist 
	EXPECT_EQ("", presentationModel->getNameById(15));

	// Assert Engineer's primary key is "Name" and "Emp_ID"
	primaryKeyString = presentationModel->getPrimaryKeyString(0);
	EXPECT_EQ("1, 3", primaryKeyString);  // 1: Name 3: Emp_ID
}