#include <iostream>
#include <QApplication>
#include <qdebug>
#include "ER_TextUI.h"
#include "ER_PresentationModel.h"
#include "ER_Model.h"
#include "ER_GUI.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;
int main(int argc, char *argv[])
{
	ER_Model* model = new ER_Model;

	ER_PresentationModel* presentationModel = new ER_PresentationModel(model);

	if (true)
	{
		QApplication app(argc, argv);
		ER_GUI* graphicalUI = new ER_GUI(presentationModel);

		graphicalUI->setMaximumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		graphicalUI->setMinimumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		graphicalUI->setWindowTitle("ER Model GUI");
		graphicalUI->show();
		return app.exec();
	}
	else
	{
		ER_TextUI* textUI = new ER_TextUI(presentationModel);
		
		textUI->displayMenu();

		delete textUI;
		delete presentationModel;
		delete model;
		system("pause");
		return 0;
	}
}
