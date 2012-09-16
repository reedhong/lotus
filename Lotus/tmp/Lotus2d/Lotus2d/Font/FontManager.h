/********************************************************************
	created:	2012/09/16
	filename: 	FontManager.h
	author:		reedhong
	
	purpose:	◊÷ÃÂπ‹¿Ì
*********************************************************************/

#ifndef __Lotus2d_FontManager_H__
#define __Lotus2d_FontManager_H__

#include "Base/Prerequisites.h"
#include "RenderSystem/Texture.h"
#include "RenderSystem/Image.h"

#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H

namespace Lotus2d {

	class ge_font_glyph
	{
		/**
		* The image for this glyph.
		*/
		Image *glyph_image;

		/**
		* The image for this glyph.
		*/
		Image *glyph_image_border;
		/**
		* The unicode character for this glyph.
		*/
		uint16 character_code;
		/**
		* The cached advance for this glyph.
		*/
		uint8 advance;
	};

	struct ge_font_glyph_container
	{
		uint32 id;
		/**
		* The texture this glyph container owned.
		*/
		Texture* cached_texture;
		/**
		 * The texture width for the cached texture.
		 */
		int texture_width;
		/**
		 * The texture height for the cached texture.
		 */
		int texture_height;
		/**
		 * The current cursor for texture caching reservation.
		 */
		int current_cursor;

		/**
		 * Is the ascii character be directly mapped to the 
		 * cached texture.
		 */
		BOOL is_ASCII_direct_mapping;

		/**
		 * The max char width with current font size.
		 */
		int max_char_width;
		/**
		 * The max char height with current font size.
		 */
		int max_char_height;
		/**
		 * The column counts with the char width & height
		 * of current font size for the cached texture.
		 */
		int column_counts;
		/**
		* The row counts with the char width & height
		* of current font size for the cached texture.
		*/
		int row_counts;
		/**
		 * The max chars the cached texture can hold for.
		 */
		int max_char_counts;

		/**
		 * The font size this glyph container holds glphys for.
		 */
		int font_size;
		/**
		 * The font height for the font size.
		 */
		int font_height;

		/**
		 * The container to hold glyphs.
		 * map(Key: char code => Value: ge_glyph*)
		 */
		map<char, ge_font_glyph*> ch_glyph_map;
		/**
		 * The character array.
		 */
		vector<char> ch_array;

		/**
		 *  border width
		 */
		uint8 border;
		
		/**
		 *  has bold
		 */
		BOOL bold;
	};

	class FontManager 
	{
	public:
		enum FONT_ID
		{
			LITTLE_FONT = 1000,
			TITLE_FONT,
			MIDDLE_FONT,
			LARGE_FONT,
			SUPER_FONT
		};

		enum FONT_CACHE_IMAGE_SIZE
		{
			FONT_CACHE_IMAGE_64x64,		///< 64x64
			FONT_CACHE_IMAGE_128x128,	///< 128x128
			FONT_CACHE_IMAGE_256x256,	///< 256x256
			FONT_CACHE_IMAGE_512x512, 	///< 512x512
			FONT_CACHE_IMAGE_1024x1024	///< 1024x1024
		};

	protected:
		FontManager();
	public:
		~FontManager();
		static FontManager * Instance(void);
		BOOL init(const char* file);
		void release();
		BOOL createFont(FONT_ID fontid,uint32 size,FONT_CACHE_IMAGE_SIZE chachesize,uint8 border,BOOL bold);

	protected:
		/**
		* The current font size.
		*/
		int current_font_size;
		/**
		* The current font color.
		*/ 
		int current_font_color;

		/**
		* The current font top color.
		*/ 
		BOOL hasgradual;

		/**
		* The current font top color.
		*/ 
		int font_top_color;

		/**
		* The current font bottom color.
		*/ 
		int font_bottom_color;

		/**
		* The current font border color.
		*/ 
		int font_border_color;

		/**
		* The current font container.
		*/
		ge_font_glyph_container* current_font_container;

		/**
		* batch draw font.
		*/
		BOOL batchdraw;
		/**
		* Should the font be rendered to the bitmap with antialiase?
		*/
		BOOL is_antialias;
		/**
		* Is the tt font loaded?
		*/
		BOOL is_font_loaded;

		/**
		* Holds the glyph container of different face size.
		*/
		vector<ge_font_glyph_container*> glyph_containers_list;

		/**
		* The free type library.
		*/
		FT_Library ft_library;
		/**
		* The free type face.
		*/
		FT_Face ft_face;

		//ge_file_handle file_handle;

		//ge_file_map	   file_map;						

	};
}

#endif
