//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGEENHANCEMENT_H
#define AVL_IMAGEENHANCEMENT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Enums/KernelShape.h"

namespace avl
{


	/// <summary>Rescales an image linearly, so that its minimum becomes inNewMinimum and the maximum of the remaining pixels becomes inNewMaximum.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inNewMinimum">Desired minimum value of the resulting image. Default value: 0.0f.</param>
	/// <param name="inNewMaximum">Desired maximum value of the resulting image. Default value: 255.0f.</param>
	/// <param name="inSaturateBrightestFraction">Fraction of the brightest pixels skipped during normalization. Default value: 0.0f.</param>
	/// <param name="inSaturateDarkestFraction">Fraction of the darkest pixels skipped during normalization. Default value: 0.0f.</param>
	/// <param name="outImage">Rescaled image.</param>
	/// <param name="outA">Multiplicative parameter of the applied linear transformation of pixel values.</param>
	/// <param name="outB">Additive parameter of the applied linear transformation of pixel values.</param>
	/// <param name="diagLinearNormalizedRegion">Region of image that has been linearly normalized.</param>
	AVL_FUNCTION void NormalizeImage
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float						inNewMinimum, 
		float						inNewMaximum, 
		float						inSaturateBrightestFraction, 
		float						inSaturateDarkestFraction, 
		avl::Image&					outImage, 
		float&						outA, 
		float&						outB, 
		avl::Region&				diagLinearNormalizedRegion = atl::Dummy<avl::Region>() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Maps image pixels to new values to achieve uniform distribution of intensities in the range (0, 255).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inSaturateBrightestFraction">Fraction of the brightest pixels skipped during normalization. Default value: 0.0f.</param>
	/// <param name="inSaturateDarkestFraction">Fraction of the darkest pixels skipped during normalization. Default value: 0.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void EqualizeImageHistogram
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float						inSaturateBrightestFraction,	
		float						inSaturateDarkestFraction,		
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Normalizes local contrast of the image using Wallis filter.</summary>
	/// <param name="inMonoImage">Monochromatic input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inTargetMean">Target local mean. Default value: 128.0f.</param>
	/// <param name="inTargetVariance">Target local variance. Default value: 90.0f.</param>
	/// <param name="inUniformnessScale">Radius of neighbourhood to uniformize. Default value: 10.</param>
	/// <param name="inBrightnessPreserveRatio">How much of original brightness to be kept. Default value: 0.1f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void NormalizeLocalContrast
	(
		const avl::Image&			inMonoImage, 
		const atl::Optional<avl::Region>&	inRoi,
		const float				inTargetMean, 
		const float				inTargetVariance, 
		const int				inUniformnessScale,
		const float				inBrightnessPreserveRatio,

		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Fills in a region of the image with pixel values interpolated from the borders of the area.</summary>
	/// <param name="inLambda">Ratio between vertical and horizontal interpolation. Default value: 0.5f.</param>
	/// <param name="inRegionToInpaint">Region to be inpainted.</param>
	AVL_FUNCTION void InpaintImage
	(
		avl::Image&			ioImage,
		float			inLambda,			
		const avl::Region&	inRegionToInpaint	
	)
	THROW_AVL_ERRORS;

	/// <summary>Enhances contrast of an image so that it appears sharper.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inContrastFactor">Value representing the strength of the contrast enhancement. Default value: 1.0f.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SharpenImage
	(
		const avl::Image&		inImage,
		float					inContrastFactor,	
		avl::KernelShape::Type	inKernel,			
		int						inRadiusX,			
		atl::Optional<int>		inRadiusY,			
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Adjusts image colors by stretching each channel separately.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AutoAdjustColors
	(
		const avl::Image&	inImage,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGEENHANCEMENT_H

