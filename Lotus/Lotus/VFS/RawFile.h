/********************************************************************
	created:	2012/08/08 
	filename: 	RawFile.h
	author:		reedhong 
	
	purpose:	操作系统自带
*********************************************************************/

#ifndef __Lotus_RawFile_H__
#define __Lotus_RawFile_H__

namespace Lotus {
	class RawFile: public File
	{
	public:
		RawFile();
		~RawFile();
	};
}

#endif