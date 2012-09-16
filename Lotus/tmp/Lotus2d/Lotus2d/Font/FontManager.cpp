/********************************************************************
	created:	2012/09/16
	filename: 	FontManager.cpp
	author:		reedhong
	
	purpose:	×ÖÌå¹ÜÀí
*********************************************************************/

#include "FontManager.h"

namespace Lotus2d {

	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{

	}
	FontManager * FontManager::Instance(void)
	{
		static FontManager s_instance;
		return &s_instance;
	}

	BOOL FontManager::init(const char* file)
	{
		if(!file) return FALSE;
		if(FT_Init_FreeType(&ft_library) != 0) return FALSE;
#if 0
		/* Create ft face */
		if (FT_New_Memory_Face(gf->ft_library, gf->file_map.data , gf->file_map.length, 0, &gf->ft_face) == 0)
		{
			gf->is_antialias = TRUE;
			gf->is_font_loaded = TRUE;
			gf->glyph_containers_list = ge_array_create(sizeof(ge_font_glyph_container*), NULL);

			switch(mode)
			{
			case FONT_LOAD_PRECACHE_ASCII:
				font_pre_cache_ASCII(gf);
				break;
			case FONT_LOAD_PRECACHE_ASCII_EX:
				font_pre_cache_extended_ASCII(gf);
				break;
			case FONT_LOAD_NORMAL:
			default:
				break;
			}
		}
#endif
		return TRUE;
	}

	void FontManager::release()
	{
		if(ft_face != NULL){
			FT_Done_Face(ft_face);
		}

		if(ft_library != NULL){
			FT_Done_FreeType(ft_library);
		}

		//ge_unmap_file(&f->file_map);
		//ge_close_file(f->file_handle);

	#if 0
	if(f->glyph_containers_list != NULL)
		{
			int count = ge_array_size(f->glyph_containers_list);
			int i = 0;

			for(; i < count; i++)
			{
				ge_font_glyph_container *glyph_container = *(ge_font_glyph_container**)ge_array_get(f->glyph_containers_list, i);
				if(glyph_container != NULL){
					font_glyph_container_destroy(glyph_container);
				}
			}
			ge_array_destroy(f->glyph_containers_list);
		}
#endif
	}

	BOOL FontManager::createFont(FONT_ID fontid,uint32 size,FONT_CACHE_IMAGE_SIZE chachesize,uint8 border,BOOL bold)
	{	
		size_t count = glyph_containers_list.size();
		for(size_t i = 0; i < count; i++){
			ge_font_glyph_container *glyph_container =glyph_containers_list[i];
			if(glyph_container->id == fontid){
				ASSERT(0); // todo:
				break;
			}
		}
		#if 0
glyph_container = font_glyph_container_create(f, size, chachesize,border);
		if(glyph_container == NULL)
		{
			return;
		}
		glyph_container->id = id;
		glyph_container->border = border;
		glyph_container->bold = bold;
		ge_array_push_back(f->glyph_containers_list, &glyph_container);
#endif

		return TRUE;
	}
}


