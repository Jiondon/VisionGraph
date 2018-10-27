//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_IMAGEPOINTTRANSFORMS_H
#define AVS_IMAGEPOINTTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/RandomTypes.h"
#include "Image/Image.h"
#include "Basic/Types.h"
#include "Enums/ColorPalette.h"
#include "Image/ImagePointTransformsState.h"
#include "Image/PixelLut.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Exponentiates each pixel to the given power.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">The exponent. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void PowerImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float								inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs gamma correction.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Gamma coefficient, where 1.0 is neutral. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CorrectGamma
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a natural logarithm of each pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor (default: 255). Default value: atl::NIL.</param>
	/// <param name="inOffset">Offset factor. Default value: 1.0f.</param>
	/// <param name="inNormalizeZero">Specifies whether the output range should be rescaled to start from 0.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagLutProfile">Profile depicting the resulting look-up table of the logarithm transform.</param>
	AVL_FUNCTION void LogarithmImage
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const float&>		inScale,			
		float							inOffset,			
		bool								inNormalizeZero,	
		avl::Image&							outImage,			
		avl::Profile&						diagLutProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reverts the pixel value range (unsigned) or applies numeric negation (signed).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void NegateImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies numeric inversion (1/x) of the pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void InvertImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inDividend,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds a scalar value to each pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be added. Default value: 50.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AddToImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtracts a scalar value from each pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be subtracted. Default value: 50.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SubtractFromImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies each pixel by a scalar value.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Multiplier. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MultiplyImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides each pixel by a scalar value.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Divisor. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DivideImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&								outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies linear transformation to pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inA">Value multiplied. Default value: 1.0f.</param>
	/// <param name="inB">Value added. Default value: 0.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RescalePixels
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inA,		
		float							inB,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Substitutes pixels having the specified value with a new value.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ReplacePixels
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		const avl::Pixel&					inOldPixel,
		const avl::Pixel&					inNewPixel,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms pixel values to their absolute values pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AbsoluteValueImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms pixel values to their square roots pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SquareRootImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Raises pixel values to the second power pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SquareImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets pixels below the low value to minimum, above the high value to maximum, and interpolates the rest.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inLowValue">The value that will be changed to minimum (usually 0). Default value: 64.0f.</param>
	/// <param name="inHighValue">The value that will be changed to maximum (usually 255). Default value: 192.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ResaturateImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inLowValue,		
		float							inHighValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets pixels below the low value to the low value and above the high value to the high value.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inLowValue">The lower threshold for the image pixel values. Default value: 64.0f.</param>
	/// <param name="inHighValue">The higher threshold for the image pixel values. Default value: 192.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CropPixels
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Optional<float>			inLowValue,		
		atl::Optional<float>			inHighValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Shows a monochromatic image in false colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPalette">Palette of colors which is used to replace pixels. Default value: Iron.</param>
	/// <param name="inNegate">Reversing palette colors.</param>
	/// <param name="inMinValue">Minimal value of pixel that will be replaced by color from palette, otherwise first color from palette will be set. Default value: 0.</param>
	/// <param name="inMaxValue">Maximal value of pixel that will be replaced by color from palette, otherwise last color from palette will be set. Default value: 255.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagPalette">Used palette preview.</param>
	AVL_FUNCTION void ColorizeImage
	(
		ColorizeImageState&					ioState,
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::ColorPalette::Type				inPalette,	
		bool								inNegate,	
		atl::Optional<int>					inMinValue,	
		atl::Optional<int>					inMaxValue, 
		avl::Image&							outImage,
		avl::Image&							diagPalette = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes pixel values for data stored in array.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inColorPoints">Last pixel value in which corresponding color will be replaced.</param>
	/// <param name="inColors">Colors corresponding to pixel levels defined in inColorPoints.</param>
	/// <param name="inComputeGradient">Compute the linear change of pixels colors between next palette colors.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LUTTransformImage
	(
		LUTTransformImageState&				ioState,
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		const atl::Array<int>&				inColorPoints,			
		const atl::Array<avl::Pixel>&		inColors,				
		const bool							inComputeGradient,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds random noise to the image</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMinValue">Minimum value of noise pixel, inclusive. Default value: 0.0f.</param>
	/// <param name="inMaxValue">Maximum value of noise pixel, exclusive. Default value: 256.0f.</param>
	/// <param name="inNoiseStrength">Noise strength. Default value: 0.5f.</param>
	/// <param name="inColorNoise">If 'True', noise will be generated separately for each channel.</param>
	/// <param name="inSeed">Random seed used to generate noise. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AddNoiseToImage
	(
		RandomState&			ioState,		
		const avl::Image&		inImage,		
		const float				inMinValue,		
		const float				inMaxValue,		
		const float				inNoiseStrength,
		const bool				inColorNoise,	
		atl::Optional<int>		inSeed,			
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	typedef avl::ImagePointTransformsState AvsFilters_ImagePointTransformsState;


	/// <summary>Exponentiates each pixel to the given power.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">The exponent. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AvsFilter_PowerImage
	(
		AvsFilters_ImagePointTransformsState&			ioState,
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs gamma correction.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inValue">Gamma coefficient, where 1.0 is neutral. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AvsFilter_CorrectGamma
	(
		AvsFilters_ImagePointTransformsState&			ioState,
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float							inValue,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a natural logarithm of each pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor (default: 255). Default value: atl::NIL.</param>
	/// <param name="inOffset">Offset factor. Default value: 1.0f.</param>
	/// <param name="inNormalizeZero">Specifies whether the output range should be rescaled to start from 0.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagLutProfile">Profile depicting the resulting look-up table of the logarithm transform.</param>
	AVL_FUNCTION void AvsFilter_LogarithmImage
	(
		AvsFilters_ImagePointTransformsState&			ioState,
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Optional<const float&>		inScale,			
		float							inOffset,			
		bool								inNormalizeZero,	
		avl::Image&							outImage,			
		avl::Profile&						diagLutProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_IMAGEPOINTTRANSFORMS_H

