#include "ER_FileManager.h"


ER_FileManager::ER_FileManager(void)
{
}


ER_FileManager::~ER_FileManager(void)
{
}

bool ER_FileManager::openFile(string path, FileType type)
{
	if (type == Write)
	{
		fout.open(path);
		if (!fout.is_open())
		{
			return false; // 無法寫入檔案
		}
		else
		{
			return true;
		}
	}
	
	if (type == Read)
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
	
	return false;
}

string ER_FileManager::readFile()
{
	string result, line;
	while (getline(fin, line))
	{
		result += line + "\n";
	}
	return result;
}

void ER_FileManager::writeLine(string content)
{
	fout << content.c_str() << endl;
}

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