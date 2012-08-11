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
		virtual FilePtr open(const String&  basepath, const String& relpath) const;
		virtual DirPtr openDir(const String&path) const;

		// 目录操作
		virtual void  listDir(const String& path, StringVector* paths) const;
		virtual bool mkDir(const String& path) const ;
		virtual bool rmDir(const String& path) const;
	};
}

#endif
