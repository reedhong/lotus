/********************************************************************
	created:	2012/09/14 
	filename: 	Stream.h
	author:		reedhong 
	
	purpose:	一般的读取和写入均为big endian，另外也提供little endian的接口，以 le结尾
					Big endian：将高序字节存储在起始地址
					Little endian：将低序字节存储在起始地址
					windows和linux的本地字节序均为 le， 网络字节序为be
					此处，我们默认本地字节序均为le，这样可以减少计算和分支判断
*********************************************************************/

#ifndef __Lotus2d_Stream_H__
#define __Lotus2d_Stream_H__

#include "Base/Prerequisites.h"

namespace Lotus2d {
	class Stream 
	{
	protected:
		/// Size of the data in the stream (may be 0 if size cannot be determined)
		size_t mSize;
	public:
		Stream();
		virtual ~Stream();
		static void swapEndian(void* pData, size_t size);

		virtual size_t read(void* buf, size_t count) = 0;
		virtual size_t write(const void* buf, size_t count)=0;
		virtual void skip(long count) = 0;
		virtual void seek( size_t pos ) = 0;
		virtual size_t tell(void)  = 0;
		virtual BOOL eof(void) const = 0;
		virtual void close(void) = 0;

		size_t size(void) const { return mSize; }
		
		virtual BOOL readBool();
		virtual uint8 read8();
		virtual uint16 read16();
		virtual uint32 read32();
		virtual uint64 read64();
		virtual float readf();

		/* 以le字节序读入*/
		virtual uint16 read16le();
		virtual uint32 read32le();
		virtual uint64 read64le();


		virtual void writeBool(BOOL b);
		virtual void write8(uint8 c);
		virtual void write16(uint16 s);
		virtual void write32(uint32 i);	
		virtual void write64(uint64 l);	
		virtual void writef(float f);
		
		/* 以le字节序写入，可以直接写入，无需转换*/
		virtual void write16le(uint16 s);
		virtual void write32le(uint32 i);	
		virtual void write64le(uint64 l);	
	};

}


#endif