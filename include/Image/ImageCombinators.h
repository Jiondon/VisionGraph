//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGECOMBINATORS_H
#define AVL_IMAGECOMBINATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Enums/ColorPalette.h"
#include "Image/ImagePointTransformsState.h"

namespace avl
{


	/// <summary>Adds two images pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Output image scaling factor. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AddImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		float					inScale,	
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds images of an array pixel by pixel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AddImages_OfArray
	(
		const atl::Array<avl::Image>& inImageArray,
		atl::Optional<const avl::Region&> inRoi,
		float inScale,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct AddImages_OfLoopState : public avl::BaseState
	{
		avl::Image stateVariable;
	};
	/// <summary>Adds images appearing in consecutive iterations pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AddImages_OfLoop
	(
		AddImages_OfLoopState& ioState,
		const avl::Image& inImage,
		atl::Optional<const avl::Region&> inRoi,
		float inScale,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtracts two images pixel by pixel. The result is signed.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Output image scaling factor. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SubtractImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		float					inScale,		
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies two images pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Output image scaling factor. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MultiplyImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		float					inScale,		
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies images of an array pixel by pixel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MultiplyImages_OfArray
	(
		const atl::Array<avl::Image>& inImageArray,
		atl::Optional<const avl::Region&> inRoi,
		float inScale,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MultiplyImages_OfLoopState : public avl::BaseState
	{
		avl::Image stateVariable;
	};
	/// <summary>Multiplies images appearing in consecutive iterations pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MultiplyImages_OfLoop
	(
		MultiplyImages_OfLoopState& ioState,
		const avl::Image& inImage,
		atl::Optional<const avl::Region&> inRoi,
		float inScale,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides two images pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inScale">Output image scaling factor. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DivideImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		float					inScale,		
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the non-negative distances between corresponding pixel values.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DifferenceImage
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the non-negative distances between corresponding pixel values.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DifferenceImage_Shifted
	(
		const avl::Image&	inImage1,
		const avl::Image&	inImage2,
		const avl::Box&		inBox1,
		const avl::Box&		inBox2,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Averages two images pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AverageImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from the lower pixel values of each corresponding pair.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MinimumImage
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the minimum of images of an array pixel by pixel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MinimumImage_OfArray
	(
		const atl::Array<avl::Image>& inImageArray,
		atl::Optional<const avl::Region&> inRoi,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MinimumImage_OfLoopState : public avl::BaseState
	{
		avl::Image stateVariable;
	};
	/// <summary>Computes the minimum of images appearing in consecutive iterations pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MinimumImage_OfLoop
	(
		MinimumImage_OfLoopState& ioState,
		const avl::Image& inImage,
		atl::Optional<const avl::Region&> inRoi,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from the higher pixel values of each corresponding pair.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MaximumImage
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the maximum of images of an array pixel by pixel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MaximumImage_OfArray
	(
		const atl::Array<avl::Image>& inImageArray,
		atl::Optional<const avl::Region&> inRoi,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MaximumImage_OfLoopState : public avl::BaseState
	{
		avl::Image stateVariable;
	};
	/// <summary>Computes the maximum of images appearing in consecutive iterations pixel by pixel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MaximumImage_OfLoop
	(
		MaximumImage_OfLoopState& ioState,
		const avl::Image& inImage,
		atl::Optional<const avl::Region&> inRoi,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Takes pixels from the first image within the specified region and from the other one elsewhere.</summary>
	/// <param name="inImage1">First source of pixels marked in inRegion.</param>
	/// <param name="inImage2">Background image.</param>
	/// <param name="inRegion">Region which describes which pixels should be taken from inImage1.</param>
	/// <param name="inRoi">Region in which pixels should be processed otherwise black pixels are placed. Default value: atl::NIL.</param>
	/// <param name="outImage">Image composed of tho input images.</param>
	AVL_FUNCTION void ComposeImages
	(
		const avl::Image&					inImage1,	
		const avl::Image&					inImage2,	
		const avl::Region&					inRegion,	
		atl::Optional<const avl::Region&>	inRoi,		
		avl::Image&							outImage	
	)
	THROW_AVL_ERRORS;

	/// <summary>Interpolates two images linearly pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inLambda">Interpolation between the input images where 0.0 value is equal to inImage0 and 1.0 to inImage1. Default value: 0.5f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LerpImages
	(
		const avl::Image&					inImage0,
		const avl::Image&					inImage1,
		atl::Optional<const avl::Region&>	inRoi,
		float								inLambda,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes weighted sum pixel by pixel.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inAmount1">Default value: 0.5f.</param>
	/// <param name="inAmount2">Default value: 0.5f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void BlendImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		atl::Optional<const avl::Region&>	inRoi,
		float					inAmount1,
		float					inAmount2,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Colorizes heat-map and blends it with background image</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inHeatMap">Confidence of defect at each pixel.</param>
	/// <param name="inPalette">Default value: BlackYellowRed.</param>
	/// <param name="inThreshold">Minimum defect confidence for choosing more of heat-map color than of input image color. Default value: 64.</param>
	/// <param name="inFuzziness">Confidence distance from inThreshold within which heat-map colors and input image colors are linearly interpolated; Auto = INF. Default value: 0.</param>
	/// <param name="inMinValue">Default value: 0.</param>
	/// <param name="inMaxValue">Default value: 255.</param>
	/// <param name="inForceMono">Converts input image to monochromatic.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagPalette">Used palette preview.</param>
	AVL_FUNCTION void VisualizeHeatMap
	(
		avl::ColorizeImageState			ioState,
		const avl::Image&				inImage,			
		const avl::Image&				inHeatMap,			
		const avl::ColorPalette::Type&	inPalette,
		int								inThreshold,		
		atl::Optional<int>				inFuzziness,		
		atl::Optional<int>				inMinValue,
		atl::Optional<int>				inMaxValue,
		bool							inForceMono,		
		avl::Image&						outImage,
		avl::Image&						diagPalette = atl::Dummy<avl::Image>()			
	)
	THROW_AVL_ERRORS;

	namespace TileTranslationMode
	{
		enum Type
		{
			FourDirections,
			EightDirections
		};
	}


	/// <summary>Computes the non-negative distances between corresponding pixel values using tiles.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inTileWidth">Default value: 16.</param>
	/// <param name="inTileTranslationMode">Default value: FourDirections.</param>
	/// <param name="inOutputFromColorImage">Flag indicating whether to use every channel of the input images separately to compute results or only channels average. Default value: False.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DifferenceImage_Flex
	(
		const avl::Image&	inImage1,
		const avl::Image&	inImage2,
		atl::Optional<const avl::Box&>	inBox1,
		atl::Optional<const avl::Box&>	inBox2,
		int					inTileWidth,
		atl::Optional<int>	inTileHeight,
		avl::TileTranslationMode::Type	inTileTranslationMode,
		const bool			inOutputFromColorImage,	
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Averages images from an array pixel by pixel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AverageImages_OfArray
	(
		const atl::Array<avl::Image>&		inImages,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Compute median value for each pixel of images from an array.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MedianImages_OfArray
	(
		const atl::Array<avl::Image>&		inImages,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>For each pixel location, get value of n-th (increasing) pixel among input images.</summary>
	/// <param name="inReverse">Reverse the ordering of pixel values to decreasing. Default value: False.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void NthImage_OfArray
	(
		const atl::Array<avl::Image>&		inImages,
		const atl::Optional<const atl::Array<avl::Region>&>&	inSourceRois,
		int inN,
		bool inReverse,			
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGECOMBINATORS_H

