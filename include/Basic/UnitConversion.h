//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_UNITCONVERSION_H
#define AVL_UNITCONVERSION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"

namespace avl
{


	/// <summary>Converts radians to degrees.</summary>
	AVL_FUNCTION void RadiansToDegrees
	(
		float inRadians,
		float& outDegrees
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts degrees to radians.</summary>
	AVL_FUNCTION void DegreesToRadians
	(
		float inDegrees,
		float& outRadians
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a length in pixels to millimetres using the given scale [px / mm].</summary>
	/// <param name="inScale">px / mm.</param>
	AVL_FUNCTION void PixelsToMillimetres
	(
		float inPixels,
		float inScale, 
		float& outMillimetres
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a length in millimetres to pixels using the given scale [px / mm].</summary>
	/// <param name="inScale">px / mm.</param>
	AVL_FUNCTION void MillimetresToPixels
	(
		float inMillimetres,
		float inScale, 
		float& outPixels
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_UNITCONVERSION_H

