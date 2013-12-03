#pragma once
#ifndef _ER_TABLE_VIEWL_ 
#define _ER_TABLE_VIEW_
#include "QTableView"
#include "ER_PresentationModel.h"
#include "ER_Observer.h"
#include <QObject>

class ER_TableView : public QTableView, public ER_Observer
{
	Q_OBJECT
public:
	ER_TableView(ER_PresentationModel*);
	~ER_TableView(void);
	void closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint);
	void updateItems();
	void updateItemsFromFile();
	void updateAddComponent(string);
	void updateConnectComponents(string);
	void updateSetPrimaryKey(int, bool);
	void updateDeleteComponents(string);
	void updateUndoEnable(bool);
	void updateRedoEnable(bool);
	void updateEditText(int, string);
	void updateEditTextReject();
	void updateMoveComponents(string);
	
protected slots:
	void doubleClickedEvent(const QModelIndex&);

private:
	ER_PresentationModel* presentationModel;
	QModelIndex currentIndex;
};

#endif