//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_PIXEL_H
#define AVS_PIXEL_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Basic/Types.h"

namespace avs
{


	/// <summary>Creates a pixel structure from individual fields.</summary>
	/// <param name="inX">Input value of channel x.</param>
	/// <param name="inY">Input value of channel y.</param>
	/// <param name="inZ">Input value of channel z.</param>
	/// <param name="inW">Input value of channel w.</param>
	/// <param name="outPixel">Output location.</param>
	AVL_FUNCTION void AvsFilter_MakePixel
	(
		float	inX,		
		float	inY,		
		float	inZ,		
		float	inW,		
		avl::Pixel&	outPixel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of pixel.</summary>
	/// <param name="inPixel">Input location.</param>
	/// <param name="outX">Output value of channel x.</param>
	/// <param name="outY">Output value of channel y.</param>
	/// <param name="outZ">Output value of channel z.</param>
	/// <param name="outW">Output value of channel w.</param>
	AVL_FUNCTION void AvsFilter_AccessPixel
	(
		const avl::Pixel&	inPixel,	
		float&			outX,		
		float&			outY,		
		float&			outZ,		
		float&			outW		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_PIXEL_H

