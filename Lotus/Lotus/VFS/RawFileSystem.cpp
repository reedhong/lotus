/********************************************************************
	created:	2012/08/08 
	filename: 	RawFileSystem.cpp
	author:		reedhong 
	
	purpose:	����ϵͳ�Դ��ļ�ϵͳ
*********************************************************************/

#include "RawFileSystem.h"
#include "RawFile.h"
#include "RawDir.h"
#include "Path.h"
#include "Main/SharedPtr.h"
#include "VFS.h"

namespace Lotus {
	RawFileSystem::RawFileSystem():FileSystem(RAW_FS)
	{
	}

	RawFileSystem::~RawFileSystem()
	{

	}

	FilePtr RawFileSystem::open(const String&  basepath, const String& relpath) const
	{
		String path = Path::join(basepath, relpath);
		RawFile* pFile = LOTUS_NEW RawFile(path);		
		return SharedPtr<RawFile>(pFile);
	}
	DirPtr RawFileSystem::openDir(const String&path) const
	{
		RawDir* pDir = LOTUS_NEW RawDir(path);		
		return SharedPtr<RawDir>(pDir);
	}	

		// Ŀ¼����
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