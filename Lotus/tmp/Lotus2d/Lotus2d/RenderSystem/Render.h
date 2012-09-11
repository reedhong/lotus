/********************************************************************
	created:	2012/09/11
	filename: 	Render.h
	author:		reedhong
	
	purpose:	Render 渲染器, 部分从Maratis裁减过来
*********************************************************************/

#ifndef __Lotus2d_Render_H__
#define __Lotus2d_Render_H__

#include "Image.h"

namespace Lotus2d{
	// blending modes
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
		ePRIMITIVE_TRIANGLE_FAN
	};

	// buffer types
	enum BUFFER_TYPES
	{
		eBUFFER_COLOR = 2,
		eBUFFER_DEPTH = 4,
		eBUFFER_STENCIL = 8
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
	public:
		Render(){};
		virtual ~Render(){};
	public:
		// view
		virtual void setOrthoView(float left, float right, float bottom, float top, float zNear, float zFar) = 0;
		virtual void setPerspectiveView(float fov, float ratio, float zNear, float zFar) = 0;

		// viewport
		virtual void setViewport(int x, int y, unsigned int width, unsigned int height) = 0;

		// clear
		virtual void clear(int buffer) = 0;
		virtual void setClearColor(const unsigned int & color) = 0;

		// texture
		virtual void enableTexture(void) = 0;
		virtual void disableTexture(void) = 0;
		virtual void setTextureGenMode(TEX_GEN_MODES mode) = 0;
		virtual void setTextureFilterMode(TEX_FILTER_MODES min, TEX_FILTER_MODES mag) = 0;
		virtual void setTextureUWrapMode(WRAP_MODES wrap) = 0;
		virtual void setTextureVWrapMode(WRAP_MODES wrap) = 0;
		virtual void setTextureCombineMode(TEX_COMBINE_MODES combine) = 0;
		virtual void bindTexture(unsigned int textureId, const unsigned int multitextureId = 0) = 0;
		virtual void createTexture(unsigned int * textureId) = 0;
		virtual void deleteTexture(unsigned int * textureId) = 0;
		virtual void sendTextureImage(Image * image, bool mipMap, bool filter, bool compress) = 0;
		virtual void texImage(unsigned int level, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels) = 0;
		virtual void texSubImage(unsigned int level, int xoffset, int yoffset, unsigned int width, unsigned int height, TYPES type, TEX_MODES mode, const void * pixels) = 0;
		virtual void generateMipMap(void) = 0;
		virtual void getTexImage(unsigned int level, Image * image){}


		// arrays
		virtual void enableVertexArray(void) = 0;
		virtual void enableColorArray(void) = 0;
		virtual void enableNormalArray(void) = 0;
		virtual void enableTexCoordArray(void) = 0;
		virtual void enableAttribArray(unsigned int location) = 0;
		virtual void disableVertexArray(void) = 0;
		virtual void disableColorArray(void) = 0;
		virtual void disableNormalArray(void) = 0;
		virtual void disableTexCoordArray(void) = 0;
		virtual void disableAttribArray(unsigned int location) = 0;
		virtual void setVertexPointer(TYPES type, unsigned int components, const void * pointer) = 0;
		virtual void setColorPointer(TYPES type, unsigned int components, const void * pointer) = 0;
		virtual void setNormalPointer(TYPES type, const void * pointer) = 0;
		virtual void setTexCoordPointer(TYPES type, unsigned int components, const void * pointer) = 0;
		virtual void setAttribPointer(unsigned int location, TYPES type, unsigned int components, const void * pointer, const bool normalized = false) = 0;

		// draw
		virtual void drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) = 0;
		virtual void drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices) = 0;

		// lines
		virtual void enableLineAntialiasing(void) = 0;
		virtual void disableLineAntialiasing(void) = 0;




		// color
		//virtual void setColor(const MColor & color) = 0;
		//virtual void setColor3(const MVector3 & color) = 0;
		//virtual void setColor4(const MVector4 & color) = 0;

		// masks
		virtual void setColorMask(bool r, bool g, bool b, bool a) = 0;
		virtual void setDepthMask(bool depth) = 0;

		// alpha
		virtual void setAlphaTest(float value) = 0;

		// depth
		virtual void enableDepthTest(void) = 0;
		virtual void disableDepthTest(void) = 0;
		virtual void setDepthMode(DEPTH_MODES mode) = 0;

		// stencil
		virtual void enableStencilTest(void) = 0;
		virtual void disableStencilTest(void) = 0;
		//virtual void setStencilFunc(STENCIL_FUNCS func, int ref=0){};
		//virtual void setStencilOp(STENCIL_OPS op){};

		// cull face
		virtual void enableCullFace(void) = 0;
		virtual void disableCullFace(void) = 0;
		virtual void setCullMode(CULL_MODES mode) = 0;



		// matrix
		virtual void loadIdentity(void) = 0;
		virtual void setMatrixMode(MATRIX_MODES mode) = 0;
		virtual void pushMatrix(void) = 0;
		virtual void popMatrix(void) = 0;
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
		virtual void enableBlending(void) = 0;
		virtual void disableBlending(void) = 0;
		virtual void setBlendingMode(BLENDING_MODES mode) = 0;

		//test
		virtual void test(void) = 0;

	};

}

#endif
