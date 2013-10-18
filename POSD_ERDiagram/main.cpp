#include <iostream>
#include "ER_TextUI.h"
#include "ER_PresentationModel.h"
#include "ER_Model.h"

using namespace std;
int main(int argc, char *argv[])
{
	ER_Model* model = new ER_Model;

	ER_PresentationModel* presentationModel = new ER_PresentationModel(model);

	ER_TextUI* textUI = new ER_TextUI(presentationModel);

	textUI->displayMenu();

	delete textUI;
	delete presentationModel;
	delete model;

	system("pause");
	return 0;
}
