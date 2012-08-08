#include <fstream>
using namespace std;

#include "ConfigParser.h"
#include "Exception/Exception.h"
#include "String/StringUtil.h"
#include "Convert/Convert.h"

namespace Lotus {
	ConfigParser::ConfigParser()
	{

	}

	ConfigParser::~ConfigParser()
	{

	}

	bool ConfigParser::open(const String& path)
	{
		ifstream ifConfig(path.c_str());
		if (!ifConfig){
			LOTUS_EXCEPT(
				Exception::ERR_FILE_NOT_FOUND, "'" + path + "' file not found!", "ConfigParser::open" );			
		}

		String line;
		String currentSection;
		while (getline(ifConfig, line)){
			StringUtil::trim(line);
			//读到注释或者空行
            if (line.empty()  || line.at(0) == '#' || line.at(0) == '@')
				continue;
			if (line.at(0) == '[' && line.at(line.length()-1) == ']')
			{
				// Section
				currentSection = line.substr(1, line.length() - 2);
				if( mSections.find(currentSection) != mSections.end()){
					LOTUS_EXCEPT(
						Exception::ERR_DUPLICATE_ITEM, "'" + path + "'  config file dump section: "+currentSection, 
							"ConfigParser::open" );
				}else{
					Section section;
					mSections.insert(make_pair(currentSection, section));
				}
			}else{
				if(currentSection.empty()){
					LOTUS_EXCEPT(
						Exception::ERR_INTERNAL_ERROR, "'" + path + "'  config file no section: ", 
						"ConfigParser::open" );
				}
				size_t pos;
				if ((pos=line.find('=')) == string::npos)
					continue;
				
				String option, value;
				option = line.substr(0, pos);
				value = line.substr(pos+1);
				StringUtil::trim(option);
				StringUtil::trim(value);

				if (option.empty())
					continue;
				mSections[currentSection].insert(make_pair(option, value));
			}
		
		}
		ifConfig.close();
		return true;
	}

	bool ConfigParser::hasSection(const String& section)
	{
			SectionIterator iter = mSections.find(section);
			return iter != mSections.end();
	}

	bool ConfigParser::hasOption(const String& section, const String& option)
	{
		SectionIterator sectionIter = mSections.find(section);
		if( sectionIter == mSections.end())
			return FALSE;
		OptionIterator optionIter = sectionIter->second.find(option);
		if( optionIter == sectionIter->second.end())
			return FALSE;

		return TRUE;
	}

	// get 
	String ConfigParser::get(const String& section, const String& option)
	{
		SectionIterator sectionIter = mSections.find(section);
		if( sectionIter == mSections.end()){
			LOTUS_EXCEPT(
				Exception::ERR_ITEM_NOT_FOUND, " can't get section: "+section, 
				"ConfigParser::get" );
			return "";
		}
		OptionIterator optionIter = sectionIter->second.find(option);
		if( optionIter == sectionIter->second.end()){
			LOTUS_EXCEPT(
			Exception::ERR_ITEM_NOT_FOUND, "can't get option: "+option, 
			"ConfigParser::get" );
			return FALSE;
		}
		return optionIter->second;
	}

	int32 ConfigParser::getInt(const String& section, const String& option)
	{
		String value = get(section, option);
		return Convert::String2Int(value);
	}

	float ConfigParser::getFloat(const String& section, const String& option)
	{
		String value = get(section, option);
		return Convert::String2Float(value);
	}
	
	bool ConfigParser::getBool(const String& section, const String& option)
	{
		String value = get(section, option);
		return Convert::String2Bool(value);
	}
	
#if 0
	vector<String> ConfigParser::getSections()
	{

	}

	vector<String> ConfigParser::getOptions(const String& section)
	{

	}
#endif
	//set
	bool ConfigParser::set(const String& section, const String& option, const String& value)
	{
		return FALSE;
	}
}