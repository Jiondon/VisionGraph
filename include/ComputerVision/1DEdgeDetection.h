//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_1DEDGEDETECTION_H
#define AVS_1DEDGEDETECTION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Enums/EdgeTransition.h"
#include "Enums/Polarity.h"
#include "Enums/Selection.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Path/Path.h"
#include "Profile/Profile.h"
#include "ComputerVision/1DEdgeDetection/ScanMap.h"
#include "ComputerVision/1DEdgeDetection/ScanMapState.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"
#include "ComputerVision/1DEdgeDetection/ScanStructs.h"

namespace avl
{


	/// <summary>Precomputes a data object that is required for fast 1D edge detection.</summary>
	/// <param name="inImageFormat">Dimensions, depth and pixel type of the image on which edge detection will be performed.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outScanMap">Optimized data object required for 1D edge detection.</param>
	/// <param name="outAlignedScanPath">Transformed input path.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributes to a single value of the extracted profile.</param>
	AVL_FUNCTION void CreateScanMap
	(
		const avl::ImageFormat&							inImageFormat,			
		const avl::Path&								inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int												inScanWidth,			
		avl::InterpolationMethod::Type					inImageInterpolation,	
		avl::ScanMap&									outScanMap,				
		atl::Optional<avl::Path&>						outAlignedScanPath = atl::NIL,	
		atl::Array<avl::Path>&							diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest transition between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edge. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdge">Found edge.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanSingleEdge
	(
		const avl::Image&					inImage,			
		const avl::ScanMap&					inScanMap,			
		const avl::EdgeScanParams&			inEdgeScanParams,	
		avl::Selection::Type				inEdgeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Conditional<avl::Edge1D>&		outEdge,			
		avl::Profile&						diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple transitions between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanMultipleEdges
	(
		const avl::Image&				inImage,			
		const ScanMap&					inScanMap,			
		const EdgeScanParams&			inEdgeScanParams,	
		float						inMinDistance,		
		atl::Optional<float>		inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Array<avl::Edge1D>&		outEdges,			
		atl::Array<avl::Gap1D>&			outGaps,			
		avl::Profile&					diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&					diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest transitions between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeCount">Number of edges to be found. Default value: 1.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edges. Default value: avl::Selection::Best.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanExactlyNEdges
	(
		const avl::Image&						inImage,			
		const ScanMap&							inScanMap,			
		const EdgeScanParams&					inEdgeScanParams,	
		int										inEdgeCount,		
		avl::Selection::Type					inEdgeSelection,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Edge1D> >&	outEdges,		
		atl::Conditional<atl::Array<avl::Gap1D> >&	outGaps,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest dark or bright pixel peak along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeSelection">Selection mode of the resulting ridge. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="outRidge">Found ridge.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	AVL_FUNCTION void ScanSingleRidge
	(
		const avl::Image&				inImage,			
		const ScanMap&					inScanMap,			
		const RidgeScanParams&			inRidgeScanParams,	
		avl::Selection::Type			inRidgeSelection,	
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Conditional<avl::Ridge1D>&	outRidge,			
		avl::Profile&					diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&					diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple dark or bright pixel peaks along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive ridges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive ridges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outGaps">Gaps between consecutive ridges.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	AVL_FUNCTION void ScanMultipleRidges
	(
		const avl::Image&					inImage,			
		const ScanMap&						inScanMap,			
		const RidgeScanParams&				inRidgeScanParams,	
		float							inMinDistance,		
		atl::Optional<float>			inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>			inLocalBlindness,	
		atl::Array<avl::Ridge1D>&			outRidges,			
		atl::Array<avl::Gap1D>&				outGaps,			
		avl::Profile&						diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest dark or bright pixel peak along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeCount">Number of ridges to be found. Default value: 1.</param>
	/// <param name="inRidgeSelection">Selection mode of the resulting ridges. Default value: avl::Selection::Best.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive ridges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive ridges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	AVL_FUNCTION void ScanExactlyNRidges
	(
		const avl::Image&					inImage,			
		const ScanMap&						inScanMap,			
		const RidgeScanParams&				inRidgeScanParams,	
		int									inRidgeCount,		
		avl::Selection::Type				inRidgeSelection,	
		float							inMinDistance,		
		atl::Optional<float>			inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>			inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Ridge1D> >&	outRidges,	
		atl::Conditional<atl::Array<avl::Gap1D> >&	outGaps,	
		avl::Profile&						diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest pair of edges across a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripe">Found stripe.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanSingleStripe
	(
		const avl::Image&				inImage,			
		const ScanMap&					inScanMap,			
		const StripeScanParams&			inStripeScanParams,	
		avl::Selection::Type			inStripeSelection,	
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Conditional<avl::Stripe1D>&	outStripe,		
		avl::Profile&					diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&					diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple pairs of edges across a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outGaps">Distances between consecutive stripes.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanMultipleStripes
	(
		const avl::Image&			inImage,			
		const ScanMap&				inScanMap,			
		const StripeScanParams&		inStripeScanParams,	
		float					inMinGapWidth,		
		atl::Optional<float>	inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Array<avl::Stripe1D>&	outStripes,			
		atl::Array<avl::Gap1D>&		outGaps,			
		avl::Profile&				diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&				diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of multiple pairs of opposite edges across a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanMap">Data precomputed with CreateScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeCount">Number of stripes to be found. Default value: 1.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripes. Default value: avl::Selection::Best.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive stripes.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outGaps">Distances between consecutive stripes.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanExactlyNStripes
	(
		const avl::Image&							inImage,			
		const ScanMap&								inScanMap,			
		const StripeScanParams&						inStripeScanParams,	
		int											inStripeCount,		
		avl::Selection::Type						inStripeSelection,	
		float									inMinGapWidth,		
		atl::Optional<float>					inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>					inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Stripe1D> >&	outStripes,		
		atl::Conditional<atl::Array<avl::Gap1D> >&	outGaps,			
		avl::Profile&								diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&								diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	typedef avl::ScanMapState ScanSingleEdgeState;
	typedef avl::ScanMapState ScanMultipleEdgesState;
	typedef avl::ScanMapState ScanExactlyNEdgesState;
	typedef avl::ScanMapState ScanSingleRidgeState;
	typedef avl::ScanMapState ScanMultipleRidgesState;
	typedef avl::ScanMapState ScanExactlyNRidgesState;
	typedef avl::ScanMapState ScanSingleStripeState;
	typedef avl::ScanMapState ScanMultipleStripesState;
	typedef avl::ScanMapState ScanExactlyNStripesState;


	/// <summary>Locates the strongest transition between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixels. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeSelection">If many edge points are possible, defines which one is selected.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdge">Found edge.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanSingleEdge
	(
		ScanSingleEdgeState&					ioState,
		const avl::Image&						inImage,					
		const avl::Path&						inScanPath,					
		atl::Optional<const avl::CoordinateSystem2D&> inScanPathAlignment,	
		int										inScanWidth,				
		avl::InterpolationMethod::Type			inImageInterpolation,		
		const avl::EdgeScanParams&				inEdgeScanParams,			
		avl::Selection::Type					inEdgeSelection,			
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<avl::Edge1D>&			outEdge,					
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL, 
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),		
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple transitions between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanMultipleEdges
	(
		ScanMultipleEdgesState&				ioState,
		const avl::Image&					inImage,				
		const avl::Path&					inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int									inScanWidth,			
		avl::InterpolationMethod::Type		inImageInterpolation,	
		const avl::EdgeScanParams&			inEdgeScanParams,		
		float							inMinDistance,			
		atl::Optional<float>			inMaxDistance,			
		atl::Optional<const avl::LocalBlindness&>			inLocalBlindness,	
		atl::Array<avl::Edge1D>&			outEdges,				
		atl::Array<avl::Gap1D>&				outGaps,				
		atl::Optional<avl::Path&>			outAlignedScanPath = atl::NIL,	
		avl::Profile&						diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>(),	
		atl::Array<avl::Path>&				diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest transitions between dark and bright pixels along a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeCount">Number of edges to be found. Default value: 1.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edges.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanExactlyNEdges
	(
		ScanExactlyNEdgesState&					ioState,
		const avl::Image&						inImage,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::EdgeScanParams&				inEdgeScanParams,	
		int										inEdgeCount,		
		avl::Selection::Type					inEdgeSelection,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Edge1D> >&	outEdges,		
		atl::Conditional<atl::Array<avl::Gap1D> >&	outGaps,		
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest dark or bright pixel peak along a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeSelection">Selection mode of the resulting ridge.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outRidge">Found ridge.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanSingleRidge
	(
		ScanSingleRidgeState&					ioState,
		const avl::Image&						inImage,				
		const avl::Path&						inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int										inScanWidth,			
		avl::InterpolationMethod::Type			inImageInterpolation,	
		const avl::RidgeScanParams&				inRidgeScanParams,		
		avl::Selection::Type					inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<avl::Ridge1D>&			outRidge,				
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,	
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),	
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple dark or bright pixel peaks along a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inMinDistance">Minimal distance between consecutive ridges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive ridges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outGaps">Gaps between consecutive ridges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanMultipleRidges
	(
		ScanMultipleRidgesState&				ioState,
		const avl::Image&						inImage,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::RidgeScanParams&				inRidgeScanParams,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Array<avl::Ridge1D>&				outRidges,			
		atl::Array<avl::Gap1D>&					outGaps,			
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest dark or bright pixel peak along a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeCount">Number of ridges to be found. Default value: 1.</param>
	/// <param name="inRidgeSelection">Selection mode of the resulting ridges.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive ridges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive ridges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outGaps">Gaps between consecutive edges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanExactlyNRidges
	(
		ScanExactlyNRidgesState&				ioState,
		const avl::Image&						inImage,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::RidgeScanParams&				inRidgeScanParams,	
		int										inRidgeCount,		
		avl::Selection::Type					inRidgeSelection,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Ridge1D> >&	outRidges,	
		atl::Conditional<atl::Array<avl::Gap1D> >&	outGaps,		
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest pair of edges across a given path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripe">Found stripe.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanSingleStripe
	(
		ScanSingleStripeState&					ioState,
		const avl::Image&						inImage,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::StripeScanParams&			inStripeScanParams,	
		avl::Selection::Type					inStripeSelection,	
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<avl::Stripe1D>&		outStripe,			
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple pairs of edges across a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outGaps">Gaps between consecutive stripes.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanMultipleStripes
	(
		ScanMultipleStripesState&				ioState,
		const avl::Image&						inImage,				
		const avl::Path&						inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int										inScanWidth,			
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::StripeScanParams&			inStripeScanParams,	
		float								inMinGapWidth,		
		atl::Optional<float>				inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Array<avl::Stripe1D>&				outStripes,			
		atl::Array<avl::Gap1D>&					outGaps,			
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),    
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of multiple pairs of opposite edges across a given path.</summary>
	/// <param name="inImage">Input image to be measured.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeCount">Number of stripes to be found. Default value: 1.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripes.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outGaps">Gaps between consecutive stripes.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagBrightnessProfile">Extracted image profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points that contributed to a single value of the extracted profile.</param>
	AVL_FUNCTION void AvsFilter_ScanExactlyNStripes
	(
		ScanExactlyNStripesState&				ioState,
		const avl::Image&						inImage,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inImageInterpolation, 
		const avl::StripeScanParams&			inStripeScanParams,	
		int										inStripeCount,		
		avl::Selection::Type					inStripeSelection,	
		float								inMinGapWidth,	
		atl::Optional<float>				inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Conditional<atl::Array<avl::Stripe1D> >&	outStripes,	
		atl::Conditional<atl::Array<avl::Gap1D> >&		outGaps,	
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagBrightnessProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>(),    
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_1DEDGEDETECTION_H

