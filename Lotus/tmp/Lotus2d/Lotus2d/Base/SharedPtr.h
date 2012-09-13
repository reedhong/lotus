/*
 * �ü���Ogre, ����ָ��
 */

#ifndef _Lotus_SharedPtr_H__
#define _Lotus_SharedPtr_H__

#include "Prerequisites.h"

namespace Lotus2d {
	enum SharedPtrFreeMethod
	{
		/// Use LOTUS_DELETE to free the memory
		SPFM_DELETE,
		/// Use LOTUS_DELETE_T to free (only MEMCATEGORY_GENERAL supported)
		SPFM_DELETE_T,
		/// Use LOTUS_FREE to free (only MEMCATEGORY_GENERAL supported)
		SPFM_FREE
	};

	template<class T> class SharedPtr
	{
	protected:
		T* pRep;
		unsigned int* pUseCount;	// ���еļ���Ҳ��ָ��ͬһ���ַ���޸�֮��ȫ�����ű仯
		SharedPtrFreeMethod useFreeMethod; // if we should use OGRE_FREE instead of OGRE_DELETE
	public:
		/** Constructor, does not initialise the SharedPtr.
			@remarks
				<b>Dangerous!</b> You have to call bind() before using the SharedPtr.
		*/
		SharedPtr() : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
        {
      
        }

		/** Constructor.
		@param rep The pointer to take ownership of
		@param freeMode The mechanism to use to free the pointer
		*/
        template< class T>
		explicit SharedPtr(T* rep, SharedPtrFreeMethod inFreeMethod = SPFM_DELETE) 
			: pRep(rep)
			, pUseCount(0)
			, useFreeMethod(inFreeMethod)
		{
			pUseCount= LOTUS2D_NEW (unsigned int ) ;
			*(pUseCount) = 1;
            //OGRE_SET_AUTO_SHARED_MUTEX_NULL
			//if (rep)
			//{
			//	OGRE_NEW_AUTO_SHARED_MUTEX
			//}
		}
		SharedPtr(const SharedPtr& r)
            : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
		{
			// lock & copy other mutex pointer
            
            //OGRE_SET_AUTO_SHARED_MUTEX_NULL
            //OGRE_MUTEX_CONDITIONAL(r.OGRE_AUTO_MUTEX_NAME)
            {
			   // OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
			    //OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
			    pRep = r.pRep;
			    pUseCount = r.pUseCount; 
				useFreeMethod = r.useFreeMethod;
			    // Handle zero pointer gracefully to manage STL containers
			    if(pUseCount)
			    {
				    ++(*pUseCount); 
			    }
            }
		}
		SharedPtr& operator=(const SharedPtr& r) {
			if (pRep == r.pRep)
				return *this;
			// Swap current data into a local copy
			// this ensures we deal with rhs and this being dependent
			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}
		
		template< class T>
		SharedPtr(const SharedPtr<T>& r)
            : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
		{
			// lock & copy other mutex pointer

            //OGRE_SET_AUTO_SHARED_MUTEX_NULL
            //OGRE_MUTEX_CONDITIONAL(r.OGRE_AUTO_MUTEX_NAME)
            {
			   // OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
			   // OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
			    pRep = r.getPointer();
			    pUseCount = r.useCountPointer();
				useFreeMethod = r.freeMethod();
			    // Handle zero pointer gracefully to manage STL containers
			    if(pUseCount)
			    {
				    ++(*pUseCount);
			    }
            }
		}
		template< class T>
		SharedPtr& operator=(const SharedPtr<T>& r) {
			if (pRep == r.getPointer())
				return *this;
			// Swap current data into a local copy
			// this ensures we deal with rhs and this being dependent
			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}
		virtual ~SharedPtr() {
            release();
		}


		inline T& operator*() const { assert(pRep); return *pRep; }
		inline T* operator->() const { assert(pRep); return pRep; }
		inline T* get() const { return pRep; }

		/** Binds rep to the SharedPtr.
			@remarks
				Assumes that the SharedPtr is uninitialised!
		*/
		void bind(T* rep, SharedPtrFreeMethod inFreeMethod = SPFM_DELETE) {
			assert(!pRep && !pUseCount);
           // OGRE_NEW_AUTO_SHARED_MUTEX
			//OGRE_LOCK_AUTO_SHARED_MUTEX
			pUseCount = 1;// TODO: OGRE_NEW_T(unsigned int, MEMCATEGORY_GENERAL)(1);
			pRep = rep;
			useFreeMethod = inFreeMethod;
		}

		inline bool unique() const { 
			//OGRE_LOCK_AUTO_SHARED_MUTEX 
			assert(pUseCount); 
			return *pUseCount == 1; 
		}
		inline unsigned int useCount() const { 
			//OGRE_LOCK_AUTO_SHARED_MUTEX 
			assert(pUseCount); 
			return *pUseCount; 
		}
		inline unsigned int* useCountPointer() const {
			return pUseCount; 
		}

		inline T* getPointer() const { 
			return pRep; 
		}

		inline SharedPtrFreeMethod freeMethod() const { 
			return useFreeMethod; 
		}

		inline bool isNull(void) const { 
			return pRep == 0; 
		}

        inline void setNull(void) { 
			if (pRep)
			{
				// can't scope lock mutex before release in case deleted
				release();
				pRep = 0;
				pUseCount = 0;
			}
        }

    protected:

        inline void release(void)
        {
			bool destroyThis = false;

            /* If the mutex is not initialized to a non-zero value, then
               neither is pUseCount nor pRep.
             */

          //  OGRE_MUTEX_CONDITIONAL(OGRE_AUTO_MUTEX_NAME)
			{
				// lock own mutex in limited scope (must unlock before destroy)
				//OGRE_LOCK_AUTO_SHARED_MUTEX
				if (pUseCount)
				{
					if (--(*pUseCount) == 0) 
					{
						destroyThis = true;
	                }
				}
            }
			if (destroyThis)
				destroy();

            //OGRE_SET_AUTO_SHARED_MUTEX_NULL
        }

        virtual void destroy(void)
        {
            // IF YOU GET A CRASH HERE, YOU FORGOT TO FREE UP POINTERS
            // BEFORE SHUTTING OGRE DOWN
            // Use setNull() before shutdown or make sure your pointer goes
            // out of scope before OGRE shuts down to avoid this.
			switch(useFreeMethod)
			{
			case SPFM_DELETE:
				LOTUS2D_DELETE pRep;
				break;
			case SPFM_DELETE_T:
				//OGRE_DELETE_T(pRep, T, MEMCATEGORY_GENERAL);
				break;
			case SPFM_FREE:
				//OGRE_FREE(pRep, MEMCATEGORY_GENERAL);
				break;
			};
			// use OGRE_FREE instead of OGRE_DELETE_T since 'unsigned int' isn't a destructor
			// we only used OGRE_NEW_T to be able to use constructor
           LOTUS2D_DELETE pUseCount; //, MEMCATEGORY_GENERAL);
			//OGRE_DELETE_AUTO_SHARED_MUTEX
        }

		virtual void swap(SharedPtr<T> &other) 
		{
			std::swap(pRep, other.pRep);
			std::swap(pUseCount, other.pUseCount);
			std::swap(useFreeMethod, other.useFreeMethod);
//#if OGRE_THREAD_SUPPORT
//			std::swap(OGRE_AUTO_MUTEX_NAME, other.OGRE_AUTO_MUTEX_NAME);
//#endif
		}
	};	// end SharedPtr

	template<class T, class U> inline bool operator==(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return a.get() == b.get();
	}

	template<class T, class U> inline bool operator!=(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return a.get() != b.get();
	}

	template<class T, class U> inline bool operator<(SharedPtr<T> const& a, SharedPtr<U> const& b)
	{
		return std::less<const void*>()(a.get(), b.get());
	}
} 

#endif