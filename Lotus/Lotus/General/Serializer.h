/********************************************************************
	created:	2012/08/29 
	filename: 	Serializer.h
	author:		reedhong 
	
	purpose:	序列化工具，用于不同类型资源的序列化
*********************************************************************/

#ifndef __Lotus_Serializer_H__
#define __Lotus_Serializer_H__

#include "Prerequisites.h"
#include "Stream.h"

namespace Lotus {

	class Serializer
	{
	public:
		Serializer();
		Serializer(StreamPtr stream);
		virtual ~Serializer();

	protected:
		uint32		mCurrentStreamLen;
		String mVersion;
		StreamPtr	mStream;
		bool		mFlipEndian;

		void attachStream(StreamPtr stream);
		// Internal methods
		virtual void writeFileHeader(void);
		virtual void writeChunkHeader(uint16 id, size_t size);

		void writeFloats(const float* const pfloat, size_t count);
		void writeShorts(const uint16* const pShort, size_t count);
		void writeInts(const uint32* const pInt, size_t count); 
		void writeBools(const bool* const pBool, size_t count);
		void writeObject(const Vector3& vec);
		void writeObject(const Quaternion& q);

		void writeString(const String& string);
		void writeData(const void* const buf, size_t size, size_t count);

		virtual void readFileHeader();
		virtual unsigned short readChunk();

		void readBools(bool* pDest, size_t count);
		void readFloats(float* pDest, size_t count);
		void readShorts( uint16* pDest, size_t count);
		void readInts(uint32* pDest, size_t count);
		void readObject(Vector3& pDest);
		void readObject(Quaternion& pDest);

		String readString();
		String readString(size_t numChars);
	};

}  // end Lotus
#endif
