/********************************************************************
	created:	2012/09/05 
	filename: 	HardwareBuffer.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_HardwareBuffer_H__
#define __Lotus_HardwareBuffer_H__

namespace Lotus {
	class HardwareBuffer 
	{
	public:
		enum LockOptions
		{
			/*
			 *这种类型的锁定允许读取和写入缓存，这是最不好的一个操作因为基本上你在告诉显卡你能够做任何操作。
			 *如果你使用影子缓存，它要求缓存数据从显卡来回传输，如果使用影子缓存的话这个影响是最小的
			 */
			eHBL_NORMAL,
			/*
			 * 这意味着你很乐意丢弃显卡上这个缓存里的所有内容。言下之意是你不会从这个缓存读取数据，
			 * 也意味着如果这个缓存正在被绘制的话，显卡可以避免抛锚，因为它将给你一个完全不同的缓存数据。
			 * 如果锁定一个没有使用影子缓存的缓存话，尽可能的使用这个参数。如果使用了影子参数的话，它的影\
			 * 响就比较小，尽管有影子缓存，它更倾向于一次性锁定整个缓存，因为它允许影子缓存使用HBL_DISCARD，
			 * 当它上传更新的内容到真正缓存的时候。
			 */
			eHBL_DISCARD,
			/* 
			 * 意味着你只想要读取缓存的内容。最好是在缓存设定了影子缓存的时候使用，因为这个时候数据不需要从显卡中下载
			 */
			eHBL_READ_ONLY,
			/*
			 * 这个很有用，如果你只是要锁定缓存的一部分的话，因为那样就不能使用HBL_DISCARD。它告诉显卡你承诺不更改这
			 * 帧中已经在绘制中的缓存的那部分。这个也是只在没有设定影子缓存的缓存上才有用。
			 */
			eHBL_NO_OVERWRITE
		};
	protected:
		size_t	mSizeInBytes;
		unsigned int mUsage;		// 此处直接使用OpenGL中usage,不在重新设置值
		bool	mIsLocked;
		size_t	mLockStart;
		size_t mLockSize;
		bool mSystemMemory;
		bool mUseShadowBuffer;
		HardwareBuffer*		mShadowBuffer;	// 一般由系统的缓存替代
		bool	mShadowUpdated;

		virtual void* lockImpl(size_t offset, size_t length, LockOptions options) = 0;
		virtual void unlockImpl(void) = 0;

	public:
		HardwareBuffer(unsigned int usage,  bool systemMemory, bool useShadowBuffer):
		  mUsage(usage), mIsLocked(false), mUseShadowBuffer(useShadowBuffer), mShadowBuffer(0),
			  mShadowUpdated(false), mSystemMemory(systemMemory)
		  {
		  }

		virtual ~HardwareBuffer() {}

		virtual void* lock(size_t offset, size_t length, LockOptions options);
		void* lock(LockOptions options);
		virtual void unlock(void);

		virtual void readData(size_t offset, size_t length, void* pDest) = 0;
		virtual void writeData(size_t offset, size_t length, const void* pSource,
			bool discardWholeBuffer = false) = 0;
		virtual void copyData(HardwareBuffer& srcBuffer, size_t srcOffset, 
			size_t dstOffset, size_t length, bool discardWholeBuffer = false);
		virtual void copyData(HardwareBuffer& srcBuffer);

		virtual void _updateFromShadow(void);
	
		/// Returns the size of this buffer in bytes
		size_t getSizeInBytes(void) const { return mSizeInBytes; }
		/// Returns the Usage flags with which this buffer was created
		unsigned int  getUsage(void) const { return mUsage; }
		/// Returns whether this buffer is held in system memory
		bool isSystemMemory(void) const { return mSystemMemory; }
		/// Returns whether this buffer has a system memory shadow for quicker reading
		bool hasShadowBuffer(void) const { return mUseShadowBuffer; }
		/// Returns whether or not this buffer is currently locked.
		bool isLocked(void) const { 
			return mIsLocked || (mUseShadowBuffer && mShadowBuffer->isLocked()); 
		}

	};
}


#endif