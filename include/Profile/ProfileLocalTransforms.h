//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILELOCALTRANSFORMS_H
#define AVL_PROFILELOCALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Profile/Profile.h"

namespace avl
{


	namespace DifferentiationMethod
	{
		enum Type
		{
			Forward,
			Backward,
			Central
		};
	}


	/// <summary>Computes the derivative of a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inCyclic">Defines whether to compute differences between first and last elements.</param>
	/// <param name="inDifferentiationMethod">Default value: Central.</param>
	AVL_FUNCTION void DifferentiateProfile
	(
		const avl::Profile&					inProfile,
		const bool							inCyclic,					
		avl::DifferentiationMethod::Type	inDifferentiationMethod,
		avl::Profile&						outDerivative
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths a profile by averaging points within a kernel.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inKernelRadius">Defines the width of the kernel as '2 * inKernelRadius + 1'. Default value: 3.</param>
	/// <param name="inCyclic">Defines whether the first element should be considered adjacent to the last element.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void SmoothProfile_Mean
	(
		const avl::Profile&	inProfile,
		const int			inKernelRadius,		
		const bool			inCyclic,			
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths a profile by averaging points within a kernel using gaussian-weighted average.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inStdDev">Standard deviation of the gaussian kernel. Default value: 0.6f.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 3.0f.</param>
	/// <param name="inCyclic">Defines whether the first element should be considered adjacent to the last element.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void SmoothProfile_Gauss
	(
		const avl::Profile&	inProfile,
		const float		inStdDev,				
		const float		inKernelRelativeSize,	
		const bool			inCyclic,				
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies a user-defined convolution to a profile.</summary>
	/// <param name="inProfile">Profile to be processed.</param>
	/// <param name="inMask">Convolution kernel mask that will be applied to the profile.</param>
	/// <param name="inNormalizeMaskValues">If set to true, the kernel mask will be normalized so that its values sum up to one. Default value: False.</param>
	/// <param name="inMaskOrigin">Index of the kernel mask element that will be aligned against the profile values. Default value: atl::NIL.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void ConvolveProfile
	(
		const avl::Profile&				inProfile,		
		const atl::Array<float>&	inMask,			
		bool							inNormalizeMaskValues,	
		atl::Optional<int>				inMaskOrigin,	
		avl::Profile&					outProfile		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes a profile by choosing minimum point within a kernel.</summary>
	/// <param name="inProfile">Profile to be processed.</param>
	/// <param name="inKernelRadius">Defines the width of the kernel as '2 * inKernelRadius + 1'. Default value: 3.</param>
	/// <param name="inCyclic">Defines whether the first element should be considered adjacent to the last element.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void ErodeProfile
	(
		const avl::Profile&	inProfile,		
		const int			inKernelRadius,	
		const bool			inCyclic,		
		avl::Profile&		outProfile		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes a profile by choosing maximum point within a kernel.</summary>
	/// <param name="inProfile">Profile to be processed.</param>
	/// <param name="inKernelRadius">Defines the width of the kernel as '2 * inKernelRadius + 1'. Default value: 3.</param>
	/// <param name="inCyclic">Defines whether the first element should be considered adjacent to the last element.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void DilateProfile
	(
		const avl::Profile&	inProfile,		
		const int			inKernelRadius,	
		const bool			inCyclic,		
		avl::Profile&		outProfile		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILELOCALTRANSFORMS_H

