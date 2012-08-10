/********************************************************************
	created:	2012/08/08 
	filename: 	Dir.h
	author:		reedhong 
	
	purpose:	虚拟文件目录项操作
*********************************************************************/

#ifndef __Lotus_Dir_H__
#define __Lotus_Dir_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Dir 
	{
	protected:
		String		mPath;
	public :
		Dir(String path):mPath(path) {}
		~Dir() {}
		/*
		 * 列出子目录
		 */
		virtual StringVectorPtr listDir() = 0;		
	};

	typedef SharedPtr<Dir> DirPtr;
}

#endif