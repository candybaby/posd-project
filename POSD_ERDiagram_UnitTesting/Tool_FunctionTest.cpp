#include "Tool_Function.h"
#include "gtest/gtest.h"

using namespace std;
class Tool_FunctionTest : public ::testing::Test
{
protected:
};

// ���� �ഫIntToString
TEST_F(Tool_FunctionTest, convertIntToString)
{
	// ����
	// �Ѽ�:int &
	// �^��:string
	// ����:�L
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

// ���� split
TEST_F(Tool_FunctionTest, split)
{
	// ����
	// �Ѽ�:string &, char, vector<string> &
	// �^��:vector<string>
	// ����:�L
	vector<string> result;
	string sourceString = "1,2,3";
	Tool_Function::split(sourceString, ',', result);
	EXPECT_EQ("1", result.at(0));
	EXPECT_EQ("2", result.at(1));
	EXPECT_EQ("3", result.at(2));

	// ����
	// �Ѽ�:string &, char
	// �^��:vector<string>
	// ����:�L
	sourceString = "1,2,3";
	result = Tool_Function::split(sourceString, ',');
	EXPECT_EQ("1", result.at(0));
	EXPECT_EQ("2", result.at(1));
	EXPECT_EQ("3", result.at(2));
}