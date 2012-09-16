/********************************************************************
	created:	2012/09/14 
	filename: 	Stream.h
	author:		reedhong 
	
	purpose:	һ��Ķ�ȡ��д���Ϊbig endian������Ҳ�ṩlittle endian�Ľӿڣ��� le��β
					Big endian���������ֽڴ洢����ʼ��ַ
					Little endian���������ֽڴ洢����ʼ��ַ
					windows��linux�ı����ֽ����Ϊ le�� �����ֽ���Ϊbe
					�˴�������Ĭ�ϱ����ֽ����Ϊle���������Լ��ټ���ͷ�֧�ж�
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

		/* ��le�ֽ������*/
		virtual uint16 read16le();
		virtual uint32 read32le();
		virtual uint64 read64le();


		virtual void writeBool(BOOL b);
		virtual void write8(uint8 c);
		virtual void write16(uint16 s);
		virtual void write32(uint32 i);	
		virtual void write64(uint64 l);	
		virtual void writef(float f);
		
		/* ��le�ֽ���д�룬����ֱ��д�룬����ת��*/
		virtual void write16le(uint16 s);
		virtual void write32le(uint32 i);	
		virtual void write64le(uint64 l);	
	};

}


#endif