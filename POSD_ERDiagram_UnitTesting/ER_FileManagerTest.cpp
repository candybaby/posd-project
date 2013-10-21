#include "ER_FileManager.h"
#include "gtest/gtest.h"

using namespace std;
class ER_FileManagerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		fileManager = new ER_FileManager();
	}

	virtual void TearDown()
	{
		delete fileManager;
	}

	ER_FileManager* fileManager;
};

// 測試 開啟檔案
TEST_F(ER_FileManagerTest, openFile)
{
	// 測試
	// 參數:string(path), FileType(type)
	// 回傳:bool(result)
	// 附註:無
	bool result;
	result = fileManager->openFile("unittest//test_file1.erd", ER_FileManager::Read);
	EXPECT_EQ(true, result);
	fileManager->closeFile();
	TearDown();

	SetUp();
	result = fileManager->openFile("unittest//file_not_found.erd", ER_FileManager::Read);
	EXPECT_EQ(false, result);
	fileManager->closeFile();
	TearDown();

	SetUp();
	result = fileManager->openFile("unittest//test_write.erd", ER_FileManager::Write);
	EXPECT_EQ(true, result);
	fileManager->closeFile();
	TearDown();

	SetUp();
	fileManager->isTestCantWrite = true;
	result = fileManager->openFile("unittest//test_cant_write.erd", ER_FileManager::Write);
	EXPECT_EQ(false, result);
	fileManager->closeFile();
}

// 測試 讀檔案(行)
TEST_F(ER_FileManagerTest, readFile)
{
	// 測試
	// 參數:無
	// 回傳:string
	// 附註:無
	fileManager->openFile("unittest//test_file1_part3.erd", ER_FileManager::Read);
	string result;
	result = fileManager->readFile();
	EXPECT_EQ("0 1,3\n4 5\n", result);
	fileManager->closeFile();
}

// 測試 寫檔案
TEST_F(ER_FileManagerTest, writeLine)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	fileManager->openFile("unittest//test_write.erd", ER_FileManager::Write);
	fileManager->writeLine("test write line");
	fileManager->closeFile();
	fileManager->openFile("unittest//test_write.erd", ER_FileManager::Read);
	EXPECT_EQ("test write line\n", fileManager->readFile());
	fileManager->closeFile();
}

// 測試 關閉檔案
TEST_F(ER_FileManagerTest, closeFile)
{
	// 測試
	// 參數:無
	// 回傳:""
	// 附註:無
	fileManager->openFile("unittest//test_file1.erd", ER_FileManager::Read);
	fileManager->closeFile();
	EXPECT_EQ(false, fileManager->fin.is_open());
	TearDown();

	SetUp();
	fileManager->openFile("unittest//test_write.erd", ER_FileManager::Write);
	fileManager->closeFile();
	EXPECT_EQ(false, fileManager->fout.is_open());
}