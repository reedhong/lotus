/********************************************************************
	created:	2012/08/08 
	filename: 	FileSystem.h
	author:		reedhong 
	
	purpose:	�����ļ�����ϵͳ
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
		FileSystem(const String& type):mfsType(type){}
		~FileSystem(){} 
		virtual const String& getType() { return mfsType; }
		/*
		 * 
		 */
		virtual FilePtr open(const String&  basepath, const String& relpath) const = 0;
		virtual DirPtr openDir(const String&path) const = 0;

		// Ŀ¼����
		virtual void listDir(const String& path, StringVector* paths) const = 0;
		virtual bool mkDir(const String& path) const = 0;
		virtual bool rmDir(const String& path) const = 0;

	};

	typedef SharedPtr<FileSystem> FileSystemPtr;
}

#endif