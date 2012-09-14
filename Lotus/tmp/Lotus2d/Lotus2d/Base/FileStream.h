/********************************************************************
	created:	2012/09/14 
	filename: 	FileStream.h
	author:		reedhong 
	
	purpose:	����c�Ľӿڣ��������ٶ�std��ʹ��
*********************************************************************/

#ifndef __Lotus2d_FileStream_H__
#define __Lotus2d_FileStream_H__

#include "Stream.h"

namespace Lotus2d {
	class FileStream: public Stream
	{
	public:
		/*
		 * mode��ֵ��c��fopen����һ��
		 */
		FileStream(const char* path,  const char* mode);
		virtual ~FileStream();
		
		virtual size_t read(void* buf, size_t count);
		virtual size_t write(const void* buf, size_t count);
		virtual void skip(long count);
		virtual void seek( size_t pos );
		virtual size_t tell(void);
		virtual BOOL eof(void)  const;
		virtual void close(void);

	private:
		FILE*	mFile;
	};
}

#endif