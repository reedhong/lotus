/********************************************************************
	created:	2012/08/11
	filename: 	GLRenderSystem.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "GLRenderSystem.h"
#include "Log/LoggerManager.h"
#include "GL/glew.h"

namespace Lotus {
	GLRenderSystem::GLRenderSystem()
	{
		// ≥ı ºªØ

	}

	GLRenderSystem::~GLRenderSystem()
	{

	}

	const String& GLRenderSystem::getName(void) const
	{
		static String strName("OpenGL Rendering Subsystem");
		return strName;
	}

	void GLRenderSystem::clearFrameBuffer(unsigned int bufferMask, const Color& color, 
		Real depth, unsigned short stencil)
	{
		GLbitfield flags = 0;
		if (bufferMask & FBT_COLOUR)
		{
			flags |= GL_COLOR_BUFFER_BIT;
			glClearColor(color.r, color.g, color.b, color.a);
			GL_CHECK_ERROR;
		}
		if (bufferMask & FBT_DEPTH)
		{
			flags |= GL_DEPTH_BUFFER_BIT;
			// Enable buffer for writing if it isn't
#if 0
			if (!mDepthWrite)
			{
				glDepthMask(GL_TRUE);
				GL_CHECK_ERROR;
			}
#endif
			glClearDepth(depth);
			GL_CHECK_ERROR;
		}
		if (bufferMask & FBT_STENCIL)
		{
			flags |= GL_STENCIL_BUFFER_BIT;
			// Enable buffer for writing if it isn't
			glStencilMask(0xFFFFFFFF);
			GL_CHECK_ERROR;
			glClearStencil(stencil);
			GL_CHECK_ERROR;
		}
		// Clear buffers
		glClear(flags);
		GL_CHECK_ERROR;
	}
}