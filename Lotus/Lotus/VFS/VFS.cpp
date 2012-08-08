/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.cpp
	author:		reedhong 
	
	purpose:	虚拟机文件系统
*********************************************************************/

#include "VFS.h"

namespace Lotus {
	VFS::VFS()
	{

	}
	VFS::~VFS()
	{

	}

	bool VFS::mount(const String& path, const String& mountPoint, const String& fsType)
	{

	}

		
	void VFS::addFileSystem(FileSystem* fs)
	{

	}

	FilePtr VFS::open(const String&path, const String& mountPoint)
	{
		return 0;
	}

	FilePtr VFS::open(const String& absolutePath)
	{
		return 0;
	}

	DirPtr VFS::openDir(const String&path, const String& mountPoint)
	{
		return 0;
	}

	DirPtr VFS::openDir(const String& absolutePath)
	{
		return 0;
	}
}
