/********************************************************************
	created:	2012/09/13
	filename: 	Texture.h
	author:		reedhong
	
	purpose:	材质
*********************************************************************/

#ifndef __Lotus_Texture_H__
#define __Lotus_Texture_H__

#include "Base/Stream.h"

namespace Lotus2d {
	class Texture
	{
	protected:
		Texture();
	public:
		static Texture* loadTexture(const char* path);
		static Texture* loadTexture(Stream* stream);
		~Texture();
		BOOL isRendable() const;
		BOOL hasBind() const{ return mTextureId != UNDIFINED;} 
		BOOL keepRawData() const{ return mKeepRawData;}
		void setKeepRawData(BOOL b) { mKeepRawData = b;}

	public:
		unsigned int			mTextureId;
		unsigned int 			mImageWidth;
		unsigned int			mImageHeight;
		unsigned int			mTextureWidth;
		unsigned int			mTextureHeight;
		unsigned char *	mImageData;
		unsigned char		mAlphaType;
		unsigned char		mKeepRawData;
		unsigned int			mOriginalFormat;

		unsigned int 			mTextureKey;		// 根据路径生成的hash值
		int32						mTextureGLobalIndex;
	};
}

#endif
