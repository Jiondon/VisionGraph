//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ASSERTIONS_H
#define AVL_ASSERTIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"
#include "Conversions/STDConversions.h"

namespace avl
{


	AVL_FUNCTION void AssertIntegerEqualTo
	(
		const int			inValue,
		const int			inExpectedValue,
		const atl::String&	inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertIntegerInRange
	(
		const int			inValue,
		atl::Optional<int>	inMinimum,
		atl::Optional<int>	inMaximum,
		const atl::String&	inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertBoolEqualTo
	(
		bool				inValue,
		bool				inExpectedValue,
		const atl::String&	inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertTrue
	(
		const bool			inValue,
		const atl::String&	inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertFalse
	(
		const bool			inValue,
		const atl::String&	inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertRealEqualTo
	(
		const float&	inValue,
		const float&	inExpectedValue,
		const atl::String&	inDescription,
		const float&	inEpsilon = 1.0f,		
		const int&			inEpsilonScale = -6
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertRealInRange
	(
		const float&		inValue,
		atl::Optional<float>	inMinimum,
		atl::Optional<float>	inMaximum,
		const atl::String&		inDescription
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void AssertStringEqualTo
	(
		const atl::String&	inString,
		const atl::String&	inExpectedString,
		const atl::String&	inDescription,
		const bool			inIgnoreCase, 
		const bool			inTrimWhitespace
	)
	THROW_AVL_ERRORS;

	/// Asserts that an object is equal to the expected one.
	template <typename Type>
	void AssertObjectEqualTo
	(
		const Type&			inObject,
		const Type&			inExpectedObject,
		const atl::String&	inDescription
	)
	{
		if (!(inObject == inExpectedObject))
		{
			atl::String message = "Assertion failed";
			
			if (!inDescription.Empty())
			{
				message += " (";
				message += inDescription;
				message += ")";
			}

			throw atl::AssertionError(message + ".");
		}
	}

	/// Asserts that an object is not equal to the expected one.
	template <typename Type>
	void AssertObjectNotEqualTo
	(
		const Type&			inObject,
		const Type&			inExpectedObject,
		const atl::String&	inDescription
	)
	{
		if (inObject == inExpectedObject)
		{
			atl::String message = "Assertion failed";
			
			if (!inDescription.Empty())
			{
				message += " (";
				message += inDescription;
				message += ")";
			}

			throw atl::AssertionError(message + ".");
		}
	}

	/// Asserts that an object is not Nil.
	template <typename Type>
	void AssertObjectNotNil
	(
		const typename atl::ToConditionalType<const Type&>::Type& inObject,
		const atl::String&	inDescription
	)
	{
		if (inObject == atl::NIL)
		{
			atl::String message = "Assertion failed";
			if (!inDescription.Empty())
			{
				message += " (";
				message += inDescription;
				message += ")";
			}
			message += ".";

			throw atl::AssertionError(message);
		}
	}

	/// Asserts that an object is Nil.
	template <typename Type>
	void AssertObjectNil
	(
		const typename atl::ToConditionalType<const Type&>::Type& inObject,
		const atl::String&	inDescription
	)
	{
		if (inObject != atl::NIL)
		{
			atl::String message = "Assertion failed";
			if (!inDescription.Empty())
			{
				message += " (";
				message += inDescription;
				message += ")";
			}
			message += ".";

			throw atl::AssertionError(message);
		}
	}

	/// Asserts that an array has expected size.
	template <typename Type>
	void AssertArraySizeEqualTo
	(
		const atl::Array<Type>&	inArray,
		const int				inReferenceSize,
		const atl::String&		inDescription
	)
	{
		if (inArray.Size() != inReferenceSize)
		{
			atl::String actual, expected;
			
			IntegerToString(inArray.Size(), actual);
			IntegerToString(inReferenceSize, expected);

			atl::String msg = "Assertion failed. ";
			msg += "Expected array size: " + expected + ". Actual array size: " + actual;

			if (!inDescription.Empty())
			{
				msg += "(" + inDescription + ")";
			}
			msg += ".";

			throw atl::AssertionError(msg);
		}
	}

} // namespace avl

#endif // AVL_ASSERTIONS_H

