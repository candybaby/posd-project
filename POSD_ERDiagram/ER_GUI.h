#pragma once
#ifndef _ER_GUI_ 
#define _ER_GUI_
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include "ER_DiagramScene.h"
#include "ER_PresentationModel.h"

QT_BEGIN_NAMESPACE
class DiagramScene;
class QGraphicsView;
class QAction;
QT_END_NAMESPACE

class ER_GUI:public QMainWindow
{
	Q_OBJECT

public:
	ER_GUI(ER_PresentationModel*);
	~ER_GUI(void);

private slots:
	void browse();

private:
	void createActions();
	void createMenus();
	void createToolbars();

	QGraphicsView *view;
	ER_DiagramScene *scene;

	//bar
	QMenu* fileMenu;
	QToolBar* fileToolBar;

	//QAction
	QAction* exitAction;
	QAction* openAction;

	ER_PresentationModel *presentationModel;
	

};
#endif
