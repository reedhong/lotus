#include "test.h"
#include "VFS/VFS.h"
#include "VFS/RawFileSystem.h"

using namespace  Lotus;
using namespace std;

void testVFS()
{
	VFS* vfs = LOTUS_NEW VFS;
	
	RawFileSystem* rfs = LOTUS_NEW RawFileSystem();
	vfs->addFileSystem(rfs);
	vfs->mount("C:\\github\\lotus\\Lotus", "sys", RAW_FS);
	
	StreamPtr fp = vfs->open("sys", "/test/test.h");


	LOTUS_DELETE vfs;
}