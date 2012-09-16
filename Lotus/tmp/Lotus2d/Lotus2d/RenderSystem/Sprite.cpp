/********************************************************************
	created:	2012/09/16
	filename: 	Sprite.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "Base/Util.h"
#include "Base/MemoryStream.h"

#include "Sprite.h"
// todo:
#include "GLHeader.h"

// todo
//#include "RapidXml/rapidxml.hpp"
//using namespace rapidxml;
#include "TinyXML/tinyxml.h"


namespace Lotus2d {

	SpriteTexture::SpriteTexture(string description, string path)
	{
		m_description  = description;
		m_path = path;
		m_texture = Texture::loadTexture(m_path.c_str());
	}

	SpriteTexture::~SpriteTexture()
	{
		SAFE_DELETE(m_texture);
	}


	SpriteSFrame::SpriteSFrame(string name)
	{
		m_name = name;
	}

	SpriteSFrame::~SpriteSFrame()
	{
		vector<SpriteFModule* >::iterator iter = m_fmodules.begin();
		for(;iter != m_fmodules.end(); ++iter){
			delete (*iter);
		}
	}

	SpriteAction::SpriteAction()
	{

	}

	SpriteAction::~SpriteAction()
	{
		vector<SpriteAFrame* >::iterator iter = m_aframes.begin();
		for(;iter != m_aframes.end(); ++iter){
			delete (*iter);
		}
	}

	VBOAction::VBOAction()
	{
		Reset();
	}

	VBOAction::~VBOAction()
	{

	}

	void VBOAction::Reset()
	{
		m_frameIdx = 0;
		m_frameDuration = 0;	
	}

	void VBOAction::load(Stream* stream)
	{
		int16 frameCount = stream->read16();
		for(int i = 0; i < frameCount; i++){
			VBOFrame frame;
			frame.m_startIndex = stream->read16();
			frame.m_vertexCount = stream->read16();
			frame.m_times = stream->read8();
			m_frames.push_back(frame);
		}
	}

	VBOFrame* VBOAction::getFrame(uint32 index)
	{
		ASSERT(index < m_frames.size());
		return &(m_frames[index]);
	}

	BOOL VBOAction::step(BOOL  doCycle)
	{
		m_frameDuration++;
		VBOFrame* frame = getFrame(m_frameIdx);
		if(frame->m_times == m_frameDuration){
			if( (m_frameIdx)+1 == m_frames.size()){
				if(doCycle){
					m_frameIdx = 0;
				}
			}else{
				m_frameIdx++;
			}
			
			m_frameDuration = 0;
		}

		return TRUE;
	}

	void VBOAction::Paint(Render* render)
	{
		VBOFrame* frame = &(m_frames[m_frameIdx]);
		glDrawArrays(GL_TRIANGLES, frame->m_startIndex, frame->m_vertexCount);
		render->checkError("glDrawArrays end");
	}


	//////////////////////////////////////////////////////////////////////////
	// CSprite

	Sprite::Sprite(void)
	{
		m_textureKey = 0;
		m_texture = NULL;
		m_hasBindBuffer = FALSE;
		m_actionIndex = 0;
		m_vertexArrayBuffer = NULL;
	}

	Sprite::~Sprite(void)
	{
		vector<VBOAction *>::iterator iter = m_actions.begin();
		for(; iter != m_actions.end(); ++iter){
			delete (*iter);
		}
		if(m_hasBindBuffer){
			glDeleteBuffers(1,&m_bufferId);
		}

		vector<SpriteTexture* >::iterator textureIter = m_spriteTextures.begin();
		for(; textureIter != m_spriteTextures.end(); ++textureIter){
			delete (*textureIter);
		}

		vector<Image* >::iterator imageIter = m_spriteImages.begin();
		for(; imageIter != m_spriteImages.end(); ++imageIter){
			delete (*imageIter);
		}


		vector<SpriteSModule* >::iterator smoduleIter = m_spriteModules.begin();
		for(;smoduleIter != m_spriteModules.end(); ++smoduleIter){
			delete (*smoduleIter);
		}

		vector<SpriteSFrame* >::iterator sframeIter = m_spriteFrames.begin();
		for(;sframeIter != m_spriteFrames.end(); ++sframeIter){
			delete (*sframeIter);
		}

		vector<SpriteAction* >::iterator actionIter = m_spriteActions.begin();
		for(;actionIter != m_spriteActions.end(); ++actionIter){
			delete (*actionIter);
		}

		SAFE_FREE(m_vertexArrayBuffer);
	}

	void Sprite::bindVBO()
	{
		Render::Instance()->bindTexture(m_texture);
		glGenBuffers(1, &m_bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VERTEX_DATA_DEF), 
			m_vertexArrayBuffer, GL_STATIC_DRAW);
		SAFE_FREE(m_vertexArrayBuffer);

		m_hasBindBuffer = TRUE;
	}

	BOOL Sprite::loadFromBinary(Stream* stream)
	{
		m_textureKey = stream->read16();
		if(m_textureKey <=0)
			return FALSE;
		uint16 actionCount = stream->read16();
		if( actionCount <= 0)
			return FALSE;
		for(uint16 i = 0; i < actionCount; i++){
			VBOAction* action = new VBOAction();
			action->load(stream);
			m_actions.push_back(action);
		}
		int32 len = stream->read32();
		if( len < VERTEX_SIZE)
			return FALSE;
		m_vertexArrayBuffer = (unsigned char*)malloc(len);
		stream->read(m_vertexArrayBuffer, len);
		m_vertexCount = len / VERTEX_SIZE;

		// TODO:
		//m_texture = ResManager::Instance()->LoadTexture(m_textureKey);
		
		ASSERT(m_texture!=NULL);

		bindVBO();
		
		return TRUE;
	}

	BOOL Sprite::loadFromXML(const char* path)
	{
		TiXmlNode* node = 0;
		TiXmlElement* element = 0;
		TiXmlElement* elem_images = 0;
		TiXmlDocument docImport(path);

		if(!docImport.LoadFile()) 
			return FALSE;
		node = docImport.FirstChild("sprite");

		if(!node)
			return FALSE;

		element = node->ToElement();
		char* char_version = (char*)element->Attribute("version");
		int version = 1; 
		if(char_version)
			version = atoi(char_version);
		if(NULL == element)
			return FALSE;



		//load images
		elem_images = element->FirstChildElement("images");
		if(elem_images)
		{
			TiXmlElement* elem_imageItem = 0;
			elem_imageItem = elem_images->FirstChildElement();
			int imageIndex = 0;
			if(elem_imageItem)
			{
				//char *hexid,*file,*key,*bg;
				char* file;
				do
				{
					file = (char*)elem_imageItem->Attribute("file");
					if(!file)return FALSE;
					char* imageName = Util::getFileNameNoExt(file);

					SpriteTexture* image= new SpriteTexture(imageName, file);
					m_spriteTextures.push_back(image);
					SAFE_FREE(imageName);

				}while(elem_imageItem = elem_imageItem->NextSiblingElement());
			}
		}

		//load modules
		TiXmlElement* elem_modules = 0;
		elem_modules = element->FirstChildElement("modules");
		if(elem_modules)
		{
			TiXmlElement* elem_moduleItem = 0;
			elem_moduleItem = elem_modules->FirstChildElement();
			if(elem_moduleItem)
			{
				char *x,*y,*width,*height,*img;
				do
				{
					x = (char*)elem_moduleItem->Attribute("x");
					if(!x)return FALSE;

					y = (char*)elem_moduleItem->Attribute("y");
					if(!y)return FALSE;

					width  = (char*)elem_moduleItem->Attribute("width");
					if(!width)return FALSE;

					height  = (char*)elem_moduleItem->Attribute("height");
					if(!height)return FALSE;

					img  = (char*)elem_moduleItem->Attribute("img");
					if(!img)return FALSE;


					SpriteSModule* smodule = new SpriteSModule();
					smodule->m_x = atoi(x);
					smodule->m_y = atoi(y);
					smodule->m_width = atoi(width);
					smodule->m_height = atoi(height);
					smodule->m_imageIndex = atoi(img);
					m_spriteModules.push_back(smodule);

				}while(elem_moduleItem = elem_moduleItem->NextSiblingElement());
			}
		}


		//loadframes
		TiXmlElement* elem_frames = 0;
		elem_frames = element->FirstChildElement("frames");
		if(elem_frames)
		{
			TiXmlElement* elem_frameItem = 0;
			elem_frameItem = elem_frames->FirstChildElement();
			if(elem_frameItem)
			{
				char *name;
				do
				{
					name  = (char*)elem_frameItem->Attribute("name");
					if(!name)return FALSE;

					SpriteSFrame* sframe= new SpriteSFrame(name);

					TiXmlElement* elem_fmdouleItem = 0;
					elem_fmdouleItem = elem_frameItem->FirstChildElement();

					if(elem_fmdouleItem)
					{
						char *module,*x,*y,*trans;
						do
						{
							module = (char*)elem_fmdouleItem->Attribute("module");
							if(!module)return FALSE;

							x = (char*)elem_fmdouleItem->Attribute("x");
							if(!x)return FALSE;

							y = (char*)elem_fmdouleItem->Attribute("y");
							if(!y)return FALSE;

							trans  = (char*)elem_fmdouleItem->Attribute("trans");
							if(!trans)return FALSE;

							SpriteFModule* fmodule = new SpriteFModule();
							fmodule->m_ox = atoi(x);
							fmodule->m_oy = atoi(y);
							fmodule->m_moduleIndex = atoi(module);
							fmodule->m_transFlag = atoi(trans);
							sframe->m_fmodules.push_back(fmodule);
						}while(elem_fmdouleItem = elem_fmdouleItem->NextSiblingElement());
					}
					m_spriteFrames.push_back(sframe);
				}while(elem_frameItem = elem_frameItem->NextSiblingElement());
			}
		}
		//end load frames

		//load actions
		TiXmlElement* elem_actions = 0;
		elem_actions = element->FirstChildElement("actions");
		if(elem_actions)
		{
			TiXmlElement* elem_actionItem = 0;
			elem_actionItem = elem_actions->FirstChildElement();
			if(elem_actionItem)
			{
				char *id,*name;//,*key,*px,*py;
				int actionid = 0;
				do
				{
					id  = (char*)elem_actionItem->Attribute("id");
					name = (char*)elem_actionItem->Attribute("name");
					if(!name)return FALSE;

					SpriteAction* action = new SpriteAction();

					action->m_id = atoi(id);
					action->m_name = name;
					action->m_key   = (char*)elem_actionItem->Attribute("key");
					action->m_px  = (char*)elem_actionItem->Attribute("px");
					action->m_py  = (char*)elem_actionItem->Attribute("py");
					action->m_boundX = atoi(elem_actionItem->Attribute("bound_x"));
					action->m_boundY = atoi(elem_actionItem->Attribute("bound_y"));
					action->m_boundW = atoi(elem_actionItem->Attribute("bound_w"));
					action->m_boundH = atoi(elem_actionItem->Attribute("bound_h"));

					m_spriteActions.push_back(action);

					TiXmlElement* elem_aframeItem = 0;
					elem_aframeItem = elem_actionItem->FirstChildElement();
					if(elem_aframeItem)
					{
						char *frame,*flip,*fx,*fy,*visible,*time;
						do
						{
							SpriteAFrame* aframe = new SpriteAFrame();

							frame  = (char*)elem_aframeItem->Attribute("frame");
							ASSERT(frame!=NULL);
							aframe->m_frameIndex = atoi(frame);

							flip	  = (char*)elem_aframeItem->Attribute("flip");
							ASSERT(flip!=NULL);
							aframe->m_flipFlag = atoi(flip);

							fx   = (char*)elem_aframeItem->Attribute("fx");
							ASSERT(fx!=NULL);
							aframe->m_fx = atoi(fx);


							fy  = (char*)elem_aframeItem->Attribute("fy");
							ASSERT(fy!=NULL);
							aframe->m_fy = atoi(fy);

							time = (char*)elem_aframeItem->Attribute("time");
							ASSERT(time!=NULL);
							aframe->m_times = atoi(time);

							visible  = (char*)elem_aframeItem->Attribute("visible");
							if(strcmp(visible, "true")){
								aframe->m_isVisible = TRUE;
							}else{
								aframe->m_isVisible = FALSE;
							}

							action->m_aframes.push_back(aframe);

						}while(elem_aframeItem = elem_aframeItem->NextSiblingElement());
					}
				}while(elem_actionItem = elem_actionItem->NextSiblingElement());
			}
		}
		if( m_spriteActions.size() == 0)
			return FALSE;
		loadVBO();
		bindVBO();
		return TRUE;
	}

	void Sprite::loadImages()
	{
		vector<SpriteSModule* >::iterator iter = m_spriteModules.begin();
		SpriteSModule* smodule = NULL;
		for(;iter != m_spriteModules.end(); ++iter){
			smodule = *iter;
			SpriteTexture* spriteTexture = m_spriteTextures[smodule->m_imageIndex];
			Image* image = Image::createImage(spriteTexture->m_texture, smodule->m_x,
				smodule->m_y, smodule->m_width, smodule->m_height);
			m_spriteImages.push_back(image);
		}
	}

	void Sprite::loadVBO()
	{
		int actionCount = m_spriteActions.size();
		int vertexOffset = 0;
		int vertexCount = 0;
		int during = 0;
		for(uint16 i = 0; i < actionCount; i++){
			VBOAction* vboAction = new VBOAction();
			m_actions.push_back(vboAction);

			SpriteAction*  spriteAction = m_spriteActions[i];
			int frameCount = spriteAction->m_aframes.size();
			for(uint16 j = 0; j < frameCount; j++ ){
				VBOFrame vboFrame;
		
				SpriteAFrame* spriteAFrame = spriteAction->m_aframes[j];
				SpriteSFrame* spriteSFrame = m_spriteFrames[spriteAFrame->m_frameIndex];

				vboFrame.m_startIndex = vertexCount;
				vboFrame.m_vertexCount = spriteSFrame->m_fmodules.size() * 6;
				vboFrame.m_times = spriteAFrame->m_times;
				vboAction->m_frames.push_back(vboFrame);
				
				vertexOffset += 72 * spriteSFrame->m_fmodules.size();  // 6个顶点，每个顶点需要材质数据{float, float}, 顶点数据 {int, int ,int }, 6*12
				vertexCount  += 6*spriteSFrame->m_fmodules.size();
			}		
		}
		m_vertexCount = vertexCount; // 要去buffer的长度

		
		int bufferLen = m_vertexCount*VERTEX_SIZE;
		m_vertexArrayBuffer = (unsigned char*)malloc(bufferLen);
		MemoryStream* outstream = new MemoryStream(m_vertexArrayBuffer, bufferLen);

		SpriteTexture* spriteTexture = m_spriteTextures[0];
		m_texture = spriteTexture->m_texture;
		float imageWidth = (float)m_texture->mImageWidth;
		float imageHeight = (float)m_texture->mImageHeight;

		for(uint16 i = 0; i < actionCount; i++){
			SpriteAction*  spriteAction = m_spriteActions[i];
			int frameCount = spriteAction->m_aframes.size();
			for(uint16 j = 0; j < frameCount; j++ ){
				SpriteAFrame* spriteAFrame = spriteAction->m_aframes[j];
				SpriteSFrame* spriteSFrame = m_spriteFrames[spriteAFrame->m_frameIndex];

				
				int fflag = spriteAFrame->m_flipFlag;
				BOOL flipX = (((fflag & FLIP_HORIZONTALLY) == 1));
				BOOL flipY = ((((fflag & FLIP_VERTICALLY) >> 1) == 1));
				for (unsigned int k = 0; k < spriteSFrame->m_fmodules.size(); k++)
				{
					int foffsetX = spriteAFrame->m_fx;
					int foffsetY = spriteAFrame->m_fy;
					SpriteFModule* fmodule = spriteSFrame->m_fmodules[k];				
					SpriteSModule* smodule = m_spriteModules[fmodule->m_moduleIndex];
					//assert(smodule != NULL && smodule->m_x >=0 && smodule->m_y >=0&& smodule->m_width <= imageWidth&& smodule->m_height <= imageHeight);

					float  x0 = smodule->m_x/imageWidth;
					float  y1 = smodule->m_y/imageHeight;
					float  x1 = (smodule->m_x + smodule->m_width)/imageWidth;
					float  y0 = (smodule->m_y + smodule->m_height)/imageHeight;

					int mflags = fmodule->m_transFlag;

					int trans = TRANS_NONE;
					if ((mflags & FLAG_ROT_90) && (mflags & FLAG_FLIP_Y)&& (mflags & FLAG_FLIP_X))
						trans = TRANS_ROT270;
					else if ((mflags & FLAG_ROT_90) && (mflags & FLAG_FLIP_Y))
						trans = TRANS_MIRROR_ROT270;
					else if ((mflags & FLAG_ROT_90) && (mflags & FLAG_FLIP_X))
						trans = TRANS_MIRROR_ROT90;
					else if ((mflags & FLAG_FLIP_Y) && (mflags & FLAG_FLIP_X)) 
						trans = TRANS_ROT180;
					else if (mflags & FLAG_ROT_90) 
						trans = TRANS_ROT90;
					else if (mflags & FLAG_FLIP_Y) 
						trans = TRANS_MIRROR_ROT180;
					else if (mflags & FLAG_FLIP_X) 
						trans = TRANS_MIRROR;

					BOOL rot = trans > TRANS_ROT180;

					if (flipX) {
						if(rot){
							trans ^= TRANS_MIRROR_ROT180 ;     
						}else{    
							trans ^= TRANS_MIRROR ;     
						}
					}
					if (flipY) {
						if(rot){
							trans ^= TRANS_MIRROR ;
						}else{

							trans ^= TRANS_MIRROR_ROT180 ;
						}    
					}
					trans = mflags;
					switch(trans)
					{
					case TRANS_NONE:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_height;
							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);


							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width+ foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);
						}
						break;
					case TRANS_MIRROR_ROT180:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_height;
							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);
						}
						break;
					case TRANS_MIRROR:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_height;
							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);


						}

						break;
					case TRANS_ROT180:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_height;
							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);


							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_width + foffsetX);
							outstream->write16le(smodule->m_height + foffsetY);
						}
						break;
					case TRANS_MIRROR_ROT270:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_width;
							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);			 
						}

						break;
					case TRANS_ROT90:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_width;
							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);



						}

						break;
					case TRANS_ROT270:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_width;
							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width + foffsetY);


						}

						break;
					case TRANS_MIRROR_ROT90:
						{
							foffsetX += fmodule->m_ox;
							foffsetY -= fmodule->m_oy + smodule->m_width;
							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x1);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(smodule->m_width +foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width +foffsetY);

							outstream->writef(x1);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(smodule->m_width +foffsetY);

							outstream->writef(x0);
							outstream->writef(y0);
							outstream->write16le(foffsetX);
							outstream->write16le(foffsetY);

							outstream->writef(x0);
							outstream->writef(y1);
							outstream->write16le(smodule->m_height + foffsetX);
							outstream->write16le(foffsetY);
						}
						break;
					}			
				}
			}		
		}
		delete outstream;
	}

	void Sprite::paint(Render* render)
	{
		ASSERT(m_vertexCount> 0);
		render->bindTexture(m_texture);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);

		glTexCoordPointer(2, GL_FLOAT, VERTEX_SIZE, NULL);
		glVertexPointer(2, GL_SHORT, VERTEX_SIZE, ((float *)NULL) + 2);
		render->checkError("sprite bind buffer");
		VBOAction* action = m_actions[m_actionIndex];
		action->Paint(render);
		render->checkError("sprite paint");

	#if 0
		//glBindTexture(GL_TEXTURE_2D, m_texture->m_textureId);
		glPushMatrix();
		glTranslatef(400, 0.0, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3d(0,0, 0);
		glTexCoord2f(1.0, 0.0); glVertex3d(400,0, 0);
		glTexCoord2f(1.0, 1.0); glVertex3d(400,100, 0);
		glTexCoord2f(0.0, 1.0); glVertex3d(0,100, 0);
		glEnd();
		glPopMatrix();
	#endif
	}

	void Sprite::paint(Render* render, int x, int y)
	{
		glPushMatrix();
		glTranslatef((float)x, (float)(y), 0);
		paint(render);
		glPopMatrix();
	}

	void Sprite::step()
	{
		VBOAction* action = m_actions[m_actionIndex];
		action->step(TRUE);
	}

	void Sprite::setAction(unsigned int index)
	{
		ASSERT(index < m_actions.size());
		m_actionIndex = index;
		VBOAction* action = m_actions[m_actionIndex];
		//action->Reset();
	}

	VBOAction* Sprite::getAction(unsigned int index)
	{
		ASSERT(index < m_actions.size());
		VBOAction* action = m_actions[m_actionIndex];
		action->Reset();
		return action;
	}

	int Sprite::getActionCount()
	{
		return m_actions.size();
	}

	string Sprite::getActionName(int index)
	{
		return m_spriteActions[index]->m_name;
	}

	void Sprite::drawAFrame(Render* render, int x, int y, BOOL flipX, BOOL flipY, int anchor)
	{
	#if 0
		CSpriteAction* action = m_actions[m_actionIndex];
		// 动态帧
		CSpriteAFrame* aframe = action->m_aframes[m_frameIndex];
		/** 获得静态帧翻转信息 */
		flipX = (((aframe->m_flipFlag & FLIP_HORIZONTALLY) == 1) ^ flipX);
		flipY = ((((aframe->m_flipFlag & FLIP_VERTICALLY) >> 1) == 1) ^ flipY);

		// 获得静态帧
		CSpriteSFrame* sframe = m_sframes[aframe->m_frameIndex];

		// 分别绘制静态帧里面的动态模块
		vector<CSpriteFModule *>::iterator iter = sframe->m_fmodules.begin();
		/** 循环内变量 */
		int fmx, fmy, trans, mx, my, mw, mh, px, py, dx, dy;
		for( ; iter != sframe->m_fmodules.end(); ++iter){
			CSpriteFModule* fmodule = *iter;
			CSpriteSModule* smodule = m_smodules[fmodule->m_moduleIndex];

			// 获得module的偏移
			fmx = fmodule->m_ox;
			fmy = fmodule->m_oy;
			trans = fmodule->m_transFlag;

			/** 获得静态module在图片上的区域位置信息 */
			mx = smodule->m_x;
			my = smodule->m_y;
			mw =smodule->m_width;
			mh = smodule->m_height; 

			BOOL rot = trans > TRANS_ROT180;

			px = fmx;
			py = fmy;

			/** 计算帧反转后module的信息 */
			if (flipX) {
				if(rot){
					px = -fmx - mh;
					trans ^= TRANS_MIRROR_ROT180 ;

				}else{
					px = -fmx - mw;
					trans ^= TRANS_MIRROR ;

				}
			}
			if (flipY) {
				if(rot){
					py = -fmy - mw;
					trans ^= TRANS_MIRROR ;
				}else{
					py = -fmy - mh;
					trans ^= TRANS_MIRROR_ROT180 ;
				}

			}
			dx = x + px + ((flipX)?-aframe->m_fx:aframe->m_fx);
			dy = y + py + aframe->m_fy;

			CGLImage* image =  m_images[fmodule->m_moduleIndex];
			render->DrawImage(image, dx, dy, trans, 0);	

		}
	#endif
	}
}