#include "Tool_Function.h"
#include "gtest/gtest.h"

using namespace std;
class Tool_FunctionTest : public ::testing::Test
{
protected:
};

// 代刚 锣传IntToString
TEST_F(Tool_FunctionTest, convertIntToString)
{
	// 代刚
	// 把计:int &
	// 肚:string
	// 爹:礚
	string result;
	int number = 1;
	result = Tool_Function::convertIntToString(number);
	EXPECT_EQ("1", result);

	number = -1;
	result = Tool_Function::convertIntToString(number);
	EXPECT_EQ("-1", result);

	number = 0;
	result = Tool_Function::convertIntToString(number);
	EXPECT_EQ("0", result);
}

// 代刚 split
TEST_F(Tool_FunctionTest, split)
{
	// 代刚
	// 把计:string &, char, vector<string> &
	// 肚:vector<string>
	// 爹:礚
	vector<string> result;
	string sourceString = "1,2,3";
	Tool_Function::split(sourceString, ',', result);
	EXPECT_EQ("1", result.at(0));
	EXPECT_EQ("2", result.at(1));
	EXPECT_EQ("3", result.at(2));

	// 代刚
	// 把计:string &, char
	// 肚:vector<string>
	// 爹:礚
	sourceString = "1,2,3";
	result = Tool_Function::split(sourceString, ',');
	EXPECT_EQ("1", result.at(0));
	EXPECT_EQ("2", result.at(1));
	EXPECT_EQ("3", result.at(2));
}