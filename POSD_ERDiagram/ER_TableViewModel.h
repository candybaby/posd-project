#pragma once
#ifndef _ER_TABLE_VIEW_MODEL_ 
#define _ER_TABLE_VIEW_MODEL_
#include <QStandardItemModel>
#include "ER_PresentationModel.h"
#include "ER_ItemFactory.h"
#include "ER_TableViewItem.h"

class ER_TableViewModel : public QStandardItemModel
{
public:
	struct ItemSorter
	{
		bool ItemSorter::operator ()(ER_TableViewItem* leftComponent, ER_TableViewItem* rightComponent)
		{
			return leftComponent->getId() < rightComponent->getId();
		}
	};
	ER_TableViewModel();
	~ER_TableViewModel();
	void mappingItems(QString);
	void sortItems();
	void mappingItemsToTable();
	QString getTextByIndex(QModelIndex);
	QString getEditedResultText(QModelIndex);
	int getIdByIndex(QModelIndex);
	void removeAllItems();
	void updateItemFromFile(string, string);

private:
	ER_ItemFactory* itemFactory;
	QList<ER_TableViewItem*> tableViewItems;
};
#endif
