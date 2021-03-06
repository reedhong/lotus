#include <iostream>
using namespace std;

#include "test.h"
#include "General/Endian.h"

int main(int argc, char**argv)
{
#ifdef TEST_LOGGER
	testLogger();
#endif

#ifdef TEST_CONFIGPARSER
	testConfigParser();
#endif

#ifdef TEST_SINGLETON
	testSingleton();
#endif

#ifdef TEST_STRING_UTIL
	testStringUtil();
#endif

#ifdef TEST_TIMER
	testTimer();
#endif

#ifdef TEST_PROFILE
	testProfile();
#endif

	 testSharedPtr();

	// testVFS();
	testMath();

	system("pause");
	return 0;
}