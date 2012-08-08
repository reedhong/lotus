/*
 * ²Ã¼ô×ÔOgre
 * created by reedhong 2012.07.23
 */
#ifndef __Lotus_Archive_H__
#define __Lotus_Archive_H__

#include "Platform/Platform.h"
#include "Stream.h"
#include "Exception/Exception.h"

namespace Lotus {

	struct FileInfo {
		/// The archive in which the file has been found (for info when performing
		/// multi-Archive searches, note you should still open through ResourceGroupManager)
		const Archive* archive;
		/// The file's fully qualified name
		String filename;
		/// Path name; separated by '/' and ending with '/'
		String path;
		/// Base filename
		String basename;
		/// Compressed size
		size_t compressedSize;
		/// Uncompressed size
		size_t uncompressedSize;
	};

	typedef vector<FileInfo> FileInfoList;
	typedef SharedPtr<FileInfoList> FileInfoListPtr;

	class Archive
	{
 protected:
        /// Archive name
        String mName; 
        /// Archive type code
        String mType;
		/// Read-only flag
		bool mReadOnly;
    public:


        /** Constructor - don't call direct, used by ArchiveFactory.
        */
        Archive( const String& name, const String& archType )
            : mName(name), mType(archType), mReadOnly(true) {}

        /** Default destructor.
        */
        virtual ~Archive() {}

		/// Get the name of this archive
		const String& getName(void) const { return mName; }

        /// Returns whether this archive is case sensitive in the way it matches files
        virtual bool isCaseSensitive(void) const = 0;

        /** Loads the archive.
        @remarks
            This initializes all the internal data of the class.
        @warning
            Do not call this function directly, it is meant to be used
            only by the ArchiveManager class.
        */
        virtual void load() = 0;

        /** Unloads the archive.
        @warning
            Do not call this function directly, it is meant to be used
            only by the ArchiveManager class.
        */
        virtual void unload() = 0;

		/** Reports whether this Archive is read-only, or whether the contents
			can be updated. 
		*/
		virtual bool isReadOnly() const { return mReadOnly; }

        /** Open a stream on a given file. 
        @note
            There is no equivalent 'close' method; the returned stream
            controls the lifecycle of this file operation.
        @param filename The fully qualified name of the file
		@param readOnly Whether to open the file in read-only mode or not (note, 
			if the archive is read-only then this cannot be set to false)
        @return A shared pointer to a DataStream which can be used to 
            read / write the file. If the file is not present, returns a null
			shared pointer.
        */
        virtual StreamPtr open(const String& filename, bool readOnly = true) const = 0;

		/** Create a new file (or overwrite one already there). 
		@note If the archive is read-only then this method will fail.
		@param filename The fully qualified name of the file
		@return A shared pointer to a DataStream which can be used to 
		read / write the file. 
		*/
		virtual StreamPtr create(const String& filename) const
		{
                        (void)filename;
			LOTUS_EXCEPT(Exception::ERR_NOT_IMPLEMENTED, 
				"This archive does not support creation of files.", 
				"Archive::create");
		}

		/** Delete a named file.
		@remarks Not possible on read-only archives
		@param filename The fully qualified name of the file
		*/
		virtual void remove(const String& filename) const
		{
                        (void)filename;
			LOTUS_EXCEPT(Exception::ERR_NOT_IMPLEMENTED, 
				"This archive does not support removal of files.", 
				"Archive::remove");
		}

        /** List all file names in the archive.
        @note
            This method only returns filenames, you can also retrieve other
            information using listFileInfo.
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @return A list of filenames matching the criteria, all are fully qualified
        */
        virtual SharedPtr<vector<String>> list(bool recursive = true, bool dirs = false) = 0;
        
        /** List all files in the archive with accompanying information.
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @return A list of structures detailing quite a lot of information about
            all the files in the archive.
        */
        virtual FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false) = 0;

        /** Find all file or directory names matching a given pattern
            in this archive.
        @note
            This method only returns filenames, you can also retrieve other
            information using findFileInfo.
        @param pattern The pattern to search for; wildcards (*) are allowed
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @return A list of filenames matching the criteria, all are fully qualified
        */
        virtual SharedPtr<vector<String>> find(const String& pattern, bool recursive = true,
            bool dirs = false) = 0;

        /** Find out if the named file exists (note: fully qualified filename required) */
        virtual bool exists(const String& filename) = 0; 

		/** Retrieve the modification time of a given file */
		virtual time_t getModifiedTime(const String& filename) = 0; 


        /** Find all files or directories matching a given pattern in this
            archive and get some detailed information about them.
        @param pattern The pattern to search for; wildcards (*) are allowed
        @param recursive Whether all paths of the archive are searched (if the 
        archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @return A list of file information structures for all files matching 
            the criteria.
        */
        virtual FileInfoListPtr findFileInfo(const String& pattern, 
            bool recursive = true, bool dirs = false) const = 0;

        /// Return the type code of this Archive
        const String& getType(void) const { return mType; }
	};
}

#endif
