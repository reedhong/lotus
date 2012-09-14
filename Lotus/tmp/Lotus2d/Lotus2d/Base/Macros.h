/********************************************************************
	created:	2012/09/11
	filename: 	Macros.h
	author:		reedhong
	
	purpose:	公共宏
*********************************************************************/

#ifndef __Lotus_Macro_H__
#define __Lotus_Macro_H__
#include <assert.h>
#include "Platform/Platform.h"

namespace Lotus2d
{

#ifdef LOTUS2D_DEBUG_MODE
#define ASSERT(c) if (c) 0; else assert(c)
#else
#define ASSERT(c) 0
#endif

	/** Anchor mode **/
#define ANCHOR_NONE				0x00
#define ANCHOR_HCENTER			0x01
#define ANCHOR_VCENTER			0x02
#define ANCHOR_LEFT				0x04
#define ANCHOR_RIGHT			0x08
#define ANCHOR_TOP				0x10
#define ANCHOR_BOTTOM			0x20
#define ANCHOR_CENTER			ANCHOR_HCENTER | ANCHOR_VCENTER

	/** Transform mode **/
#define TRANS_NONE				0x00
#define TRANS_MIRROR			0x02
#define TRANS_ROT180			0x03
#define TRANS_ROT90				0x05
#define TRANS_ROT270			0x06

#define TRANS_MIRROR_ROT180		0x01
#define TRANS_MIRROR_ROT270		0x04
#define TRANS_MIRROR_ROT90		0x07

	/** Math operation **/
#define	MAX(a, b)	((a) > (b)) ? (a) : (b)
#define MIN(a, b)	((a) < (b)) ? (a) : (b)
#define ABS(a)		((a) > 0) ? (a) : (-(a))

	/** Pixel operation **/
#ifndef ARGB
#define ARGB(a, r, g, b)		((a << 24) | (r << 16) | (g << 8) | b)
#endif 

#ifndef RGBA
#define RGBA(r, g, b, a)		((a << 24) | (b << 16) | (g << 8) | r)
#endif

#define RGBA4444(r, g, b, a)		((a << 24) | (b << 16) | (g << 8) | r)
	// 2 Versions.
	//#define RGB888_TO_RGB565(rgb)	  ((((rgb) & 0xF80000)>>8) | (((rgb) & 0xFC00)>>5) | (((rgb) & 0xF8)>>3))
#define RGB888_TO_RGB565(color) ((((color) >> 16 & 0xff & 0xf8) >> 3 | ((color) >> 8 & 0xff & 0xfc) << 3 | ((color) & 0xf8) << 8))
#define RGB565_TO_RGB888(_value)	  (((((_value) & 0x1f) * 255) / 31) << 16) | (((((_value >> 5) & 0x3f) * 255) / 63) << 8) | ((((_value >> 11) & 0x1f) * 255) / 31)

	/** Parse int to float color component */
#define GL_COLOR_ALPHA_FLOAT(color)	  (((color) >> 24) & 0xFF) / 255.0f
#define GL_COLOR_RED_FLOAT(color)		  (((color) >> 16) & 0xFF) / 255.0f
#define GL_COLOR_GREEN_FLOAT(color)	  (((color) >> 8) & 0xFF) / 255.0f
#define GL_COLOR_BLUE_FLOAT(color)	  ((color) & 0xFF) / 255.0f
	/** Parse int to byte color component */
#define GL_COLOR_ALPHA_BYTE(color)	  (((color) >> 24) & 0xFF)
#define GL_COLOR_RED_BYTE(color)	  (((color) >> 16) & 0xFF)
#define GL_COLOR_GREEN_BYTE(color)	  (((color) >> 8) & 0xFF)
#define GL_COLOR_BLUE_BYTE(color)	  ((color) & 0xFF)

#define GL_COLOR_RED 0xFFFF0000
#define GL_COLOR_GREEN 0xFF00FF00
#define GL_COLOR_BLUE 0xFF0000FF
#define GL_COLOR_BLACK 0xFF000000
#define GL_COLOR_WHITE 0xFFFFFFFF


#define LOTUS2D_NEW	new
#define LOTUS2D_DELETE	delete

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)     if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
	//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)     if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
	//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x)     if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
	//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)     if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif



}

#endif