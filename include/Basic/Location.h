//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_LOCATION_H
#define AVS_LOCATION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Basic/Types.h"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Returns the center point of a pixel indicated by the provided location.</summary>
	/// <param name="inLocation">Pixel location.</param>
	/// <param name="outCenter">Center point of the provided pixel.</param>
	AVL_FUNCTION void LocationCenter
	(
		const avl::Location&	inLocation,		
		avl::Point2D&			outCenter		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns corners of a location.</summary>
	AVL_FUNCTION void LocationCorners_Deprecated
	(
		const avl::Location&	inLocation,
		avl::Point2D&			outTopLeftCorner,
		avl::Point2D&			outTopRightCorner,
		avl::Point2D&			outBottomRightCorner,
		avl::Point2D&			outBottomLeftCorner
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a Location by given number of pixels along each axis</summary>
	/// <param name="inLocation">Input location.</param>
	/// <param name="inDeltaX">Shift along the x axis.</param>
	/// <param name="inDeltaY">Shift along the y axis.</param>
	/// <param name="inInverse">Switches to inverse operation.</param>
	/// <param name="outLocation">Shifted location.</param>
	AVL_FUNCTION void TranslateLocation
	(
		const avl::Location&	inLocation,		
		int						inDeltaX,		
		int						inDeltaY,		
		bool					inInverse,		
		avl::Location&			outLocation		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a location structure from individual fields.</summary>
	/// <param name="inX">Input x-coordinate.</param>
	/// <param name="inY">Input y-coordinate.</param>
	/// <param name="outLocation">Output location.</param>
	AVL_FUNCTION void AvsFilter_MakeLocation
	(
		int				inX,		
		int				inY,		
		avl::Location&	outLocation	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of location.</summary>
	/// <param name="inLocation">Input location.</param>
	/// <param name="outX">Output x-coordinate.</param>
	/// <param name="outY">Output y-coordinate.</param>
	AVL_FUNCTION void AvsFilter_AccessLocation
	(
		const avl::Location&	inLocation,	
		int&					outX,		
		int&					outY		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_LOCATION_H

