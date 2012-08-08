/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.h
	author:		reedhong 
	
	purpose:	虚拟机文件系统, 鉴于Ogre的资源存储管理有些繁琐
*********************************************************************/

#ifndef __Lotus_VFS_H__
#define __Lotus_VFS_H__

#include "Main/Singleton.h"
#include "FileSystem.h"
#include "File.h"
#include "Dir.h"

namespace Lotus {
	class VFS: public Singleton<VFS>
	{
	public:
		VFS();
		virtual ~VFS();

		/*
		 * 加载新的文件系统
		 */
		bool mount(const String& path, const String& mountPoint, const String& fsType);

		/*
		 * 添加文件系统
		 */
		void addFileSystem(FileSystem* fs);

		/*
		 * @path: 为加载到mountPoint的相对路径，这里我们均采取Linux的命令模式 actor/monster/test.xml
		 */
		FilePtr	 open(const String& relativePath, const String& mountPoint);
		FilePtr open(const String& absolutePath);

		/*
		 * 打开某个目录项
		 */
		DirPtr openDir(const String&path, const String& mountPoint);
		DirPtr openDir(const String& absolutePath);
	};
}

#endif