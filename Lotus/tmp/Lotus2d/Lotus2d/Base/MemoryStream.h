/********************************************************************
	created:	2012/09/14 
	filename: 	MemoryStream.h
	author:		reedhong 
	
	purpose:	ÄÚ´æStream£¬¶ÁÐ´¾ù¿É
*********************************************************************/

#ifndef __Lotus2d_MemoryStream_H__
#define __Lotus2d_MemoryStream_H__

#include "Base/Prerequisites.h"
#include "Stream.h"

namespace Lotus2d {
	class MemoryStream: public Stream
	{
	public:
		MemoryStream(const uint8 *buffer, size_t len, BOOL freeOnClose=FALSE);
		virtual ~MemoryStream();
	public:
		virtual size_t read(void* buf, size_t count);
		virtual size_t write(const void* buf, size_t count);
		virtual void skip(long count);
		virtual void seek( size_t pos );
		virtual size_t tell(void);
		virtual BOOL eof(void) const ;
		virtual void close(void);
		void setFreeOnClose(BOOL b) { mfreeOnClose = b;}

	private:
		uint8*		mBuffer;
		uint8*		mBufferStart;
		uint8*		mBufferEnd;
		BOOL		mfreeOnClose;
	};
}

#endif