#include "test.h"

#include "General/SharedPtr.h"
#include <vector>
using namespace std;
using namespace Lotus;

class Base
{
public:
	int i;
	int j;
	char* buf;
	
	Base():i(0),j (20)
	{
		buf = new char[32];
	}

	~Base()
	{
		delete[] buf;
	}
};

typedef SharedPtr<Base>	ShareBasePtr;

void testSharedPtr()
{
	Base* b = new Base();
	ShareBasePtr bp(b);
	ShareBasePtr bp2 = bp;

	vector<ShareBasePtr> arrays;
	arrays.push_back(bp);
	arrays.push_back(bp2);
}
