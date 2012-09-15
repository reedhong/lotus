/********************************************************************
	created:	2012/09/11
	filename: 	Image.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus2d_Image_H__
#define __Lotus2d_Image_H__

#include "Texture.h"

namespace Lotus2d {
	class Image
	{
	public:
		Image();
		~Image();
		BOOL isRendable() const;
	public:
		static Image* createImage(Texture* texturePtr, int  x, int  y, int  w,  int  h, BOOL flipY=FALSE);

	public:
		void setTextureRect(int  x, int  y, int  w,  int  h, BOOL flipY=FALSE);
	public:
		Texture*	mTexture;	

		float m_tx0;
		float m_ty0;
		float m_tx1;
		float m_ty1;

		float m_x;
		float m_y;
		float m_width;
		float m_height;

	};
}

#endif
