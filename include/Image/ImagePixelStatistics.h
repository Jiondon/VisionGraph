//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGEPIXELSTATISTICS_H
#define AVL_IMAGEPIXELSTATISTICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "Enums/HSxColorModel.h"
#include "Image/Image.h"

namespace avl
{


	/// <summary>Finds the location and the value of the darkest pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageMinimum
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Optional<avl::Location&>		outMinimumLocation,
		atl::Optional<float&>			outMinimumValue = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the location and the value of the brightest pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageMaximum
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Optional<avl::Location&>		outMaximumLocation,
		atl::Optional<float&>			outMaximumValue = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of the image pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageSum
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Pixel&							outSumColor,
		atl::Optional<float&>			outSumValue = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of the image pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outAverageColor">Average of each channel.</param>
	/// <param name="outAverageValue">Average of the entire image.</param>
	AVL_FUNCTION void ImageAverage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Pixel&							outAverageColor,		
		atl::Optional<float&>			outAverageValue = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of the HSV, HSL or HSI image pixel values.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inColorModel">Selected color model.</param>
	/// <param name="inMinSaturation">Default value: 0.</param>
	/// <param name="outHAverage">Output hue average.</param>
	/// <param name="outSAverage">Output saturation average.</param>
	/// <param name="outBAverage">Output brightness average.</param>
	AVL_FUNCTION void ImageAverageHSx
	(
		const avl::Image&					inRgbImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::HSxColorModel::Type			inColorModel,	
		atl::Optional<int>					inMinSaturation,
		int&								outHAverage,	
		int&								outSAverage,	
		int&								outBAverage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes various statistics of the image pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageStatistics
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Optional<avl::Location&>		outMinimumLocation,
		atl::Optional<float&>			outMinimumValue,
		atl::Optional<avl::Location&>		outMaximumLocation,
		atl::Optional<float&>			outMaximumValue,
		atl::Optional<avl::Pixel&>			outAverageColor,
		atl::Optional<float&>			outAverageValue,
		atl::Optional<avl::Pixel&>			outSumColor,
		atl::Optional<float&>			outSumValue
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGEPIXELSTATISTICS_H

