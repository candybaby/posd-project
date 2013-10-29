#include "Tool_Function.h"

// Âà´«IntToString
string Tool_Function::convertIntToString(int &targetInt) 
{
	string tempString;
	stringstream stringStream(tempString);
	stringStream << targetInt;
	return stringStream.str();
}

// split
vector<string> Tool_Function::split(const std::string &sourceString, char delim, std::vector<std::string> &resultVector) 
{
	stringstream stringStream(sourceString);
	string item;
	while (getline(stringStream, item, delim)) 
	{
		resultVector.push_back(item);
	}
	return resultVector;
}

vector<string> Tool_Function::split(const string &sourceString, char delim)
{
	vector<string> resultVector;
	split(sourceString, delim, resultVector);
	return resultVector;
}