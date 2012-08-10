/********************************************************************
	created:	2012/08/08 
	filename: 	Dir.h
	author:		reedhong 
	
	purpose:	�����ļ�Ŀ¼�����
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
		 * �г���Ŀ¼
		 */
		virtual StringVectorPtr listDir() = 0;		
	};

	typedef SharedPtr<Dir> DirPtr;
}

#endif