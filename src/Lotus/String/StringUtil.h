/*
 * 字符串相关的一些功能函数, 怀念python中一些丰富的接口，此处模仿之
 * 部分的实现学习Ogre
 * create by reedhong 2012.07.22
 */

#ifndef __String_Util_H__
#define __String_Util_H__

#include <vector>
using namespace std;
#include "Platform/Platform.h"

namespace Lotus
{
	class StringUtil
	{
public:
		//typedef StringStream StrStreamType;

        /** Removes any whitespace characters, be it standard space or
            TABs and so on.
            @remarks
                The user may specify wether they want to trim only the
                beginning or the end of the String ( the default action is
                to trim both).
        */
        static void trim( String& str, bool left = true, bool right = true );

        /** Returns a StringVector that contains all the substrings delimited
            by the characters in the passed <code>delims</code> argument.
            @param
                delims A list of delimiter characters to split by
            @param
                maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
                parameters is > 0, the splitting process will stop after this many splits, left to right.
            @param
                preserveDelims Flag to determine if delimiters should be saved as substrings
        */
		static vector<String> split( const String& str, const String& delims = "\t\n ", unsigned int maxSplits = 0, bool preserveDelims = false);

		/** Returns a StringVector that contains all the substrings delimited
            by the characters in the passed <code>delims</code> argument, 
			or in the <code>doubleDelims</code> argument, which is used to include (normal) 
			delimeters in the tokenised string. For example, "strings like this".
            @param
                delims A list of delimiter characters to split by
			@param
                delims A list of double delimeters characters to tokenise by
            @param
                maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
                parameters is > 0, the splitting process will stop after this many splits, left to right.
        */
		static vector<String> tokenise( const String& str, const String& delims = "\t\n ", const String& doubleDelims = "\"", unsigned int maxSplits = 0);

		/** Lower-cases all the characters in the string.
        */
        static void toLowerCase( String& str );

        /** Upper-cases all the characters in the string.
        */
        static void toUpperCase( String& str );


        /** Returns whether the string begins with the pattern passed in.
        @param pattern The pattern to compare with.
        @param lowerCase If true, the start of the string will be lower cased before
            comparison, pattern should also be in lower case.
        */
        static bool startsWith(const String& str, const String& pattern, bool lowerCase = true);

        /** Returns whether the string ends with the pattern passed in.
        @param pattern The pattern to compare with.
        @param lowerCase If true, the end of the string will be lower cased before
            comparison, pattern should also be in lower case.
        */
        static bool endsWith(const String& str, const String& pattern, bool lowerCase = true);

        /** Method for standardising paths - use forward slashes only, end with slash.
        */
        static String standardisePath( const String &init);
		/** Returns a normalized version of a file path
		This method can be used to make file path strings which point to the same directory  
		but have different texts to be normalized to the same text. The function:
		- Transforms all backward slashes to forward slashes.
		- Removes repeating slashes.
		- Removes initial slashes from the beginning of the path.
		- Removes ".\" and "..\" meta directories.
		- Sets all characters to lowercase (if requested)
		@param init The file path to normalize.
		@param makeLowerCase If true, transforms all characters in the string to lowercase.
		*/
       static String normalizeFilePath(const String& init, bool makeLowerCase = true);


        /** Method for splitting a fully qualified filename into the base name
            and path.
        @remarks
            Path is standardised as in standardisePath
        */
        static void splitFilename(const String& qualifiedName,
            String& outBasename, String& outPath);

		/** Method for splitting a fully qualified filename into the base name,
		extension and path.
		@remarks
		Path is standardised as in standardisePath
		*/
		static void splitFullFilename(const String& qualifiedName, 
			String& outBasename, String& outExtention, 
			String& outPath);

		/** Method for splitting a filename into the base name
		and extension.
		*/
		static void splitBaseFilename(const String& fullName, 
			String& outBasename, String& outExtention);


        /** Simple pattern-matching routine allowing a wildcard pattern.
        @param str String to test
        @param pattern Pattern to match against; can include simple '*' wildcards
        @param caseSensitive Whether the match is case sensitive or not
        */
        static bool match(const String& str, const String& pattern, bool caseSensitive = true);


		/** replace all instances of a sub-string with a another sub-string.
		@param source Source string
		@param replaceWhat Sub-string to find and replace
		@param replaceWithWhat Sub-string to replace with (the new sub-string)
		@return An updated string with the sub-string replaced
		*/
		static const String replaceAll(const String& source, const String& replaceWhat, const String& replaceWithWhat);

        /// Constant blank string, useful for returning by ref where local does not exist
        static const String BLANK;
	};
}

#endif