/********************************************************************
	created:	2012/08/08 
	filename: 	RawFileSystem.cpp
	author:		reedhong 
	
	purpose:	操作系统自带文件系统
*********************************************************************/

#include "RawFileSystem.h"

namespace Lotus {
	RawFileSystem::RawFileSystem()
	{

	}

	RawFileSystem::~RawFileSystem()
	{

	}

	FilePtr RawFileSystem::open(const String&  path) 
	{
		return 0;
	}
	DirPtr RawFileSystem::openDir(const String&path)
	{
		return 0;
	}	
}  // end Lotus