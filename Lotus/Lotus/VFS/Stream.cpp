#include "Stream.h"
#include "String/StringUtil.h"

namespace Lotus {
	template <typename T> Stream& Stream::operator >>(T& val)
	{
		read(static_cast<void*>(&val), sizeof(T));
		return *this;
	}
	//-----------------------------------------------------------------------
	String Stream::getLine(bool trimAfter)
	{
		char tmpBuf[STREAM_TEMP_SIZE];
		String retString;
		size_t readCount;
		// Keep looping while not hitting delimiter
		while ((readCount = read(tmpBuf, STREAM_TEMP_SIZE-1)) != 0)
		{
			// Terminate string
			tmpBuf[readCount] = '\0';

			char* p = strchr(tmpBuf, '\n');
			if (p != 0)
			{
				// Reposition backwards
				skip((long)(p + 1 - tmpBuf - readCount));
				*p = '\0';
			}

			retString += tmpBuf;

			if (p != 0)
			{
				// Trim off trailing CR if this was a CR/LF entry
				if (retString.length() && retString[retString.length()-1] == '\r')
				{
					retString.erase(retString.length()-1, 1);
				}

				// Found terminator, break out
				break;
			}
		}

		if (trimAfter)
		{
			StringUtil::trim(retString);
		}

		return retString;
	}


	//-----------------------------------------------------------------------
	size_t Stream::readLine(char* buf, size_t maxCount, const String& delim)
	{
		// Deal with both Unix & Windows LFs
		bool trimCR = false;
		if (delim.find_first_of('\n') != String::npos)
		{
			trimCR = true;
		}

		char tmpBuf[STREAM_TEMP_SIZE];
		size_t chunkSize = std::min(maxCount, (size_t)STREAM_TEMP_SIZE-1);
		size_t totalCount = 0;
		size_t readCount; 
		while (chunkSize && (readCount = read(tmpBuf, chunkSize)) != 0)
		{
			// Terminate
			tmpBuf[readCount] = '\0';

			// Find first delimiter
			size_t pos = strcspn(tmpBuf, delim.c_str());

			if (pos < readCount)
			{
				// Found terminator, reposition backwards
				skip((long)(pos + 1 - readCount));
			}

			// Are we genuinely copying?
			if (buf)
			{
				memcpy(buf+totalCount, tmpBuf, pos);
			}
			totalCount += pos;

			if (pos < readCount)
			{
				// Trim off trailing CR if this was a CR/LF entry
				if (trimCR && totalCount && buf && buf[totalCount-1] == '\r')
				{
					--totalCount;
				}

				// Found terminator, break out
				break;
			}

			// Adjust chunkSize for next time
			chunkSize = std::min(maxCount-totalCount, (size_t)STREAM_TEMP_SIZE-1);
		}

		// Terminate
		if(buf)
			buf[totalCount] = '\0';

		return totalCount;
	}
	//-----------------------------------------------------------------------
	size_t Stream::skipLine(const String& delim)
	{
		char tmpBuf[STREAM_TEMP_SIZE];
		size_t total = 0;
		size_t readCount;
		// Keep looping while not hitting delimiter
		while ((readCount = read(tmpBuf, STREAM_TEMP_SIZE-1)) != 0)
		{
			// Terminate string
			tmpBuf[readCount] = '\0';

			// Find first delimiter
			size_t pos = strcspn(tmpBuf, delim.c_str());

			if (pos < readCount)
			{
				// Found terminator, reposition backwards
				skip((long)(pos + 1 - readCount));

				total += pos + 1;

				// break out
				break;
			}

			total += readCount;
		}

		return total;
	}
	//-----------------------------------------------------------------------
	String Stream::getAsString(void)
	{
		// Read the entire buffer - ideally in one read, but if the size of
		// the buffer is unknown, do multiple fixed size reads.
		size_t bufSize = (mSize > 0 ? mSize : 4096);
		// TODO:
		char* pBuf = (char *)malloc(sizeof(char)* bufSize);
		// Ensure read from begin of stream
		seek(0);
		String result;
		while (!eof())
		{
			size_t nr = read(pBuf, bufSize);
			result.append(pBuf, nr);
		}
		//OGRE_FREE(pBuf, MEMCATEGORY_GENERAL);
		free(pBuf);
		return result;
	}
}