#pragma once
#include <iostream> 
#include <fstream> 
#include <string>
#ifndef _ER_FILEMANAGER_ 
#define _ER_FILEMANAGER_

using namespace std;

class ER_FileManager
{
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
	string readFile();
	void closeFile();

private:
	ofstream fout;
	ifstream fin;
};
#endif
