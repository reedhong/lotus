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
	};
}

#endif