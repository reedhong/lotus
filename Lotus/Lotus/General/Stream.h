/********************************************************************
	created:	2012/08/29 
	filename: 	Stream.h
	author:		reedhong 
	
	purpose:	Á÷: ÎÄ¼þ£¬ÍøÂç
*********************************************************************/

#ifndef __Lotus_Stream_H__
#define __Lotus_Stream_H__

#include "Prerequisites.h"

namespace Lotus {
	class Stream
	{
	public:
		enum AccessMode
		{
			READ = 1, 
			WRITE = 2
		};
	protected:
		/// The name (e.g. resource name) that can be used to identify the source fot his data (optional)
		String mName;		
        /// Size of the data in the stream (may be 0 if size cannot be determined)
        size_t mSize;
		/// What type of access is allowed (AccessMode)
		uint16 mAccess;

		#define LOTUS_STREAM_TEMP_SIZE 128
	public:
		/// Constructor for creating unnamed streams
        Stream(uint16 accessMode = READ) : mSize(0), mAccess(accessMode) {}
		/// Constructor for creating named streams
		Stream(const String& name, uint16 accessMode = READ) 
			: mName(name), mSize(0), mAccess(accessMode) {}
		/// Returns the name of the stream, if it has one.
		const String& getName(void) { return mName; }
		/// Gets the access mode of the stream
		uint16 getAccessMode() const { return mAccess; }
		/** Reports whether this stream is readable. */
		virtual bool isReadable() const { return (mAccess & READ) != 0; }
		/** Reports whether this stream is writeable. */
		virtual bool isWriteable() const { return (mAccess & WRITE) != 0; }
        virtual ~Stream() {}
		// Streaming operators
        template<typename T> Stream& operator>>(T& val);
		/** Read the requisite number of bytes from the stream, 
			stopping at the end of the file.
		@param buf Reference to a buffer pointer
		@param count Number of bytes to read
		@return The number of bytes read
		*/
		virtual size_t read(void* buf, size_t count) = 0;
		/** Write the requisite number of bytes from the stream (only applicable to 
			streams that are not read-only)
		@param buf Pointer to a buffer containing the bytes to write
		@param count Number of bytes to write
		@return The number of bytes written
		*/
		virtual size_t write(const void* buf, size_t count)
		{
                        (void)buf;
                        (void)count;
			// default to not supported
			return 0;
		}

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
		virtual void skip(long count) = 0;
	
		/** Repositions the read point to a specified byte.
	    */
	    virtual void seek( size_t pos ) = 0;
		
		/** Returns the current byte offset from beginning */
	    virtual size_t tell(void)  = 0;

		/** Returns true if the stream has reached the end.
	    */
	    virtual bool eof(void) const = 0;

		/** Returns the total size of the data to be read from the stream, 
			or 0 if this is indeterminate for this stream. 
		*/
        size_t size(void) const { return mSize; }

        /** Close the stream; this makes further operations invalid. */
        virtual void close(void) = 0;
		
	};

	typedef SharedPtr<Stream> StreamPtr;
}

#endif