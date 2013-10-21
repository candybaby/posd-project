#include "ER_FileManager.h"

ER_FileManager::ER_FileManager(void)
{
	isTestCantWrite = false;
}

ER_FileManager::~ER_FileManager(void)
{
}

// 開啟檔案
bool ER_FileManager::openFile(string path, FileType type)
{
	if (type == Write)
	{
		fout.open(path);
		if (!fout.is_open() || isTestCantWrite)
		{
			return false; // 無法寫入檔案
		}
		else
		{
			return true;
		}
	}
	else // type == Read
	{
		fin.open(path);
		if (!fin.is_open())
		{
			return false; // 無法讀取檔案
		}
		else
		{
			return true;
		}
	}
}

// 讀檔案(行)
string ER_FileManager::readFile()
{
	string result, line;
	while (getline(fin, line))
	{
		result += line + "\n";
	}
	return result;
}

// 寫檔案
void ER_FileManager::writeLine(string content)
{
	fout << content.c_str() << endl;
}

// 關閉檔案
void ER_FileManager::closeFile()
{
	if (fout)
	{
		fout.close();
	}
	if (fin)
	{
		fin.close();
	}
}