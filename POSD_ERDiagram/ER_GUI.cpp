#include <QtGui>
#include <QLabel>
#include <QHeaderView>
#include "ER_GUI.h"
#include <QFileDialog>
#include "ER_ItemEntity.h"
#include "ER_ItemAttribute.h"
#include "ER_ItemRelationship.h"
#include "ER_ItemConnection.h"

ER_GUI::ER_GUI(ER_PresentationModel* presentationModel)
{
	this->presentationModel = presentationModel;
	createActions();
	createMenus();
	createToolbars();
	scene = new ER_DiagramScene(presentationModel, this);
	scene->setSceneRect(QRectF(0, 0, 4000, 3000));
	view = new QGraphicsView(scene);

	tableViewModel = new ER_TableViewModel();
	tableView = new ER_TableView(this->presentationModel);
	tableView->setModel(tableViewModel);
	tableView->setAutoScroll(true);
	QHeaderView* headerView = tableView->horizontalHeader();
	headerView->setStretchLastSection(true);

	QLabel* label = new QLabel;
	label->setText("Components");
	label->setStyleSheet("QLabel { background-color : #b3b3b3; qproperty-alignment: AlignCenter; }");
	QFont font;
	font.setPointSize(16);
	font.setBold(true);
	label->setFont(font);

	QSplitter* tableViewBox = new QSplitter;
	tableViewBox->setOrientation(Qt::Vertical);
	tableViewBox->addWidget(label);
	tableViewBox->addWidget(tableView);

	//
	textViewer = new ER_TextView(this->presentationModel);
	textViewer->setReadOnly(true);
	textViewer->setVisible(false);
	QSplitter* sceneTableBox = new QSplitter;
	sceneTableBox->setOrientation(Qt::Vertical);
	sceneTableBox->addWidget(view);
	sceneTableBox->addWidget(textViewer);
	//

	QSplitter* splitter = new QSplitter;
	splitter->addWidget(sceneTableBox);
	splitter->addWidget(tableViewBox);
	QList<int> sizes;
	sizes.push_back(900);
	sizes.push_back(300);
	splitter->setSizes(sizes);
	
	setCentralWidget(splitter);
	view->setMouseTracking(true);
}


ER_GUI::~ER_GUI(void)
{
	delete scene;
	delete view;
	delete fileMenu;
	delete addItemMenu;
	delete editMenu;
	delete fileToolBar;
	delete editorToolBar;
	delete stateToolBar;
	delete stateTypeButtonGroup;
	delete exitAction;
	delete openAction;
	delete addAttributeAction;
	delete addEntityAction;
	delete addRelationshipAction;
	delete undoAction;
	delete redoAction;
	delete deleteItemAction;
	delete cutAction;
	delete copyAction;
	delete pasteAction;
	delete saveAction;
	delete saveAsXmlAction;
	delete presentationModel;
}

// 創建Actions
void ER_GUI::createActions()
{
	openAction = new QAction(QIcon("images/folder.png"), tr("O&pen..."), this);
	openAction->setShortcut(tr("Ctrl+O"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(browse()));

	saveAction = new QAction(QIcon("images/save.png"), tr("S&ave"), this);
	saveAction->setShortcut(tr("Ctrl+S"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveComponent()));

	saveAsXmlAction = new QAction(tr("S&ave as xml"), this);
	connect(saveAsXmlAction, SIGNAL(triggered()), this, SLOT(saveComponentAsXml()));

	exitAction = new QAction(QIcon("images/exit.png"), tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	addAttributeAction = new QAction(tr("A&ttribute"), this);
	connect(addAttributeAction, SIGNAL(triggered()), this, SLOT(changeToAddAttributeMode()));

	addEntityAction = new QAction(tr("E&ntity"), this);
	connect(addEntityAction, SIGNAL(triggered()), this, SLOT(changeToAddEntityMode()));

	addRelationshipAction = new QAction(tr("R&elationship"), this);
	connect(addRelationshipAction, SIGNAL(triggered()), this, SLOT(changeToAddRelationShipMode()));

	undoAction = new QAction(QIcon("images/undo.png"), tr("U&ndo"), this);
	undoAction->setShortcut(tr("Ctrl+Z"));
	undoAction->setEnabled(false);
	connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

	redoAction = new QAction(QIcon("images/redo.png"), tr("R&edo"), this);
	redoAction->setShortcut(tr("Ctrl+Y"));
	redoAction->setEnabled(false);
	connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

	deleteItemAction = new QAction(QIcon("images/delete.png"), tr("D&elete"), this);
	deleteItemAction->setShortcut(QKeySequence::Delete);
	deleteItemAction->setEnabled(false);
	connect(deleteItemAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

	cutAction = new QAction(QIcon("images/cut.png"), tr("C&ut"), this);
	cutAction->setShortcut(tr("Ctrl+X"));
	cutAction->setEnabled(false);
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

	copyAction = new QAction(QIcon("images/copy.png"), tr("C&opy"), this);
	copyAction->setShortcut(tr("Ctrl+C"));
	copyAction->setEnabled(false);
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

	pasteAction = new QAction(QIcon("images/paste.png"), tr("P&aste"), this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setEnabled(false);
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

	aboutAction = new QAction(tr("A&bout"), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
}

// 創建Menus
void ER_GUI::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsXmlAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	addItemMenu = menuBar()->addMenu(tr("&Add"));
	addItemMenu->addAction(addAttributeAction);
	addItemMenu->addAction(addEntityAction);
	addItemMenu->addAction(addRelationshipAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAction);
	editMenu->addAction(redoAction);
	editMenu->addAction(deleteItemAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
}

// 創建Toolbars
void ER_GUI::createToolbars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(saveAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(exitAction);

	editorToolBar = addToolBar(tr("edit"));
	editorToolBar->addAction(undoAction);
	editorToolBar->addSeparator();
	editorToolBar->addAction(redoAction);
	editorToolBar->addSeparator();
	editorToolBar->addAction(deleteItemAction);
	editorToolBar->addSeparator();
	editorToolBar->addAction(cutAction);
	editorToolBar->addSeparator();
	editorToolBar->addAction(copyAction);
	editorToolBar->addSeparator();
	editorToolBar->addAction(pasteAction);

	QToolButton* pointerButton = new QToolButton;
	pointerButton->setCheckable(true);
	pointerButton->setChecked(true);
	pointerButton->setIcon(QIcon("images/pointer.png"));

	QToolButton* attributeButton = new QToolButton;
	attributeButton->setCheckable(true);
	attributeButton->setIcon(QIcon("images/attribute.png"));

	QToolButton* entityButton = new QToolButton;
	entityButton->setCheckable(true);
	entityButton->setIcon(QIcon("images/entity.png"));

	QToolButton* relationshipButton = new QToolButton;
	relationshipButton->setCheckable(true);
	relationshipButton->setIcon(QIcon("images/relationship.png"));

	QToolButton* connecterButton = new QToolButton;
	connecterButton->setCheckable(true);
	connecterButton->setIcon(QIcon("images/linepointer.png"));

	QToolButton* primaryKeySettingButton = new QToolButton;
	primaryKeySettingButton->setCheckable(true);
	primaryKeySettingButton->setIcon(QIcon("images/key.png"));

	stateTypeButtonGroup = new QButtonGroup(this);
	stateTypeButtonGroup->addButton(pointerButton, ER_DiagramScene::Pointer);
	stateTypeButtonGroup->addButton(attributeButton, ER_DiagramScene::InsertAttribute);
	stateTypeButtonGroup->addButton(entityButton, ER_DiagramScene::InsertEntity);
	stateTypeButtonGroup->addButton(relationshipButton, ER_DiagramScene::InsertRelationship);
	stateTypeButtonGroup->addButton(connecterButton, ER_DiagramScene::Connecter);
	stateTypeButtonGroup->addButton(primaryKeySettingButton, ER_DiagramScene::SetPrimaryKey);
	connect(stateTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

	QToolButton* tableViewButton = new QToolButton;
	tableViewButton->setCheckable(true);
	tableViewButton->setIcon(QIcon("images/tableView.png"));
	connect(tableViewButton, SIGNAL(pressed()), this, SLOT(textViewSwitch()));

	stateToolBar = addToolBar(tr("State"));
	stateToolBar->addWidget(pointerButton);
	stateToolBar->addWidget(attributeButton);
	stateToolBar->addWidget(entityButton);
	stateToolBar->addWidget(relationshipButton);
	stateToolBar->addSeparator();
	stateToolBar->addWidget(connecterButton);
	stateToolBar->addSeparator();
	stateToolBar->addWidget(primaryKeySettingButton);
	stateToolBar->addSeparator();
	stateToolBar->addWidget(tableViewButton);
}

void ER_GUI::setDeleteEnable(bool flag)
{
	deleteItemAction->setEnabled(flag);
}

void ER_GUI::setUndoEnable(bool flag)
{
	undoAction->setEnabled(flag);
}

void ER_GUI::setRedoEnable(bool flag)
{
	redoAction->setEnabled(flag);
}

void ER_GUI::setCutEnable(bool flag)
{
	cutAction->setEnabled(flag);
}

void ER_GUI::setCopyEnable(bool flag)
{
	copyAction->setEnabled(flag);
}

void ER_GUI::setPasteEnable(bool flag)
{
	pasteAction->setEnabled(flag);
}

void ER_GUI::checkWannaSave()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, tr("Entity Relation Diagramming Tool"),
		"The diagram has been modified.<br />Do you want to save your changes?",
		QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		saveComponent();
	}
}

void ER_GUI::closeEvent(QCloseEvent* event)
{
	if (presentationModel->getHasModify())
	{
		checkWannaSave();
	}
	QMainWindow::closeEvent(event);
}

// 瀏覽檔案總管
void ER_GUI::browse()
{
	QString directory = QFileDialog::getOpenFileName(this, tr("Find File"), "C://", tr("ERD File (*.erd)"));
	if (directory != "")
	{
		presentationModel->readComponentsFile(directory.toStdString());
	}
}

// 存檔
void ER_GUI::saveComponent()
{
	QString directory = QFileDialog::getSaveFileName(this, tr("Save File"), "C://", tr("ERD File (*.erd)"));
	if (directory != "")
	{
		presentationModel->storeComponents(directory.toStdString());
	}
}

// 存檔 XML格式
void ER_GUI::saveComponentAsXml()
{
	QString directory = QFileDialog::getSaveFileName(this, tr("Save File"), "C://", tr("XML File (*.xml)"));
	if (directory != "")
	{
		presentationModel->storeComponentsAsXml(directory.toStdString());
	}
}

// 處理點選pointerGroup事件
void ER_GUI::pointerGroupClicked(int index)
{
	scene->setMode(ER_DiagramScene::Mode(stateTypeButtonGroup->checkedId()));
}

void ER_GUI::changeToPointerMode()
{
	stateTypeButtonGroup->button((int)ER_DiagramScene::Pointer)->click();
}

void ER_GUI::changeToAddAttributeMode()
{
	stateTypeButtonGroup->button((int)ER_DiagramScene::InsertAttribute)->click();
}

void ER_GUI::changeToAddEntityMode()
{
	stateTypeButtonGroup->button((int)ER_DiagramScene::InsertEntity)->click();
}

void ER_GUI::changeToAddRelationShipMode()
{
	stateTypeButtonGroup->button((int)ER_DiagramScene::InsertRelationship)->click();
}

// action undo
void ER_GUI::undo()
{
	scene->undo();
}

// action redo
void ER_GUI::redo()
{
	scene->redo();
}

// action deleteItem
void ER_GUI::deleteItem()
{
	scene->deleteItem();
}

// action cut
void ER_GUI::cut()
{
	scene->cut();
}

// action copy
void ER_GUI::copy()
{
	scene->copy();
}

// action paste
void ER_GUI::paste()
{
	scene->paste();
}

void ER_GUI::showAboutDialog()
{
	QMessageBox::information(this, tr("About Entity Relation Diagramming Tool"), 
		"<p>Entity Relation Diagramming Tool</p><p>Version : 1.0</p><p>Author : 102598006@ntut</p>");
}

void ER_GUI::textViewSwitch()
{
	textViewer->setVisible(!textViewer->isVisible());
}