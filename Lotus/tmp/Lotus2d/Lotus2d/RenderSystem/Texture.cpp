/********************************************************************
	created:	2012/09/14
	filename: 	Texture.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Texture.h"
#include "Png/Png.h"
#include "GLHeader.h"
#include "Base/FileStream.h"

namespace Lotus2d {
	Texture::Texture():mTextureId(UNDIFINED), mKeepRawData(FALSE),mImageData(0)
	{

	}

	Texture::~Texture()
	{

	}
	BOOL Texture::isRendable() const
	{
		return (mTextureId!=UNDIFINED) || (mTextureId==UNDIFINED && mImageData) ;
	}

	Texture* Texture::loadTexture(const char* path)
	{
		FileStream stream(path, "rb");
		return loadTexture(&stream);
	}

	Texture* Texture::loadTexture(Stream* stream)
	{
		GLuint texId = 0;
		Png* png = Png::loadPng(stream);
		if (NULL == png){
			SAFE_DELETE(png);
			return NULL;
		}
		// TODO:
		Texture* texture = new Texture();

		texture->mKeepRawData = 0;
		texture->mImageWidth = png->m_width;
		texture->mImageHeight = png->m_height;
		texture->mTextureWidth = png->m_width;
		texture->mTextureHeight = png->m_height;

		// 此处channel上还可以做文章

		// TODO:
		texture->mImageData = (uint8*)malloc((size_t)4 * texture->mImageWidth * texture->mImageHeight);
		memcpy(texture->mImageData,png->m_pixelData,(size_t)4 * texture->mImageWidth * texture->mImageHeight);

		texture->mTextureId = UNDIFINED;

		switch(png->m_channel){
		case 1:
			texture->mOriginalFormat = GL_LUMINANCE;
			break;
		case 2:
			texture->mOriginalFormat = GL_LUMINANCE_ALPHA;
			break;
		case 3:
			texture->mOriginalFormat = GL_RGB;
			break;
		case 4:
			texture->mOriginalFormat = GL_RGBA;
			break;
		}
		
		// TODO
		texture->mTextureKey = 0; // CSystem::GetIntMD5(filename);

		SAFE_DELETE(png);
		return texture;
	}
}