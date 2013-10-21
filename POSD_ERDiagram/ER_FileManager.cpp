#include "ER_FileManager.h"

ER_FileManager::ER_FileManager(void)
{
	isTestCantWrite = false;
}

ER_FileManager::~ER_FileManager(void)
{
}

// �}���ɮ�
bool ER_FileManager::openFile(string path, FileType type)
{
	if (type == Write)
	{
		fout.open(path);
		if (!fout.is_open() || isTestCantWrite)
		{
			return false; // �L�k�g�J�ɮ�
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
			return false; // �L�kŪ���ɮ�
		}
		else
		{
			return true;
		}
	}
}

// Ū�ɮ�(��)
string ER_FileManager::readFile()
{
	string result, line;
	while (getline(fin, line))
	{
		result += line + "\n";
	}
	return result;
}

// �g�ɮ�
void ER_FileManager::writeLine(string content)
{
	fout << content.c_str() << endl;
}

// �����ɮ�
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