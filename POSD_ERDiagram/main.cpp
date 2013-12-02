#include <iostream>
#include <QApplication>
#include <qdebug>
#include "ER_TextUI.h"
#include "ER_PresentationModel.h"
#include "ER_Model.h"
#include "ER_GUI.h"

using namespace std;
int main(int argc, char *argv[])
{
	ER_Model* model = new ER_Model;

	ER_PresentationModel* presentationModel = new ER_PresentationModel(model);

	if (argc == 1 || strcmp(argv[1], "guimode") == 0)
	{
		QApplication app(argc, argv);
		ER_GUI* graphicalUI = new ER_GUI(presentationModel);

		graphicalUI->setWindowTitle("ER Model GUI");
		graphicalUI->show();
		return app.exec();
	}
	else if (argc > 1 && strcmp(argv[1], "textmode") == 0)
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
