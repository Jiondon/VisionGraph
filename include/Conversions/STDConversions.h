//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_STDCONVERSIONS_H
#define AVL_STDCONVERSIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"

namespace avl
{


	/// <summary>Converts an integer to a real number.</summary>
	AVL_FUNCTION void IntegerToReal
	(
		int inInteger,
		float& outReal
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an integer to a double number.</summary>
	AVL_FUNCTION void IntegerToDouble
	(
		int inInteger,
		double& outDouble
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a long to a double number.</summary>
	AVL_FUNCTION void LongToDouble
	(
		const atl::int64&	inLong,
		double&		outDouble
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a real number to an integer.</summary>
	AVL_FUNCTION void RealToInteger
	(
		float inReal,
		int& outInteger
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an integer to a string.</summary>
	AVL_FUNCTION void IntegerToString
	(
		int inInteger,
		atl::String& outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a long to a string.</summary>
	AVL_FUNCTION void LongToString
	(
		const atl::int64&	inLong,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a real number to a string.</summary>
	AVL_FUNCTION void RealToString
	(
		float		inReal,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a double number to a string.</summary>
	AVL_FUNCTION void DoubleToString
	(
		const double&	inDouble,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a boolean value to a string.</summary>
	AVL_FUNCTION void BoolToString
	(
		bool inBool,
		atl::String& outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of integer numbers to an array of real numbers.</summary>
	AVL_FUNCTION void IntegerArrayToRealArray
	(
		const atl::Array<int>& inIntegerArray,
		atl::Array<float>& outRealArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of real numbers to an array of integer numbers.</summary>
	AVL_FUNCTION void RealArrayToIntegerArray
	(
		const atl::Array<float>& inRealArray,
		atl::Array<int>& outIntegerArray 
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a file path to a string.</summary>
	AVL_FUNCTION void FileToString
	(
		const atl::File& inFile,
		atl::String& outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a file path.</summary>
	AVL_FUNCTION void StringToFile
	(
		const atl::String& inString,
		atl::File& outFile
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a directory path to a string.</summary>
	AVL_FUNCTION void DirectoryToString
	(
		const atl::Directory& inDirectory,
		atl::String& outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a directory path.</summary>
	AVL_FUNCTION void StringToDirectory
	(
		const atl::String& inString,
		atl::Directory& outDirectory
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an Integer to Long</summary>
	AVL_FUNCTION void IntegerToLong
	(
		const int&	inInteger,
		atl::int64& outLong
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a Real to Double</summary>
	AVL_FUNCTION void RealToDouble
	(
		const float&	inReal,
		double&		outDouble
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a Long to Integer</summary>
	AVL_FUNCTION void LongToInteger
	(
		atl::int64		inLong,
		int&			outInteger
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a Double to Real</summary>
	AVL_FUNCTION void DoubleToReal
	(
		const double&	inDouble,
		float&			outReal
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_STDCONVERSIONS_H

