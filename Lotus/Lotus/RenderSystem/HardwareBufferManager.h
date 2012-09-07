/********************************************************************
	created:	2012/09/05 
	filename: 	HardwareBufferManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_HardwareBufferManager_H__
#define __Lotus_HardwareBufferManager_H__

namespace Lotus {
	class HardwareBufferManager: public Singleton<HardwareBufferManager>
	{
	public:
		HardwareBufferManager();
		~HardwareBufferManager();
	};
}

#endif
