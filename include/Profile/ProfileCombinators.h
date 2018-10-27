//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILECOMBINATORS_H
#define AVL_PROFILECOMBINATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Profile/Profile.h"

namespace avl
{


	struct AccumulateProfileState
	{
		avl::Profile profile;
	};


	/// <summary>Computes the minimum of two profiles point by point.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MinimumProfile
	(
		const avl::Profile&		inProfile1,
		const avl::Profile&		inProfile2,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the minimum of profiles of an array.</summary>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MinimumProfile_OfArray
	(
		const atl::Array<avl::Profile>& inProfileArray,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MinimumProfile_OfLoopState : public avl::BaseState
	{
		avl::Profile stateVariable;
	};
	/// <summary>Computes the minimum of profiles appearing in consecutive iterations.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MinimumProfile_OfLoop
	(
		MinimumProfile_OfLoopState& ioState,
		const avl::Profile& inProfile,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the maximum of two profiles point by point.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MaximumProfile
	(
		const avl::Profile&		inProfile1,
		const avl::Profile&		inProfile2,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the maximum of profiles of an array.</summary>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MaximumProfile_OfArray
	(
		const atl::Array<avl::Profile>& inProfileArray,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MaximumProfile_OfLoopState : public avl::BaseState
	{
		avl::Profile stateVariable;
	};
	/// <summary>Computes the maximum of profiles appearing in consecutive iterations.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MaximumProfile_OfLoop
	(
		MaximumProfile_OfLoopState& ioState,
		const avl::Profile& inProfile,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds two profiles value by value.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AddProfiles
	(
		const avl::Profile&		inProfile1,
		const avl::Profile&		inProfile2,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds profiles of an array value by value.</summary>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AddProfiles_OfArray
	(
		const atl::Array<avl::Profile>& inProfileArray,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct AddProfiles_OfLoopState : public avl::BaseState
	{
		avl::Profile stateVariable;
	};
	/// <summary>Adds profiles appearing in consecutive iterations value by value.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AddProfiles_OfLoop
	(
		AddProfiles_OfLoopState& ioState,
		const avl::Profile& inProfile,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtracts two profiles value by value.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void SubtractProfiles
	(
		const avl::Profile&		inProfile1,
		const avl::Profile&		inProfile2,
		avl::Profile&			outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies two profiles value by value.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MultiplyProfiles
	(
		const avl::Profile&	inProfile1,
		const avl::Profile&	inProfile2,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies profiles of an array value by value.</summary>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MultiplyProfiles_OfArray
	(
		const atl::Array<avl::Profile>& inProfileArray,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MultiplyProfiles_OfLoopState : public avl::BaseState
	{
		avl::Profile stateVariable;
	};
	/// <summary>Multiplies profiles appearing in consecutive iterations value by value.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void MultiplyProfiles_OfLoop
	(
		MultiplyProfiles_OfLoopState& ioState,
		const avl::Profile& inProfile,
		avl::Profile& outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides two profiles value by value.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void DivideProfiles
	(
		const avl::Profile&	inProfile1,
		const avl::Profile&	inProfile2,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes profile representing difference between corresponding values of given profiles.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void DifferenceProfile
	(
		const avl::Profile&	inProfile1,
		const avl::Profile&	inProfile2,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Concatenates two profiles into one.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void JoinProfiles
	(
		const avl::Profile&	inProfile1,
		const avl::Profile&	inProfile2,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a profile of most recent values.</summary>
	/// <param name="inMaxCount">Number of last values that are remembered. Default value: atl::NIL.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AccumulateProfile
	(
		AccumulateProfileState&			ioState,
		const float&				inValue,
		atl::Optional<int>				inMaxCount,		
		avl::Profile&					outProfile
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILECOMBINATORS_H

