/********************************************************************
	created:	2012/08/09 
	filename: 	RenderSystem.h
	author:		reedhong 
	
	purpose:	RenderSystem
*********************************************************************/

#ifndef __Lotus_RenderSystem_H__
#define __Lotus_RenderSystem_H__

#include "Main/Prerequisites.h"
#include "Math/Matrix.h"
#include "ResourceManage/TextureManager.h"
#include "RenderSupport.h"
//#include "RenderContext.h"
#include "RenderCapabilities.h"
#include "Main/Color.h"
#include "Viewport.h"
#include "Camera.h"


namespace Lotus {
	class RenderSystem
	{
	protected:
		// Texture manager
		// A concrete class of this will be created and
		// made available under the TextureManager singleton,
		// managed by the RenderSystem
		TextureManager* mTextureManager;
	
		// for stats
		size_t mBatchCount;
		size_t mFaceCount;
		size_t mVertexCount;
		
		// system attribute
		RenderCapabilities*	mCapabilities;
		RenderSupport*						mSupport;
		//RenderContext*						mContext;

		// matrix
		Matrix4	mVeiwMatrix;
		Matrix4	mWorldMatrix;
		Matrix4	mTextureMatrix;

		// view port:
		Viewport	mViewport;
		Camera		mCamera;
	public:
		RenderSystem();
		virtual ~RenderSystem();
		virtual const String& getName(void) const = 0;
		virtual  void test(void ) const  = 0;
		virtual void drawCoordinateSystem(int tileSize=10) =0;
		/*
		 * set material
		 */
#if 0
		void _setSurfaceParams(const Color &ambient,
			const Color &diffuse, const Color &specular,
			const Color &emissive, Real shininess,
			TrackVertexColourType tracking);
#endif

		virtual void clearFrameBuffer(unsigned int bufferMask, 
			const Color& color = Color::Black, 
			float depth = 1.0f, unsigned short stencil = 0) = 0;
	};
}


#endif