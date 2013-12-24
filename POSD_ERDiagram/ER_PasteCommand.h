#pragma once
#ifndef _ER_PASTE_COMMAND_ 
#define _ER_PASTE_COMMAND_
#include "ER_Command.h"

class ER_PasteCommand : public ER_Command
{
public:
	ER_PasteCommand(ER_Model*, vector<ERD_Component*>, int);
	~ER_PasteCommand(void);
	bool isExistNode(int);
	string execute();
	string unexecute();
	void pasteNodes();
	void pasteConnections();
	void clearConnections();

private:
	ER_Model* model;
	vector<ERD_Component*> candidatePasteComponents;
	vector<ERD_Connection*> connections;
	vector<int> pastedComponentIds;
	int modelCurrentId;
	int pasteComponentCount;
	map<int, int> mappingCloneId;
	int continuePasteCommandCount;
};
#endif