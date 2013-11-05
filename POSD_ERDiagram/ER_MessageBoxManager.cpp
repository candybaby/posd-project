#include "ER_MessageBoxManager.h"

// 顯示MessageBox
void ER_MessageBoxManager::showMessageBox(string sourceString)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("MessageBox");
	msgBox.setText(QString(QString::fromLocal8Bit(sourceString.c_str())));
	msgBox.exec();
}

// 顯示MessageBox
void ER_MessageBoxManager::showMessageBox(string sourceString, string titleString)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(QString(QString::fromLocal8Bit(titleString.c_str())));
	msgBox.setText(QString(QString::fromLocal8Bit(sourceString.c_str())));
	msgBox.exec();
}