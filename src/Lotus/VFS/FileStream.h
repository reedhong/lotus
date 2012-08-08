/*
 * stream ²Ã¼ô×ÔOgre FileStreamDataStream
 * created by reedhong 2012.07.23
 */

#ifndef __Lotus_FileStream_H__
#define __Lotus_FileStream_H__

#include "Stream.h"
#include <fstream>
using namespace std;

namespace Lotus
{
	class FileStream:public Stream
	{
	protected:
		fstream		mFStream;
	public:
		FileStream(const String& path, bool readOnly = true);
		FileStream(const String& path, const String& name, bool readOnly = true);
		~FileStream();

		/** @copydoc DataStream::read
		*/
		size_t read(void* buf, size_t count);

		/** @copydoc DataStream::write
		*/
		size_t write(const void* buf, size_t count);

		/** @copydoc DataStream::readLine
		*/
        size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");
		
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
	};
}

#endif
