#pragma once
#ifndef _ER_EDIT_TEXT_COMMAND_ 
#define _ER_EDIT_TEXT_COMMAND_
#include "ER_Command.h"
#include "ER_Model.h"

class ER_EditTextCommand : public ER_Command
{
public:
	ER_EditTextCommand(ER_Model*, int, string);
	~ER_EditTextCommand(void);
	string execute();
	string unexecute();

private:
	ER_Model* model;
	int id;
	string text;
	string preText;
};
#endif
