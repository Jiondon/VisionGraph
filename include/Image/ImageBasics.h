//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_IMAGEBASICS_H
#define AVS_IMAGEBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/Anchor2D.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/TestImageId.h"
#include "Image/Image.h"
#include "AVLCommon/MatrixTypes.h"
#include "Basic/Types.h"
#include "Geometry/Geometry.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Surface/Surface.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Creates an image copy with the same size and pixel format.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CopyImageData
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets image pixels to the specified value.</summary>
	/// <param name="inRegion">Input region. Default value: atl::NIL.</param>
	/// <param name="inValue">The new background color.</param>
	AVL_FUNCTION void ClearImage
	(
		avl::Image&							ioImage,
		atl::Optional<const avl::Region&>	inRegion,
		const avl::Pixel&					inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a single pixel of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLocation">Location of the pixel to be accessed.</param>
	/// <param name="outPixel">Output pixel.</param>
	/// <param name="outValue">Average pixel value.</param>
	AVL_FUNCTION void GetImagePixel
	(
		const avl::Image&		inImage, 
		const avl::Location&	inLocation,	
		avl::Pixel&				outPixel, 
		float&				outValue 
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an interpolated single pixel of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPoint">Point on the input image to be accessed.</param>
	/// <param name="inInterpolation">Default value: Bilinear.</param>
	/// <param name="outPixel">Output pixel.</param>
	/// <param name="outValue">Average pixel value.</param>
	AVL_FUNCTION void GetImagePixel_Interpolated
	(
		const avl::Image&				inImage,	
		const avl::Point2D&				inPoint,	
		avl::InterpolationMethod::Type	inInterpolation,
		avl::Pixel&						outPixel,	
		float&						outValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a pixel of an image to the selected value.</summary>
	/// <param name="inLocation">Location of the pixel to be set.</param>
	/// <param name="inPixel">New pixel value.</param>
	AVL_FUNCTION void SetImagePixel
	(
		avl::Image&				ioImage,
		const avl::Location&	inLocation,	
		const avl::Pixel&		inPixel		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets pixels of an image to the selected value.</summary>
	/// <param name="inLocations">Locations of the pixels to be set.</param>
	/// <param name="inPixel">New pixel value.</param>
	AVL_FUNCTION void SetImagePixels
	(
		avl::Image&							ioImage,
		const atl::Array<avl::Location>&	inLocations,	
		const avl::Pixel&					inPixel			
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts an array of pixel values from a single row of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inChannelIndex">Selects a channel of the input image. Default value: atl::NIL.</param>
	/// <param name="inRowIndex">Selects a row of the input image.</param>
	/// <param name="outValues">Output pixel values of the row.</param>
	/// <param name="outPixels">Output pixels of the row.</param>
	AVL_FUNCTION void GetImageRow
	(
		const avl::Image&			inImage,			
		atl::Optional<int>			inChannelIndex,		
		const int					inRowIndex,			
		atl::Array<float>&		outValues,			
		atl::Array<avl::Pixel>&		outPixels			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets pixel values in a single entire row of an image.</summary>
	/// <param name="inChannelIndex">Selects a channel of the input image. Default value: atl::NIL.</param>
	/// <param name="inRowIndex">Selects a row of the input image.</param>
	/// <param name="inValues">New values for specified row.</param>
	AVL_FUNCTION void SetImageRow
	(
		avl::Image&						ioImage,
		atl::Optional<int>				inChannelIndex,		
		const int						inRowIndex,			
		const atl::Array<float>&	inValues			
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts an array of pixel values from a single column of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inChannelIndex">Selects a channel of the input image. Default value: atl::NIL.</param>
	/// <param name="inColumnIndex">Selects a column of the input image.</param>
	/// <param name="outValues">Output pixel values of the column.</param>
	/// <param name="outPixels">Output pixels of the column.</param>
	AVL_FUNCTION void GetImageColumn
	(
		const avl::Image&		inImage,			
		atl::Optional<int>		inChannelIndex,		
		const int				inColumnIndex,		
		atl::Array<float>&	outValues,			
		atl::Array<avl::Pixel>&	outPixels			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets pixel values in a single entire column of an image.</summary>
	/// <param name="inChannelIndex">Selects a channel of the input image. Default value: atl::NIL.</param>
	/// <param name="inColumnIndex">Selects a column of the input image.</param>
	/// <param name="inValues">New values for specified column.</param>
	AVL_FUNCTION void SetImageColumn
	(
		avl::Image&						ioImage,
		atl::Optional<int>				inChannelIndex,		
		const int						inColumnIndex,		
		const atl::Array<float>&	inValues			
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces the box of image dimensions</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outBox">Output box.</param>
	AVL_FUNCTION void ImageBox
	(
		const avl::Image&	inImage,	
		avl::Box&			outBox				
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a uniform image.</summary>
	/// <param name="inWidth">Width of the created image. Default value: 320.</param>
	/// <param name="inHeight">Height of the created image. Default value: 240.</param>
	/// <param name="inColor">Color of all pixels of the created image.</param>
	/// <param name="inChannels">Number of channels. Default value: 3.</param>
	/// <param name="inPixelType">Default value: UInt8.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void EmptyImage
	(
		const int					inWidth,		
		const int					inHeight,		
		const avl::Pixel&			inColor,		
		const int					inChannels,		
		const avl::PlainType::Type&	inPixelType,
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a sample image.</summary>
	/// <param name="inImageId">ID of test image.</param>
	/// <param name="outRgbImage">Output color image.</param>
	/// <param name="outMonoImage">Output mono image.</param>
	AVL_FUNCTION void TestImage
	(
		avl::TestImageId::Type inImageId,	
		avl::Image&	outRgbImage,				
		avl::Image&	outMonoImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point of image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPointAnchor">Selecting one of the 9 characteristic points. Default value: TopLeft.</param>
	AVL_FUNCTION void ImageCharacteristicPoint
	(
		const avl::Image&			inImage,
		const avl::Anchor2D::Type	inPointAnchor,	
		avl::Point2D&				outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a single-channel image to a matrix.</summary>
	AVL_FUNCTION void ImageToMatrix
	(
		const avl::Image&		inMonoImage,
		avl::Matrix&			outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a matrix image to a single-channel real image.</summary>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MatrixToImage
	(
		const avl::Matrix&	inMatrix,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a pixel array to a single-channel image.</summary>
	/// <param name="inWidth">Output image width.</param>
	/// <param name="inHeight">Output image height.</param>
	/// <param name="inType">Output image pixel type. Default value: UInt8.</param>
	/// <param name="inDepth">Output image depth.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MakeImage
	(
		const atl::Array<avl::Pixel>&	inPixels,
		const int						inWidth,	
		const int						inHeight,	
		avl::PlainType::Type			inType,		
		const int						inDepth,	
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized Image object as avdata file.</summary>
	/// <param name="inImage">Image to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveImageObject
	(
		const avl::Image& inImage,		
		const atl::File& inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized Image object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outImage">Deserialized output Image.</param>
	AVL_FUNCTION void LoadImageObject
	(
		const atl::File&	inFilename,		
		avl::Image&			outImage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image by joining an array of 1D profiles into consecutive image rows.</summary>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void JoinProfilesIntoImage
	(
		const atl::Array<avl::Profile>&	inProfiles,
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	struct JoinProfilesIntoImage_OfSeriesState : public BaseState
	{
		int singleProfileSize;
		int numOfProfile;
		Image wholeImage;

		JoinProfilesIntoImage_OfSeriesState()
			: numOfProfile(0)
		{}
	};


	/// <summary>Creates an image by joining 1D profiles, which appear in consecutive iterations.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inSeriesSize">Number of profiles that constitute a single image.</param>
	/// <param name="outImage">A depth image every inSeriesSize iterations, or Nil in all other iterations.</param>
	AVL_FUNCTION void JoinProfilesIntoImage_OfSeries
	(
		JoinProfilesIntoImage_OfSeriesState&		ioState,
		const avl::Profile&							inProfile,
		const int									inSeriesSize,	
		atl::Conditional<avl::Image>&				outImage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a new image with a standard pitch alignment.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RealignImagePitch
	(
		const avl::Image&	inImage,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image of z-values of the given points.</summary>
	/// <param name="inMissingPointValue">Value assigned to pixels where point is undefined.</param>
	/// <param name="inPixelOffset">Value added to every pixel. Default value: 0.0f.</param>
	/// <param name="inPixelScale">Value every pixel is multiplied by. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CreateImageFromPoint3DGrid
	(
		const avl::Point3DGrid&	inPoint3DGrid,
		const float				inMissingPointValue,	
		const float				inPixelOffset,			
		const float				inPixelScale,			
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image of z-values of the given points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inPixelType">Output image pixel type. Default value: Real.</param>
	/// <param name="inPixelOffset">Offset that the input surface values have in the output image; if set to Nil, surface zOffset is chosen. Default value: atl::NIL.</param>
	/// <param name="inPixelScale">Scale that the input surface values have in the output image; if set to Nil, surface zScale is chosen. Default value: 1.0D.</param>
	/// <param name="inMissingPointValue">Value assigned to pixels where point is undefined. Default value: 0.0f.</param>
	/// <param name="outImage">Input surface depth image.</param>
	AVL_FUNCTION void CreateImageFromSurface
	(
		const avl::Surface&		inSurface,		
		avl::PlainType::Type	inPixelType,	
		atl::Optional<double>	inPixelOffset,	
		atl::Optional<double>	inPixelScale,	
		atl::Optional<float>	inMissingPointValue,	
		avl::Image&				outImage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts a single element from an array of images at the specified index.</summary>
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndex">Index within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outImage">Element from the array.</param>
	AVL_FUNCTION void AvsFilter_GetImageArrayElement_Linked
	(
		atl::Array<avl::Image>&	inArray,	
		int						inIndex,	
		bool					inInverse,	
		avl::Image&				outImage	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a new image with additional pitch size.</summary>
	/// <param name="inImage">Input array.</param>
	/// <param name="inDeltaPitch">Additional pitch bytes for line.</param>
	/// <param name="outImage">Element from the array.</param>
	AVL_FUNCTION void ExpandImagePitch
	(
		const avl::Image&		inImage,		
		const int				inDeltaPitch,	
		avl::Image&				outImage		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Returns individual fields of an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outWidth">Output image width.</param>
	/// <param name="outHeight">Output image height.</param>
	/// <param name="outDepth">Output number of image color channels.</param>
	/// <param name="outType">Output pixel format.</param>
	/// <param name="outPixelSize">Output pixel size in bytes.</param>
	/// <param name="outPitch">Length of images pixel line with padding.</param>
	AVL_FUNCTION void AvsFilter_AccessImage
	(
		const avl::Image&		inImage,		
		int&					outWidth,		
		int&					outHeight,		
		int&					outDepth,		
		avl::PlainType::Type&	outType,		
		int&					outPixelSize,	
		int&					outPitch		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_IMAGEBASICS_H

