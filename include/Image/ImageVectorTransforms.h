//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGEVECTORTRANSFORMS_H
#define AVL_IMAGEVECTORTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Enums/ImageLocalTransformsEnums.h"
#include "Enums/AngleRange.h"

namespace avl
{


	/// <summary>Computes gradient magnitudes of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MeasurePixelVectors
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Adjusts gradient angles to a given range.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void NormalizePixelVectors
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::GradientAngleRange::Type		inAngleRange,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates image gradients.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RotatePixelVectors
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		const float							inAngle,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Rescales an image treating pixels as vectors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inVectorLength">Desired vector length after normalization. Default value: 255.0f.</param>
	/// <param name="outImage">Rescaled image.</param>
	AVL_FUNCTION void ResizePixelVectors
	(
		const avl::Image& inImage,							
		atl::Optional<const avl::Region&>	inRoi,			
		const float inVectorLength,							
		avl::Image& outImage								
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGEVECTORTRANSFORMS_H

