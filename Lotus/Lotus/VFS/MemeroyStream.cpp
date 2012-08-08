#include "MemoryStream.h"
#include "Main/Macro.h"
namespace Lotus
{
	MemoryStream::MemoryStream(void* pMem, size_t inSize, bool freeOnClose, bool readOnly)
		: Stream(static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		mData = mPos = static_cast<uint8*>(pMem);
		mSize = inSize;
		mEnd = mData + mSize;
		mFreeOnClose = freeOnClose;
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(const String& name, void* pMem, size_t inSize, 
		bool freeOnClose, bool readOnly)
		: Stream(name, static_cast<uint16>(readOnly ? READ : (READ | WRITE)))
	{
		mData = mPos = static_cast<uint8*>(pMem);
		mSize = inSize;
		mEnd = mData + mSize;
		mFreeOnClose = freeOnClose;
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(Stream& sourceStream, 
		bool freeOnClose, bool readOnly)
		: Stream(static_cast<uint16>(readOnly ? READ : (READ | WRITE)))
	{
		// Copy data from incoming stream
		mSize = sourceStream.size();
		if (mSize == 0 && !sourceStream.eof())
		{
			// size of source is unknown, read all of it into memory
			String contents = sourceStream.getAsString();
			mSize = contents.size();
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			memcpy(mData, contents.data(), mSize);
			mEnd = mData + mSize;
		}
		else
		{
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			mEnd = mData + sourceStream.read(mData, mSize);
			mFreeOnClose = freeOnClose;
		}
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(StreamPtr& sourceStream, 
		bool freeOnClose, bool readOnly)
		: Stream(static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		// Copy data from incoming stream
		mSize = sourceStream->size();
		if (mSize == 0 && !sourceStream->eof())
		{
			// size of source is unknown, read all of it into memory
			String contents = sourceStream->getAsString();
			mSize = contents.size();
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			memcpy(mData, contents.data(), mSize);
			mEnd = mData + mSize;
		}
		else
		{
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			mEnd = mData + sourceStream->read(mData, mSize);
			mFreeOnClose = freeOnClose;
		}
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(const String& name, Stream& sourceStream, 
		bool freeOnClose, bool readOnly)
		: Stream(name, static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		// Copy data from incoming stream
		mSize = sourceStream.size();
		if (mSize == 0 && !sourceStream.eof())
		{
			// size of source is unknown, read all of it into memory
			String contents = sourceStream.getAsString();
			mSize = contents.size();
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			memcpy(mData, contents.data(), mSize);
			mEnd = mData + mSize;
		}
		else
		{
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			mEnd = mData + sourceStream.read(mData, mSize);
			mFreeOnClose = freeOnClose;
		}
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(const String& name, const StreamPtr& sourceStream, 
		bool freeOnClose, bool readOnly)
		: Stream(name, static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		// Copy data from incoming stream
		mSize = sourceStream->size();
		if (mSize == 0 && !sourceStream->eof())
		{
			// size of source is unknown, read all of it into memory
			String contents = sourceStream->getAsString();
			mSize = contents.size();
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			memcpy(mData, contents.data(), mSize);
			mEnd = mData + mSize;
		}
		else
		{
			mData = (uint8*)malloc(mSize*sizeof(uint8));
			mPos = mData;
			mEnd = mData + sourceStream->read(mData, mSize);
			mFreeOnClose = freeOnClose;
		}
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(size_t inSize, bool freeOnClose, bool readOnly)
		: Stream(static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		mSize = inSize;
		mFreeOnClose = freeOnClose;
		mData = (uint8*)malloc(mSize*sizeof(uint8));
		mPos = mData;
		mEnd = mData + mSize;
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::MemoryStream(const String& name, size_t inSize, 
		bool freeOnClose, bool readOnly)
		: Stream(name, static_cast<int8>(readOnly ? READ : (READ | WRITE)))
	{
		mSize = inSize;
		mFreeOnClose = freeOnClose;
		mData = (uint8*)malloc(mSize*sizeof(uint8));
		mPos = mData;
		mEnd = mData + mSize;
		ASSERT(mEnd >= mPos);
	}
	//-----------------------------------------------------------------------
	MemoryStream::~MemoryStream()
	{
		close();
	}
	//-----------------------------------------------------------------------
	size_t MemoryStream::read(void* buf, size_t count)
	{
		size_t cnt = count;
		// Read over end of memory?
		if (mPos + cnt > mEnd)
			cnt = mEnd - mPos;
		if (cnt == 0)
			return 0;

		ASSERT (cnt<=count);

		memcpy(buf, mPos, cnt);
		mPos += cnt;
		return cnt;
	}
	//---------------------------------------------------------------------
	size_t MemoryStream::write(const void* buf, size_t count)
	{
		size_t written = 0;
		if (isWriteable())
		{
			written = count;
			// we only allow writing within the extents of allocated memory
			// check for buffer overrun & disallow
			if (mPos + written > mEnd)
				written = mEnd - mPos;
			if (written == 0)
				return 0;

			memcpy(mPos, buf, written);
			mPos += written;
		}
		return written;
	}
	//-----------------------------------------------------------------------
	size_t MemoryStream::readLine(char* buf, size_t maxCount, 
		const String& delim)
	{
		// Deal with both Unix & Windows LFs
		bool trimCR = false;
		if (delim.find_first_of('\n') != String::npos)
		{
			trimCR = true;
		}

		size_t pos = 0;

		// Make sure pos can never go past the end of the data 
		while (pos < maxCount && mPos < mEnd)
		{
			if (delim.find(*mPos) != String::npos)
			{
				// Trim off trailing CR if this was a CR/LF entry
				if (trimCR && pos && buf[pos-1] == '\r')
				{
					// terminate 1 character early
					--pos;
				}

				// Found terminator, skip and break out
				++mPos;
				break;
			}

			buf[pos++] = *mPos++;
		}

		// terminate
		buf[pos] = '\0';

		return pos;
	}
	//-----------------------------------------------------------------------
	size_t MemoryStream::skipLine(const String& delim)
	{
		size_t pos = 0;

		// Make sure pos can never go past the end of the data 
		while (mPos < mEnd)
		{
			++pos;
			if (delim.find(*mPos++) != String::npos)
			{
				// Found terminator, break out
				break;
			}
		}

		return pos;

	}
	//-----------------------------------------------------------------------
	void MemoryStream::skip(long count)
	{
		size_t newpos = (size_t)( ( mPos - mData ) + count );
		ASSERT( mData + newpos <= mEnd );        

		mPos = mData + newpos;
	}
	//-----------------------------------------------------------------------
	void MemoryStream::seek( size_t pos )
	{
		ASSERT( mData + pos <= mEnd );
		mPos = mData + pos;
	}
	//-----------------------------------------------------------------------
	size_t MemoryStream::tell(void)
	{
		//mData is start, mPos is current location
		return mPos - mData;
	}
	//-----------------------------------------------------------------------
	bool MemoryStream::eof(void) const
	{
		return mPos >= mEnd;
	}
	//-----------------------------------------------------------------------
	void MemoryStream::close(void)    
	{
		if (mFreeOnClose && mData)
		{
			free(mData);
			mData = 0;
		}

	}
}