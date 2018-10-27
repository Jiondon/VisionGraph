//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ENUMERATE_FILES_STATE_H
#define ENUMERATE_FILES_STATE_H

#include "ATL/Array.h"
#include "ATL/AtlTypes.h"
#include "ATL/AtlString.h"
#include "AVLCommon/BaseState.h"
#include "AVLCommon/Enums/FileSortingOrder.h"

namespace avl
{

	struct FileEnumItem
	{
		atl::String path;
		atl::String name;
		atl::String ext;
		atl::uint64 size;
		atl::uint64 date;
	};

	struct EnumerateFilesState : public BaseState
	{
		atl::String directory;
		atl::String extensions;
		avl::FileSortingOrder::Type sortingOrder;
		bool processSubdirectories;

		atl::Array<FileEnumItem> enumeratedFiles;
		int currentIndex;
	};

}


#endif // ENUMERATE_FILES_STATE_H