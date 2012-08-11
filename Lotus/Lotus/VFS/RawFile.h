/********************************************************************
	created:	2012/08/08 
	filename: 	RawFile.h
	author:		reedhong 
	
	purpose:	操作系统自带
*********************************************************************/

#ifndef __Lotus_RawFile_H__
#define __Lotus_RawFile_H__

#include <fstream>
using namespace std;

#include "File.h"

namespace Lotus {
	class RawFile: public File
	{
	private:	
		fstream		mFStream;
		bool			mIsClose;
	public:
		RawFile(const String& path, size_t size=0, unsigned char accessMode = READ);
		virtual ~RawFile();

	/** Read the requisite number of bytes from the stream, 
			stopping at the end of the file.
		@param buf Reference to a buffer pointer
		@param count Number of bytes to read
		@return The number of bytes read
		*/
		virtual size_t read(void* buf, size_t count);
		/** Write the requisite number of bytes from the stream (only applicable to 
			streams that are not read-only)
		@param buf Pointer to a buffer containing the bytes to write
		@param count Number of bytes to write
		@return The number of bytes written
		*/
		virtual size_t write(const void* buf, size_t count);

		virtual size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");
		

	    virtual String getLine( bool trimAfter = true );


	    virtual String getAsString(void);

		virtual size_t skipLine(const String& delim = "\n");

		/** Skip a defined number of bytes. This can also be a negative value, in which case
		the file pointer rewinds a defined number of bytes. */
		virtual void skip(long count);
	
		/** Repositions the read point to a specified byte.
	    */
	    virtual void seek( size_t pos );
		
		/** Returns the current byte offset from beginning */
	    virtual size_t tell(void);

		/** Returns true if the stream has reached the end.
	    */
	    virtual bool eof(void) const;

		/** Returns the total size of the data to be read from the stream, 
			or 0 if this is indeterminate for this stream. 
		*/

        /** Close the stream; this makes further operations invalid. */
        virtual void close(void);
	};
}

#endif