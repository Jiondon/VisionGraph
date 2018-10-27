//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILESPATIALTRANSFORMS_H
#define AVL_PROFILESPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Confines a profile to its continuous subsequence.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inStart">Index of the first element of the input profile that will be included in the output profile.</param>
	/// <param name="inLength">Length of the output profile. Default value: atl::NIL.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void CropProfile
	(
		const avl::Profile&			inProfile,
		const int					inStart,	
		atl::Optional<const int&>	inLength,	
		avl::Profile&				outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Extends the profile by adding zeros at the beginning and at the end.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inStart">Same as in CropProfile.</param>
	/// <param name="inLength">Length of the output profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void UncropProfile
	(
		const avl::Profile&			inProfile,
		int							inStart,	
		int							inLength,	
		avl::Profile&				outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves the last element ahead of the first one (inShift times).</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inShift">Default value: 0.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void RotateProfile
	(
		const avl::Profile&	inProfile,
		const int			inShift,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Reduces the length of the profile by averaging its elements.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inN">The scaling coefficient. Default value: 2.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void ShrinkProfileNTimes
	(
		const avl::Profile&	inProfile,
		const int			inN,		
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	namespace ResizeProfileInterpolation
	{
		enum Type
		{
			NearestNeighbour,
			Linear
		};
	}


	/// <summary>Changes the size of a profile, preserving its shape.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inNewSize">Default value: 1.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void ResizeProfile
	(
		const avl::Profile&						inProfile,
		const int&								inNewSize,
		avl::ResizeProfileInterpolation::Type	inInterpolation,
		avl::Profile&							outProfile
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILESPATIALTRANSFORMS_H

