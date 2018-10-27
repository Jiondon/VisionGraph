//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGECONVERSIONS_H
#define AVL_IMAGECONVERSIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "Region/Region.h"
#include "Image/Image.h"

namespace avl
{


	AVL_FUNCTION void FillImageBuffer
	(
		avl::Image&				outImage,
		int						inWidth,
		int						inHeight,
		avl::PlainType::Type	inType,
		int						inDepth,
		int						inPitch,
		atl::byte*				inData
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void FillImagePreviewBuffer
	(
		const avl::Image&	inImage,
		int				inPreviewWidth,
		int				inPreviewHeight,
		atl::byte*		inBuffer,
		int				inBufferStride,
		bool			inHighQualityScaling
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a multichannel image from a monochromatic one by replicating its channel.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inNewDepth">Default value: 3.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ConvertToMultichannel
	(
		const avl::Image&					inMonoImage,
		atl::Optional<const avl::Region&>	inRoi,
		int									inNewDepth,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the type of pixel components.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inNewType">Type of the output image. Default value: UInt8.</param>
	/// <param name="inDepthDelta">Pixel values will be multiplied by 2^inDepthDelta. For example, use -4 to convert 12-bit to 8-bit images. Default value: 0.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ConvertPixelType
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::PlainType::Type		inNewType,		
		int							inDepthDelta,	
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from a single channel of the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SelectChannel
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		int						inChannelIndex,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a monochromatic image by averaging the input image channels.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AverageChannels
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a monochromatic image by averaging the input image channels. The output image may keep a reference to data owned by the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AverageChannels_Linked
	(
		avl::Image&							inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a monochromatic image from weighted averages of the input image channels.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inWeight1">Weight of the first channel.</param>
	/// <param name="inWeight2">Weight of the second channel.</param>
	/// <param name="inWeight3">Weight of the third channel.</param>
	/// <param name="inWeight4">Weight of the fourth channel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void AverageChannels_Weighted
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		int						inWeight1,	
		int						inWeight2,	
		int						inWeight3,	
		int						inWeight4,	
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a multichannel image from several monochromatic ones.</summary>
	/// <param name="inMonoImage1">An image that becomes the first channel.</param>
	/// <param name="inMonoImage2">An image that becomes the second channel.</param>
	/// <param name="inMonoImage3">An image that becomes the third channel. Default value: atl::NIL.</param>
	/// <param name="inMonoImage4">An image that becomes the fourth channel. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MergeChannels
	(
		const avl::Image&					inMonoImage1,	
		const avl::Image&					inMonoImage2,	
		atl::Optional<const avl::Image&>	inMonoImage3,	
		atl::Optional<const avl::Image&>	inMonoImage4,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Reverses the order of channels in an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image with reversed channels.</param>
	AVL_FUNCTION void ReverseChannels
	(
		const avl::Image& inImage,		
		avl::Image& outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates several monochromatic images from individual channels of the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outMonoImage1">Image of the first channel.</param>
	/// <param name="outMonoImage2">Image of the second channel.</param>
	/// <param name="outMonoImage3">Image of the third channel (if exists).</param>
	/// <param name="outMonoImage4">Image of the fourth channel (if exists).</param>
	AVL_FUNCTION void SplitChannels
	(
		const avl::Image&			inImage,
		avl::Image&					outMonoImage1,	
		avl::Image&					outMonoImage2,	
		atl::Optional<avl::Image&>	outMonoImage3,	
		atl::Optional<avl::Image&>	outMonoImage4	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a monochromatic image by summing the values of the input image channels.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">output mono image.</param>
	AVL_FUNCTION void AddChannels
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a monochromatic image by summing the values of the input image channels with saturation.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">output mono image.</param>
	AVL_FUNCTION void AddChannels_Saturation
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGECONVERSIONS_H

