#pragma once
#ifndef _TOOL_FUNCTION_ 
#define _TOOL_FUNCTION_
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Tool_Function
{
public:
	static string convertIntToString(int &);
	static vector<string> split(const string &, char, vector<string> &);
	static vector<string> split(const string &, char);
};

#endif