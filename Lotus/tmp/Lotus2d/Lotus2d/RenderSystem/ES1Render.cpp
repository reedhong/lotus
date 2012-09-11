/********************************************************************
	created:	2012/09/11
	filename: 	ES1Render.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "GLES/gl.h"

#include "ES1Render.h"

namespace Lotus2d {
	static GLenum returnGLType(TYPES type)
	{
		switch(type)
		{
		default:
			//	return GL_NONE;

			//case eBOOL:
			//return GL_BOOL;

		case eBYTE:
			return GL_BYTE;

		case eUBYTE:
			return GL_UNSIGNED_BYTE;

		case eSHORT:
			return GL_SHORT;

		case eUSHORT:
			return GL_UNSIGNED_SHORT;


		case eFLOAT:
			return GL_FLOAT;

			//case eDOUBLE:
			//return GL_DOUBLE;
		}
	}

	static GLenum returnPrimitiveType(PRIMITIVE_TYPES type)
	{
		switch(type)
		{
		default:
			//return GL_NONE;

		case ePRIMITIVE_LINES:
			return GL_LINES;

		case ePRIMITIVE_LINE_LOOP:
			return GL_LINE_LOOP;

		case ePRIMITIVE_LINE_STRIP:
			return GL_LINE_STRIP;

		case ePRIMITIVE_TRIANGLES:
			return GL_TRIANGLES;

		case ePRIMITIVE_TRIANGLE_STRIP:
			return GL_TRIANGLE_STRIP;
		}
	}

	static GLenum returnTexFilterMode(TEX_FILTER_MODES mode)
	{
		switch(mode)
		{
		default:
		case eTEX_FILTER_NEAREST:
			return GL_NEAREST;

		case eTEX_FILTER_NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;

		case eTEX_FILTER_NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;

		case eTEX_FILTER_LINEAR:
			return GL_LINEAR;

		case eTEX_FILTER_LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;

		case eTEX_FILTER_LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	static GLenum returnTexMode(TEX_MODES mode)
	{
		switch(mode)
		{
			//case eR:
			//	return GL_R;

			//case eRG:
			//	return GL_RG;

		default:
		case eRGB:
			return GL_RGB;

		case eRGBA:
			return GL_RGBA;

			//case eDEPTH:
			//	return GL_DEPTH_COMPONENT;
		}
	}

	ES1Render::ES1Render()
	{
		int i = 20;
		i++;

		glMatrixMode        (GL_MODELVIEW);

		i++;
		glLoadIdentity      ();

		i++;
		glEnable( GL_BLEND );
		glEnable			(GL_TEXTURE_2D);
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		//glShadeModel(GL_SMOOTH);

		glColor4f( 1,1,1,1 );

		glMatrixMode        (GL_PROJECTION);
		glLoadIdentity      ();

		glDisable				( GL_DEPTH_TEST );
		glDisable				( GL_CULL_FACE );
		glDisable				(GL_LIGHTING);
		glDisableClientState	(GL_NORMAL_ARRAY);
		glDisable				( GL_ALPHA_TEST );

		glMatrixMode        (GL_MODELVIEW);


		glOrthox(-160<<16, 160<<16, -120<<16, 120<<16, -128<<16, 128<<16);
		glMatrixMode(GL_MODELVIEW);
		glClearColorx(0x10000, 0x10000, 0, 0);
		glColor4x(0x10000, 0, 0, 0);



    /* Set projection matrix so screen extends to (-160, -120) at bottom left 
    * and to (160, 120) at top right, with -128..128 as Z buffer. */

    glMatrixMode(GL_PROJECTION);
	}


	ES1Render::~ES1Render()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	// view
	void ES1Render::setOrthoView(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		glOrthof(left, right, bottom, top, zNear, zFar);
	}

	void ES1Render::setPerspectiveView(float fov, float ratio, float zNear, float zFar)
	{

	}

	// viewport
	void ES1Render::setViewport(int x, int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	// clear
	void ES1Render::clear(int buffer)
	{
		switch(buffer)
		{
		case eBUFFER_COLOR:
			glClear(GL_COLOR_BUFFER_BIT);
			return;

		case eBUFFER_DEPTH:
			glClear(GL_DEPTH_BUFFER_BIT);
			return;

		case eBUFFER_STENCIL:
			glClear(GL_STENCIL_BUFFER_BIT);
			return;

		case eBUFFER_COLOR | eBUFFER_DEPTH:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			return;

		case eBUFFER_COLOR | eBUFFER_STENCIL:
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			return;

		case eBUFFER_COLOR |eBUFFER_DEPTH | eBUFFER_STENCIL:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			return;

		case eBUFFER_DEPTH | eBUFFER_STENCIL:
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			return;
		}
	}

	void ES1Render::setClearColor(const unsigned int & color)
	{

	}

	// texture
	void ES1Render::enableTexture(void)
	{

	}

	void ES1Render::disableTexture(void)
	{

	}

	void ES1Render::setTextureGenMode(TEX_GEN_MODES mode)
	{

	}

	void ES1Render::setTextureFilterMode(TEX_FILTER_MODES min, TEX_FILTER_MODES mag)
	{

	}

	void ES1Render::setTextureUWrapMode(WRAP_MODES wrap)
	{

	}

	void ES1Render::setTextureVWrapMode(WRAP_MODES wrap)
	{

	}

	void ES1Render::setTextureCombineMode(TEX_COMBINE_MODES combine)
	{

	}

	void ES1Render::bindTexture(unsigned int textureId, const unsigned int multitextureId)
	{

	}

	void ES1Render::createTexture(unsigned int * textureId)
	{

	}

	void ES1Render::deleteTexture(unsigned int * textureId)
	{

	}

	void ES1Render::sendTextureImage(Image * image, bool mipMap, bool filter, bool compress)
	{

	}

	void ES1Render::texImage(unsigned int level, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels)
	{

	}

	void ES1Render::texSubImage(unsigned int level, int xoffset, int yoffset, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels)
	{

	}
	void ES1Render::generateMipMap(void) 
	{

	}
	void ES1Render::getTexImage(unsigned int level, Image * image)
	{

	}


	// arrays
	void ES1Render::enableVertexArray(void) 
	{

	}

	void ES1Render::enableColorArray(void)
	{

	}

	void ES1Render::enableNormalArray(void)
	{

	}

	void ES1Render::enableTexCoordArray(void)
	{

	}
	void ES1Render::enableAttribArray(unsigned int location)
	{

	}
	void ES1Render::disableVertexArray(void)
	{

	}
	void ES1Render::disableColorArray(void)
	{

	}
	void ES1Render::disableNormalArray(void)
	{

	}
	void ES1Render::disableTexCoordArray(void)
	{

	}
	void ES1Render::disableAttribArray(unsigned int location) 
	{

	}
	void ES1Render::setVertexPointer(TYPES type, unsigned int components, const void * pointer)
	{

	}
	void ES1Render::setColorPointer(TYPES type, unsigned int components, const void * pointer)
	{

	}
	void ES1Render::setNormalPointer(TYPES type, const void * pointer)
	{

	}
	void ES1Render::setTexCoordPointer(TYPES type, unsigned int components, const void * pointer)
	{

	}
	void ES1Render::setAttribPointer(unsigned int location, TYPES type, unsigned int components, const void * pointer, const bool normalized)
	{

	}

	// draw
	void ES1Render::drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) 
	{

	}
	void ES1Render::drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices)
	{

	}

	// lines
	void ES1Render::enableLineAntialiasing(void) 
	{

	}
	void ES1Render::disableLineAntialiasing(void) 
	{

	}




	// color
	//void setColor(const MColor & color) = 0;
	//void setColor3(const MVector3 & color) = 0;
	//void setColor4(const MVector4 & color) = 0;

	// masks
	void ES1Render::setColorMask(bool r, bool g, bool b, bool a)
	{

	}
	void ES1Render::setDepthMask(bool depth) 
	{

	}

	// alpha
	void ES1Render::setAlphaTest(float value)
	{

	}

	// depth
	void ES1Render::enableDepthTest(void)
	{

	}
	void ES1Render::disableDepthTest(void)
	{

	}
	void ES1Render::setDepthMode(DEPTH_MODES mode)
	{

	}

	// stencil
	void ES1Render::enableStencilTest(void) 
	{

	}
	void ES1Render::disableStencilTest(void) 
	{

	}
	//void setStencilFunc(STENCIL_FUNCS func, int ref=0){};
	//void setStencilOp(STENCIL_OPS op){};

	// cull face
	void ES1Render::enableCullFace(void) 
	{

	}
	void ES1Render::disableCullFace(void) 
	{

	}
	void ES1Render::setCullMode(CULL_MODES mode)
	{

	}



	// matrix
	void ES1Render::loadIdentity(void) 
	{

	}
	void ES1Render::setMatrixMode(MATRIX_MODES mode) 
	{

	}
	void ES1Render::pushMatrix(void) 
	{

	}
	void ES1Render::popMatrix(void) 
	{

	}

	// blending
	void ES1Render::enableBlending(void) 
	{

	}
	void ES1Render::disableBlending(void) 
	{

	}
	void ES1Render::setBlendingMode(BLENDING_MODES mode) 
	{

	}

	void ES1Render::test(void)
	{

	}
}