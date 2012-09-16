/********************************************************************
	created:	2012/09/14 
	filename: 	Stream.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Stream.h"

namespace Lotus2d {
	Stream::Stream()
	{

	}

	Stream::~Stream()
	{

	}

	void Stream::swapEndian(void* pData, size_t size)
	{
		unsigned char swapByte;
		for(unsigned int byteIndex = 0; byteIndex < size/2; byteIndex++)
		{
			swapByte = *(char *)((size_t)pData + byteIndex);
			*(unsigned char *)((size_t)pData + byteIndex) = *(unsigned char *)((size_t)pData + size - byteIndex - 1);
			*(unsigned char *)((size_t)pData + size - byteIndex - 1) = swapByte;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// read
	BOOL Stream::readBool()
	{
		uint8 c;
		read(&c, 1);
		return c==TRUE;
	}
	uint8 Stream::read8()
	{
		uint8 c;
		read(&c, 1);
		return c;
	}
	uint16 Stream::read16()
	{
		uint16 s;
		read(&s, 2);
		swapEndian(&s, 2);
		return s;
	}

	uint32 Stream::read32()
	{
		uint32 i;
		read(&i, 4);
		swapEndian(&i, 4);
		return i;
	}
	uint64 Stream::read64()
	{
		uint64 l;
		read(&l, sizeof(uint64));
		swapEndian(&l, sizeof(uint64));
		return l;
	}

	float Stream::readf()
	{
		float f;
		read(&f, sizeof(float));
		return f;
	}

	uint16 Stream::read16le()
	{
		uint16 s;
		read(&s, 2);
		return s;
	}

	uint32 Stream::read32le()
	{
		uint32 i;
		read(&i, 4);
		return i;
	}
	uint64 Stream::read64le()
	{
		uint64 l;
		read(&l, sizeof(uint64));
		return l;
	}

	//////////////////////////////////////////////////////////////////////////
	// write
	void Stream::writeBool(BOOL b)
	{
		write8(b);
	}
	void Stream::write8(uint8 c)
	{
		write(&c, 1);
	}

	void Stream::write16(uint16 s)
	{
		swapEndian(&s, 2);
		write(&s, 2);
	}

	void Stream::write32(uint32 i)
	{
		swapEndian(&i, 4);
		write(&i, 4);
	}

	void Stream::write64(uint64 l)
	{
		swapEndian(&l, sizeof(uint64));
		write(&l, sizeof(uint64));
	}

	void Stream::writef(float f)
	{
		write(&f, sizeof(float));
	}

	void Stream::write16le(uint16 s)
	{
		write(&s, 2);
	}

	void Stream::write32le(uint32 i)
	{
		write(&i, 4);
	}

	void Stream::write64le(uint64 l)
	{
		write(&l, sizeof(uint64));
	}
}