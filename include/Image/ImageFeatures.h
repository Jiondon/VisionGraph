//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGEFEATURES_H
#define AVL_IMAGEFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "ComputerVision/1DEdgeDetection/ScanMapState.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/Polarity.h"
#include "Enums/ProjectionDirection.h"
#include "Geometry/Geometry.h"
#include "Histogram/Histogram.h"
#include "Image/Image.h"
#include "Image/Extremum2D.h"
#include "Image/ImageLocalExtremaVerification.h"
#include "Path/Path.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Returns an array of pixels from the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImagePixels
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Array<avl::Pixel>&				outPixels
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an array of pixel values from the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImagePixelValues
	(
		const avl::Image&			inImage,
		atl::Optional<const avl::Region&>	inRoi,
		atl::Array<float>&			outPixelValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the histogram of the image pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inChannelIndex">Selects a channel of the input image.</param>
	/// <param name="inBinSize">Width of a single histogram bin. Default value: 1.0f.</param>
	/// <param name="inDomainBegin">The lowest value that will be considered in the output histogram. Default value: 0.0f.</param>
	/// <param name="inDomainEnd">The upper-bound for values that will be considered in the output histogram. Default value: 256.0f.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void ImageHistogram
	(	
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		int									inChannelIndex,		
		const float&					inBinSize,			
		float							inDomainBegin,		
		float							inDomainEnd,		
		avl::Histogram&						outHistogram
	)
	THROW_AVL_ERRORS;

	namespace ImageMomentType
	{
		enum Type
		{
			_00,
			_01,
			_10,
			_02,
			_11,
			_20
		};
	}


	/// <summary>Computes the selected moment of an image in regular and normalized (divided by sum of pixel values) variant.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageMoment
	(	
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::ImageMomentType::Type			inMomentType,
		bool								inCentral,
		float&							outMoment,
		atl::Optional<float&>			outNormMoment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the orientation of an image using image moments. The result range is from 0.0 to 180.0.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageOrientation
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		float&							outOrientationAngle
	)
	THROW_AVL_ERRORS;

	namespace ProjectionMode
	{
		enum Type
		{
			Average,
			Maximum,
			Minimum,
			Sum
		};
	}


	/// <summary>Computes the average (or other statistic) for each image row or column and then merges the obtained results into a profile.</summary>
	/// <param name="inImage">Monochromatic image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inProjectionDirection">Combine pixel values for image rows (horizontal) or columns (vertical).</param>
	/// <param name="inProjectionMode">Determines how the pixel values are combined. Default value: Sum.</param>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void ImageProjection
	(
		const avl::Image&					inImage,				
		atl::Optional<const avl::Region&>	inRoi,
		avl::ProjectionDirection::Type		inProjectionDirection,	
		avl::ProjectionMode::Type			inProjectionMode,		
		avl::Profile&						outProfile
	)
	THROW_AVL_ERRORS;

	typedef ScanMapState ImageProfileAlongPathState;


	/// <summary>Creates a series of segments across the input path, measures the average pixel intensity on each of the segments, and creates the final profile from that values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanPath">Path along which the profile is extracted.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan area. Default value: 5.</param>
	/// <param name="inInterpolationMethod">Interpolation method used to compute pixel brightness in locations of not-integer coordinates. Default value: Bilinear.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the extracted profile. Default value: 0.6f.</param>
	/// <param name="outProfile">The resulting profile of the pixel brightness.</param>
	/// <param name="outPath">The path consisting of the points from which the resulting profile is extracted.</param>
	/// <param name="outAlignedScanPath">Input scan path after transformation (in the image coordinates).</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void ImageProfileAlongPath
	(
		ImageProfileAlongPathState&				ioState,
		const avl::Image&						inImage,				
		const avl::Path&						inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int										inScanWidth,			
		avl::InterpolationMethod::Type			inInterpolationMethod,	
		float								inSmoothingStdDev,		
		avl::Profile&							outProfile,				
		avl::Path&								outPath,				
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL, 
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an image in which the pixel values denote the estimated distances to the nearest bright pixel in the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inThreshold">Minimal brightness above which pixels are called bright. Default value: 128.</param>
	/// <param name="inStraightDistance">Distance between two neighboring in a row or a column pixels. Default value: 1.0f.</param>
	/// <param name="inDiagonalDistance">Distance between two pixels connected by vertices. Default value: 1.414f.</param>
	/// <param name="inMaxDistance">Maximum value of the calculated distance. Default value: 255.0f.</param>
	/// <param name="outImage">Output distance image.</param>
	AVL_FUNCTION void DistanceTransform
	(
		const avl::Image&	inImage,			
		int					inThreshold,		
		float			inStraightDistance,	
		float			inDiagonalDistance,	
		float			inMaxDistance,		
		avl::Image&			outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a point with coordinates equal to image mass center in brightness scale.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageMassCenter
	(	
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Point2D&						outMassCenter
	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds image locations characterized by locally maximal pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inConsiderPlateaus">Consider multi-pixel maxima (plateaus) or not.</param>
	/// <param name="inMinValue">Minimal value of maximum to be considered. Default value: atl::NIL.</param>
	/// <param name="inMaxValue">Maximal value of minimum to be considered. Default value: atl::NIL.</param>
	/// <param name="inMinDistance">Minimal distance between two found maxima.</param>
	/// <param name="inMaximaVerification">Maxima verification structure. Default value: atl::NIL.</param>
	/// <param name="outLocalMaxima">Found local maxima.</param>
	/// <param name="outMaximaRegions">Regions of local maxima (plateaus and singletons).</param>
	AVL_FUNCTION void ImageLocalMaxima
	(
		const avl::Image&							inImage,
		atl::Optional<const avl::Region&>			inRoi,
		bool										inConsiderPlateaus,	
		atl::Optional<float>					inMinValue,			
		atl::Optional<float>					inMaxValue,			
		float									inMinDistance,		
		atl::Optional<const avl::ImageLocalExtremaVerification&>	inMaximaVerification,	
		atl::Optional<atl::Array<avl::Extremum2D>&>	outLocalMaxima,	
		atl::Optional<atl::Array<avl::Region>&>		outMaximaRegions = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds image locations characterized by locally minimal pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inConsiderLowlands">Consider multi-pixel minima (lowlands) or not.</param>
	/// <param name="inMinValue">Minimal value of maximum to be considered. Default value: atl::NIL.</param>
	/// <param name="inMaxValue">Maximal value of minimum to be considered. Default value: atl::NIL.</param>
	/// <param name="inMinDistance">Minimal distance between two found minima.</param>
	/// <param name="inMinimaVerification">Minima verification structure. Default value: atl::NIL.</param>
	/// <param name="outLocalMinima">Found local minima.</param>
	/// <param name="outMinimaRegions">Regions of local minima (plateaus and singletons).</param>
	AVL_FUNCTION void ImageLocalMinima
	(
		const avl::Image&							inImage,
		atl::Optional<const avl::Region&>			inRoi,
		bool										inConsiderLowlands,	
		atl::Optional<float>					inMinValue,			
		atl::Optional<float>					inMaxValue,			
		float									inMinDistance,		
		atl::Optional<const avl::ImageLocalExtremaVerification&>	inMinimaVerification,	
		atl::Optional<atl::Array<avl::Extremum2D>&>	outLocalMinima,	
		atl::Optional<atl::Array<avl::Region>&>		outMinimaRegions = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the geometrical center of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void ImageCenter
	(
		const avl::Image&	inImage,
		avl::Point2D&		outCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns corners of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void ImageCorners_Deprecated
	(
		const avl::Image&	inImage,
		avl::Point2D&		outTopLeftCorner,
		avl::Point2D&		outTopRightCorner,
		avl::Point2D&		outBottomRightCorner,
		avl::Point2D&		outBottomLeftCorner
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a value dependent on sharpness of the image. The value is bigger for sharper images.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ImageSharpness
	(
		const avl::Image&				inImage,
		atl::Optional<const avl::Box&>	inRoi,
		float&						outSharpness
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds ridge pixels in an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPolarity">Specifies the type of ridges to be detected (Bright, Dark or Any).</param>
	/// <param name="inMinValue">Minimal value of pixel to be considered. Default value: atl::NIL.</param>
	/// <param name="inMaxValue">Maximal value of pixel to be considered. Default value: atl::NIL.</param>
	/// <param name="inNoiseLevel">Defines how much stronger a pixel has to be than its neighbors to be deemed a ridge pixel.</param>
	/// <param name="outRidges">Region of ridges.</param>
	AVL_FUNCTION void ImageRidges
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Polarity::Type					inPolarity,		
		atl::Optional<float>				inMinValue,		
		atl::Optional<float>				inMaxValue,		
		const float							inNoiseLevel,	
		avl::Region&						outRidges		
	)
	THROW_AVL_ERRORS;

	namespace NonMaximaMethod
	{
		enum Type
		{
			Interpolated,
			Nearest,
			Double,
			Quadruple
		};
	}


	/// <summary>Finds ridge pixels in a gradient image.</summary>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void GradientImageRidges
	(
		const avl::Image&			inGradientImage,
		const avl::Image&			inMagnitudeImage,
		avl::NonMaximaMethod::Type	inMethod,
		int							inMinValue,
		avl::Region&				outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates standard deviation of image pixel values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of Interest. Default value: atl::NIL.</param>
	/// <param name="outStandardDeviation">Calculated standard deviation.</param>
	AVL_FUNCTION void ImageStandardDeviation
	(
		const avl::Image&					inImage,				
		atl::Optional<const avl::Region&>	inRoi,					
		float&							outStandardDeviation	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGEFEATURES_H

