/********************************************************************
	created:	2012/08/08 
	filename: 	VFS.cpp
	author:		reedhong 
	
	purpose:	虚拟机文件系统
*********************************************************************/

#include "VFS.h"
#include "Exception/Exception.h"
#include "String/StringUtil.h"

namespace Lotus {
	template<> VFS* Singleton<VFS>::msInstance = NULL;
	VFS::VFS()
	{

	}
	VFS::~VFS()
	{

	}

	bool VFS::mount(const String& path, const String& mountPoint, const String& fsType)
	{
		map<String, FileSystemPtr>::iterator iterFS = mFileSystemMap.find(fsType);
		if( iterFS == mFileSystemMap.end()){
			LOTUS_EXCEPT(Exception::ERR_INVALIDPARAMS, "fs type can not find",
				"VFS::mount");
			return false;
		}

		FileSystemPtr ptr = iterFS->second;

		map<String, String>::iterator iterMP = mPathMap.find(mountPoint);
		if( iterMP != mPathMap.end()){
			LOTUS_EXCEPT(Exception::ERR_INVALIDPARAMS, "mount point has exisited",
				"VFS::mount");
			return false;
		}
		mPathMap.insert(make_pair(mountPoint, path));
		mMountPointMap.insert(make_pair(mountPoint, ptr));

		return true;
	}

		
	void VFS::addFileSystem(FileSystem* fs)
	{
		FileSystemPtr ptr(fs);
		map<String, FileSystemPtr>::iterator iter = mFileSystemMap.find(fs->getType());
		ASSERT( iter == mFileSystemMap.end());
		mFileSystemMap.insert(make_pair(fs->getType(), ptr));
	}

	StreamPtr VFS::open(const String& absPath)
	{
		String stdAbsPath = StringUtil::normalizeFilePath(absPath, false);
		String::size_type pos = stdAbsPath.find('/', 0);
		ASSERT(pos != String::npos);

		String mountPoint = stdAbsPath.substr(0, pos);
		String relPath = stdAbsPath.substr(pos+1);

		return open(mountPoint, relPath);

	}

	StreamPtr VFS::open(const String& mountPoint, const String& relpath)
	{
		String stdRelPath = StringUtil::normalizeFilePath(relpath,false);

		map<String, String>::iterator iterPM = mPathMap.find(mountPoint);
		ASSERT( iterPM != mPathMap.end());
		String abspath = iterPM->second;

		map<String, FileSystemPtr>::iterator iterMP = mMountPointMap.find(mountPoint);
		ASSERT( iterMP != mMountPointMap.end());

		FileSystemPtr fsp = iterMP->second;
		
		return fsp->open(abspath, stdRelPath);
	}



}  // end Lotus
