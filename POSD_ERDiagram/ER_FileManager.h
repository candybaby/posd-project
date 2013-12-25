#pragma once
#ifndef _ER_FILEMANAGER_ 
#define _ER_FILEMANAGER_
#include <iostream> 
#include <fstream> 
#include <string>
#include "gtest/gtest_prod.h"

using namespace std;

class ER_FileManager
{
friend class ER_FileManagerTest;
FRIEND_TEST(ER_FileManagerTest, closeFile);

public:
	enum FileType
	{
		Read,
		Write
	};
	ER_FileManager(void);
	~ER_FileManager(void);
	bool openFile(string, FileType);
	void writeLine(string);
	void write(string);
	string readFile();
	void closeFile();
	bool isTestCantWrite;

private:
	ofstream fout;
	ifstream fin;
};
#endif
