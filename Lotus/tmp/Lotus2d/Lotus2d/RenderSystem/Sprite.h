/********************************************************************
	created:	2012/09/16
	filename: 	Sprite.h
	author:		reedhong
	
	purpose:	Sprite����
*********************************************************************/

#ifndef __Lotus2d_Sprite_H__
#define __Lotus2d_Sprite_H__


#include "Base/Prerequisites.h"
#include "Base/Stream.h"
#include "Texture.h"
#include "Render.h"

namespace Lotus2d {
	//////////////////////////////////////////////////////////////////////////
	// ����xml����
	class SpriteTexture
	{
	public:
		string					m_description;
		string					m_path;
		Texture*		m_texture;
	public:
		SpriteTexture(string description, string path);
		~SpriteTexture();
	};

	// ��̬ģ��
	struct SpriteSModule
	{
		int	m_x;
		int	m_y;
		int	m_width;
		int	m_height;
		int	m_imageIndex;
	};


	// ��̬ģ��
	struct SpriteFModule
	{
		int	m_ox;
		int	m_oy;
		int	m_moduleIndex;
		int	m_transFlag; // ��תģʽ
	};

	// ��̬֡
	class SpriteSFrame
	{
	public:
		SpriteSFrame(string name);
		~SpriteSFrame();
	public:
		string	m_name;
		vector<SpriteFModule *> m_fmodules;
	};

	// ��̬֡
	struct SpriteAFrame
	{
		int m_frameIndex;
		int m_flipFlag;
		int m_fx;
		int m_fy;
		int m_times;
		BOOL m_isVisible;
	};

	// N����̬֡������һ��������ÿ��sprite������N������
	class SpriteAction
	{
	public:
		SpriteAction();
		~SpriteAction();
	public:
		int m_id;
		int m_boundX;
		int m_boundY;
		int m_boundW;
		int m_boundH;
		string	m_name;
		string m_key;
		string m_px;
		string m_py;
		vector<SpriteAFrame *> m_aframes;
	};



	//////////////////////////////////////////////////////////////////////////
	// vbo-->֡
	class VBOFrame
	{
	public:
		uint16 m_startIndex;
		uint16 m_vertexCount;
		uint16 m_times;
		VBOFrame(){
			m_startIndex = 0;
			m_vertexCount = 0;
			m_times = 0;
		}
		VBOFrame(const VBOFrame& frame){
			m_startIndex = frame.m_startIndex;
			m_vertexCount = frame.m_vertexCount;
			m_times = frame.m_times;
		}
	};
	
	// vbo����
	class VBOAction
	{
	public:
		VBOAction();
		~VBOAction();
		void Reset();
		void load(Stream* stream);

		VBOFrame* getFrame(uint32 index);
		BOOL step(BOOL  doCycle=TRUE);
		void Paint(Render* render);

	public:
		uint32	m_frameIdx;
		uint32	m_frameDuration;
		vector<VBOFrame>	m_frames;
	};

	class Sprite
	{
	public:
		Sprite(void);
		~Sprite(void);
	public:	
		BOOL loadFromBinary(Stream* stream);
		BOOL loadFromXML(const char* path);

		void paint(Render* render);
		void paint(Render* render, int x, int y);
		
		// paint 
		void drawAFrame(Render* render,int x, int y, BOOL flipX=FALSE, BOOL flipY=FALSE, int anchor=0);

		void step();
		void setAction(unsigned int index);
		VBOAction* getAction(unsigned int index);
		int getActionCount();
		string getActionName(int index);
	private:	
			/* 
		 * ���ز���СͼƬ
		 */
		void loadImages();
		/*
		 * ���ز�������
		 */
		void loadVBO();
		void bindVBO();
	public:
		// ����xml������	
		vector<SpriteTexture* >	m_spriteTextures;
		vector<Image * > m_spriteImages;
		vector<SpriteSModule *>	m_spriteModules;
		vector<SpriteSFrame *> m_spriteFrames;
		vector<SpriteAction* > m_spriteActions;


		//  vbo �������
		vector<VBOAction *>	m_actions;
		int					m_actionIndex;

		int					m_textureKey;

		Texture*			m_texture;
		BOOL				m_hasBindBuffer;

		unsigned char*		m_vertexArrayBuffer;		// ���������Ӧ��buf m_vertexCount*12
		int32				m_vertexCount;						// ����ĸ���
		uint32				m_bufferId;	

	};
}

#endif