/********************************************************************
	created:	2012/08/08 
	filename: 	RawDir.h
	author:		reedhong 
	
	purpose:	ϵͳ�Դ�
*********************************************************************/
#ifndef __Lotus_RawDir_H__
#define __Lotus_RawDir_H__

#include "Dir.h"

namespace Lotus {
	class RawDir : public Dir 
	{
	public:
		RawDir(const String path);
		virtual ~RawDir();
	};
}

#endif
