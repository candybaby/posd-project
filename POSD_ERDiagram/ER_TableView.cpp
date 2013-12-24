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

// �ƹ��s�I�ƥ�
void ER_TableView::doubleClickedEvent(const QModelIndex& index)
{
	currentIndex = index;
}

// �����s�边
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

// ��s����
void ER_TableView::updateItems()
{
	ER_TableViewModel* model = (ER_TableViewModel*)this->model();
	model->removeAllItems();
	string nodesMessage = presentationModel->getGuiNodes();
	string connectionsMessage = presentationModel->getGuiConnections();
	model->updateItemFromFile(nodesMessage, connectionsMessage);
}

// ��s ����Ӧ�file
void ER_TableView::updateItemsFromFile()
{
	updateItems();
}

// ��s �s�WComponent
void ER_TableView::updateAddComponent(string)
{
	updateItems();
}

// ��s �s�uComponent
void ER_TableView::updateConnectComponents(string)
{
	updateItems();
}

// ��s Set Primary Key
void ER_TableView::updateSetPrimaryKey(int, bool)
{
	//updateItems();
}

// ��s Delete Components
void ER_TableView::updateDeleteComponents(string)
{
	updateItems();
}

// ��s undo enable
void ER_TableView::updateUndoEnable(bool)
{
	updateItems();
}

// ��s redo enable
void ER_TableView::updateRedoEnable(bool)
{
	updateItems();
}

// ��s Edit Text
void ER_TableView::updateEditText(int, string)
{
	updateItems();
}

// ��s Edit Text Reject
void ER_TableView::updateEditTextReject()
{
	updateItems();
}

// ��s Move Components
void ER_TableView::updateMoveComponents(string)
{
	// empty
}

// ��s Can Paste State
void ER_TableView::updateCanPasteState(bool)
{
	// empty
}

// ��s debug message
void ER_TableView::updateDebugMessage(string)
{
	// empty
}