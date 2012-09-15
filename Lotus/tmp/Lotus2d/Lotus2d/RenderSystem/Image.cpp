/********************************************************************
	created:	2012/09/11
	filename: 	Image.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Base/Macros.h"
#include "Image.h"


namespace Lotus2d{
	Image::Image():mTexture(NULL)
	{

	}

	Image::~Image()
	{
	}

	BOOL Image::isRendable() const
	{
		return (mTexture) && (mTexture->isRendable());
	}
	//////////////////////////////////////////////////////////////////////

	Image* Image::createImage(Texture* texturePtr, int  x, int  y, int  w,  int  h, BOOL flipY)
	{
		Image* image = new Image();
		image->mTexture = texturePtr;
		image->setTextureRect(x, y, w, h,flipY);
		return image;	 
	}


	void Image::setTextureRect(int  x, int  y, int  w,  int  h, BOOL flipY)
	{ 
		m_x = (float)x;
		m_y = (float)y;
		m_width = (float)w;
		m_height = (float)h;

		m_tx0 = m_x/mTexture->mTextureWidth;
		m_tx1 = (m_x+m_width)/mTexture->mTextureWidth;

		if(flipY){
			m_ty0 = 1.0f-m_y/mTexture->mTextureHeight;
			m_ty1 = 1.0f-(m_y+m_height)/mTexture->mTextureHeight;
		}else{
			this->m_ty0 = m_y/mTexture->mTextureHeight;
			this->m_ty1 = (m_y+m_height)/mTexture->mTextureHeight;
		}
	}
}