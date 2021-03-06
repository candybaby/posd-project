#pragma once
#ifndef _ER_MULTIPLEDELETE_COMMAND_ 
#define _ER_MULTIPLEDELETE_COMMAND_
#include "ER_Command.h"
#include <vector>

class ER_MultipleDeleteCommand : public ER_Command
{
public:
	ER_MultipleDeleteCommand(ER_Model*, vector<int>);
	~ER_MultipleDeleteCommand(void);
	ERD_Component* findComponentById(int);
	bool deleteComponentById(int);
	void clearTempData();
	void deleteConnectionsByTargetIds(vector<int>);
	void deleteRelatedConnectionByTargetId(int);
	void deleteNodeByTargetIds(vector<int>);
	string execute();
	string unexecute();

private:
	ER_Model* model;
	vector<int> targetIds;
	vector<int> deleteIds;
	vector<ERD_Component*> relatedComponents;
	vector<ERD_Component*> targetNodes;
};
#endif
