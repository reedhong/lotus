/********************************************************************
	created:	2012/09/06 
	filename: 	HardwareShadowBuffer.h
	author:		reedhong 
	
	purpose:	硬件buffer在系统内存中的缓冲
*********************************************************************/

#ifndef __Lotus_HardwareShadowBuffer_H__
#define __Lotus_HardwareShadowBuffer_H__

#include "General/Prerequisites.h"
#include "HardwareBuffer.h"

namespace Lotus {
	class HardwareBufferManager;
	class HardwareShadowBuffer:public HardwareBuffer
	{
	protected:
		unsigned char*				mData;
		HardwareBufferManager*		mgr;
		void* lockImpl(size_t offset, size_t length, LockOptions options);
		void unlockImpl(void);

	public:
		HardwareShadowBuffer(size_t size, unsigned int usage, HardwareBufferManager* mgr);		
		~HardwareShadowBuffer();
		/** See HardwareBuffer. */
		void readData(size_t offset, size_t length, void* pDest);
		/** See HardwareBuffer. */
		void writeData(size_t offset, size_t length, const void* pSource,
			bool discardWholeBuffer = false);
		/** Override HardwareBuffer to turn off all shadowing. */
		void* lock(size_t offset, size_t length, LockOptions options);
		/** Override HardwareBuffer to turn off all shadowing. */
		void unlock(void);
	};
}

#endif

