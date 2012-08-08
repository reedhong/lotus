#include <iostream>
using namespace std;

#include "String/StringUtil.h"
using namespace Lotus;

#include "test.h"

void testStringUtil()
{
	String testStr = " dfdfdf\r\n";
	StringUtil::trim(testStr);

	testStr = "dfdfd|dfd|dfdfd|ddd|";
	vector<String> str = StringUtil::split(testStr, "|");

	cout << "end" << endl;
}