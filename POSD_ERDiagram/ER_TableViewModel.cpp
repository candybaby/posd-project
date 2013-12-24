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

// 訊息對應到items
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

// 依據id將item重新sort一遍
void ER_TableViewModel::sortItems()
{
	ItemSorter ItemSorter;
	std::sort(tableViewItems.begin(), tableViewItems.end(), ItemSorter);
}

// 將tableViewItems 內容放置table上
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

// 更新物件來自File
void ER_TableViewModel::updateItemFromFile(string nodeMessage, string connectionsMessage)
{
	mappingItems(QString(QString::fromLocal8Bit(nodeMessage.c_str())));
	mappingItems(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));
	sortItems();
	mappingItemsToTable();
}

// 取得根據Index所要的Text
QString ER_TableViewModel::getTextByIndex(QModelIndex index)
{
	return item(index.row(), index.column())->text();
}

// 取得編輯完成後的結果文字
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

// 取得根據Index所要的ID
int ER_TableViewModel::getIdByIndex(QModelIndex index)
{
	int row = index.row();
	return tableViewItems.at(row)->getId();
}

// 刪除全部的Items
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


