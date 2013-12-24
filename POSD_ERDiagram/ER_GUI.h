#pragma once
#ifndef _ER_GUI_ 
#define _ER_GUI_
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QMenu>
#include <QTableView>
#include "ER_DiagramScene.h"
#include "ER_PresentationModel.h"
#include "ER_TableViewModel.h"
#include "ER_TableView.h"

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
	void changeToPointerMode();
	void setDeleteEnable(bool);
	void setUndoEnable(bool);
	void setRedoEnable(bool);
	void setCutEnable(bool);
	void setCopyEnable(bool);
	void setPasteEnable(bool);

private slots:
	void browse();
	void pointerGroupClicked(int);
	void changeToAddAttributeMode();
	void changeToAddEntityMode();
	void changeToAddRelationShipMode();
	void undo();
	void redo();
	void deleteItem();
	void cut();
	void copy();
	void paste();
	void showAboutDialog();

private:
	void createActions();
	void createMenus();
	void createToolbars();

	QGraphicsView* view;
	ER_DiagramScene* scene;
	ER_TableView* tableView;
	ER_TableViewModel* tableViewModel;

	//menu
	QMenu* fileMenu;
	QMenu* addItemMenu;
	QMenu* editMenu;
	QMenu* helpMenu;

	//bar
	QToolBar* fileToolBar;
	QToolBar* editorToolBar;
	QToolBar* stateToolBar;
	

	//QButtonGroup
	QButtonGroup *stateTypeButtonGroup;

	//QAction
	QAction* exitAction;
	QAction* openAction;
	QAction* addAttributeAction;
	QAction* addEntityAction;
	QAction* addRelationshipAction;
	QAction* undoAction;
	QAction* redoAction;
	QAction* deleteItemAction;
	QAction* cutAction;
	QAction* copyAction;
	QAction* pasteAction;
	QAction* aboutAction;

	ER_PresentationModel *presentationModel;
};
#endif
