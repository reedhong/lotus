/*
 * 解析类似于windows  .ini的配置文件，由于太喜欢python中的ConfigParser接口，所以此处完全模仿之
 * created by reedhong 2012.7.17
 */

#ifndef __LOTUS_CONFIG_PARSER_H__
#define __LOTUS_CONFIG_PARSER_H__

#include "Main/Prerequisites.h"

namespace Lotus
{
	/*
	 * 注释： @  或者  #
	 * 
	 */
	class ConfigParser
	{
	public:
		ConfigParser();
		~ConfigParser();
		bool open(const String& path);	

		bool hasSection(const String& section);

		bool hasOption(const String& section, const String& option);

		// get 
		String get(const String& section, const String& option);
		int32 getInt(const String& section, const String& option);
		float getFloat(const String& section, const String& option);
		bool getBool(const String& section, const String& option);
		vector<String> getSectionIter();
		vector<String> getOptions(const String& section);
		//set
		bool set(const String& section, const String& option, const String& value);

		// write
		//bool write(const String& path );
	private:		
		typedef map<String, String> Section;
		typedef map<String, Section>::iterator SectionIterator;
		typedef map<String, String>::iterator OptionIterator;
		map<String, Section>	mSections;

	};
}

#endif