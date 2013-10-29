#include <QtGui>
#include <QLabel>
#include "ER_GUI.h"
#include <QFileDialog>




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
	QString directory = QFileDialog::getOpenFileName(this,
		tr("Find File"), QDir::currentPath(), tr("ERD File (*.erd)"));
	string message;
	message = presentationModel->readComponentsFile(directory.toStdString());
	QMessageBox msgBox;
	msgBox.setText(QString(QString::fromLocal8Bit(message.c_str())));
	msgBox.exec();
}
