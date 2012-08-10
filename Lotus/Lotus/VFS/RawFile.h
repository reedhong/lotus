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

		/** Get a single line from the stream.
		@remarks
			The delimiter character is not included in the data
			returned, and it is skipped over so the next read will occur
			after it. The buffer contents will include a
			terminating character.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
		@param buf Reference to a buffer pointer
		@param maxCount The maximum length of data to be read, excluding the terminating character
		@param delim The delimiter to stop at
		@return The number of bytes read, excluding the terminating character
		*/
		virtual size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");
		
	    /** Returns a String containing the next line of data, optionally 
		    trimmed for whitespace. 
	    @remarks
		    This is a convenience method for text streams only, allowing you to 
		    retrieve a String object containing the next line of data. The data
		    is read up to the next newline character and the result trimmed if
		    required.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
	    @param 
		    trimAfter If true, the line is trimmed for whitespace (as in 
		    String.trim(true,true))
	    */
	    virtual String getLine( bool trimAfter = true );

	    /** Returns a String containing the entire stream. 
	    @remarks
		    This is a convenience method for text streams only, allowing you to 
		    retrieve a String object containing all the data in the stream.
	    */
	    virtual String getAsString(void);

		/** Skip a single line from the stream.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
		@param delim The delimiter(s) to stop at
		@return The number of bytes skipped
		*/
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