/*
 * stream ²Ã¼ô×ÔOgre MemoryStream
 * created by reedhong 2012.07.23
 */

#ifndef __Lotus_Memory_Stream_H__
#define __Lotus_Memory_Stream_H__

#include "Platform/Platform.h"

#include "Stream.h"

namespace Lotus
{
	class MemoryStream: public Stream
	{
protected:
        /// Pointer to the start of the data area
	    uint8* mData;
        /// Pointer to the current position in the memory
	    uint8* mPos;
        /// Pointer to the end of the memory
	    uint8* mEnd;
        /// Do we delete the memory on close
		bool mFreeOnClose;			
	public:
		
		/** Wrap an existing memory chunk in a stream.
		@param pMem Pointer to the existing memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed. Note: it's important that if you set
			this option to true, that you allocated the memory using OGRE_ALLOC_T
			with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
			matches up.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(void* pMem, size_t size, bool freeOnClose = false, bool readOnly = false);
		
		/** Wrap an existing memory chunk in a named stream.
		@param name The name to give the stream
		@param pMem Pointer to the existing memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed. Note: it's important that if you set
			this option to true, that you allocated the memory using OGRE_ALLOC_T
			with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
			matches up.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(const String& name, void* pMem, size_t size, 
				bool freeOnClose = false, bool readOnly = false);

		/** Create a stream which pre-buffers the contents of another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param sourceStream Another DataStream which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(Stream& sourceStream, 
				bool freeOnClose = true, bool readOnly = false);
		
		/** Create a stream which pre-buffers the contents of another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param sourceStream Weak reference to another DataStream which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(StreamPtr& sourceStream, 
				bool freeOnClose = true, bool readOnly = false);

		/** Create a named stream which pre-buffers the contents of 
			another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param name The name to give the stream
		@param sourceStream Another DataStream which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(const String& name, Stream& sourceStream, 
				bool freeOnClose = true, bool readOnly = false);

        /** Create a named stream which pre-buffers the contents of 
        another stream.
        @remarks
        This constructor can be used to intentionally read in the entire
        contents of another stream, copying them to the internal buffer
        and thus making them available in memory as a single unit.
        @param name The name to give the stream
        @param sourceStream Another DataStream which will provide the source
        of data
        @param freeOnClose If true, the memory associated will be destroyed
        when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
        */
        MemoryStream(const String& name, const StreamPtr& sourceStream, 
            bool freeOnClose = true, bool readOnly = false);

        /** Create a stream with a brand new empty memory chunk.
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(size_t size, bool freeOnClose = true, bool readOnly = false);
		/** Create a named stream with a brand new empty memory chunk.
		@param name The name to give the stream
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		MemoryStream(const String& name, size_t size, 
				bool freeOnClose = true, bool readOnly = false);

		~MemoryStream();

		/** Get a pointer to the start of the memory block this stream holds. */
		uint8* getPtr(void) { return mData; }
		
		/** Get a pointer to the current position in the memory block this stream holds. */
		uint8* getCurrentPtr(void) { return mPos; }
		
		/** @copydoc DataStream::read
		*/
		size_t read(void* buf, size_t count);

		/** @copydoc DataStream::write
		*/
		size_t write(const void* buf, size_t count);

		/** @copydoc DataStream::readLine
		*/
		size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");
		
		/** @copydoc DataStream::skipLine
		*/
		size_t skipLine(const String& delim = "\n");

		/** @copydoc DataStream::skip
		*/
		void skip(long count);
	
		/** @copydoc DataStream::seek
		*/
	    void seek( size_t pos );
		
		/** @copydoc DataStream::tell
		*/
	    size_t tell(void);

		/** @copydoc DataStream::eof
		*/
	    bool eof(void) const;

        /** @copydoc DataStream::close
        */
        void close(void);

		/** Sets whether or not to free the encapsulated memory on close. */
		void setFreeOnClose(bool free) { mFreeOnClose = free; }
	};
}

#endif
