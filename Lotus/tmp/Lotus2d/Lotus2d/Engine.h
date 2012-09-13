/********************************************************************
	created:	2012/09/11
	filename: 	Lotus2d.h
	author:		reedhong
	
	purpose:	�����������
*********************************************************************/

#ifndef __Lotus2d_H__
#define __Lotus2d_H__

#include "Base/Macros.h"
#include "Base/Types.h"
#include "Platform/Platform.h"

#include "RenderSystem/Render.h"

namespace Lotus2d{
	// ���������
	class Engine {
	private:
		Engine();
	public:
		~Engine();

		// instance
		static Engine * Instance(void);
	};
}


#endif