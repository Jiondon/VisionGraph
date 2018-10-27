//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_EXIF_H
#define AVL_EXIF_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "ATL/Array.hxx"

namespace avl
{


	/// <summary>Reads an EXIF informations from the JPG image.</summary>
	/// <param name="inFile">Path to the JPG file.</param>
	/// <param name="outDateTime">Date time when image was taken.</param>
	/// <param name="outDescription">Additional image description.</param>
	/// <param name="outOrientation">Image orientation.</param>
	/// <param name="outValues">Values of all EXIF tags.</param>
	/// <param name="outLabels">Names of all EXIF tags.</param>
	AVL_FUNCTION void EXIF_LoadFromJpgFile
	(
		const atl::File&				inFile,					
		atl::String&					outDateTime,			
		atl::String&					outDescription,			
		atl::String&					outOrientation,			
		atl::Array<atl::String>&		outValues,				
		atl::Array<atl::String>&		outLabels				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_EXIF_H

