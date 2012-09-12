/********************************************************************
	created:	2012/09/11
	filename: 	ES1Render.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus2d_ES1Render_H__
#define __Lotus2d_ES1Render_H__


#include "Render.h"

namespace Lotus2d {
	class ES1Render: public Render
	{
	public:
		ES1Render();
		virtual ~ES1Render();

		// view
		virtual void setOrthoView(float left, float right, float bottom, float top, float zNear, float zFar);
		virtual void setPerspectiveView(float fov, float ratio, float zNear, float zFar);

		// viewport
		virtual void setViewport(int x, int y, unsigned int width, unsigned int height);

		// clear
		virtual void clearScreen(int argb);

		// color 
		virtual void setColor(int color);

		// texture
		virtual void enableTexture(void);
		virtual void disableTexture(void);
		virtual void setTextureGenMode(TEX_GEN_MODES mode);
		virtual void setTextureFilterMode(TEX_FILTER_MODES min, TEX_FILTER_MODES mag);
		virtual void setTextureUWrapMode(WRAP_MODES wrap);
		virtual void setTextureVWrapMode(WRAP_MODES wrap);
		virtual void setTextureCombineMode(TEX_COMBINE_MODES combine);
		virtual void bindTexture(unsigned int textureId, const unsigned int multitextureId = 0);
		virtual void createTexture(unsigned int * textureId);
		virtual void deleteTexture(unsigned int * textureId);
		virtual void sendTextureImage(Image * image, bool mipMap, bool filter, bool compress) ;
		virtual void texImage(unsigned int level, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels);
		virtual void texSubImage(unsigned int level, int xoffset, int yoffset, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels);
		virtual void generateMipMap(void) ;
		virtual void getTexImage(unsigned int level, Image * image);

		//  vertex arrays
		virtual void enableVertexArray(void) ;
		virtual void enableColorArray(void);
		virtual void enableTexCoordArray(void);

		virtual void disableVertexArray(void);
		virtual void disableColorArray(void);
		virtual void disableTexCoordArray(void);

		virtual void setVertexPointer(TYPES type, unsigned int components, const void * pointer);
		virtual void setColorPointer(TYPES type, unsigned int components, const void * pointer);
		virtual void setTexCoordPointer(TYPES type, unsigned int components, const void * pointer);
		virtual void resetVertexArrayStatus();

		// draw
		virtual void begin(PRIMITIVE_TYPES type);
		virtual void vertex3f( float x, float y, float z );
		virtual void vertex2f( float x, float y );
		virtual void vertex2i( int x, int y );
		virtual void texCoord2i( int s, int t );
		virtual void texCoord2f(float s, float t );
		virtual void color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		virtual void color4ubv( unsigned char *rgba );
		virtual void color3f( float r, float g, float b );
		virtual void color4f( float r, float g, float b, float a );
		virtual void end();

		virtual void drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) ;
		virtual void drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices) ;
		virtual void drawRect(int x, int y, int w, int h, int argb);



		// masks
		virtual void setColorMask(bool r, bool g, bool b, bool a);
		// alpha
		virtual void setAlphaTest(float value);

		// matrix
		virtual void loadIdentity(void) ;
		virtual void setMatrixMode(MATRIX_MODES mode) ;
		virtual void pushMatrix(void) ;
		virtual void popMatrix(void) ;
#if 0
		virtual void multMatrix(const MMatrix4x4 * matrix) = 0;
		virtual void translate(const MVector3 & position) = 0;
		virtual void rotate(const MVector3 & axis, float angle) = 0;
		virtual void scale(const MVector3 & scale) = 0;
		virtual void getViewport(int * viewport) = 0;
		virtual void getModelViewMatrix(MMatrix4x4 * matrix) = 0;
		virtual void getProjectionMatrix(MMatrix4x4 * matrix) = 0;
		virtual void getTextureMatrix(MMatrix4x4 * matrix) = 0;
#endif

		// blending
		virtual void enableBlending(void) ;
		virtual void disableBlending(void) ;
		virtual void setBlendingMode(BLENDING_MODES mode) ;

		virtual void test(void);

		// checkError
		virtual void checkError(const char* message);
	};
}

#endif 
