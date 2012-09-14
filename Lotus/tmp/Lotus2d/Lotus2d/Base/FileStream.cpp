/********************************************************************
	created:	2012/09/14 
	filename: 	FileStream.cpp
	author:		reedhong 
	
	purpose:  
*********************************************************************/

#include "FileStream.h"

namespace Lotus2d {
	FileStream::FileStream(const char* path, const char* mode)
	{
		mFile = fopen(path, mode);
		ASSERT(mFile!=NULL);
	}

	FileStream::~FileStream()
	{

	}

	size_t FileStream::read(void* buf, size_t count)
	{
		return fread(buf, 1, count,	mFile);
	}

	size_t FileStream::write(const void* buf, size_t count)
	{
		return fwrite(buf, 1, count, mFile);
	}

	void FileStream::skip(long count)
	{
		fseek(mFile, count, SEEK_CUR);
	}

	void FileStream::seek( size_t pos )
	{
		fseek(mFile, static_cast<long>(pos), SEEK_SET);
	}

	size_t FileStream::tell(void)
	{
		return ftell(mFile);
	}

	BOOL FileStream::eof(void) const 
	{	
		return feof(mFile) != 0;
	}

	void FileStream::close(void)
	{
		if(mFile){
			fclose(mFile);
			mFile = NULL;
		}
	}
}