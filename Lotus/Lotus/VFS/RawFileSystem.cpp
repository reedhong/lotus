/********************************************************************
	created:	2012/08/08 
	filename: 	RawFileSystem.cpp
	author:		reedhong 
	
	purpose:	操作系统自带文件系统
*********************************************************************/

#include "RawFileSystem.h"
#include "RawFile.h"
#include "RawDir.h"
#include "Path.h"
#include "General/SharedPtr.h"
#include "VFS.h"

namespace Lotus {
	RawFileSystem::RawFileSystem():FileSystem(RAW_FS)
	{
	}

	RawFileSystem::~RawFileSystem()
	{

	}

	StreamPtr RawFileSystem::open(const String&  basepath, const String& relpath) const
	{
		String path = Path::join(basepath, relpath);
		RawFile* pFile = LOTUS_NEW RawFile(path);		
		return SharedPtr<RawFile>(pFile);
	}


		// 目录操作
	void RawFileSystem::listDir(const String& path, StringVector* paths) const
	{
		
	}

	bool RawFileSystem::mkDir(const String& path) const
	{
		return true;
	}

	bool RawFileSystem::rmDir(const String& path) const
	{
		return true;
	}

}  // end Lotus