/********************************************************************
	created:	2012/08/08 
	filename: 	FileSystem.h
	author:		reedhong 
	
	purpose:	虚拟文件抽象系统
*********************************************************************/

#ifndef __Lotus_FileSystem_H__
#define __Lotus_FileSystem_H__

#include "General/Prerequisites.h"
#include "General/Stream.h"

namespace Lotus {
	class FileSystem 
	{
	protected:
		String		mfsType;
	public:
		FileSystem(const String& type):mfsType(type){}
		~FileSystem(){} 
		virtual const String& getType() { return mfsType; }
		/*
		 * 
		 */
		virtual StreamPtr open(const String&  basepath, const String& relpath) const = 0;

		// 目录操作
		virtual void listDir(const String& path, StringVector* paths) const = 0;
		virtual bool mkDir(const String& path) const = 0;
		virtual bool rmDir(const String& path) const = 0;

	};

	typedef SharedPtr<FileSystem> FileSystemPtr;
}

#endif