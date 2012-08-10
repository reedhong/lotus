/********************************************************************
	created:	2012/08/08 
	filename: 	FileSystem.h
	author:		reedhong 
	
	purpose:	虚拟文件抽象系统
*********************************************************************/

#ifndef __Lotus_FileSystem_H__
#define __Lotus_FileSystem_H__

#include "Main/Prerequisites.h"
#include "File.h"
#include "Dir.h"
namespace Lotus {
	class FileSystem 
	{
	protected:
		String		mfsType;
	public:
		FileSystem();
		~FileSystem();
		virtual const String& getType() const = 0;
		virtual FilePtr open(const String&  path) const = 0;

		virtual DirPtr openDir(const String&path) const = 0;

		// 目录操作
		virtual StringVectorPtr listDir(const String& path) const = 0;
		virtual bool mkDir(const String& path) const = 0;
		virtual bool rmDir(const String& path) const = 0;

		// 路径相关操作
		virtual bool isPath(const string& path) const = 0;
		virtual bool joinPath(const string& path1, const String &path2);

	};
}

#endif