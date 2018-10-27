//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_FORMAT_H
#define AVL_FORMAT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "Geometry/Geometry.h"
#include "Geometry3D/Geometry3D.h"
#include "Basic/Types.h"

namespace avl
{


	/// <summary>Converts a location to a string of format "(X, Y)".</summary>
	/// <param name="inDigitCount">How many characters the output coordinate should have at least.</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the signs of the coordinates even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="inSystemBase">The base of the numeral system. Default value: 10.</param>
	/// <param name="inPrintBrackets">Determines whether the brackets should be printed or not. Default value: True.</param>
	AVL_FUNCTION void FormatLocationToString
	(
		const avl::Location&	inLocation,
		const int				inDigitCount,		
		const atl::String&		inTrailingCharacter,
		const bool				inForceSignPrinting,
		const atl::String&		inSuffix,			
		const int				inSystemBase,		
		const bool				inPrintBrackets,	
		atl::String&			outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a 2D point to a string of format "(X, Y)".</summary>
	/// <param name="inIntegerDigitCount">How many characters the integer part of the coordinates should have at least.</param>
	/// <param name="inFractionalDigitCount">How many characters the fractional part of the coordinates should have. Default value: 3.</param>
	/// <param name="inDecimalMark">The symbol used to separate the integer part from the fractional part of the coordinates. Default value: \".\".</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the signs of the numbers even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="inPrintBrackets">Determines whether the brackets should be printed or not. Default value: True.</param>
	AVL_FUNCTION void FormatPoint2DToString
	(
		const avl::Point2D&		inPoint,
		const int				inIntegerDigitCount,	
		const int				inFractionalDigitCount,	
		const atl::String&		inDecimalMark,		
		const atl::String&		inTrailingCharacter,
		const bool				inForceSignPrinting,
		const atl::String&		inSuffix,			
		const bool				inPrintBrackets,	
		atl::String&			outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a 3D point to a string of format "(X, Y, Z)".</summary>
	/// <param name="inIntegerDigitCount">How many characters the integer part of the coordinates should have at least.</param>
	/// <param name="inFractionalDigitCount">How many characters the fractional part of the coordinates should have. Default value: 3.</param>
	/// <param name="inDecimalMark">The symbol used to separate the integer part from the fractional part of the coordinates. Default value: \".\".</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the signs of the numbers even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="inPrintBrackets">Determines whether the brackets should be printed or not. Default value: True.</param>
	AVL_FUNCTION void FormatPoint3DToString
	(
		const avl::Point3D&		inPoint,
		const int				inIntegerDigitCount,	
		const int				inFractionalDigitCount,	
		const atl::String&		inDecimalMark,		
		const atl::String&		inTrailingCharacter,
		const bool				inForceSignPrinting,
		const atl::String&		inSuffix,			
		const bool				inPrintBrackets,	
		atl::String&			outString
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_FORMAT_H

