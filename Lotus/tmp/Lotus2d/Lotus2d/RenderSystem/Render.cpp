/********************************************************************
	created:	2012/09/11
	filename: 	ES1Render.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Render.h"
#include "Base/Macros.h"
#include "GLHeader.h"
#include "string.h"

namespace Lotus2d {
	static GLenum returnGLType(TYPES type)
	{
		switch(type)
		{
		default:
			//	return GL_NONE;

			//case eBOOL:
			//return GL_BOOL;

		case eBYTE:
			return GL_BYTE;

		case eUBYTE:
			return GL_UNSIGNED_BYTE;

		case eSHORT:
			return GL_SHORT;

		case eUSHORT:
			return GL_UNSIGNED_SHORT;


		case eFLOAT:
			return GL_FLOAT;

			//case eDOUBLE:
			//return GL_DOUBLE;
		}
	}

	static GLenum returnPrimitiveType(PRIMITIVE_TYPES type)
	{
		switch(type)
		{
		default:
			//return GL_NONE;

		case ePRIMITIVE_LINES:
			return GL_LINES;

		case ePRIMITIVE_LINE_LOOP:
			return GL_LINE_LOOP;

		case ePRIMITIVE_LINE_STRIP:
			return GL_LINE_STRIP;

		case ePRIMITIVE_TRIANGLES:
			return GL_TRIANGLES;

		case ePRIMITIVE_TRIANGLE_STRIP:
			return GL_TRIANGLE_STRIP;
		}
	}

	static GLenum returnTexFilterMode(TEX_FILTER_MODES mode)
	{
		switch(mode)
		{
		default:
		case eTEX_FILTER_NEAREST:
			return GL_NEAREST;

		case eTEX_FILTER_NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;

		case eTEX_FILTER_NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;

		case eTEX_FILTER_LINEAR:
			return GL_LINEAR;

		case eTEX_FILTER_LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;

		case eTEX_FILTER_LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	static GLenum returnTexMode(TEX_MODES mode)
	{
		switch(mode)
		{
			//case eR:
			//	return GL_R;

			//case eRG:
			//	return GL_RG;

		default:
		case eRGB:
			return GL_RGB;

		case eRGBA:
			return GL_RGBA;

			//case eDEPTH:
			//	return GL_DEPTH_COMPONENT;
		}
	}

	Render::Render():mVertexIndex(0), mPrimitiveType(ePRIMITIVE_QUARD),mLineWidth(2)
	{
		for (int i = 0; i < MAX_ARRAY_SIZE * 3 / 2; i+=6 ) {
			int q = i / 6 * 4;
			mQuadIndexes[ i + 0 ] = q + 0;
			mQuadIndexes[ i + 1 ] = q + 1;
			mQuadIndexes[ i + 2 ] = q + 2;
			mQuadIndexes[ i + 3 ] = q + 0;
			mQuadIndexes[ i + 4 ] = q + 2;
			mQuadIndexes[ i + 5 ] = q + 3;
		}
		mCurrentTextureId = UNDIFINED;
	}

	void Render::init(int width, int height, float mScale)
	{
		glMatrixMode        (GL_MODELVIEW);
		glViewport          (0, 0, width, height);
		glMatrixMode        (GL_MODELVIEW);
		glLoadIdentity      ();

		glEnable( GL_BLEND );
		glEnable			(GL_TEXTURE_2D);
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


		glColor4f( 1,1,1,1 );

		glMatrixMode        (GL_PROJECTION);
		glLoadIdentity      ();

		glOrthof				(0, (float)width, 0,(float)height,  -99999, 99999);  // 左下 0，0
		//glOrthof				(0, (float)width, (float)height, 0, -99999, 99999); // 左上0,0

		glDisable				( GL_DEPTH_TEST );
		glDisable				( GL_CULL_FACE );
		glDisable				(GL_LIGHTING);
		glDisableClientState	(GL_NORMAL_ARRAY);
		glDisable				( GL_ALPHA_TEST );

		glMatrixMode        (GL_MODELVIEW);

		resetVertexArrayStatus();

	}


	Render::~Render()
	{

	}

	// instance
	Render * Render::Instance(void)
	{
		static Render s_instance;
		return &s_instance;
	}


	//////////////////////////////////////////////////////////////////////////
	void Render::clearScreen(int argb)
	{
		glClearColor(GL_COLOR_RED_FLOAT(argb), GL_COLOR_GREEN_FLOAT(argb), GL_COLOR_BLUE_FLOAT(argb), GL_COLOR_ALPHA_FLOAT(argb));
		glClear( GL_COLOR_BUFFER_BIT );
	}


	void Render::setColor(int argb)
	{
		glColor4f(GL_COLOR_RED_FLOAT(argb), GL_COLOR_GREEN_FLOAT(argb), GL_COLOR_BLUE_FLOAT(argb), GL_COLOR_ALPHA_FLOAT(argb));
		mColor = argb;
	}

	// texture
	void Render::enableTexture(void)
	{
		glEnable(GL_TEXTURE_2D);
	}

	void Render::disableTexture(void)
	{
		glDisable( GL_TEXTURE_2D );
	}
	
	void Render::bindTexture(Texture* texture, BOOL  isLinearFiltering)
	{
		GLuint texId = 0;
		if(!texture->hasBind()){
			glGenTextures( 1, &texId );
			texture->mTextureId = texId;
			glBindTexture(GL_TEXTURE_2D, texId);
			if(isLinearFiltering)
			{		
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			}
			checkError("bind");
			glTexImage2D(
				GL_TEXTURE_2D, 0,
				texture->mOriginalFormat, texture->mTextureWidth, texture->mTextureHeight, 0,
				texture->mOriginalFormat, GL_UNSIGNED_BYTE, texture->mImageData );
			if(!texture->keepRawData()){	// 不保留原始数据
				SAFE_FREE(texture->mImageData);
			}
			mCurrentTextureId = texture->mTextureId;
			checkError("bind");
		}else if ( mCurrentTextureId != texture->mTextureId){
			mCurrentTextureId = texture->mTextureId;
			glBindTexture(GL_TEXTURE_2D, mCurrentTextureId);
			if(isLinearFiltering)
			{		
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			}
		}
	}

	// arrays
	void Render::enableVertexArray(void) 
	{
		glEnableClientState(GL_VERTEX_ARRAY);
	}

	void Render::enableColorArray(void)
	{
		glEnableClientState(GL_COLOR_ARRAY);
	}

	void Render::enableTexCoordArray(void)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Render::disableVertexArray(void)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void Render::disableColorArray(void)
	{
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void Render::disableTexCoordArray(void)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Render::setVertexPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glVertexPointer(components, returnGLType(type), 0, pointer);
	}
	void Render::setColorPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glColorPointer(components, returnGLType(type), 0, pointer);
	}

	void Render::setTexCoordPointer(TYPES type, unsigned int components, const void * pointer)
	{
		glTexCoordPointer(components, returnGLType(type), 0, pointer);
	}

	void Render::resetVertexArrayStatus()
	{
		glVertexPointer( 3, GL_FLOAT, sizeof( mVertexArray[0] ), mVertexArray );
		glEnableClientState( GL_VERTEX_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, sizeof( mTexcoordArray[0] ), mTexcoordArray );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof( mColorArray[0] ), mColorArray );
	}

	//////////////////////////////////////////////////////////////////////////
	 //draw
	void Render::begin(PRIMITIVE_TYPES type)
	{
		if(mVertexIndex)
			end();
		mVertexIndex = 0;
		mPrimitiveType = type;
	}

	void Render::vertex3f( float x, float y, float z )
	{
		ASSERT(mVertexIndex < MAX_ARRAY_SIZE );
		GLfloat v[3] = {x,y,z};
		memcpy(mVertexArray[mVertexIndex++],v,sizeof(mVertexArray[0]));
	}

	void Render::vertex2f( float x, float y )
	{
		ASSERT(mVertexIndex < MAX_ARRAY_SIZE );
		GLfloat v[3] = {x,y,0};
		memcpy(mVertexArray[mVertexIndex++],v,sizeof(mVertexArray[0]));
	}

	void Render::vertex2i( int x, int y )
	{
		ASSERT(mVertexIndex < MAX_ARRAY_SIZE );
		GLfloat v[3] = {(float)x,(float)y,0};
		memcpy(mVertexArray[mVertexIndex++],v,sizeof(mVertexArray[0]));
	}

	void Render::texCoord2i( int s, int t )
	{
		ASSERT(mVertexIndex < MAX_ARRAY_SIZE );
		GLfloat v[2] = {(float)s,(float)t};
		memcpy(mTexcoordArray[mVertexIndex],v,sizeof(mTexcoordArray[0]));
	}

	void Render::texCoord2f(float s, float t )
	{
		ASSERT(mVertexIndex < MAX_ARRAY_SIZE );
		GLfloat v[2] = {s, t};
		memcpy(mTexcoordArray[mVertexIndex],v,sizeof(mTexcoordArray[0]));
	}

	void Render::color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	{
		ASSERT( mVertexIndex < MAX_ARRAY_SIZE );
		GLubyte v[4] = {r,g,b,a};
		memcpy(mColorArray[mVertexIndex],v,sizeof(mColorArray[0]));
	}

	void Render::color4ubv( unsigned char *rgba )
	{
		ASSERT( mVertexIndex < MAX_ARRAY_SIZE );
		memcpy(mColorArray[mVertexIndex],rgba,sizeof(mColorArray[0]));
	}

	void Render::color3f( float r, float g, float b )
	{
		GLubyte v[4] = {(GLubyte) ( r * 255 ),(GLubyte) ( g * 255 ),(GLubyte) ( b * 255 ), 255 };
		color4ubv(v);
	}

	void Render::color4f( float r, float g, float b, float a )
	{
		GLubyte v[4] = {(GLubyte) ( r * 255 ),(GLubyte) ( g * 255 ),(GLubyte) ( b * 255 ),(GLubyte) ( a * 255 )};
		color4ubv(v);
	}

	void Render::end()
	{
		// 如果用到VBO技术就需要打开此处
		//resetVertexArrayStatus();
		if(mVertexIndex>0)
		{
			if ( mPrimitiveType == ePRIMITIVE_QUARD ) {
					glDrawElements( GL_TRIANGLES, mVertexIndex / 4 * 6, GL_UNSIGNED_SHORT, mQuadIndexes );
			} else {
				glDrawArrays( returnPrimitiveType(mPrimitiveType), 0,  mVertexIndex);
			}
		}
		mVertexIndex = 0;
		mPrimitiveType = ePRIMITIVE_QUARD;//默认GL_QUADS

		checkError("end");

	}

	void Render::drawArray(PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) 
	{
		glDrawArrays(returnPrimitiveType(type), begin, size);
	}
	void Render::drawElement(PRIMITIVE_TYPES type, unsigned int size, TYPES indicesType, const void * indices)
	{
		glDrawElements(returnPrimitiveType(type), size, returnGLType(indicesType), indices);
	}

	void Render::drawRect(int x, int y, int w, int h, int argb)
	{
		// todo
		//if(!isRectInClip(x,y,w,h))
		//	return;

		end();//此行是为了提交以前的材质的东西，防止影响
		glDisable( GL_TEXTURE_2D );
		glDisableClientState (GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_LINE_SMOOTH);
		setColor(argb);

		glLineWidth( 1 );
		begin(ePRIMITIVE_LINES);
		for(int i = 0; i < mLineWidth;i++)
		{
			vertex2i(i>0?x-1:x, y );
			vertex2i(i>0?x+w+1:x+w, y);

			vertex2i(x+w, y);
			vertex2i( x + w, y + h );

			vertex2i( i>0?x + w+1:x+w, y + h );
			vertex2i( i>0?x-1:x , y+h );

			vertex2i( x , y+h );
			vertex2i(x, y );

			x++;
			y++;
			w-=2;
			h-=2;
		}
		end();

		glLineWidth((float)mLineWidth );
		glColor4f( 1, 1, 1 ,1);
	}

	void Render::drawLine(int x1, int y1, int x2, int y2, int argb, int  lineWidth)
	{
		end();
		glDisable( GL_TEXTURE_2D );
		setColor(argb);
		glLineWidth((float)lineWidth);
		begin(ePRIMITIVE_LINES);
		vertex2i(x1, y1 );
		vertex2i(x2, y2 );
		end();
	}
	void Render::drawTexture(const Texture* texture, float x, float y, int transfer, int anchor)
	{
		if( !texture || !texture->isRendable())
			return ;

		static Image image;

		image.mTexture = (Texture *)texture;
		image.setTextureRect(0, 0, texture->mTextureWidth, texture->mTextureHeight);
		drawImage(&image,x,y,transfer,anchor);
	}

	void Render::drawImage(const Image* image, float x, float y,int transfer,int anchor)
	{
		glEnable( GL_TEXTURE_2D );
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		if(!image|| !image->isRendable())
			return;
		if(anchor!=0){
			if(anchor&ANCHOR_HCENTER){
				x-=image->m_width/2;
			}else if(anchor&ANCHOR_RIGHT){
				x-=image->m_width;
			}

			if(anchor&ANCHOR_VCENTER){
				y-=image->m_height/2;
			}else if(anchor&ANCHOR_BOTTOM){
				y-=image->m_height;
			}
		}

		bindTexture(image->mTexture);
		//begin(ePRIMITIVE_TRIANGLES);
		switch(transfer)
		{
		case TRANS_NONE:
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x + image->m_width, y + image->m_height);
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x, y + image->m_height);
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x, y );
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x + image->m_width, y );
			break;
		case TRANS_MIRROR_ROT180:
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x, y );
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x + image->m_width, y );
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x + image->m_width, y + image->m_height);
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x, y + image->m_height);
			break;
		case TRANS_MIRROR:

			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x, y );
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x + image->m_width, y );
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x + image->m_width, y + image->m_height);
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x, y + image->m_height);

			break;
		case TRANS_ROT180:
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x + image->m_width, y + image->m_height);
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x, y + image->m_height);
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x, y );
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x + image->m_width, y );
			break;
		case TRANS_MIRROR_ROT270:

			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x, y + image->m_width);
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x, y );
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x + image->m_height, y );
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x + image->m_height, y + image->m_width);

			break;
		case TRANS_ROT90:
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x + image->m_height, y );
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x + image->m_height, y + image->m_width); 
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x, y + image->m_width); 
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x, y );

			break;
		case TRANS_ROT270:

			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x, y + image->m_width);
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x, y );
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x + image->m_height, y );
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x + image->m_height, y + image->m_width);

			break;
		case TRANS_MIRROR_ROT90:
			texCoord2f( image->m_tx1, image->m_ty0 );	vertex2f(x + image->m_height, y );
			texCoord2f( image->m_tx0, image->m_ty0 );	vertex2f(x + image->m_height, y + image->m_width); 
			texCoord2f( image->m_tx0, image->m_ty1 );	vertex2f(x, y + image->m_width); 
			texCoord2f( image->m_tx1, image->m_ty1 );	vertex2f(x, y );
			break;
		}
		end();
	
	}



	
	// masks
	void Render::setColorMask(bool r, bool g, bool b, bool a)
	{
		glColorMask(r, g, b, a);
	}

	// alpha
	void Render::setAlphaTest(float value)
	{
		if(value > 0.0f)
			glEnable(GL_ALPHA_TEST);
		else {
			glDisable(GL_ALPHA_TEST);
		}

		glAlphaFunc(GL_GREATER, value);
	}


	// matrix
	void Render::loadIdentity(void) 
	{
		glLoadIdentity();
	}
	void Render::setMatrixMode(MATRIX_MODES mode) 
	{
		switch(mode)
		{
		case eMATRIX_MODELVIEW:
			glMatrixMode(GL_MODELVIEW);
			return;

		case eMATRIX_PROJECTION:
			glMatrixMode(GL_PROJECTION);
			return;

		case eMATRIX_TEXTURE:
			glMatrixMode(GL_TEXTURE);
			return;
		}
	}
	void Render::pushMatrix(void) 
	{
		glPushMatrix();
	}
	void Render::popMatrix(void) 
	{
		glPopMatrix();
	}

	// blending
	void Render::enableBlending(void) 
	{

	}
	void Render::disableBlending(void) 
	{

	}
	void Render::setBlendingMode(BLENDING_MODES mode) 
	{

	}

	void Render::checkError(const char* message)
	{
		GLint err = glGetError();
		if ( err != GL_NO_ERROR ) {
			printf( "GL ERROR %d from %s\n", err, message );
		}
	}
}