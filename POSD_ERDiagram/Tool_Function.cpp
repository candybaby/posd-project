#include "Tool_Function.h"

string Tool_Function::intToString(int &i) 
{
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

vector<string> Tool_Function::split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

vector<string> Tool_Function::split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}
