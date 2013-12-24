#include "ER_TableView.h"
#include "ER_TableViewModel.h"
#include "QDebug"


ER_TableView::ER_TableView(ER_PresentationModel* presentationModel)
{
	this->presentationModel = presentationModel;
	this->presentationModel->registerModelObserver(this);
	connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(doubleClickedEvent(const QModelIndex&)));
}


ER_TableView::~ER_TableView(void)
{
}

// 滑鼠連點事件
void ER_TableView::doubleClickedEvent(const QModelIndex& index)
{
	currentIndex = index;
}

// 關閉編輯器
void ER_TableView::closeEditor(QWidget* editer, QAbstractItemDelegate::EndEditHint hint)
{
	ER_TableViewModel* model = (ER_TableViewModel*)this->model();
	QString text = model->getEditedResultText(currentIndex);
	int id = model->getIdByIndex(currentIndex);
	if (text != "")
	{
		presentationModel->setComponentText(id, text.toStdString());
	}
	QTableView::closeEditor(editer, hint);
}

// 更新物件
void ER_TableView::updateItems()
{
	ER_TableViewModel* model = (ER_TableViewModel*)this->model();
	model->removeAllItems();
	string nodesMessage = presentationModel->getGuiNodes();
	string connectionsMessage = presentationModel->getGuiConnections();
	model->updateItemFromFile(nodesMessage, connectionsMessage);
}

// 更新 物件來自file
void ER_TableView::updateItemsFromFile()
{
	updateItems();
}

// 更新 新增Component
void ER_TableView::updateAddComponent(string)
{
	updateItems();
}

// 更新 連線Component
void ER_TableView::updateConnectComponents(string)
{
	updateItems();
}

// 更新 Set Primary Key
void ER_TableView::updateSetPrimaryKey(int, bool)
{
	//updateItems();
}

// 更新 Delete Components
void ER_TableView::updateDeleteComponents(string)
{
	updateItems();
}

// 更新 undo enable
void ER_TableView::updateUndoEnable(bool)
{
	updateItems();
}

// 更新 redo enable
void ER_TableView::updateRedoEnable(bool)
{
	updateItems();
}

// 更新 Edit Text
void ER_TableView::updateEditText(int, string)
{
	updateItems();
}

// 更新 Edit Text Reject
void ER_TableView::updateEditTextReject()
{
	updateItems();
}

// 更新 Move Components
void ER_TableView::updateMoveComponents(string)
{
	// empty
}

// 更新 Can Paste State
void ER_TableView::updateCanPasteState(bool)
{
	// empty
}

// 更新 debug message
void ER_TableView::updateDebugMessage(string)
{
	// empty
}