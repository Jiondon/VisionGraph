//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGESEGMENTATION_H
#define AVL_IMAGESEGMENTATION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Region/Region.h"
#include "ImageSegmentation/ExtractBlobsStructs.h"
#include "ImageSegmentation/RegionProcessingParams.h"

namespace avl
{


	namespace BlobsDifferenceMeasure
	{
		enum Type
		{
			Mean,
			Neighbour,
			Bounds
		};
	}

	namespace BlobMergingMethod
	{
		enum Type
		{
			Neighbor,
			NeighborVerified,
			MeanLinear,
			MeanSorted
		};
	}
	
	namespace TileSize
	{
		enum Type
		{
			_4x4,
			_8x8,
			_16x16,
			_32x32
		};
	}


	/// <summary>Segments an image into blobs by thresholding.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inThresholdParams">Parameters for thresholding an image.</param>
	/// <param name="inRegionProcessingParams">Parameters for opening and closing of a region.</param>
	/// <param name="inBlobSplittingParams">Parameters for splitting region into blobs.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
	/// <param name="diagBaseRegion">Region of pixels right after thresholding.</param>
	AVL_FUNCTION void ExtractBlobs_Intensity
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Region&>		inRoi,					
		const avl::IntensityThresholdParams&	inThresholdParams,		
		const avl::RegionProcessingParams&		inRegionProcessingParams,	
		const avl::BlobSplittingParams&			inBlobSplittingParams,	
		atl::Array<avl::Region>&				outBlobs,				
		atl::Array<int>&						diagBlobAreas = atl::Dummy< atl::Array<int> >(),			
		avl::Region&							diagBaseRegion = atl::Dummy<avl::Region>()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs by dynamic thresholding.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inThresholdParams">Parameters for dynamic thresholding.</param>
	/// <param name="inRegionProcessingParams">Parameters for opening and closing of a region.</param>
	/// <param name="inBlobSplittingParams">Parameters for splitting region into blobs.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
	/// <param name="diagBaseRegion">Region of pixels right after thresholding.</param>
	AVL_FUNCTION void ExtractBlobs_Dynamic
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Region&>		inRoi,					
		const avl::DynamicThresholdParams&		inThresholdParams,		
		const avl::RegionProcessingParams&		inRegionProcessingParams,	
		const avl::BlobSplittingParams&			inBlobSplittingParams,	
		atl::Array<avl::Region>&				outBlobs,				
		atl::Array<int>&						diagBlobAreas = atl::Dummy< atl::Array<int> >(),			
		avl::Region&							diagBaseRegion = atl::Dummy<avl::Region>()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs by color-based thresholding.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inThresholdParams">Parameters for color-based thresholding.</param>
	/// <param name="inRegionProcessingParams">Parameters for opening and closing of a region.</param>
	/// <param name="inBlobSplittingParams">Parameters for splitting region into blobs.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
	/// <param name="diagBaseRegion">Region of pixels right after thresholding.</param>
	AVL_FUNCTION void ExtractBlobs_Color
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Region&>		inRoi,					
		const avl::ColorThresholdParams&		inThresholdParams,		
		const avl::RegionProcessingParams&		inRegionProcessingParams,	
		const avl::BlobSplittingParams&			inBlobSplittingParams,	
		atl::Array<avl::Region>&				outBlobs,				
		atl::Array<int>&						diagBlobAreas = atl::Dummy< atl::Array<int> >(),			
		avl::Region&							diagBaseRegion = atl::Dummy<avl::Region>()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs by thresholding Difference of Gaussians.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inStdDev">Smoothing standard deviation for the smaller Gaussian kernel. Default value: 3.0f.</param>
	/// <param name="inStdDevRatio">Defines how many times larger is the second Gaussian kernel. Default value: 1.6f.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the Gaussian kernel. Default value: 3.0f.</param>
	/// <param name="inThresholdParams">Parameters for thresholding an image.</param>
	/// <param name="inRegionProcessingParams">Parameters for opening and closing of a region.</param>
	/// <param name="inBlobSplittingParams">Parameters for splitting region into blobs.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
	/// <param name="diagBaseRegion">Region of pixels right after thresholding.</param>
	AVL_FUNCTION void ExtractBlobs_DoG
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Region&>		inRoi,					
		float								inStdDev,				
		float								inStdDevRatio,			
		float								inKernelRelativeSize,	
		const avl::IntensityThresholdParams&	inThresholdParams,		
		const avl::RegionProcessingParams&		inRegionProcessingParams,	
		const avl::BlobSplittingParams&			inBlobSplittingParams,	
		atl::Array<avl::Region>&				outBlobs,				
		atl::Array<int>&						diagBlobAreas = atl::Dummy< atl::Array<int> >(),			
		avl::Region&							diagBaseRegion = atl::Dummy<avl::Region>()			
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMinArea">Default value: 20.</param>
	AVL_FUNCTION void SplitRegionIntoBlobs_Carbon
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,
		int								inMinArea,
		atl::Optional<int>				inMaxArea,
		atl::Array< avl::Region >&		outBlobs
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs examining differences between pixels values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inMergingMethod">Defines a criterion by which two pixels can be merged into one blob. Default value: Neighbor.</param>
	/// <param name="inConnectivity">Defines if pixels can be merged only horizontally and vertically, or also diagonally.</param>
	/// <param name="inMaxDifference">Maximal tonal difference that allows two pixels to be merged into one blob. Default value: 5.</param>
	/// <param name="inHysteresis">Change of MaxDifference after each pass.</param>
	/// <param name="inPassCount">Number of iterations in which the entire image is scanned for pixels that can be merged.</param>
	/// <param name="inDirectional">When 'True' the filter can segment results of GradientDirAndPresenceImage.</param>
	/// <param name="inMinArea">Minimal area of a blob that may be accepted. Default value: 20.</param>
	/// <param name="inMaxArea">Minimal area of a blob that may be accepted. Default value: atl::NIL.</param>
	AVL_FUNCTION void SegmentImage_Gray_Linear
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::BlobMergingMethod::Type		inMergingMethod,	
		avl::RegionConnectivity::Type		inConnectivity,		
		int									inMaxDifference,	
		int									inHysteresis,		
		int									inPassCount,		
		bool								inDirectional,		
		int									inMinArea,			
		atl::Optional<int>					inMaxArea,			
		atl::Array<avl::Region>&			outBlobs
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs examining differences between pixels values, first pass is tiled.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inMergingMethod">Defines a criterion by which two pixels can be merged into one blob. Default value: Neighbor.</param>
	/// <param name="inMaxDifference">Maximal tonal difference that allows two pixels to be merged into one blob. Default value: 5.</param>
	/// <param name="inHysteresis">Change of MaxDifference between first and second iteration.</param>
	/// <param name="inTonalDrift">When 'True' blobs can be merged even if the illumination is not even. Default value: True.</param>
	/// <param name="inDirectional">When 'True' the filter can segment results of GradientDirAndPresenceImage.</param>
	/// <param name="inMinArea">Minimal area of a blob that may be accepted. Default value: 20.</param>
	/// <param name="inMaxArea">Minimal area of a blob that may be accepted. Default value: atl::NIL.</param>
	AVL_FUNCTION void SegmentImage_Gray_Tiled
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::BlobMergingMethod::Type		inMergingMethod,	
		int									inMaxDifference,	
		int									inHysteresis,		
		bool								inTonalDrift,		
		bool								inDirectional,		
		int									inMinArea,			
		atl::Optional<int>					inMaxArea,			
		atl::Array<avl::Region>&			outBlobs
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs examining histograms of gray values.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMaxDifference">Default value: 5.</param>
	/// <param name="inTonalDrift">Default value: True.</param>
	/// <param name="inMinArea">Default value: 20.</param>
	AVL_FUNCTION void SegmentImage_Histogram
	(
		const avl::Image&			inImage,
		int							inMaxDifference,
		int							inHysteresis,
		bool						inTonalDrift,
		bool						inDirectional,
		int							inMinArea,
		atl::Optional<int>			inMaxArea,
		atl::Array<avl::Region>&	outBlobs
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average direction within the region of interest.</summary>
	/// <param name="inDaPImage">A result of GradientDirAndPresenceImage filter.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void DaPImageMedian
	(
		const avl::Image&					inDaPImage,		
		atl::Optional<const avl::Region&>	inRoi,
		float&								outMedianAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average direction within the region of interest.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void DaPImageAverage
	(
		const avl::Image&					inDaPImage,
		atl::Optional<const avl::Region&>	inRoi,
		float&								outAverageAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs examining differences between neighbouring pixels values.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inMaxDifference">Maximal difference between two neighbouring blobs to be merged. Default value: 5.0f.</param>
	/// <param name="inDifferenceMeasure">Measure of blobs difference. Default value: Neighbour.</param>
	/// <param name="inMinArea">Minimal area of a blob. Default value: 50.</param>
	/// <param name="inMaxArea">Maximal area of a blob. Default value: atl::NIL.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	AVL_FUNCTION void SegmentImage_Gray
	(
		const avl::Image&						inImage,			
		atl::Optional<const avl::Region&>		inRoi,				
		const float							inMaxDifference,	
		const avl::BlobsDifferenceMeasure::Type	inDifferenceMeasure,
		const int								inMinArea,			
		atl::Optional<int>						inMaxArea,			
		atl::Array<avl::Region>&				outBlobs			
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image into blobs using image edges as their borders.</summary>
	/// <param name="inImage">Image from which blobs are extracted.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inFrameSize">How many pixels from the region border are excluded from the results. Default value: 1.</param>
	/// <param name="inStdDev">Amount of smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 15.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 5.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: 0.0f.</param>
	/// <param name="inMinArea">Minimal area of a detected blob. Default value: 50.</param>
	/// <param name="inMaxArea">Maximal area of a detected blob. Default value: atl::NIL.</param>
	/// <param name="inComputeNestingLevels">Flag indicating whether nesting levels should be computed.</param>
	/// <param name="inEdgeClosing">Radius of enclosing small holes in the detected blobs. Default value: 1.</param>
	/// <param name="outBlobs">Blobs extracted from the input image.</param>
	/// <param name="outNestingLevels">Nesting level of each extracted blob.</param>
	/// <param name="diagEdgeRegion">Region of the found edges.</param>
	AVL_FUNCTION void SegmentImage_Edges
	(
		const avl::Image&					inImage,								
		atl::Optional<const avl::Region&>	inRoi,									
		const int							inFrameSize,							
		float								inStdDev,								
		float								inEdgeThreshold,						
		float								inEdgeHysteresis,						
		const float							inMaxJoiningDistance,					
		const int							inMinArea,								
		atl::Optional<int>					inMaxArea,								
		bool								inComputeNestingLevels,					
		const int							inEdgeClosing,							
		atl::Array<avl::Region>&			outBlobs,								
		atl::Optional<atl::Array<int>&>		outNestingLevels = atl::NIL,			
		avl::Region&						diagEdgeRegion = atl::Dummy<Region>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes dark basins which are separated by at least inThreshold height watershed.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inThreshold">Input minimum separating watershed height. Default value: 10.</param>
	/// <param name="outBasins">Output dark basins found.</param>
	AVL_FUNCTION void ImageWatersheds
	(
		const avl::Image&			inImage,		
		const int					inThreshold,	
		atl::Array<avl::Region>&	outBasins		
	)
	THROW_AVL_ERRORS;

	/// <summary>Segments an image basing on distance to model colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inReferenceColors">Colors to compare pixels to.</param>
	/// <param name="inMaxDifference">Maximal difference between pixel and reference color to be accepted. Default value: 5.0f.</param>
	/// <param name="inDifferenceMultipliers">Scales for maximum differences for each color. Default value: atl::NIL.</param>
	/// <param name="inChromaAmount">Proportion of chromatic information in distance computation. Default value: 0.7f.</param>
	/// <param name="inForceDisjointRegions">Force output regions to be disjoint.</param>
	/// <param name="outRegions">Regions of pixels closest to colors.</param>
	AVL_FUNCTION void SegmentImage_Color
	(
		const avl::Image&							inImage,
		const atl::Optional<avl::Region>&			inRoi,
		const atl::Array<avl::Pixel>&				inReferenceColors,		
		const float								inMaxDifference,		
		atl::Optional<const atl::Array<float>&>	inDifferenceMultipliers,
		float									inChromaAmount,			
		bool										inForceDisjointRegions, 
		atl::Array<avl::Region>&					outRegions				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGESEGMENTATION_H

