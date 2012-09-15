/********************************************************************
	created:	2012/09/11
	filename: 	ES1Render.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus2d_ES1Render_H__
#define __Lotus2d_ES1Render_H__

#include "Base/Config.h"
#include "Image.h"
#include "Texture.h"

namespace Lotus2d {
	enum BLENDING_MODES
	{
		eBLENDING_NONE = 0,
		eBLENDING_ALPHA,
		eBLENDING_ADD,
		eBLENDING_SUB,
		eBLENDING_LIGHT,
		eBLENDING_PRODUCT
	};

	// depth modes
	enum DEPTH_MODES
	{
		eDEPTH_NONE = 0,
		eDEPTH_ALWAYS,
		eDEPTH_LESS,
		eDEPTH_GREATER,
		eDEPTH_EQUAL,
		eDEPTH_LEQUAL,
		eDEPTH_GEQUAL,
		eDEPTH_NOTEQUAL
	};

	// matrix modes
	enum MATRIX_MODES
	{
		eMATRIX_MODELVIEW = 0,
		eMATRIX_PROJECTION,
		eMATRIX_TEXTURE,
	};

	// primitives types
	enum PRIMITIVE_TYPES
	{
		ePRIMITIVE_POINTS = 0,
		ePRIMITIVE_LINES,
		ePRIMITIVE_LINE_LOOP,
		ePRIMITIVE_LINE_STRIP,
		ePRIMITIVE_TRIANGLES,
		ePRIMITIVE_TRIANGLE_STRIP,
		ePRIMITIVE_TRIANGLE_FAN,
		ePRIMITIVE_QUARD
	};



	// texture image mode
	enum TEX_MODES
	{
		eDEPTH = 0,
		eR = 1,
		eRG = 2,
		eRGB = 3,
		eRGBA = 4
	};

	// texture gen modes
	enum TEX_GEN_MODES
	{
		eTEX_GEN_NONE = 0,
		eTEX_GEN_SPHERE_MAP,
		eTEX_GEN_CUBE_MAP
	};

	// texture combine modes
	enum TEX_COMBINE_MODES
	{
		eTEX_COMBINE_REPLACE = 0,
		eTEX_COMBINE_MODULATE,
		eTEX_COMBINE_ALPHA,
		eTEX_COMBINE_ADD,
		eTEX_COMBINE_SUB,
		eTEX_COMBINE_DOT
	};

	// texture filtering modes
	enum TEX_FILTER_MODES
	{
		eTEX_FILTER_NEAREST = 0,
		eTEX_FILTER_NEAREST_MIPMAP_NEAREST,
		eTEX_FILTER_NEAREST_MIPMAP_LINEAR,
		eTEX_FILTER_LINEAR,
		eTEX_FILTER_LINEAR_MIPMAP_NEAREST,
		eTEX_FILTER_LINEAR_MIPMAP_LINEAR,
	};

	// wrap modes
	enum WRAP_MODES
	{
		eWRAP_REPEAT = 0,
		eWRAP_CLAMP
	};

	// cull modes
	enum CULL_MODES
	{
		eCULL_NONE = 0,
		eCULL_FRONT,
		eCULL_BACK,
		eCULL_FRONT_BACK
	};

	// types
	enum TYPES
	{
		eBOOL = 0,
		eBYTE,
		eUBYTE,
		eSHORT,
		eUSHORT,
		eINT,
		eUINT,
		eFLOAT
	};
	class Render
	{
	private:
		Render();
	public:
		 ~Render();
		 // instance
		 static Render * Instance(void);
	protected:
		int	mColor;// 按照argb存储，在一个整数里面
		float mTexcoordArray[MAX_ARRAY_SIZE][2];
		char mColorArray[MAX_ARRAY_SIZE][4];
		float mVertexArray[MAX_ARRAY_SIZE][3];
		short mQuadIndexes[MAX_ARRAY_SIZE * 3 / 2 ];	// 索引数组
		PRIMITIVE_TYPES mPrimitiveType;
		int mVertexIndex;		//  当前是第几个顶点
		int mLineWidth;
		int mWidth;
		int mHeight;
		float mScale;
		int mCurrentTextureId; // 记录当前的纹理id
	public:
		// init
		void init(int width, int height, float mScale);

		int getWidth() { return mWidth;}
		int getHeight() { return mHeight;}
		float getScale() { return mScale;}

		int getLineWidth() { return mLineWidth;}
		void setLineWidth(int width) { mLineWidth = width;}
		// clear
		void clearScreen(int argb);

		// color 
		int getColor() { return mColor;}
		void setColor(int color);

		// texture
		void enableTexture(void);
		void disableTexture(void);
		/*
		 * 绑定材质，如果没有提交显卡，需要生成材质id，指定纹理数据，进行提交
		 */
		void  bindTexture(Texture* texture, BOOL  isLinearFiltering=TRUE);


		//  vertex arrays
		void enableVertexArray(void) ;
		void enableColorArray(void);
		void enableTexCoordArray(void);

		void disableVertexArray(void);
		void disableColorArray(void);
		void disableTexCoordArray(void);

		void setVertexPointer(TYPES type, unsigned int components, const void * pointer);
		void setColorPointer(TYPES type, unsigned int components, const void * pointer);
		void setTexCoordPointer(TYPES type, unsigned int components, const void * pointer);
		void resetVertexArrayStatus();

		// draw
		void begin(PRIMITIVE_TYPES type);
		void vertex3f( float x, float y, float z );
		void vertex2f( float x, float y );
		void vertex2i( int x, int y );
		void texCoord2i( int s, int t );
		void texCoord2f(float s, float t );
		void color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		void color4ubv( unsigned char *rgba );
		void color3f( float r, float g, float b );
		void color4f( float r, float g, float b, float a );
		void end();

		void drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) ;
		void drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices) ;
		void drawRect(int x, int y, int w, int h, int argb);
		void drawLine(int x1, int y1, int x2, int y2, int argb, int lineWidth=1);
		void drawImage(const Image* image, float x, float y,int transfer=TRANS_NONE,int anchor=ANCHOR_TOP|ANCHOR_LEFT);
		void drawTexture(const Texture* texture, float x, float y,int transfer=TRANS_NONE,int anchor=ANCHOR_TOP|ANCHOR_LEFT);


		// masks
		void setColorMask(bool r, bool g, bool b, bool a);
		// alpha
		void setAlphaTest(float value);

		// matrix
		void loadIdentity(void) ;
		void setMatrixMode(MATRIX_MODES mode) ;
		void pushMatrix(void) ;
		void popMatrix(void) ;
		#if 0
		void multMatrix(const MMatrix4x4 * matrix) = 0;
		void translate(const MVector3 & position) = 0;
		void rotate(const MVector3 & axis, float angle) = 0;
		void scale(const MVector3 & scale) = 0;
		void getViewport(int * viewport) = 0;
		void getModelViewMatrix(MMatrix4x4 * matrix) = 0;
		void getProjectionMatrix(MMatrix4x4 * matrix) = 0;
		void getTextureMatrix(MMatrix4x4 * matrix) = 0;
		#endif

		// blending
		void enableBlending(void) ;
		void disableBlending(void) ;
		void setBlendingMode(BLENDING_MODES mode) ;

	
		// checkError
		void checkError(const char* message);
	};
}

#endif 
