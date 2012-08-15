#ifndef __Lotus_Test_H__
#define __Lotus_Test_H__


#define TEST_CONFIGPARSER
#define TEST_LOGGER
//#define TEST_SINGLETON
#define TEST_STRING_UTIL
#define TEST_TIMER
#define TEST_PROFILE

void testLogger();
void testConfigParser();
void testSingleton();
void testStringUtil();
void testTimer();
void testProfile();

void testSharedPtr();
void testVFS();

void testMath();

#endif