/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.h
	author:		reedhong 
	
	purpose:	虚拟机文件系统, 鉴于Ogre的资源存储管理有些繁琐
*********************************************************************/

#ifndef __Lotus_VFS_H__
#define __Lotus_VFS_H__

#include "General/Singleton.h"
#include "FileSystem.h"

namespace Lotus {	
	const static String RAW_FS = "raw";
	class VFS: public Singleton<VFS>
	{
	public:
	
	private:
		map<String, FileSystemPtr>		mMountPointMap;	// 建立mount point-> fs的映射
		map<String, String>					mPathMap;	// 建立mount　point->Path的映射
		map<String, FileSystemPtr>		mFileSystemMap;		// 所支持的fsType->fs的映射
	public:
		VFS();
		virtual ~VFS();

		/*
		 * 加载新的文件系统
		 */
		bool mount(const String& abspath, const String& mountPoint, const String& fsType);

		/*
		 * 添加文件系统
		 */
		void addFileSystem(FileSystem* fs);

		/*
		 * @path: 为加载到mountPoint的相对路径，这里我们均采取Linux的命令模式 actor/monster/test.xml
		 */
		StreamPtr	 open( const String& mountPoint, const String& relpath);

		/*
		 * 虚拟的绝对路径
		 */
		StreamPtr open(const String& absPath);

		/*
		 * 打开某个目录项
		 */
		//DirPtr openDir(const String&path, const String& mountPoint);
		//DirPtr openDir(const String& absolutePath);
	};
}

#endif