#pragma once
#ifndef _ER_TEXTUI_ 
#define _ER_TEXTUI_
#include <iostream>
#include <sstream>
#include "ER_PresentationModel.h"
#include "Tool_Function.h"

class ER_TextUI
{
public:
	enum MenuCommand
	{
		Option_1,
		Option_2,
		Option_3,
		Option_4,
		Option_5,
		Option_6,
		Option_7,
		Option_8,
		Option_9,
		Option_10,
		Option_11,
		SIZE_OF_MenuCommand 
	};
	static const char* MenuCommandNames[SIZE_OF_MenuCommand];

	ER_TextUI(void);
	ER_TextUI(ER_PresentationModel*);
	~ER_TextUI(void);
	void displayMenu();
	void processCommand();
	void addNode();
	void connectTwoNodes();
	void displayCurrentDiagram();
	void setPrimaryKey();
	int option1Question(string addNodeCommand, int type );
	void printAddNodeResult(int type, int id, string addNodeName);
	void printNodes();
	void printConnections();
	void printComponents();
	void printEntities();
	void printAttributesById(int);
	void option2Question(string &);
	vector<int> findAttributes(int);
	void printEntityPrimaryKey(int);
	void printTables();

private:
	ER_PresentationModel presentationModel;
};

#endif