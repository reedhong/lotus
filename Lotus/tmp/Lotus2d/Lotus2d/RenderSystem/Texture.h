/********************************************************************
	created:	2012/09/13
	filename: 	Texture.h
	author:		reedhong
	
	purpose:	²ÄÖÊ
*********************************************************************/

#ifndef __Lotus_Texture_H__
#define __Lotus_Texture_H__

#include "Base/SharedPtr.h"

namespace Lotus2d {
	class Texture
	{
	public:
		Texture(void);
		~Texture(void);
	public:
		unsigned int			m_textureId;
		float						m_imageWidth;
		float						m_imageHeight;
		float						m_textureWidth;
		float						m_textureHeight;
		unsigned char *	m_imageData;
		unsigned char		m_alphaType;
		unsigned char		m_keepRawData;
		unsigned int			m_originalFormat;
		unsigned int			m_refid;
		
		// TODO:
		int							m_textureGLobalIndex;
		unsigned int 			m_textureKey;
	};

	typedef SharedPtr<Texture> TexturePtr;
}

#endif
