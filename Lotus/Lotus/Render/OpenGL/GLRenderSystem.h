/********************************************************************
	created:	2012/08/11
	filename: 	GLRenderSystem.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_GLRenderSystem_H__
#define __Lotus_GLRenderSystem_H__

#include "Main/Prerequisites.h"
#include "Render/RenderSystem.h"

namespace Lotus {
	class GLRenderSystem: public RenderSystem
	{
	public:
		GLRenderSystem();
		~GLRenderSystem();

		virtual const String& getName(void) const;
		virtual void clearFrameBuffer(unsigned int bufferMask, 
			const Color& color = Color::Black, 
			Real depth = 1.0f, unsigned short stencil = 0);

		virtual void test(void ) const;
		virtual void drawCoordinateSystem(int tileSize=5);
	};
}

#endif

