/********************************************************************
	created:	2012/08/29 
	filename: 	Pool.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef  __Lotus_Pool_H__
#define __Lotus_Pool_H__

#include "Prerequisites.h"

namespace Lotus {
	/** Template class describing a simple pool of items.
	*/
	template <typename T>
	class Pool
	{
	protected:
		typedef typename list<T>::type ItemList;
		ItemList mItems;
		//OGRE_AUTO_MUTEX
	public:
		Pool() {} 
		virtual ~Pool() {}

		/** Get the next item from the pool.
		@return pair indicating whether there was a free item, and the item if so
		*/
		virtual std::pair<bool, T> removeItem()
		{
			//OGRE_LOCK_AUTO_MUTEX
			std::pair<bool, T> ret;
			if (mItems.empty())
			{
				ret.first = false;
			}
			else
			{
				ret.first = true;
				ret.second = mItems.front();
				mItems.pop_front();
			}
			return ret;
		}

		/** Add a new item to the pool. 
		*/
		virtual void addItem(const T& i)
		{
			//OGRE_LOCK_AUTO_MUTEX
			mItems.push_front(i);
		}
		/// Clear the pool
		virtual void clear()
		{
			//OGRE_LOCK_AUTO_MUTEX
			mItems.clear();
		}



	};

}

#endif
