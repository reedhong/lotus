#include "General/Singleton.h"
#include <iostream>
using namespace std;
using namespace Lotus;

class TestSingleton:public Singleton<TestSingleton>
{
public:
	TestSingleton(){

	};
	~TestSingleton(){};

	void PrintTest()
	{
		cout << "fuck u" << endl;
	}

	int value;
};

 template<> TestSingleton* Singleton<TestSingleton>::msInstance = 0;

void testSingleton()
{
	TestSingleton* test = new TestSingleton();
	TestSingleton::Instance()->PrintTest();
	TestSingleton::Instance()->value = 20;
	TestSingleton* test2 = new TestSingleton();
	delete test;

}
