/********************************************************************
	created:	2012/08/08 
	filename: 	RawFileSystem.cpp
	author:		reedhong 
	
	purpose:	����ϵͳ�Դ��ļ�ϵͳ
*********************************************************************/

#include "RawFileSystem.h"
#include "RawFile.h"
#include "RawDir.h"
#include "Main/SharedPtr.h"

namespace Lotus {
	RawFileSystem::RawFileSystem()
	{

	}

	RawFileSystem::~RawFileSystem()
	{

	}

	FilePtr RawFileSystem::open(const String&  path) 
	{
		RawFile* pFile = LOTUS_NEW RawFile(path);		
		return SharedPtr<RawFile>(pFile);
	}
	DirPtr RawFileSystem::openDir(const String&path)
	{
		RawDir* pDir = LOTUS_NEW RawDir(path);		
		return SharedPtr<RawDir>(pDir);
	}	
}  // end Lotus