/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.h
	author:		reedhong 
	
	purpose:	������ļ�ϵͳ, ����Ogre����Դ�洢������Щ����
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
		 * �����µ��ļ�ϵͳ
		 */
		bool mount(const String& path, const String& mountPoint, const String& fsType);

		/*
		 * ����ļ�ϵͳ
		 */
		void addFileSystem(FileSystem* fs);

		/*
		 * @path: Ϊ���ص�mountPoint�����·�����������Ǿ���ȡLinux������ģʽ actor/monster/test.xml
		 */
		FilePtr	 open(const String& relativePath, const String& mountPoint);
		FilePtr open(const String& absolutePath);

		/*
		 * ��ĳ��Ŀ¼��
		 */
		DirPtr openDir(const String&path, const String& mountPoint);
		DirPtr openDir(const String& absolutePath);
	};
}

#endif