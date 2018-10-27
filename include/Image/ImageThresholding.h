//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGETHRESHOLDING_H
#define AVL_IMAGETHRESHOLDING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/HSxColorModel.h"
#include "Enums/ThresholdMethod.h"
#include "Enums/KernelShape.h"
#include "Region/RegionOfInterest.h"
#include "Image/Image.h"

namespace avl
{


	/// <summary>Transforms each pixel value to maximum or minimum depending on whether they belong to the specified range.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinValue">Minimum value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxValue">Maximum value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">A tolerance for inMin/MaxValue that results in intermediate output values. Default value: 0.0f.</param>
	AVL_FUNCTION void ThresholdImage
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<float>			inMinValue,		
		atl::Optional<float>			inMaxValue,		
		float							inFuzziness,	
		avl::Image&							outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>FIXME for testing RegionOfInterest</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinValue">Minimum value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxValue">Maximum value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">A tolerance for inMin/MaxValue that results in intermediate output values. Default value: 0.0f.</param>
	AVL_FUNCTION void ThresholdImage_RegionOfInterest
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::RegionOfInterest&>	inRoi,			
		atl::Optional<float>			inMinValue,		
		atl::Optional<float>			inMaxValue,		
		float							inFuzziness,	
		avl::Image&							outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image with a different threshold value for each pixel (inBaseImage(x, y) + inValue).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inBaseImage">Pixels of this image are subtracted from inImage before thresholding.</param>
	/// <param name="inMinRelativeValue">Minimum relative value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxRelativeValue">Maximum relative value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">A tolerance for inMin/MaxRelativeValue that results in intermediate output values. Default value: 0.0f.</param>
	AVL_FUNCTION void ThresholdImage_Relative
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		const avl::Image&					inBaseImage,		
		atl::Optional<float>			inMinRelativeValue,	
		atl::Optional<float>			inMaxRelativeValue,	
		float							inFuzziness,		
		avl::Image&							outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image relatively to some value calculated in a local rectangular neighbourhood.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region in which pixels are written. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Region from which pixels are read. Default value: atl::NIL.</param>
	/// <param name="inReferenceMethod">Specifies how the local threshold value will be calculated (see SmoothImage filter family). Default value: Mean.</param>
	/// <param name="inKernel">Kernel shape. Default value: Box.</param>
	/// <param name="inRadiusX">Horizontal radius of local neighbourhood. Default value: 5.</param>
	/// <param name="inRadiusY">Vertical radius of local neighbourhood (Auto = inRadiusX). Default value: atl::NIL.</param>
	/// <param name="inMinRelativeValue">Minimum relative value of a pixel that is considered foreground (Auto = -INF). Default value: 0.0f.</param>
	/// <param name="inMaxRelativeValue">Maximum relative value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">A tolerance for inMin/MaxRelativeValue that results in intermediate output values. Clamped on half of pixel max value (e.g. max fuzziness for uint8 image is 128). Default value: 0.0f.</param>
	/// <param name="diagBaseImage">Diagnostic threshold values.</param>
	AVL_FUNCTION void ThresholdImage_Dynamic
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const avl::Region&>	inSourceRoi,		
		avl::ThresholdDynamicReferenceMethod::Type inReferenceMethod, 
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,			
		atl::Optional<int>					inRadiusY,			
		atl::Optional<float>			inMinRelativeValue,	
		atl::Optional<float>			inMaxRelativeValue,	
		float							inFuzziness,		
		avl::Image&						outMonoImage,
		avl::Image&						diagBaseImage = atl::Dummy<avl::Image>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image relatively to some value calculated in a local rectangular neighbourhood.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region in which pixels are written. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Region from which pixels are read. Default value: atl::NIL.</param>
	/// <param name="inReferenceMethod">Specifies how the local threshold value will be calculated (see SmoothImage filter family). Default value: Mean.</param>
	/// <param name="inKernel">Kernel shape. Default value: Box.</param>
	/// <param name="inRadiusX">Horizontal radius of local neighbourhood. Default value: 5.</param>
	/// <param name="inRadiusY">Vertical radius of local neighbourhood (Auto = inRadiusX). Default value: atl::NIL.</param>
	/// <param name="inMinRelativeValue">Minimum relative value of a pixel that is considered foreground (Auto = -INF). Default value: 0.0f.</param>
	/// <param name="inMaxRelativeValue">Maximum relative value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">A tolerance for inMin/MaxRelativeValue that results in intermediate output values. Clamped on half of pixel max value (e.g. max fuzziness for uint8 image is 128). Default value: 0.0f.</param>
	AVL_FUNCTION void ThresholdImage_DynamicWithBase
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const avl::Region&>	inSourceRoi,		
		avl::ThresholdDynamicReferenceMethod::Type inReferenceMethod, 
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,			
		atl::Optional<int>					inRadiusY,			
		atl::Optional<float>			inMinRelativeValue,	
		atl::Optional<float>			inMaxRelativeValue,	
		float							inFuzziness,		
		avl::Image&						outMonoImage,
		avl::Image&						outBaseImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each pixel value to minimum or maximum depending on whether it belongs to specified region in the HSV, HSL or HSI color space.</summary>
	/// <param name="inRgbImage">Input image in the RGB color space.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inColorModel">Selected color model.</param>
	/// <param name="inBeginHue">Lowest acceptable Hue; if higher than inEndHue, then range wrapping is used. Default value: 0.</param>
	/// <param name="inEndHue">Highest acceptable Hue, if lower than inBeginHue, then range wrapping is used. Default value: 255.</param>
	/// <param name="inMinSaturation">Default value: 128.</param>
	/// <param name="inMinBrightness">Minimum brightness; denotes V, L or I, depending on inColorModel. Default value: 128.</param>
	/// <param name="inMaxBrightness">Maximum brightness; denotes V, L or I, depending on inColorModel. Default value: atl::NIL.</param>
	/// <param name="inFuzziness">Tolerance for value ranges that results in intermediate output values.</param>
	/// <param name="diagHSxImage">Image in HSx color space.</param>
	AVL_FUNCTION void ThresholdImage_HSx
	(
		const avl::Image&					inRgbImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		avl::HSxColorModel::Type			inColorModel,		
		int									inBeginHue,			
		int									inEndHue,			
		atl::Optional<int>					inMinSaturation,
		atl::Optional<int>					inMaxSaturation,
		atl::Optional<int>					inMinBrightness,	
		atl::Optional<int>					inMaxBrightness,	
		float							inFuzziness,		
		avl::Image&							outMonoImage,
		avl::Image&							diagHSxImage = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each pixel value to minimum or maximum depending on whether it belongs to the specified range for each individual pixel component.</summary>
	/// <param name="inRgbImage">Input image, usually in the RGB color space.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinRed">Minimum for the first pixel component, usually Red (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxRed">Maximum for the first pixel component, usually Red (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inMinGreen">Minimum for the second pixel component, usually Green (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxGreen">Maximum for the second pixel component, usually Green (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inMinBlue">Minimum for the third pixel component, usually Blue (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxBlue">Maximum for the third pixel component, usually Blue (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inFuzziness">Tolerance for the ranges that results in intermediate output values.</param>
	AVL_FUNCTION void ThresholdImage_RGB
	(
		const avl::Image&			inRgbImage,		
		atl::Optional<const avl::Region&>	inRoi,	
		atl::Optional<int>			inMinRed,		
		atl::Optional<int>			inMaxRed,		
		atl::Optional<int>			inMinGreen,		
		atl::Optional<int>			inMaxGreen,		
		atl::Optional<int>			inMinBlue,		
		atl::Optional<int>			inMaxBlue,		
		float					inFuzziness,	
		avl::Image&					outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each pixel value to maximum or minimum depending on the distance from a given color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRgbColor">Color to compare the image to.</param>
	/// <param name="inChromaAmount">Proportion of chromatic information in distance computation. Default value: 0.7f.</param>
	/// <param name="inMaxDifference">Maximum difference between image pixel and model color. Default value: 5.0f.</param>
	/// <param name="inFuzziness">A tolerance for computed difference that results in intermediate output values. Default value: 0.0f.</param>
	AVL_FUNCTION void ThresholdImage_Color
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		const avl::Pixel&					inRgbColor,			
		float							inChromaAmount,		
		float							inMaxDifference,	
		float							inFuzziness,		
		avl::Image&							outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region containing image pixels with values within the specified range.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinValue">Minimum value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxValue">Maximum value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inHysteresis">Defines how much the threshold criteria are lowered for pixels neighboring with other foreground pixels. Default value: 0.0f.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThresholdToRegion
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<float>			inMinValue,		
		atl::Optional<float>			inMaxValue,		
		float							inHysteresis,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image with a different threshold value for each pixel (inBaseImage(x, y) + inValue).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inBaseImage">Pixels of this image are subtracted from inImage before thresholding.</param>
	/// <param name="inMinRelativeValue">Minimum relative value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxRelativeValue">Maximum relative value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inHysteresis">Defines how much the threshold criteria are lowered for pixels neighboring with other foreground pixels. Default value: 0.0f.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThresholdToRegion_Relative
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		const avl::Image&					inBaseImage,		
		atl::Optional<float>			inMinRelativeValue,	
		atl::Optional<float>			inMaxRelativeValue,	
		float							inHysteresis,		
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image relatively to the average pixel value in a local rectangular neighborhood.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region in which pixels are written. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Region from which pixels are read. Default value: atl::NIL.</param>
	/// <param name="inRadiusX">Horizontal radius of internal mean blur. Default value: 5.</param>
	/// <param name="inRadiusY">Vertical radius of internal mean blur (Auto = inRadiusX). Default value: atl::NIL.</param>
	/// <param name="inMinRelativeValue">Minimum relative value of a pixel that is considered foreground (Auto = -INF). Default value: 5.0f.</param>
	/// <param name="inMaxRelativeValue">Maximum relative value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inHysteresis">Defines how much the threshold criteria are lowered for pixels neighboring with other foreground pixels. Default value: 0.0f.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="diagBaseImage">Diagnostic blurred image.</param>
	AVL_FUNCTION void ThresholdToRegion_Dynamic
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const avl::Region&>	inSourceRoi,		
		int									inRadiusX,			
		atl::Optional<int>					inRadiusY,			
		atl::Optional<float>			inMinRelativeValue,	
		atl::Optional<float>			inMaxRelativeValue,	
		float							inHysteresis,		
		avl::Region&						outRegion,
		avl::Image&						diagBaseImage = atl::Dummy<avl::Image>() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region containing image pixels which belongs to specified region in HSV, HSL or HSI space.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inColorModel">Selected color model.</param>
	/// <param name="inBeginHue">Lowest acceptable Hue; if higher than inEndHue, then range wrapping is used. Default value: 0.</param>
	/// <param name="inEndHue">Highest acceptable Hue, if lower than inBeginHue, then range wrapping is used. Default value: 255.</param>
	/// <param name="inMinSaturation">Default value: 128.</param>
	/// <param name="inMinBrightness">Minimum brightness; denotes V, L or I, depending on inColorModel. Default value: 128.</param>
	/// <param name="inMaxBrightness">Maximum brightness; denotes V, L or I, depending on inColorModel. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="diagHSxImage">Diagnostic image in HSx color space.</param>
	AVL_FUNCTION void ThresholdToRegion_HSx
	(
		const avl::Image&					inRgbImage,
		atl::Optional<const avl::Region&>	inRoi,
		const avl::HSxColorModel::Type		inColorModel,		
		int									inBeginHue,			
		int									inEndHue,			
		atl::Optional<int>					inMinSaturation,
		atl::Optional<int>					inMaxSaturation,
		atl::Optional<int>					inMinBrightness,	
		atl::Optional<int>					inMaxBrightness,	
		avl::Region&						outRegion,
		avl::Image&							diagHSxImage = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region containing image pixels which belongs to the specified range for each individual pixel component.</summary>
	/// <param name="inRgbImage">Input image, usually in the RGB color space.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinRed">Minimum for the first pixel component, usually Red (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxRed">Maximum for the first pixel component, usually Red (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inMinGreen">Minimum for the second pixel component, usually Green (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxGreen">Maximum for the second pixel component, usually Green (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inMinBlue">Minimum for the third pixel component, usually Blue (Auto = -INF). Default value: 128.</param>
	/// <param name="inMaxBlue">Maximum for the third pixel component, usually Blue (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThresholdToRegion_RGB
	(
		const avl::Image&					inRgbImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<int>					inMinRed,		
		atl::Optional<int>					inMaxRed,		
		atl::Optional<int>					inMinGreen,		
		atl::Optional<int>					inMaxGreen,		
		atl::Optional<int>					inMinBlue,		
		atl::Optional<int>					inMaxBlue,		
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region containing image pixels with values close to the given color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRgbColor">Color to compare the image to.</param>
	/// <param name="inChromaAmount">Proportion of chromatic information in distance computation. Default value: 0.7f.</param>
	/// <param name="inMaxDifference">Maximum difference between image pixel and model color. Default value: 5.0f.</param>
	/// <param name="inHysteresis">Defines how much the difference criterium is lowered for pixels neighboring with other foreground pixels. Default value: 0.0f.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThresholdToRegion_Color
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		const avl::Pixel&					inRgbColor,			
		float							inChromaAmount,		
		float							inMaxDifference,	
		float							inHysteresis,		
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Thresholds an image with a hysteresis, i.e. with a lower threshold for neighboring pixels.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inMinValue">Minimum value of a pixel that is considered foreground (Auto = -INF). Default value: 128.0f.</param>
	/// <param name="inMaxValue">Maximum value of a pixel that is considered foreground (Auto = +INF). Default value: atl::NIL.</param>
	/// <param name="inHysteresis">Defines how much the threshold criteria are lowered for pixels neighboring with other foreground pixels. Default value: 16.0f.</param>
	AVL_FUNCTION void ThresholdImage_Hysteresis
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<float>			inMinValue,		
		atl::Optional<float>			inMaxValue,		
		float							inHysteresis,	
		avl::Image&							outMonoImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects best threshold value using the image histogram.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inMethod">Method used to select the best threshold.</param>
	/// <param name="outThresholdValue">Best threshold separating background pixels from foreground pixels.</param>
	/// <param name="diagThresholdRatings">Contains ratings gained if that threshold would be chosen.</param>
	/// <param name="diagBackgroundPixelsFraction">Fraction of pixels that are darker than the index value.</param>
	/// <param name="diagForegroundPixelsFraction">Fraction of pixels that are brighter than the index value.</param>
	AVL_FUNCTION void SelectThresholdValue
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::ThresholdSelectionMethod::Type	inMethod,						
		float&							outThresholdValue,				
		atl::Array<float>&				diagThresholdRatings = atl::Dummy< atl::Array<float> >(),			
		atl::Array<float>&				diagBackgroundPixelsFraction = atl::Dummy< atl::Array<float> >(),	
		atl::Array<float>&				diagForegroundPixelsFraction = atl::Dummy< atl::Array<float> >()	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGETHRESHOLDING_H

