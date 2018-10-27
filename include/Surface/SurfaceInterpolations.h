//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SURFACEINTERPOLATIONS_H
#define AVL_SURFACEINTERPOLATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Surface/Surface.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Smooths a surface using a gaussian kernel.</summary>
	/// <param name="inRoi">Range of output points to be computed. Default value: atl::NIL.</param>
	/// <param name="inStdDevX">Horizontal smoothing standard deviation. Default value: 1.0f.</param>
	/// <param name="inStdDevY">Vertical smoothing standard deviation. Default value: atl::NIL.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 2.0f.</param>
	/// <param name="diagKernelRadiusX">Horizontal radius of Gaussian kernel being used.</param>
	/// <param name="diagKernelRadiusY">Vertical radius of Gaussian kernel being used.</param>
	AVL_FUNCTION void SmoothSurface_Gauss
	(
		const avl::Surface&					inSurface,
		atl::Optional<const avl::Region&>	inRoi,				
		float								inStdDevX,				
		atl::Optional<float>				inStdDevY,				
		const float							inKernelRelativeSize,	
		avl::Surface&						outSurface,
		int&								diagKernelRadiusX = atl::Dummy<int>(),		
		int&								diagKernelRadiusY = atl::Dummy<int>()		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SURFACEINTERPOLATIONS_H

