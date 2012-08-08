/********************************************************************
	created:	2012/08/08 
	filename: 	RawFileSystem.h
	author:		reedhong 
	
	purpose:	操作系统自带文件系统
*********************************************************************/

#ifndef __Lotus_RawFileSystem_H__
#define __Lotus_RawFileSystem_H__

#include "FileSystem.h"

namespace Lotus {
	class RawFileSystem:  public FileSystem
	{
	public: 
		RawFileSystem();
		virtual ~RawFileSystem();
		virtual FilePtr open(const String&  path) ;
		virtual DirPtr openDir(const String&path);
	};
}

#endif
