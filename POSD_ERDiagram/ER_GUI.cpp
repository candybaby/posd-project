#include <QtGui>
#include <QLabel>
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

	QHBoxLayout *layout = new QHBoxLayout;
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
}


ER_GUI::~ER_GUI(void)
{
}

// 創建Actions
void ER_GUI::createActions()
{
	openAction = new QAction(QIcon("images/folder.png"), tr("O&pen..."), this);
	openAction->setShortcut(tr("Ctrl+O"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(browse()));

	exitAction = new QAction(QIcon("images/exit.png"), tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+X"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

// 創建Menus
void ER_GUI::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

// 創建Toolbars
void ER_GUI::createToolbars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(exitAction);

	QToolButton* pointerButton = new QToolButton;
	pointerButton->setCheckable(true);
	pointerButton->setChecked(true);
	pointerButton->setIcon(QIcon("images/pointer.png"));

	QToolButton* connecterButton = new QToolButton;
	connecterButton->setCheckable(true);
	connecterButton->setIcon(QIcon("images/linepointer.png"));

	QToolButton* attributeButton = new QToolButton;
	attributeButton->setCheckable(true);
	attributeButton->setIcon(QIcon("images/attribute.png"));

	QToolButton* entityButton = new QToolButton;
	entityButton->setCheckable(true);
	entityButton->setIcon(QIcon("images/entity.png"));

	QToolButton* relationshipButton = new QToolButton;
	relationshipButton->setCheckable(true);
	relationshipButton->setIcon(QIcon("images/relationship.png"));

	pointerTypeGroup = new QButtonGroup(this);
	pointerTypeGroup->addButton(pointerButton, ER_DiagramScene::Pointer);
	pointerTypeGroup->addButton(connecterButton, ER_DiagramScene::Connecter);
	pointerTypeGroup->addButton(attributeButton, ER_DiagramScene::InsertAttribute);
	pointerTypeGroup->addButton(entityButton, ER_DiagramScene::InsertEntity);
	pointerTypeGroup->addButton(relationshipButton, ER_DiagramScene::InsertRelationship);
	connect(pointerTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

	stateToolBar = addToolBar(tr("State"));
	stateToolBar->addWidget(pointerButton);
	stateToolBar->addWidget(connecterButton);
	stateToolBar->addWidget(attributeButton);
	stateToolBar->addWidget(entityButton);
	stateToolBar->addWidget(relationshipButton);
}

// 瀏覽檔案總管
void ER_GUI::browse()
{
	QString directory = QFileDialog::getOpenFileName(this, tr("Find File"), "C://", tr("ERD File (*.erd)"));
	if (directory != "")
	{
		presentationModel->readComponentsFile(directory.toStdString());
	}
	scene->addItemsFromModel();
}

// 處理點選pointerGroup事件
void ER_GUI::pointerGroupClicked(int index)
{
	scene->setMode(ER_DiagramScene::Mode(pointerTypeGroup->checkedId()));
}