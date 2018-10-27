//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_PROFILEBASICS_H
#define AVS_PROFILEBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "Profile/Profile.h"
#include "Enums/ProfileInterpolationMethod.h"

namespace avl
{


	/// <summary>Sets the offset and the scale of a profile in the X axis.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inXOffset">Default value: 0.0f.</param>
	/// <param name="inXScale">Default value: 1.0f.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void SetProfileXTransform
	(
		const avl::Profile&	inProfile,
		float				inXOffset,
		float				inXScale,
		avl::Profile&		outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a single value from a profile, located at the specified index.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inInverse">Reversed order of elements.</param>
	AVL_FUNCTION void GetProfileElement
	(
		const avl::Profile&	inProfile,
		const int			inIndex,
		const bool			inInverse,	
		float&			outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns linear interpolation between two consecutive values from a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inIndex">Default value: 0.0f.</param>
	AVL_FUNCTION void GetProfileElement_Interpolated
	(
		const avl::Profile&		inProfile,
		bool					inCyclic,
		bool					inSmooth,
		float				inIndex,
		float&				outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a single element in a profile, located at the specified index.</summary>
	/// <param name="inInverse">Reversed order of elements.</param>
	AVL_FUNCTION void SetProfileElement
	(
		avl::Profile&		ioProfile,
		const int			inIndex,
		const bool			inInverse,	
		const float		inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an array of all indices of the input profile (0, 1, 2, ...).</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileIndices
	(
		const avl::Profile&		inProfile,
		atl::Array<int>&		outIndices
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an array of all X and Y coordinates of the input profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileCoordinates
	(
		const avl::Profile&		inProfile,
		atl::Array<float>&		outXCoordinates,
		atl::Array<float>&		outYCoordinates
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an uniform profile of the given size.</summary>
	/// <param name="inValue">Input common value of all elements.</param>
	/// <param name="inSize">Input the number of elements. Default value: 1.</param>
	/// <param name="inXOffset">X offset of the output profile. Default value: 0.0f.</param>
	/// <param name="inXScale">X scale of the output profile. Default value: 1.0f.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void CreateUniformProfile
	(
		float			inValue,	
		int				inSize,		
		float			inXOffset,	
		float			inXScale,	
		avl::Profile&	outProfile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Serializes a profile to an AVDATA file.</summary>
	/// <param name="inProfile">Profile to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveProfile
	(
		const avl::Profile&	inProfile,	
		const atl::File&	inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Deserializes a profile from an AVDATA file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outProfile">Deserialized output Profile.</param>
	AVL_FUNCTION void LoadProfile
	(
		const atl::File&	inFilename,		
		avl::Profile&		outProfile			
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input profile contains at least one element, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void SkipEmptyProfile
	(
		const avl::Profile&				inProfile,
		atl::Conditional<avl::Profile>&	outNotEmptyProfile,
		bool&							outIsNotEmpty
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a profile structure.</summary>
	/// <param name="inXScale">Default value: 1.0f.</param>
	/// <param name="inValues">Input values of the profile.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void AvsFilter_MakeProfile
	(
		const float					inXOffset,
		const float					inXScale,
		const atl::Array<float>&	inValues,	
		avl::Profile&				outProfile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outValues">Output values of the profile.</param>
	AVL_FUNCTION void AvsFilter_AccessProfile
	(
		const avl::Profile&	inProfile,		
		float&				outXOffset,
		float&				outXScale,
		atl::Array<float>&	outValues		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_PROFILEBASICS_H

