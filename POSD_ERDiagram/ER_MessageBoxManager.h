#pragma once
#ifndef _MESSAGEBOX_MANAGER_ 
#define _MESSAGEBOX_MANAGER_
#include <QMessageBox>

using namespace std;
class ER_MessageBoxManager
{
public:
	static void showMessageBox(string);
	static void showMessageBox(string, string);
};

#endif
