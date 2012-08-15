/********************************************************************
	created:	2012/08/11
	filename: 	GLRenderSystem.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "GLRenderSystem.h"
#include "Log/LoggerManager.h"
#include "GL/glew.h"
#include  "GL/glut.h"
#include "GLCommon.h"
#include "Render/RenderCommon.h"

namespace Lotus {
	GLRenderSystem::GLRenderSystem()
	{
		// ³õÊ¼»¯

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

	void GLRenderSystem::test() const
	{
	
	}

	void GLRenderSystem::drawCoordinateSystem(int tileSize)
	{

		glDisable( GL_TEXTURE_2D );
		glColor4f(1.0, 0,0,1);
		glBegin(GL_LINES); // x : R

		glVertex3i(-10000,0,0);
		glVertex3i(10000,0,0);
		glEnd();
		glColor4f(0,1.0,0,1);
		glBegin(GL_LINES); // y : G
		glVertex3i(0,100000,0);
		glVertex3i(0,-10000,0);
		glEnd();
		glColor4f(0,0,1,1);
		glBegin(GL_LINES); // z: B
		glVertex3i(0,0,-10000);
		glVertex3i(0,0,100000);
		glEnd();
#if 0
		GLColor(0xFF000000);
		//glLineWidth(5);
		glBegin(GL_LINES); // point
		glVertex3i(m_camera.x,m_camera.y,m_camera.z);
		glVertex3i((int)m_pointX, (int)m_pointY, (int)m_pointZ);
		glEnd();
		GLColor(0xFFFFFF00);
		glBegin(GL_LINES); // camera
		//gluLookAt(m_camera.x,  m_camera.y, m_camera.z,m_camera.x,  m_camera.y, 0, 0,1,0);
		glVertex3i(m_camera.x,m_camera.y,m_camera.z);
		glVertex3i(m_camera.x,m_camera.y, 100);
		glEnd();
#endif
#if 1
		glColor4f(1,1,1,1); // »ÒÉ«
		//glPushMatrix();
		//int MAX_LEN = 5120;
		for(int i = -1000; i <= 1000; i += tileSize)
		{
			if( i ==0) continue;
			glBegin(GL_LINES);				
			glVertex3f(-1000, i, 0);					
			glVertex3f(1000, i, 0);
			glVertex3f(i, -1000,0);							
			glVertex3f(i, 1000,0);
			glEnd();
		}
		//glPopMatrix();
#endif
		glEnable( GL_TEXTURE_2D );	
	}
}  // end Lotus