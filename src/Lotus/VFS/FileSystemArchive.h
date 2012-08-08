/********************************************************************
	created:	2012/08/07 
	filename: 	FileSystemArchive.h
	author:		reedhong 
	
	purpose:	基本的文件路径操作， 裁剪自Ogre
*********************************************************************/

#ifndef __Lotus_FileSystemArchive_H__
#define __Lotus_FileSystemArchive_H__

#include "Archive.h"

namespace Lotus {
	class FileSystemArchive: public Archive 
	{
 protected:
        /** Utility method to retrieve all files in a directory matching pattern.
        @param pattern File pattern
        @param recursive Whether to cascade down directories
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @param simpleList Populated if retrieving a simple list
        @param detailList Populated if retrieving a detailed list
        @param currentDir The current directory relative to the base of the 
            archive, for file naming
        */
        void findFiles(const String& pattern, bool recursive, bool dirs,
            StringVector* simpleList, FileInfoList* detailList) const;

		OGRE_AUTO_MUTEX
    public:
        FileSystemArchive(const String& name, const String& archType );
        ~FileSystemArchive();

        /// @copydoc Archive::isCaseSensitive
        bool isCaseSensitive(void) const;

        /// @copydoc Archive::load
        void load();
        /// @copydoc Archive::unload
        void unload();

        /// @copydoc Archive::open
        DataStreamPtr open(const String& filename, bool readOnly = true) const;

		/// @copydoc Archive::create
		DataStreamPtr create(const String& filename) const;

		/// @copydoc Archive::delete
		void remove(const String& filename) const;

		/// @copydoc Archive::list
        StringVectorPtr list(bool recursive = true, bool dirs = false);

        /// @copydoc Archive::listFileInfo
        FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);

        /// @copydoc Archive::find
        StringVectorPtr find(const String& pattern, bool recursive = true,
            bool dirs = false);

        /// @copydoc Archive::findFileInfo
        FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
            bool dirs = false) const;

        /// @copydoc Archive::exists
        bool exists(const String& filename);

		/// @copydoc Archive::getModifiedTime
		time_t getModifiedTime(const String& filename);

		/// Set whether filesystem enumeration will include hidden files or not.
		/// This should be called prior to declaring and/or initializing filesystem
		/// resource locations. The default is true (ignore hidden files).
		static void setIgnoreHidden(bool ignore)
		{
			msIgnoreHidden = ignore;
		}

		/// Get whether hidden files are ignored during filesystem enumeration.
		static bool getIgnoreHidden()
		{
			return msIgnoreHidden;
		}

		static bool msIgnoreHidden;

	}; // end FileSystemArchive
} // end Lotus


#endif

