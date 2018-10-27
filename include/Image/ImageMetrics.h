//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGEMETRICS_H
#define AVL_IMAGEMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/DistanceMeasure.h"
#include "Basic/Types.h"
#include "Image/Image.h"

namespace avl
{


	namespace CorrelationMeasure
	{
		enum Type
		{
			NormalizedCrossCorrelation,
			CrossCorrelation
		};
	}


	/// <summary>Computes the correlation of pattern and image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPatternImage">Pattern to be compared with input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inCorrelationMeasure">Measure of correlation.</param>
	/// <param name="outCorrelation">Value of correlation of pattern and image.</param>
	AVL_FUNCTION void ImageCorrelation
	(
		const avl::Image&				inImage,
		const avl::Image&				inPatternImage,			
		atl::Optional<const avl::Region&>		inRoi,					
		avl::CorrelationMeasure::Type	inCorrelationMeasure,	
		float&						outCorrelation			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an image of correlation between a pattern and the input image at each possible location.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPatternImage">Pattern to be compared with input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPatternRoi">Range of pixels in the pattern to be processed. Default value: atl::NIL.</param>
	/// <param name="inCorrelationMeasure">Measure of correlation.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ImageCorrelationImage
	(
		const avl::Image&					inImage,
		const avl::Image&					inPatternImage,			
		atl::Optional<const avl::Region&>	inRoi,					
		atl::Optional<const avl::Region&>	inPatternRoi,			
		avl::CorrelationMeasure::Type		inCorrelationMeasure,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures dissimilarity between two images.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPatternImage">Pattern to be compared with input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inDistanceMeasure">Measure of distance.</param>
	/// <param name="outDifference">Value of difference between pattern and image.</param>
	AVL_FUNCTION void ImageDifference
	(
		const avl::Image&			inImage,				
		const avl::Image&			inPatternImage,			
		atl::Optional<const avl::Region&> inRoi,					
		avl::DistanceMeasure::Type	inDistanceMeasure,		
		float&					outDifference			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an image of differences between a moving pattern and the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPatternImage">Pattern to be compared with input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPatternRoi">Range of pixels in the pattern to be processed. Default value: atl::NIL.</param>
	/// <param name="inDistanceMeasure">Measure of distance.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ImageDifferenceImage
	(
		const avl::Image&			inImage,
		const avl::Image&			inPatternImage,		
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const avl::Region&>	inPatternRoi,		
		avl::DistanceMeasure::Type	inDistanceMeasure,	
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two pixels using chromatic and non-chromatic information. Assumes RGB-like color space.</summary>
	/// <param name="inChromaAmount">Proportion of chromatic information in distance computation. Default value: 0.7f.</param>
	AVL_FUNCTION void ColorDistance
	(
		const avl::Pixel&	inPixelA,
		const avl::Pixel&	inPixelB,
		float			inChromaAmount, 
		float&			outDistance
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares each pixel with the specified color using chromatic and non-chromatic information.</summary>
	/// <param name="inImage">Unsigned color image used in comparison.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRgbColor">Color to compare the image to.</param>
	/// <param name="inChromaAmount">Proportion of chromatic information in distance computation. Default value: 0.7f.</param>
	/// <param name="outValueImage">Unsigned image of distances.</param>
	AVL_FUNCTION void ColorDistanceImage
	(
		const avl::Image&					inImage, 
		atl::Optional<const avl::Region&>	inRoi,
		const avl::Pixel&					inRgbColor, 
		float							inChromaAmount, 
		avl::Image&							outValueImage 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGEMETRICS_H

