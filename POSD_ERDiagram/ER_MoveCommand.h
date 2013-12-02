#pragma once
#ifndef _ER_MOVE_COMMAND_ 
#define _ER_MOVE_COMMAND_
#include <vector>
#include "ER_Command.h"

using namespace std;

class ER_MoveCommand : public ER_Command
{
public:
	ER_MoveCommand(ER_Model*, string, int, int);
	~ER_MoveCommand(void);
	string execute();
	string unexecute();
	void moveCommand(int, int);

private:
	ER_Model* model;
	vector<int> idVector;
	string idString;
	int deltaX;
	int deltaY;
};
#endif