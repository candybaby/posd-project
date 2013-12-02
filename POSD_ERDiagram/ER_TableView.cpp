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

void ER_TableView::doubleClickedEvent(const QModelIndex& index)
{
	qDebug() << "Index" << index.column() << ", " << index.row();
	currentIndex = index;
}

void ER_TableView::closeEditor(QWidget* editer, QAbstractItemDelegate::EndEditHint hint)
{
	qDebug() << "closeEditor" << editer;
	ER_TableViewModel* model = (ER_TableViewModel*)this->model();
	QString text = model->getEditedResultText(currentIndex);
	int id = model->getIdByIndex(currentIndex);
	if (text != "")
	{
		presentationModel->setComponentText(id, text.toStdString());
	}
	QTableView::closeEditor(editer, hint);
}

void ER_TableView::updateItems()
{
	ER_TableViewModel* model = (ER_TableViewModel*)this->model();
	model->removeAllItems();
	string nodesMessage = presentationModel->getGuiNodes();
	string connectionsMessage = presentationModel->getGuiConnections();
	model->updateItemFromFile(nodesMessage, connectionsMessage);
}

void ER_TableView::updateItemsFromFile()
{
	updateItems();
}

void ER_TableView::updateAddComponent(string)
{
	updateItems();
}

void ER_TableView::updateConnectComponents(string)
{
	updateItems();
}

void ER_TableView::updateSetPrimaryKey(int, bool)
{
	//updateItems();
}

void ER_TableView::updateDeleteComponents(string)
{
	updateItems();
}

void ER_TableView::updateUndoEnable(bool)
{
	updateItems();
}

void ER_TableView::updateRedoEnable(bool)
{
	updateItems();
}

void ER_TableView::updateEditText(int, string)
{
	updateItems();
}

void ER_TableView::updateEditTextReject()
{
	updateItems();
}

void ER_TableView::updateMoveComponent(string)
{
	// empty
}