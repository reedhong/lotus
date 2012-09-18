/********************************************************************
	created:	2012/09/17
	filename: 	UString.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "UString.h"

namespace Lotus2d {


	/* Judge if the specified utf-8 character's head start is valid. */
#define UTF8_LEGAL_STARTCHAR(src)		\
	((src[0] & 0x80) == 0 ||		\
	((src[0] & 0xFF) >= 0xC2 &&		\
	(src[0] & 0xFF) <= 0xDF) ||		\
	(src[0] & 0xF0) == 0xE0 ||		\
	(src[0] & 0xFF) == 0xF0)

	/* Judge the len of bytes with the specified utf-8 character */
#define UTF8_SEQ_LENGTH(src)			\
	((src[0] & 0x80) == 0 ? 1 : 		\
	(((src[0] & 0xFF) >= 0xC2 &&		\
	(src[0] & 0xFF) <= 0xDF) ? 2 : 	\
	((src[0] & 0xF0) == 0xE0 ? 3 : 	\
	((src[0] & 0xFF) == 0xF0 ? 4 : 0))))

	/* Judge if the specified utf-8 character is valid. */
#define UTF8_SEQ_VALID(src)			\
	((src[0] & 0x80) == 0 ? 1 : 		\
	(((src[0] & 0xFF) >= 0xC2 &&		\
	(src[0] & 0xFF) <= 0xDF &&		\
	(src[1] & 0xC0) == 0x80) ? 2 : 	\
	((src[0] & 0xF0) == 0xE0 &&		\
	(src[1] & 0xC0) == 0x80 &&		\
	(src[2] & 0xC0) == 0x80 ? 3 : 	\
	((src[0] & 0xFF) == 0xF0 &&		\
	(src[1] & 0xC0) == 0x80 &&		\
	(src[2] & 0xC0) == 0x80 &&		\
	(src[3] & 0xC0) == 0x80 ? 4 : 0))))

	/* Get the character code of the specified utf-8 character */
#define UTF8_GET_CHAR(src)			\
	((src[0] & 0x80) == 0 ? src[0] : 	\
	(((src[0] & 0xFF) >= 0xC2 &&		\
	(src[0] & 0xFF) <= 0xDF &&		\
	(src[1] & 0xC0) == 0x80) ?		\
	((src[0] & 0x1F) << 6) |		\
	(src[1] & 0x3F) : 		\
	((src[0] & 0xF0) == 0xE0 &&		\
	(src[1] & 0xC0) == 0x80 &&		\
	(src[2] & 0xC0) == 0x80 ?		\
	((src[0] & 0x0F) << 12) |		\
	((src[1] & 0x3F) << 6) |		\
	(src[2] & 0x3F) :			\
	((src[0] & 0xFF) == 0xF0 &&		\
	(src[1] & 0xC0) == 0x80 &&		\
	(src[2] & 0xC0) == 0x80 &&		\
	(src[3] & 0xC0) == 0x80 ?		\
	((src[1] & 0x3F) << 12) |		\
	((src[2] & 0x3F) << 6) |		\
	(src[3] & 0x3F) : -1))))

	/* Get the len of bytes in the format of utf-8 of the specified character code */
#define UTF8_CHAR_LENGTH(ch)			\
	((ch >= 0x00000 && ch <= 0x0007F) ? 1 : \
	(ch >= 0x00080 && ch <= 0x007FF) ? 2 :	\
	(ch >= 0x00800 && ch <= 0x0FFFF) ? 3 :	\
	(ch >= 0x10000 && ch <= 0x3FFFF) ? 4 : 1) //FIXME HERE. 

	/* Put the specified character code to the specified utf-8 coded string */
#define UTF8_PUT_CHAR(dest, ch)				\
	((ch >= 0x00000 && ch <= 0x0007F) ? 		\
	(dest[0] = ch) :				\
	(ch >= 0x00080 && ch <= 0x007FF) ? 		\
	((dest[0] = ((ch >>  6) & 0x1F) | 0xC0),	\
	(dest[1] = ( ch        & 0x3F) | 0x80)) :	\
	(ch >= 0x00800 && ch <= 0x0FFFF) ? 		\
	((dest[0] = ((ch >> 12) & 0x0F) | 0xE0),	\
	(dest[1] = ((ch >>  6) & 0x3F) | 0x80),	\
	(dest[2] = ( ch        & 0x3F) | 0x80)) :	\
	(ch >= 0x10000 && ch <= 0x3FFFF) ? 		\
	((dest[0] = 0xF0),				\
	(dest[1] = ((ch >> 12) & 0x3F) | 0x80),	\
	(dest[2] = ((ch >>  6) & 0x3F) | 0x80),	\
	(dest[3] = ( ch        & 0x3F) | 0x80)) : 0)



	UString::UString()
	{
		init(NULL, 0);
	}

	UString::UString(const char* buf)
	{
		init(buf, strlen(buf));
	}

	UString::UString(const char* buf, size_t len)
	{
		init(buf, len);
	}

	UString::UString(const UString& str)
	{
		init(str.c_str(), str.length());
	}

	UString::~UString()
	{
		if( utf_data != localBuffer){
			SAFE_DELETE(utf_data);
		}
	}

	size_t UString::length() const
	{
		return str_len;
	}

	size_t UString::size() const
	{
		return 0;
	}

	BOOL UString::empty() const
	{
		return FALSE;
	}

	const char* UString::c_str() const
	{
		return utf_data;
	}


	int UString::get(size_t index) const
	{
		char* str = utf_data;

		if(!str_len){
			return -1;
		}

		while (index > 0){
			int ch = UTF8_GET_CHAR(str);
			if (!ch){
				return -1;
			}

			str += UTF8_CHAR_LENGTH(ch);
			index--;
		}

		return UTF8_GET_CHAR(str);
	}

	int UString::getUnicodeFromIterator()
	{
		char* str = utf_data+iter;
		if(!(*str)){
			iter = 0;
			return -1;
		}
		int ch = UTF8_GET_CHAR(str);
		if (!ch){
			iter = 0;
			return -1;
		}
		iter += UTF8_CHAR_LENGTH(ch);
		return ch;
	}

	void UString::init(const char* buf, size_t len)
	{
		localBuffer[0]='\0';
		utf_data = localBuffer;		// stream data width utf-8 format.
		utf_dataLen = 0;	// len of stream data.
		str_len = 0;		// len of string.
		iter =0;
		if(buf == NULL)
			return;
		str_len = _utf_string_len(buf, len);

		/* Init the string */
		str_len = str_len;
		utf_dataLen = len;
		if(LocalFixStringSize<=len){
			utf_data = (char*)malloc(len+1);
		}
		memcpy(utf_data, buf, len);
		utf_data[len] = 0;
	}

	int UString::_utf_string_len(const char* buf, size_t size)
	{
		int len = 0;
		int i = 0;
		if (buf == NULL){
			return 0;
		}
		while(i < (int)size){
			int sl = UTF8_SEQ_LENGTH(buf);
			if (sl){
				len++;
				buf += sl;
			}
			else{  // Something wrong here, failure recover.
				// utf8_data++;
				break;
			}
			i += sl;
		}

		if(i > (int)size){ // Overflow, invalid data stream.
			return -1;
		}

		return len;
	}
}