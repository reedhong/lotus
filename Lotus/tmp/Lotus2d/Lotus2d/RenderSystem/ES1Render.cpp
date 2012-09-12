/********************************************************************
	created:	2012/09/11
	filename: 	ES1Render.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "GLES/gl.h"
#include "ES1Render.h"
#include "Base/Macros.h"

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
		glMatrixMode        (GL_MODELVIEW);
		glLoadIdentity      ();

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

		resetVertexArrayStatus();

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

	void ES1Render::clearScreen(int argb)
	{
		glClearColor(GL_COLOR_RED_FLOAT(argb), GL_COLOR_GREEN_FLOAT(argb), GL_COLOR_BLUE_FLOAT(argb), GL_COLOR_ALPHA_FLOAT(argb));
		glClear( GL_COLOR_BUFFER_BIT );
	}


	void ES1Render::setColor(int argb)
	{
		glColor4f(GL_COLOR_RED_FLOAT(argb), GL_COLOR_GREEN_FLOAT(argb), GL_COLOR_BLUE_FLOAT(argb), GL_COLOR_ALPHA_FLOAT(argb));
		mColor = argb;
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
		glEnableClientState(GL_VERTEX_ARRAY);
	}

	void ES1Render::enableColorArray(void)
	{
		glEnableClientState(GL_COLOR_ARRAY);
	}

	void ES1Render::enableTexCoordArray(void)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void ES1Render::disableVertexArray(void)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void ES1Render::disableColorArray(void)
	{
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void ES1Render::disableTexCoordArray(void)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void ES1Render::setVertexPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glVertexPointer(components, returnGLType(type), 0, pointer);
	}
	void ES1Render::setColorPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glColorPointer(components, returnGLType(type), 0, pointer);
	}

	void ES1Render::setTexCoordPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glTexCoordPointer(components, returnGLType(type), 0, pointer);
	}

	void ES1Render::resetVertexArrayStatus()
	{
		glVertexPointer( 3, GL_FLOAT, sizeof( mVertexArray[0] ), mVertexArray );
		glEnableClientState( GL_VERTEX_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, sizeof( mTexcoordArray[0] ), mTexcoordArray );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( mColorArray[0] ), mColorArray );
	}
	// draw
	void ES1Render::begin(PRIMITIVE_TYPES type)
	{
		if(mVertexIndex)
			end();
		mVertexIndex = 0;
		mPrimitiveType = type;
	}

	void ES1Render::vertex3f( float x, float y, float z )
	{

	}

	void ES1Render::vertex2f( float x, float y )
	{

	}

	void ES1Render::vertex2i( int x, int y )
	{

	}

	void ES1Render::texCoord2i( int s, int t )
	{

	}

	void ES1Render::texCoord2f(float s, float t )
	{

	}

	void ES1Render::color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	{

	}

	void ES1Render::color4ubv( unsigned char *rgba )
	{

	}

	void ES1Render::color3f( float r, float g, float b )
	{

	}

	void ES1Render::color4f( float r, float g, float b, float a )
	{

	}

	void ES1Render::end()
	{
		// 如果用到VBO技术就需要打开此处
		//resetVertexArrayStatus();
		if(mVertexIndex>0)
		{
			if ( mPrimitiveType == ePRIMITIVE_QUARD ) {
					glDrawElements( GL_TRIANGLES, mVertexIndex / 4 * 6, GL_UNSIGNED_SHORT, mQuadIndexes );
			} else {
				glDrawArrays( returnPrimitiveType(mPrimitiveType), 0,  mVertexIndex);
			}
		}
		mVertexIndex = 0;
		mPrimitiveType = ePRIMITIVE_QUARD;//默认GL_QUADS
#ifdef DEBUG	
		checkError("end");
#endif	
	}

	void ES1Render::drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) 
	{
		glDrawArrays(returnPrimitiveType(type), begin, size);
	}
	void ES1Render::drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices)
	{
		glDrawElements(returnPrimitiveType(type), size, returnGLType(indicesType), indices);
	}

	// masks
	void ES1Render::setColorMask(bool r, bool g, bool b, bool a)
	{
		glColorMask(r, g, b, a);
	}

	// alpha
	void ES1Render::setAlphaTest(float value)
	{
		if(value > 0.0f)
			glEnable(GL_ALPHA_TEST);
		else {
			glDisable(GL_ALPHA_TEST);
		}

		glAlphaFunc(GL_GREATER, value);
	}


	// matrix
	void ES1Render::loadIdentity(void) 
	{
		glLoadIdentity();
	}
	void ES1Render::setMatrixMode(MATRIX_MODES mode) 
	{
		switch(mode)
		{
		case eMATRIX_MODELVIEW:
			glMatrixMode(GL_MODELVIEW);
			return;

		case eMATRIX_PROJECTION:
			glMatrixMode(GL_PROJECTION);
			return;

		case eMATRIX_TEXTURE:
			glMatrixMode(GL_TEXTURE);
			return;
		}
	}
	void ES1Render::pushMatrix(void) 
	{
		glPushMatrix();
	}
	void ES1Render::popMatrix(void) 
	{
		glPopMatrix();
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

	void ES1Render::checkError(const char* message)
	{
		GLint err = glGetError();
		if ( err != GL_NO_ERROR ) {
			// TODO:
			//LOGD( "GL ERROR %d from %s\n", err, message );
		}
	}
}