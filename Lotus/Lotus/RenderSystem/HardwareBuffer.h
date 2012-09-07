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
			 *�������͵����������ȡ��д�뻺�棬������õ�һ��������Ϊ���������ڸ����Կ����ܹ����κβ�����
			 *�����ʹ��Ӱ�ӻ��棬��Ҫ�󻺴����ݴ��Կ����ش��䣬���ʹ��Ӱ�ӻ���Ļ����Ӱ������С��
			 */
			eHBL_NORMAL,
			/*
			 * ����ζ��������ⶪ���Կ��������������������ݡ�����֮�����㲻�����������ȡ���ݣ�
			 * Ҳ��ζ���������������ڱ����ƵĻ����Կ����Ա�����ê����Ϊ��������һ����ȫ��ͬ�Ļ������ݡ�
			 * �������һ��û��ʹ��Ӱ�ӻ���Ļ��滰�������ܵ�ʹ��������������ʹ����Ӱ�Ӳ����Ļ�������Ӱ\
			 * ��ͱȽ�С��������Ӱ�ӻ��棬����������һ���������������棬��Ϊ������Ӱ�ӻ���ʹ��HBL_DISCARD��
			 * �����ϴ����µ����ݵ����������ʱ��
			 */
			eHBL_DISCARD,
			/* 
			 * ��ζ����ֻ��Ҫ��ȡ��������ݡ�������ڻ����趨��Ӱ�ӻ����ʱ��ʹ�ã���Ϊ���ʱ�����ݲ���Ҫ���Կ�������
			 */
			eHBL_READ_ONLY,
			/*
			 * ��������ã������ֻ��Ҫ���������һ���ֵĻ�����Ϊ�����Ͳ���ʹ��HBL_DISCARD���������Կ����ŵ��������
			 * ֡���Ѿ��ڻ����еĻ�����ǲ��֡����Ҳ��ֻ��û���趨Ӱ�ӻ���Ļ����ϲ����á�
			 */
			eHBL_NO_OVERWRITE
		};
	protected:
		size_t	mSizeInBytes;
		unsigned int mUsage;		// �˴�ֱ��ʹ��OpenGL��usage,������������ֵ
		bool	mIsLocked;
		size_t	mLockStart;
		size_t mLockSize;
		bool mSystemMemory;
		bool mUseShadowBuffer;
		HardwareBuffer*		mShadowBuffer;	// һ����ϵͳ�Ļ������
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