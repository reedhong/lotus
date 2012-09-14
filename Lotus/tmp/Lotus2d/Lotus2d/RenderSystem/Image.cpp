/********************************************************************
	created:	2012/09/11
	filename: 	Image.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Base/Macros.h"
#include "Image.h"


namespace Lotus2d{
	Image::Image()
	{

	}

	Image::~Image()
	{
	}
	//////////////////////////////////////////////////////////////////////

	Image* Image::createImage(Texture* texturePtr, float x, float y, float w, float h, bool flipY)
	{
		Image* image = LOTUS2D_NEW Image();
		image->mTexturePtr = texturePtr;
		image->setTextureRect(x, y, w, h,flipY);
		return image;	 
	}


	void Image::setTextureRect(float x, float y, float w, float h, bool flipY) 
	{ 
		m_x = x;
		m_y = y;
		m_width = w;
		m_height = h;

		m_tx0 = x/mTexturePtr->m_textureWidth;
		m_tx1 = (x+w)/mTexturePtr->m_textureWidth;

		if(flipY){
			m_ty0 = 1.0f-y/mTexturePtr->m_textureHeight;
			m_ty1 = 1.0f-(y+h)/mTexturePtr->m_textureHeight;
		}else{
			this->m_ty0 = y/mTexturePtr->m_textureHeight;
			this->m_ty1 = (y+h)/mTexturePtr->m_textureHeight;
		}
	}
}