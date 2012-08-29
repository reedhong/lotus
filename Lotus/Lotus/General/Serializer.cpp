/********************************************************************
	created:	2012/08/29 
	filename: 	Serializer.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Serializer.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Exception/Exception.h"

namespace Lotus {
	const size_t STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	const uint16 HEADER_STREAM_ID = 0x1000;
	const uint16 OTHER_ENDIAN_HEADER_STREAM_ID = 0x0010;
	const int MAX_STR_LEN = 255;		// 这个其实限制了动画等命名的长度
	Serializer::Serializer()
	{
		// TODO:
		// 暂时认为无须交换字节序
		//mFlipEndian =  (Endian::s_IsLittleEndian != true);

	}

	Serializer::Serializer(StreamPtr stream):mStream(stream)
	{
		
	}

	Serializer::~Serializer()
	{
		
	}

	void Serializer::attachStream(StreamPtr stream)
	{
		mStream = stream;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// 写
	void Serializer::writeFileHeader(void)
	{
		uint16 val = HEADER_STREAM_ID;
		writeShorts(&val, 1);

		writeString(mVersion);
	}

	void Serializer::writeChunkHeader(uint16 id, size_t size)
	{
		writeShorts(&id, 1);
		uint32 uint32size = static_cast<uint32>(size);
		writeInts(&uint32size, 1);
	}

	void Serializer::writeFloats(const float* const pfloat, size_t count)
	{
		writeData(pfloat, sizeof(float), count);
	}


	void Serializer::writeShorts(const uint16* const pShort, size_t count)
	{
		writeData(pShort, sizeof(unsigned short), count);
	}

	void Serializer::writeInts(const uint32* const pInt, size_t count)
	{
		writeData(pInt, sizeof(unsigned int), count);
	}

	void Serializer::writeBools(const bool* const pBool, size_t count)
	{
#	if LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE || LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE_IOS
		char * pCharToWrite = (char *)malloc(sizeof(char) * count);
		for(unsigned int i = 0; i < count; i++)
		{
			*(char *)(pCharToWrite + i) = *(bool *)(pBool + i);
		}

		writeData(pCharToWrite, sizeof(char), count);

		free(pCharToWrite);
#	else
		writeData(pBool, sizeof(bool), count);
#	endif
	}

	void Serializer::writeObject(const Vector3& vec)
	{
		float tmp[3]  = {vec.x, vec.y, vec.z};
		writeFloats(tmp, 3);
	}

	void Serializer::writeObject(const Quaternion& q)
	{
		float tmp[4] = { q.x, q.y, q.z, q.w };
		writeFloats(tmp, 4);
	}

	void Serializer::writeString(const String& string)
	{
		// Old, backwards compatible way - \n terminated
		mStream->write(string.c_str(), string.length());
		// Write terminating newline char
		char terminator = '\n';
		mStream->write(&terminator, 1);
	}

	void Serializer::writeData(const void* const buf, size_t size, size_t count)
	{
		mStream->write(buf, size * count);
	}

	//////////////////////////////////////////////////////////////////////////
	// 读
	void Serializer::readFileHeader()	
	{
		unsigned short headerID;

		// Read header ID
		readShorts(&headerID, 1);

		if (headerID == HEADER_STREAM_ID)
		{
			// Read version
			String ver = readString();
			if (ver != mVersion)
			{
				LOTUS_EXCEPT(Exception::ERR_INTERNAL_ERROR, 
					"Invalid file: version incompatible, file reports " + String(ver) +
					" Serializer is version " + mVersion,
					"Serializer::readFileHeader");
			}
		}
		else
		{
			LOTUS_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Invalid file: no header", 
				"Serializer::readFileHeader");
		}
	}

	unsigned short Serializer::readChunk()
	{
		unsigned short id;
		readShorts(&id, 1);
		readInts(&mCurrentStreamLen, 1);
		return id;
	}

	void Serializer::readBools(bool* pDest, size_t count)
	{
		//XXX Nasty Hack to convert 1 byte bools to 4 byte bools
#	if LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE || LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE_IOS
		char * pTemp = (char *)malloc(1*count); // to hold 1-byte bools
		mStream->read(pTemp, 1 * count);
		for(unsigned int i = 0; i < count; i++)
			*(bool *)(pDest + i) = *(char *)(pTemp + i);

		free (pTemp);
#	else
		mStream->read(pDest, sizeof(bool) * count);
#	endif
	}

	void Serializer::readFloats(float* pDest, size_t count)
	{
		mStream->read(pDest, sizeof(float) * count);
		//flipFromLittleEndian(pDest, sizeof(float), count);
	}


	void Serializer::readShorts( uint16* pDest, size_t count)
	{
        mStream->read(pDest, sizeof(unsigned short) * count);
	}

	void Serializer::readInts(uint32* pDest, size_t count)
	{
        mStream->read(pDest, sizeof(unsigned int) * count);
	}

	void Serializer::readObject(Vector3& pDest)
	{
		float tmp[3];
		readFloats(tmp, 3);
		pDest.x = tmp[0];
		pDest.y = tmp[1];
		pDest.z = tmp[2];
	}

	void Serializer::readObject(Quaternion& pDest)
	{
		float tmp[4];
		readFloats(tmp, 4);
		pDest.x = tmp[0];
		pDest.y = tmp[1];
		pDest.z = tmp[2];
		pDest.w = tmp[3];
	}

	String Serializer::readString()
	{
        return mStream->getLine(false);
	}

	String Serializer::readString(size_t numChars)
	{
		assert (numChars <= MAX_STR_LEN);
		char str[MAX_STR_LEN];
		mStream->read(str, numChars);
		str[numChars] = '\0';
		return str;
	}
}