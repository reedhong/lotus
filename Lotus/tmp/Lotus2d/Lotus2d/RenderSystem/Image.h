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
	protected:
		Image(void);
	public:
		~Image(void);

	public:
		static Image* createImage(TexturePtr texturePtr, float x, float y, float w, float h,bool flipY = false);

	public:
		void setTextureRect(float x, float y, float w, float h,bool flipY = false) ;
	public:
		TexturePtr	mTexturePtr;	

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
