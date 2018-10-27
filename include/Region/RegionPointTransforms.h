//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONPOINTTRANSFORMS_H
#define AVL_REGIONPOINTTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Computes a region of pixels not contained in the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionComplement
	(
		const avl::Region& inRegion,
		avl::Region& outRegion 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONPOINTTRANSFORMS_H

