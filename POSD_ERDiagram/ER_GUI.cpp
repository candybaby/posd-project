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
	scene = new ER_DiagramScene(this);
	scene->setSceneRect(QRectF(0, 0, 4000, 3000));

	QHBoxLayout *layout = new QHBoxLayout;
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);

	//QGraphicsItem *item = new ER_ItemEntity("T123123sdas");
	//item->setPos(2400,1600);
	//scene->addItem(item);

	//ER_ItemComponent *item1 = new ER_ItemEntity("231asdasd");
	//item1->setPos(1800,1400);
	//scene->addItem(item1);

	//ER_ItemComponent *item2 = new ER_ItemAttribute("231dfsdffffff", true);
	//item2->setPos(2000,1600);
	//scene->addItem(item2);

	//ER_ItemComponent *item3 = new ER_ItemRelationship("dfsdfsdfffffff");
	//item3->setPos(1700,1300);
	//scene->addItem(item3);

	//item = new ER_ItemConnection("1", item1, item3);
	////((ER_ItemConnection*)item)->setConnection(item1, item3);
	//scene->addItem(item);

	//item = new ER_ItemConnection("1");
	////((ER_ItemConnection*)item)->setConnection(item1, item2);
	//scene->addItem(item);
}


ER_GUI::~ER_GUI(void)
{
}

void ER_GUI::createActions()
{
	openAction = new QAction(QIcon("images/folder.png"), tr("O&pen..."), this);
	openAction->setShortcut(tr("Ctrl+O"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(browse()));

	exitAction = new QAction(QIcon("images/exit.png"), tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+X"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void ER_GUI::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void ER_GUI::createToolbars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(exitAction);
}

void ER_GUI::browse()
{
	QString directory = QFileDialog::getOpenFileName(this, tr("Find File"), "C://", tr("ERD File (*.erd)"));
	if (directory != "")
	{
		presentationModel->readComponentsFile(directory.toStdString());
		//string message;
		//message = presentationModel->readComponentsFile(directory.toStdString());
		//ER_MessageBoxManager::showMessageBox(message);
	}
	addItemsFromFile();
}

void ER_GUI::addItemsFromFile()
{
	string nodesMessage = presentationModel->getGuiNodes();
	//ER_MessageBoxManager::showMessageBox(nodesMessage);
	scene->addItemNodes(QString(QString::fromLocal8Bit(nodesMessage.c_str())));

	string connectionsMessage = presentationModel->getGuiConnections();
	//ER_MessageBoxManager::showMessageBox(connectionsMessage);
	scene->addItemConnections(QString(QString::fromLocal8Bit(connectionsMessage.c_str())));
	//scene->addItems(QString(QString::fromLocal8Bit(nodesMessage.c_str())));
	scene->updateItemPosition();
}