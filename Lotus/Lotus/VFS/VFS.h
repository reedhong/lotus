/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.h
	author:		reedhong 
	
	purpose:	������ļ�ϵͳ, ����Ogre����Դ�洢������Щ����
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
		map<String, FileSystemPtr>		mMountPointMap;	// ����mount point-> fs��ӳ��
		map<String, String>					mPathMap;	// ����mount��point->Path��ӳ��
		map<String, FileSystemPtr>		mFileSystemMap;		// ��֧�ֵ�fsType->fs��ӳ��
	public:
		VFS();
		virtual ~VFS();

		/*
		 * �����µ��ļ�ϵͳ
		 */
		bool mount(const String& abspath, const String& mountPoint, const String& fsType);

		/*
		 * ����ļ�ϵͳ
		 */
		void addFileSystem(FileSystem* fs);

		/*
		 * @path: Ϊ���ص�mountPoint�����·�����������Ǿ���ȡLinux������ģʽ actor/monster/test.xml
		 */
		StreamPtr	 open( const String& mountPoint, const String& relpath);

		/*
		 * ����ľ���·��
		 */
		StreamPtr open(const String& absPath);

		/*
		 * ��ĳ��Ŀ¼��
		 */
		//DirPtr openDir(const String&path, const String& mountPoint);
		//DirPtr openDir(const String& absolutePath);
	};
}

#endif