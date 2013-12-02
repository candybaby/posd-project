#pragma once
#ifndef _ER_TABLE_VIEW_ITEM_ 
#define _ER_TABLE_VIEW_ITEM_
#include "QString"
class ER_TableViewItem
{
public:
	ER_TableViewItem(int, QString, QString);
	~ER_TableViewItem();
	void setText(QString);
	int getId();
	QString getText();
	QString getType();

private:
	int id;
	QString text;
	QString type;
};
#endif
