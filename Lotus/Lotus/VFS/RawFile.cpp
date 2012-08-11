/********************************************************************
	created:	2012/08/08 
	filename: 	RawFile.cpp
	author:		reedhong 
	
	purpose:	系统自带
*********************************************************************/
#include "Exception/Exception.h"
#include "Log/LoggerManager.h"
#include "RawFile.h"


namespace Lotus {
	RawFile::RawFile(const String& path, size_t size, unsigned char accessMode):
		File(path, size, accessMode), mIsClose(false)
	{
		ios_base::openmode mode = ios_base::in;
		if(accessMode != READ){
			mode = ios_base::out;
		}

		mFStream.open(path.c_str(), mode);
		if(! mFStream.is_open()){
			LOTUS_EXCEPT(
				Exception::ERR_FILE_NOT_FOUND, "'" + path + "' file not found!", "FileStream::FileStream" );		
		}
	}

	RawFile::~RawFile()
	{
		if(!mIsClose && mFStream.is_open()){
			close();
		}
	}

	size_t RawFile::read(void* buf, size_t count)
	{
		mFStream.read(static_cast<char*>(buf), static_cast<std::streamsize>(count));
		return mFStream.gcount();
	}
	//-----------------------------------------------------------------------
	size_t RawFile::write(const void* buf, size_t count)
	{
		size_t written = 0;
		if (isWriteable() && mFStream)
		{
			mFStream.write(static_cast<const char*>(buf), static_cast<std::streamsize>(count));
			written = count;
		}
		return written;
	}
	//-----------------------------------------------------------------------
	size_t RawFile::readLine(char* buf, size_t maxCount, 
		const String& delim)
	{
		if (delim.empty())
		{
			LOTUS_EXCEPT(Exception::ERR_INVALIDPARAMS, "No delimiter provided",
				"FileStream::readLine");
		}
		if (delim.size() > 1)
		{
			LoggerManager::Instance()->log(eLogError,
				"WARNING: FileStream::readLine - using only first delimeter");
		}
		// Deal with both Unix & Windows LFs
		bool trimCR = false;
		if (delim.at(0) == '\n') 
		{
			trimCR = true;
		}
		// maxCount + 1 since count excludes terminator in getline
		mFStream.getline(buf, static_cast<std::streamsize>(maxCount+1), delim.at(0));
		size_t ret = mFStream.gcount();
		// three options
		// 1) we had an eof before we read a whole line
		// 2) we ran out of buffer space
		// 3) we read a whole line - in this case the delim character is taken from the stream but not written in the buffer so the read data is of length ret-1 and thus ends at index ret-2
		// in all cases the buffer will be null terminated for us

		if (mFStream.eof()) 
		{
			// no problem
		}
		else if (mFStream.fail())
		{
			// Did we fail because of maxCount hit? No - no terminating character
			// in included in the count in this case
			if (ret == maxCount)
			{
				// clear failbit for next time 
				mFStream.clear();
			}
			else
			{
				LOTUS_EXCEPT(Exception::ERR_INTERNAL_ERROR, 
					"Streaming error occurred", 
					"FileStream::readLine");
			}
		}
		else 
		{
			// we need to adjust ret because we want to use it as a
			// pointer to the terminating null character and it is
			// currently the length of the data read from the stream
			// i.e. 1 more than the length of the data in the buffer and
			// hence 1 more than the _index_ of the NULL character
			--ret;
		}

		// trim off CR if we found CR/LF
		if (trimCR && buf[ret-1] == '\r')
		{
			--ret;
			buf[ret] = '\0';
		}
		return ret;
	}

	String RawFile::getLine( bool trimAfter)
	{
		return "";
	}


	String RawFile::getAsString(void)
	{
		return "";
	}

	size_t RawFile::skipLine(const String& delim)
	 {
		return 0;
	 }
	//-----------------------------------------------------------------------
	void RawFile::skip(long count)
	{
#if defined(STLPORT)
		// Workaround for STLport issues: After reached eof of file stream,
		// it's seems the stream was putted in intermediate state, and will be
		// fail if try to repositioning relative to current position.
		// Note: tellg() fail in this case too.
		if (mInStream->eof())
		{
			mInStream->clear();
			// Use seek relative to either begin or end to bring the stream
			// back to normal state.
			mInStream->seekg(0, std::ios::end);
		}
#endif 		
		mFStream.clear(); //Clear fail status in case eof was set
		mFStream.seekg(static_cast<std::ifstream::pos_type>(count), std::ios::cur);
	}
	//-----------------------------------------------------------------------
	void RawFile::seek( size_t pos )
	{		
		mFStream.clear(); //Clear fail status in case eof was set
		mFStream.seekg(static_cast<std::streamoff>(pos), std::ios::beg);
	}
	//-----------------------------------------------------------------------
	size_t RawFile::tell(void)
	{
		mFStream.clear(); //Clear fail status in case eof was set
		return (size_t)mFStream.tellg();	
		
	}
	//-----------------------------------------------------------------------
	bool RawFile::eof(void) const
	{
		return mFStream.eof();
	}
	//-----------------------------------------------------------------------
	void RawFile::close(void)
	{
		if(mFStream.is_open()){
			mFStream.flush();
			mFStream.close();
			mIsClose = true;
		}
	}
} // Lotus