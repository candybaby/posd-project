#pragma once
#ifndef _ER_DELETE_COMMAND_ 
#define _ER_DELETE_COMMAND_
#include "ER_Command.h"
#include "gtest/gtest_prod.h"
#include <vector>

class ER_DeleteCommand : public ER_Command
{
friend class ER_DeleteCommandTest;
FRIEND_TEST(ER_DeleteCommandTest, clearTempData);

public:
	ER_DeleteCommand(ER_Model*, int);
	ER_DeleteCommand(ER_Model*, vector<int>);
	~ER_DeleteCommand(void);
	ERD_Component* findComponentById(int);
	bool deleteComponentById(int);
	void clearTempData();
	string execute();
	string unexecute();

private:
	ER_Model* model;
	int targetId;
	ERD_Component* target;
	vector<ERD_Component*> relatedComponents;
};
#endif