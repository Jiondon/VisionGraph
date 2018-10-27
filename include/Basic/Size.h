//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_SIZE_H
#define AVS_SIZE_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Basic/Types.h"

namespace avs
{


	/// <summary>Creates a size structure from individual fields.</summary>
	/// <param name="inWidth">Input width.</param>
	/// <param name="inHeight">Input height.</param>
	/// <param name="outSize">Output box.</param>
	AVL_FUNCTION void AvsFilter_MakeSize
	(
		int		inWidth,	
		int		inHeight,	
		avl::Size&	outSize		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of size.</summary>
	/// <param name="inSize">Input box.</param>
	/// <param name="outWidth">Output width.</param>
	/// <param name="outHeight">Output height.</param>
	AVL_FUNCTION void AvsFilter_AccessSize
	(
		const avl::Size&	inSize,		
		int&		outWidth,	
		int&		outHeight	
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_SIZE_H

