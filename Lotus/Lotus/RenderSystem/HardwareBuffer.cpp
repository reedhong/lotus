/********************************************************************
	created:	2012/09/06 
	filename: 	HardwareBuffer.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Exception/Exception.h"

#include "HardwareBuffer.h"

namespace Lotus {
	void * HardwareBuffer::lock(size_t offset, size_t length, LockOptions options)
	{
		ASSERT(!isLocked() && "Cannot lock this buffer, it is already locked!");

		void* ret = NULL;
		if ((length + offset) > mSizeInBytes)
		{
			LOTUS_EXCEPT(Exception::ERR_INVALIDPARAMS,
				"Lock request out of bounds.",
				"HardwareBuffer::lock");
		}
		else if (mUseShadowBuffer)
		{
			if (options != eHBL_READ_ONLY)
			{
				// we have to assume a read / write lock so we use the shadow buffer
				// and tag for sync on unlock()
				mShadowUpdated = true;
			}

			ret = mShadowBuffer->lock(offset, length, options);
		}
		else
		{
			// Lock the real buffer if there is no shadow buffer 
			ret = lockImpl(offset, length, options);
			mIsLocked = true;
		}
		mLockStart = offset;
		mLockSize = length;
		return ret;
	}

	void* HardwareBuffer::lock(LockOptions options)
	{
		return this->lock(0, mSizeInBytes, options);
	}
	

	void HardwareBuffer::copyData(HardwareBuffer& srcBuffer, size_t srcOffset, 
			size_t dstOffset, size_t length, bool discardWholeBuffer)
		{
			const void *srcData = srcBuffer.lock(
				srcOffset, length, eHBL_READ_ONLY);
			this->writeData(dstOffset, length, srcData, discardWholeBuffer);
			srcBuffer.unlock();
		}

		/** Copy all data from another buffer into this one. 
		@remarks
			Normally these buffers should be of identical size, but if they're
			not, the routine will use the smallest of the two sizes.
		*/
		void HardwareBuffer::copyData(HardwareBuffer& srcBuffer)
		{
			size_t sz = std::min(getSizeInBytes(), srcBuffer.getSizeInBytes()); 
			copyData(srcBuffer, 0, 0, sz, true);
		}
			
			/// Updates the real buffer from the shadow buffer, if required
        void HardwareBuffer::_updateFromShadow(void)
        {
            if (mUseShadowBuffer && mShadowUpdated)
            {
                // Do this manually to avoid locking problems
                const void *srcData = mShadowBuffer->lockImpl(
					mLockStart, mLockSize, eHBL_READ_ONLY);
				// Lock with discard if the whole buffer was locked, otherwise normal
				LockOptions lockOpt;
				if (mLockStart == 0 && mLockSize == mSizeInBytes)
					lockOpt = eHBL_DISCARD;
				else
					lockOpt = eHBL_NORMAL;
				
                void *destData = this->lockImpl(
					mLockStart, mLockSize, lockOpt);
				// Copy shadow to real
                memcpy(destData, srcData, mLockSize);
                this->unlockImpl();
                mShadowBuffer->unlockImpl();
                mShadowUpdated = false;
            }
        }
}