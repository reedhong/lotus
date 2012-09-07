/********************************************************************
	created:	2012/09/06 
	filename: 	HardwareShadowBuffer.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "HardwareShadowBuffer.h"

namespace Lotus {
	HardwareShadowBuffer::HardwareShadowBuffer(size_t size, unsigned int usage, HardwareBufferManager* mgr):
		HardwareBuffer(usage, true, false), mgr(mgr)
	{
		mData = static_cast<unsigned char*>(LOTUS_NEW unsigned char[size]);
		mSizeInBytes = size;

	}
	HardwareShadowBuffer::~HardwareShadowBuffer()
	{
		LOTUS_DELETE[] mData;
	}
	
	void HardwareShadowBuffer::readData(size_t offset, size_t length, void* pDest)
	{
		ASSERT((offset + length) <= mSizeInBytes);
		memcpy(pDest, mData + offset, length);
	}

	
	void HardwareShadowBuffer::writeData(size_t offset, size_t length, const void* pSource,
		bool discardWholeBuffer)
	{
		ASSERT((offset + length) <= mSizeInBytes);
		// ignore discard, memory is not guaranteed to be zeroised
		memcpy(mData + offset, pSource, length);
	}

	void* HardwareShadowBuffer::lockImpl(size_t offset, size_t length, LockOptions options)
	{
		return mData+offset;
	}
	
	void HardwareShadowBuffer::unlockImpl(void)
	{

	}

	void* HardwareShadowBuffer::lock(size_t offset, size_t length, LockOptions options)
	{
		mIsLocked = true;
		return mData+offset;
	}
	
	void HardwareShadowBuffer::unlock(void)
	{
		mIsLocked = false;
	}
}