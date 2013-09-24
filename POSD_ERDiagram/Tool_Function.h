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
	static string intToString(int &);
	static vector<string> split(const string &s, char delim, vector<string> &elems);
	static vector<string> split(const string &s, char delim);
};

#endif