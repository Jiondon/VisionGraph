//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_FILESYSTEM_H
#define AVL_FILESYSTEM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "EnumerateFilesState.h"
#include "System/FileAccessMode.h"
#include "AVLCommon/Enums/FileSortingOrder.h"

namespace avl
{


	/// <summary>Provides information about file, e.g. size, modification time</summary>
	/// <param name="inFile">Input file.</param>
	/// <param name="outSizeInKBytes">File size in kilobytes.</param>
	/// <param name="outSizeInBytes">File size in bytes.</param>
	/// <param name="outIsReadOnly">Flag indicating whether the file is read-only.</param>
	/// <param name="outAccessTime">File access time.</param>
	/// <param name="outModificationTime">File modification time.</param>
	/// <param name="outCreationTime">File creation time.</param>
	AVL_FUNCTION void FileAttributes
	(
		const atl::File&	inFile,					
		int&				outSizeInKBytes,		
		atl::int64&			outSizeInBytes,			
		bool&				outIsReadOnly,			
		atl::String&		outAccessTime,			
		atl::String&		outModificationTime,	
		atl::String&		outCreationTime			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes bytes passed as integer values to a file.</summary>
	/// <param name="inBytes">Numerical values of bytes (0-255) to write.</param>
	/// <param name="inFileAccessMode">Default value: CreateOrErase.</param>
	AVL_FUNCTION void SaveBytes_Deprecated
	(
		const atl::Array<int>&		inBytes,			
		avl::FileAccessMode::Type	inFileAccessMode,
		const atl::File&			inFile,
		bool						inIgnoreErrors
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads bytes from a file and returns them as integer values.</summary>
	/// <param name="outBytes">Numerical values of bytes (0-255) read.</param>
	AVL_FUNCTION void LoadBytes_Deprecated
	(
		const atl::File&	inFile,
		atl::Array<int>&	outBytes	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a directory tree if it does not exist.</summary>
	AVL_FUNCTION void CreateDirectories
	(
		const atl::Directory&	inDirectory,
		bool&					outSuccess
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes a directory (tree) recursively</summary>
	AVL_FUNCTION void RemoveDirectory
	(
		const atl::Directory&	inDirectory,
		bool&					outSuccess
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes files that match a pattern from a directory</summary>
	/// <param name="inMask">see FindFiles filter for inMask documentation.</param>
	AVL_FUNCTION void RemoveFiles
	(
		const atl::Directory&   inStartDirectory,
		const atl::String&	    inMask,				
		bool&				    outSuccess
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a given file is present.</summary>
	AVL_FUNCTION void TestFileExists
	(
		const atl::File&	inFile,
		bool&				outSuccess
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a given file is empty. (size is 0, contains no data)</summary>
	AVL_FUNCTION void TestFileEmpty
	(
		const atl::File&	inFile,
		bool&				outEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a given directory is present.</summary>
	AVL_FUNCTION void TestDirectoryExists
	(
		const atl::Directory&	inDirectory,
		bool&					outExists
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a given directory is empty.</summary>
	AVL_FUNCTION void TestDirectoryEmpty
	(
		const atl::Directory&	inDirectory,
		bool&					outEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns subdirectories of the input directory.</summary>
	/// <param name="inStartDirectory">Default value: \".\".</param>
	AVL_FUNCTION void FindDirectories
	(
		const atl::Directory& inStartDirectory,
		bool			 inRecursive,
		atl::Array<atl::Directory>& outDirectories,
		bool&						outFound
	)
	THROW_AVL_ERRORS;

	/// <summary>Enumerates the files present in a disk directory.</summary>
	/// <param name="inDirectory">Input directory.</param>
	/// <param name="inExtensions">Allowed extensions separated by semicolon.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="inRepeat">Determines whether to repeat reading directory after reading all files.</param>
	/// <param name="inProcessSubdirectories">Flag indicating whether to enumerate files from the subdirectories or not.</param>
	/// <param name="inInvert">Flag indicating whether to enumerate files backwards or not.</param>
	/// <param name="outFilePath">Output file path.</param>
	/// <param name="outFileName">Output file name.</param>
	AVL_FUNCTION bool EnumerateFiles
	(
		EnumerateFilesState&	ioState,
		const atl::Directory&	inDirectory,		
		const atl::String&		inExtensions,		
		avl::FileSortingOrder::Type	inSortingOrder,	
		bool					inRepeat,			
		bool					inProcessSubdirectories,	
		bool					inInvert,			
		atl::File&				outFilePath,		
		atl::String&			outFileName			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns files of the input directory.</summary>
	/// <param name="inStartDirectory">Input directory. Default value: \".\".</param>
	/// <param name="inMask">Regular expression. Default value: \"*\".</param>
	/// <param name="inSubdirs">Read subdirectories.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="outFilePaths">File paths.</param>
	/// <param name="outFileNames">File names.</param>
	AVL_FUNCTION void FindFiles
	(
		const atl::Directory&		inStartDirectory,	
		const atl::String&			inMask,				
		bool						inSubdirs, 			
		avl::FileSortingOrder::Type	inSortingOrder,		
		atl::Array<atl::File>&		outFilePaths,		
		atl::Array<atl::String>&	outFileNames,		
		bool&						outFound
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns CRC checksum of the input file.</summary>
	AVL_FUNCTION void FileChecksum
	(
		const atl::File&	inFile,
		atl::String&		outChecksum
	)
	THROW_AVL_ERRORS;

	struct GenerateFileNameState : public BaseState
	{
		int i;
	};


	/// <summary>Generates consecutive file names, e.g. for saving series of images</summary>
	/// <param name="inDirectory">Input directory. Default value: \".\".</param>
	/// <param name="inPattern">File name pattern, $ is replaced by date, # is replaced by number. Default value: \"file_$_####.txt\".</param>
	/// <param name="outFile">Generated file name.</param>
	AVL_FUNCTION void GenerateFileName
	(
		GenerateFileNameState&	ioState,
		const atl::Directory&	inDirectory,	
		const atl::String&		inPattern,		
		atl::File&				outFile			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_FILESYSTEM_H

