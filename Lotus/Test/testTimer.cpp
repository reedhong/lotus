#include <iostream>
using namespace std;
#include "test.h"

#include "General/Timer.h"
using namespace Lotus;


void testTimer()
{
	Timer timer;
	
	cout << "\n===========test Timer Begin" << endl;
	long microsBegin = timer.getMicroseconds();
	long millisBegin = timer.getMilliseconds();

	Timer::sleep(199);

	long microsEnd = timer.getMicroseconds();
	long millisEnd = timer.getMilliseconds();

	cout << "microsEnd-microsBegin=" << (microsEnd-microsBegin) << endl;
	cout << "millisEnd-millisBegin=" << (millisEnd-millisBegin) << endl;

	cout << "===========test Timer end" << endl;

}