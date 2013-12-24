#include "ER_TableViewModel.h"
#include "QtDebug"


ER_TableViewModel::ER_TableViewModel()
{
	setColumnCount(2);
	setHeaderData(0, Qt::Horizontal, "Type");
	setHeaderData(1, Qt::Horizontal, "Text");
}

ER_TableViewModel::~ER_TableViewModel()
{
	removeAllItems();
}

// �T��������items
void ER_TableViewModel::mappingItems(QString message)
{
	QStringList componentsList = message.split('\n');

	for (int i = 0; i < componentsList.size() - 1; i++)
	{
		QStringList componentList = componentsList.at(i).split(',');
		ER_TableViewItem* item = itemFactory->createTableItem(componentList);
		tableViewItems.push_back(item);
	}
}

// �̾�id�Nitem���ssort�@�M
void ER_TableViewModel::sortItems()
{
	ItemSorter ItemSorter;
	std::sort(tableViewItems.begin(), tableViewItems.end(), ItemSorter);
}

// �NtableViewItems ���e��mtable�W
void ER_TableViewModel::mappingItemsToTable()
{
	for (int i = 0; i < tableViewItems.size(); i++)
	{
		QStandardItem* typeItem = new QStandardItem(tableViewItems.at(i)->getType());
		typeItem->setEditable(false);
		setItem(i, 0 , typeItem);
		QString text = tableViewItems.at(i)->getText() + " id: ";
		text.append(QString::number(tableViewItems.at(i)->getId()));
		setItem(i, 1 , new QStandardItem(text));
		//setItem(i, 1 , new QStandardItem(tableViewItems.at(i)->getText()));
	}
}

// ��s����Ӧ�File
void ER_TableViewModel::updateItemFromFile(string nodeMessage, string connectionsMessage)
{
	mappingItems(QString(QString::fromLocal8Bit(nodeMessage.c_str())));
	mappingItems(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));
	sortItems();
	mappingItemsToTable();
}

// ���o�ھ�Index�ҭn��Text
QString ER_TableViewModel::getTextByIndex(QModelIndex index)
{
	return item(index.row(), index.column())->text();
}

// ���o�s�觹���᪺���G��r
QString ER_TableViewModel::getEditedResultText(QModelIndex index)
{
	QString result, itemText = getTextByIndex(index);
	ER_TableViewItem* viewItem = tableViewItems.at(index.row());
	if (viewItem->getText() == itemText)
	{
		result = "";
	}
	else if (itemText == "")
	{
		item(index.row(), index.column())->setText(viewItem->getText());
	}
	else
	{
		result = itemText;
	}
	return result;
}

// ���o�ھ�Index�ҭn��ID
int ER_TableViewModel::getIdByIndex(QModelIndex index)
{
	int row = index.row();
	return tableViewItems.at(row)->getId();
}

// �R��������Items
void ER_TableViewModel::removeAllItems()
{
	removeRows(0, rowCount());
	while (tableViewItems.size() > 0)
	{
		ER_TableViewItem* delData = tableViewItems.back();
		tableViewItems.pop_back();
		delete delData;
	}
}


