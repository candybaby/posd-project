#include "ER_TableViewItem.h"


ER_TableViewItem::ER_TableViewItem(int id, QString text, QString type)
{
	this->id = id;
	this->text = text;
	this->type = type;
}


ER_TableViewItem::~ER_TableViewItem()
{
}

void ER_TableViewItem::setText(QString text)
{
	this->text = text;
}

int ER_TableViewItem::getId()
{
	return this->id;
}

QString ER_TableViewItem::getText()
{
	return this->text;
}

QString ER_TableViewItem::getType()
{
	return this->type;
}
