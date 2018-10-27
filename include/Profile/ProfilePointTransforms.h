//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILEPOINTTRANSFORMS_H
#define AVL_PROFILEPOINTTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Adds a scalar value to each element of a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AddToProfile
	(
		const avl::Profile&		inProfile,
		float				inValue,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtracts a scalar value from each element of a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void SubtractFromProfile
	(
		const avl::Profile&		inProfile,
		float				inValue,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each profile value to its negation.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void NegateProfile
	(
		const avl::Profile&		inProfile,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies each element of a profile by a scalar value.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inValue">Default value: 2.0f.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MultiplyProfile
	(
		const avl::Profile&	inProfile,
		float				inValue,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides each element of a profile by a scalar value.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inValue">Default value: 2.0f.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void DivideProfile
	(
		const avl::Profile&	inProfile,
		float				inValue,	
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each profile value to its absolute value.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AbsoluteProfile
	(
		const avl::Profile&		inProfile,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies linear transformation to profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inA">Value multiplied. Default value: 1.0f.</param>
	/// <param name="inB">Value added. Default value: 0.0f.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void RescaleProfile
	(
		const avl::Profile&	inProfile,
		float				inA,		
		float				inB,		
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILEPOINTTRANSFORMS_H

