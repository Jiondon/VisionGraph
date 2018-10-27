//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DEBUG_PREVIEW_WINDOWS_H
#define AVL_DEBUG_PREVIEW_WINDOWS_H


#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "Region/Region.h"
#include "AVLCommon/Config.h"

namespace avl
{
	struct DebugPreviewWindowState;


	// Shows image in separated window. When called first time creates new window with size fit to image.
	AVL_FUNCTION bool DebugPreviewShowImage
	(
		DebugPreviewWindowState&	ioState,
		const Image&				inImage,
		const wchar_t*				inWindowName = L"Image Preview",
		int							inPosX = -1,
		int							inPosY = -1
	) THROW_AVL_ERRORS;

	// Creates new separated window and shows image in it. DebugPreviewCloseAllWindows need to be called
	// to free resources reserved by this function.
	AVL_FUNCTION void DebugPreviewShowNewImage
	(
		const Image&				inImage,
		const wchar_t*				inWindowName = L"Image Preview",
		int							inPosX = -1,
		int							inPosY = -1
	) THROW_AVL_ERRORS;

	// Shows region in separated window. When called first time creates new window with size fit to region.
	AVL_FUNCTION bool DebugPreviewShowRegion
	(
		DebugPreviewWindowState&	ioState,
		const Region&				inRegion,
		const wchar_t*				inWindowName = L"Region Preview",
		int							inPosX = -1,
		int							inPosY = -1
	) THROW_AVL_ERRORS;

	// Creates new separated window and shows region in it. DebugPreviewCloseAllWindows need to be called
	// to free resources reserved by this function.
	AVL_FUNCTION void DebugPreviewShowNewRegion
	(
		const Region&				inRegion,
		const wchar_t*				inWindowName = L"Region Preview",
		int							inPosX = -1,
		int							inPosY = -1
	) THROW_AVL_ERRORS;


	// Closes all active debug preview windows and terminates preview window subsystem.
	AVL_FUNCTION void DebugPreviewCloseAllWindows( void ) THROW_AVL_ERRORS;

	// Waits until user closes all active debug windows.
	AVL_FUNCTION void DebugPreviewWaitForWindowsClose( void ) THROW_AVL_ERRORS;

	// Waits until user closes any of active debug windows.
	AVL_FUNCTION void DebugPreviewWaitForAnyWindowClose( void ) THROW_AVL_ERRORS;

	// Closes debug preview window.
	AVL_FUNCTION void DebugPreviewCloseWindow( DebugPreviewWindowState& ioWindow ) THROW_AVL_ERRORS;


	struct DebugPreviewWindowState
	{
		int index;

		DebugPreviewWindowState() : index(-1)
		{
		}

		~DebugPreviewWindowState()
		{
			DebugPreviewCloseWindow(*this);
		}
	};
}


#endif // AVL_DEBUG_PREVIEW_WINDOWS_H
