/********************************************************************
	created:	2012/09/14 
	filename: 	MemroyStream.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "MemoryStream.h"

namespace Lotus2d {
	MemoryStream::MemoryStream(const uint8 *buffer, size_t len, BOOL freeOnClose):mfreeOnClose(freeOnClose)
	{
		mBuffer =  (uint8 *)buffer;
		mBufferStart = (uint8 *)buffer;
		mBufferEnd = (uint8 *)buffer + len;
		mSize = len;
	}

	MemoryStream::~MemoryStream()
	{
		mBuffer = mBufferStart = mBufferEnd  = 0;
		close();
	}

	size_t MemoryStream::read(void* buf, size_t count)
	{
		ASSERT(count <= (size_t)(mBufferEnd-mBuffer));
		memcpy(buf, mBuffer, count);
		mBuffer += count;

		return count;
	}

	size_t MemoryStream::write(const void* buf, size_t count)
	{
		ASSERT(count <= (size_t)(mBufferEnd-mBuffer));
		memcpy(mBuffer, buf, count);
		mBuffer += count;

		return count;
	}
	void MemoryStream::skip(long count)
	{
		ASSERT(count <= (mBufferEnd-mBuffer));
		mBuffer += count;
	}
	void MemoryStream::seek( size_t pos )
	{
		ASSERT(pos <= (size_t)(mBufferEnd-mBufferStart));
		mBuffer = mBufferStart+pos;
	}
	size_t MemoryStream::tell(void)
	{
		return (mBuffer-mBufferStart);
	}
	BOOL MemoryStream::eof(void) const 
	{
		return (mBuffer == mBufferEnd);
	}
	void MemoryStream::close(void)
	{
		if(mfreeOnClose && mBufferStart){
			// TODO: 
			free(mBufferStart);
		}
	}
}