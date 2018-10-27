//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_SHAPEFITTING3D_H
#define AVS_SHAPEFITTING3D_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Enums/Selection.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/CircleFittingMethod.h"
#include "Enums/MeasureObjectMethod.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"
#include "ComputerVision/1DEdgeDetection/ScanParams3D.h"
#include "ComputerVision/1DEdgeDetection/ScanStructs3D.h"
#include "ComputerVision/1DEdgeDetection/ScanMapState.h"
#include "ComputerVision/ShapeFitting/FittingMap.h"
#include "ComputerVision/ShapeFitting/FittingFields.h"
#include "ComputerVision/ImageAnalysis/ScanFields.h"
#include "Geometry3D/Geometry3D.h"
#include "Surface/Surface.h"
#include "Surface/SurfaceFormat.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Precomputes a data object that is required for fast circle fitting on surfaces.</summary>
	/// <param name="inSurfaceFormat">Dimensions, depth image pixel type, coordinate offsets and scales of a surface on which circle fitting will be performed.</param>
	/// <param name="inFittingField">Defines a ring in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field in pixels of the surface depth image. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of depth image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for circle fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreateCircleFittingMap3D
	(
		const avl::SurfaceFormat&						inSurfaceFormat,		
		const avl::CircleFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		const int										inScanCount,			
		int												inScanWidth,			
		avl::InterpolationMethod::Type					inSurfaceInterpolation,	
		avl::CircleFittingMap&							outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast segment fitting on surfaces.</summary>
	/// <param name="inSurfaceFormat">Dimensions, depth image pixel type, coordinate offsets and scales of a surface on which segment fitting will be performed.</param>
	/// <param name="inFittingField">Defines a rectangle in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field in pixels of the surface depth image. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of depth image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for segment fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreateSegmentFittingMap3D
	(
		const avl::SurfaceFormat&						inSurfaceFormat,		
		const avl::SegmentFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		const int										inScanCount,			
		int												inScanWidth,			
		avl::InterpolationMethod::Type					inSurfaceInterpolation,	
		avl::SegmentFittingMap&							outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast path fitting on surfaces.</summary>
	/// <param name="inSurfaceFormat">Dimensions, depth image pixel type, coordinate offsets and scales of a surface on which path fitting will be performed.</param>
	/// <param name="inFittingField">Defines a stripe in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">The width of each scan field in pixels of the surface depth image. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of depth image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for path fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreatePathFittingMap3D
	(
		const avl::SurfaceFormat&						inSurfaceFormat,		
		const avl::PathFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>							inScanStep,				
		int												inScanWidth,			
		avl::InterpolationMethod::Type					inSurfaceInterpolation,	
		avl::PathFittingMap&							outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit the circle to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::SelectionBest.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitCircleToEdges3D
	(
		const avl::Surface&					inSurface,				
		const CircleFittingMap&				inFittingMap,			
		const EdgeScanParams3D&				inEdgeScanParams,		
		avl::Selection::Type				inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		float								inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle3D>& 	outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit the circle to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle in the middle of found stripe or nothing if the fitting fails.</param>
	/// <param name="outInnerCircle">Fitted inner circle.</param>
	/// <param name="outOuterCircle">Fitted outer circle.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle circle of a surface stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitCircleToStripe3D
	(
		const avl::Surface&					inSurface,				
		const CircleFittingMap&				inFittingMap,			
		const StripeScanParams3D&			inStripeScanParams,		
		avl::Selection::Type				inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		float								inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle3D>& 	outCircle,				
		atl::Conditional<avl::Circle3D>&	outInnerCircle,			
		atl::Conditional<avl::Circle3D>&	outOuterCircle,			
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point3D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit segment to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitSegmentToEdges3D
	(
		const avl::Surface&				inSurface,				
		const avl::SegmentFittingMap&	inFittingMap,			
		const EdgeScanParams3D&			inEdgeScanParams,		
		avl::Selection::Type			inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		float						inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment3D>&	outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit segment to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outLeftSegment">Fitted left segment.</param>
	/// <param name="outRightSegment">Fitted right segment.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle segment of a surface stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitSegmentToStripe3D
	(
		const avl::Surface&				inSurface,				
		const avl::SegmentFittingMap&	inFittingMap,			
		const StripeScanParams3D&		inStripeScanParams,		
		avl::Selection::Type			inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		float							inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment3D>&	outSegment,				
		atl::Conditional<avl::Segment3D>& 	outLeftSegment,			
		atl::Conditional<avl::Segment3D>& 	outRightSegment,		
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point3D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and creates a path from the detected points.</summary>
	/// <param name="inSurface">Surface to fit the path to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxPathInterpolationLength">Maximal number of consecutive points not found. Default value: atl::NIL.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitPathToEdges3D
	(
		const avl::Surface&				inSurface,				
		const avl::PathFittingMap&		inFittingMap,			
		const EdgeScanParams3D&			inEdgeScanParams,		
		avl::Selection::Type			inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		atl::Optional<int>				inMaxPathInterpolationLength,	
		atl::Optional<float>			inMaxDeviationDelta,		
		float							inMaxIncompleteness,	
		atl::Conditional<atl::Array<avl::Point3D> >&	outPath,	
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),		
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and creates a path from the detected points.</summary>
	/// <param name="inSurface">Surface to fit the path to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxPathInterpolationLength">Maximal number of consecutive points not found. Default value: atl::NIL.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outLeftPath">Fitted left path.</param>
	/// <param name="outRightPath">Fitted right path.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitPathToStripe3D
	(
		const avl::Surface&				inSurface,				
		const avl::PathFittingMap&		inFittingMap,			
		const StripeScanParams3D&		inStripeScanParams,		
		avl::Selection::Type			inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		atl::Optional<int>				inMaxPathInterpolationLength,	
		atl::Optional<float>			inMaxDeviationDelta,	
		float							inMaxIncompleteness,	
		atl::Conditional<atl::Array<avl::Point3D> >&	outPath,	
		atl::Conditional<atl::Array<avl::Point3D> >&	outLeftPath,	
		atl::Conditional<atl::Array<avl::Point3D> >&	outRightPath,	
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),		
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>(Pre)computes surface sampling locations used by MeasureObjectWidth3D function.</summary>
	/// <param name="inSurfaceFormat">Information about dimensions, depth and pixel type of the surface.</param>
	/// <param name="inScanField">Field in which scans will be performed.</param>
	/// <param name="inScanFieldAlignment">Adjusts the scan field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">Number of scans to be performed. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the scan area. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outAlignedScanField">Field in which the scans will be performed.</param>
	/// <param name="diagScanSegments">Array of scan segments.</param>
	AVL_FUNCTION void CreateSurfaceMeasurementMap
	(
		const avl::SurfaceFormat&		inSurfaceFormat,			
		const avl::SegmentScanField&	inScanField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanFieldAlignment,
		int								inScanCount,			
		int								inScanWidth,			
		avl::InterpolationMethod::Type	inSurfaceInterpolation,	
		atl::Array<avl::ScanMap>&		outMeasurementMap,
		atl::Optional<avl::SegmentScanField&>	outAlignedScanField = atl::NIL,	
		atl::Array<avl::Segment2D>&		diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the width of an object using stripe detection.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inMeasurementMap">Input measurement map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the object stripe extraction process.</param>
	/// <param name="inMeasureMethod">Method used to measure the object.</param>
	/// <param name="inStripeSelection">Selection mode of edges of the object. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="inOutlierCount">Determines how many outlying points are rejected before the width is measured.</param>
	/// <param name="outObjectWidth">Width of the object.</param>
	/// <param name="outSegment1">First edge of the object.</param>
	/// <param name="outSegment2">Second edge of the object.</param>
	/// <param name="diagPoints1">Detected edge points on the first side.</param>
	/// <param name="diagPoints2">Detected edge points on the second side.</param>
	AVL_FUNCTION void MeasureObjectWidth3D
	(
		const avl::Surface&				inSurface,									
		const atl::Array<avl::ScanMap>&	inMeasurementMap,							
		const avl::StripeScanParams3D&	inStripeScanParams,							
		avl::MeasureObjectMethod::Type	inMeasureMethod,							
		avl::Selection::Type			inStripeSelection,							
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,				
		atl::Optional<int>				inMaxInterpolationLength,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,				
		int									inOutlierCount,							
		atl::Conditional<float>&			outObjectWidth,							
		atl::Conditional<avl::Segment2D>&	outSegment1,							
		atl::Conditional<avl::Segment2D>&	outSegment2,							
		atl::Array<avl::Point3D>&			diagPoints1 = atl::Dummy< atl::Array<avl::Point3D> >(),							
		atl::Array<avl::Point3D>&			diagPoints2 = atl::Dummy< atl::Array<avl::Point3D> >()								
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	struct CircleFitting3DState : public avl::BaseState
	{
		avl::CircleFittingMap fittingMap;
	};

	struct SegmentFitting3DState : public avl::BaseState
	{
		avl::SegmentFittingMap fittingMap;
	};

	struct PathFitting3DState : public avl::BaseState
	{
		avl::PathFittingMap fittingMap;
	};

	typedef CircleFitting3DState FitCircleToEdges3DState;
	typedef CircleFitting3DState FitCircleToStripe3DState;
	typedef SegmentFitting3DState FitSegmentToEdges3DState;
	typedef SegmentFitting3DState FitSegmentToStripe3DState;
	typedef PathFitting3DState FitPathToEdges3DState;
	typedef PathFitting3DState FitPathToStripe3DState;


	/// <summary>Performs a series of 1D edge detections in 3D and finds a circle that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit the circle to.</param>
	/// <param name="inFittingField">Circle fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitCircleToEdges3D
	(
		FitCircleToEdges3DState&					ioState,
		const avl::Surface&							inSurface,				
		const avl::CircleFittingField&				inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int											inScanCount,			
		int											inScanWidth,			
		const avl::InterpolationMethod::Type		inSurfaceInterpolation,	
		const avl::EdgeScanParams3D&				inEdgeScanParams,		
		avl::Selection::Type						inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,		
		atl::Optional<int>							inMaxInterpolationLength,	
		float										inMaxIncompleteness,	
		avl::CircleFittingMethod::Type				inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>		inOutlierSuppression, 
		atl::Conditional<avl::Circle3D>& 			outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::CircleFittingField&>		outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&					diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&				diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&					diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&					diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections in 3D and finds a circle that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit the circle to.</param>
	/// <param name="inFittingField">Circle fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil MinStripeWidth: 0.0f MaxStripeWidth: Nil StripePolarity: High ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle in the middle of found stripe or nothing if the fitting fails.</param>
	/// <param name="outInnerCircle">Fitted inner circle.</param>
	/// <param name="outOuterCircle">Fitted outer circle.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle circle of a surface stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitCircleToStripe3D
	(
		FitCircleToStripe3DState&					ioState,
		const avl::Surface&							inSurface,				
		const avl::CircleFittingField&				inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int											inScanCount,			
		int											inScanWidth,			
		const avl::InterpolationMethod::Type		inSurfaceInterpolation,	
		const avl::StripeScanParams3D&				inStripeScanParams,		
		avl::Selection::Type						inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,		
		atl::Optional<int>							inMaxInterpolationLength,	
		float										inMaxIncompleteness,	
		avl::CircleFittingMethod::Type				inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>		inOutlierSuppression, 
		atl::Conditional<avl::Circle3D>& 			outCircle,				
		atl::Conditional<avl::Circle3D>&			outInnerCircle,			
		atl::Conditional<avl::Circle3D>&			outOuterCircle,			
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point3D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::CircleFittingField&>		outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&					diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&				diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&					diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&					diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections in 3D and finds a segment that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit segment to.</param>
	/// <param name="inFittingField">Segment fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitSegmentToEdges3D
	(
		FitSegmentToEdges3DState&				ioState,
		const avl::Surface&						inSurface,				
		const avl::SegmentFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inSurfaceInterpolation,	
		const avl::EdgeScanParams3D&			inEdgeScanParams,		
		avl::Selection::Type					inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		float									inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment3D>& 		outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::SegmentFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections in 3D and finds a segment that best matches the detected points.</summary>
	/// <param name="inSurface">Surface to fit segment to.</param>
	/// <param name="inFittingField">Segment fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil MinStripeWidth: 0.0f MaxStripeWidth: Nil StripePolarity: High ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outLeftSegment">Fitted left segment.</param>
	/// <param name="outRightSegment">Fitted right segment.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle segment of a surface stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitSegmentToStripe3D
	(
		FitSegmentToStripe3DState&		ioState,
		const avl::Surface&				inSurface,				
		const avl::SegmentFittingField&	inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int								inScanCount,			
		int								inScanWidth,			
		const avl::InterpolationMethod::Type	inSurfaceInterpolation,	
		const avl::StripeScanParams3D&	inStripeScanParams,		
		avl::Selection::Type			inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		float							inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment3D>&	outSegment,				
		atl::Conditional<avl::Segment3D>& 	outLeftSegment,			
		atl::Conditional<avl::Segment3D>& 	outRightSegment,		
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point3D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::SegmentFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&		diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&	diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&		diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections in 3D and creates a path from the detected points.</summary>
	/// <param name="inSurface">Surface to fit path to.</param>
	/// <param name="inFittingField">Path fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: 5.0f.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="inMaxPathInterpolationLength">Maximal number of consecutive points not found. Default value: 1.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitPathToEdges3D
	(
		FitPathToEdges3DState&					ioState,
		const avl::Surface&						inSurface,				
		const avl::PathFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>					inScanStep,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inSurfaceInterpolation,	
		const avl::EdgeScanParams3D&			inEdgeScanParams,		
		avl::Selection::Type					inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Optional<int>						inMaxPathInterpolationLength,	
		atl::Optional<float>					inMaxDeviationDelta,		
		float									inMaxIncompleteness,	
		atl::Conditional<atl::Array<avl::Point3D> >& 	outPath,		
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceEdge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::PathFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),		
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections in 3D and creates a path from the detected points.</summary>
	/// <param name="inSurface">Surface to fit path to.</param>
	/// <param name="inFittingField">Path fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: 5.0f.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil MinStripeWidth: 0.0f MaxStripeWidth: Nil StripePolarity: High ).</param>
	/// <param name="inStripeSelection">Selection mode of stripes.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="inMaxPathInterpolationLength">Maximal number of consecutive points not found. Default value: 1.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outLeftPath">Fitted left path.</param>
	/// <param name="outRightPath">Fitted right path.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagHeightProfiles">Extracted surface height profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitPathToStripe3D
	(
		FitPathToStripe3DState&					ioState,
		const avl::Surface&						inSurface,				
		const avl::PathFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>					inScanStep,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inSurfaceInterpolation,	
		const avl::StripeScanParams3D&			inStripeScanParams,		
		avl::Selection::Type					inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Optional<int>						inMaxPathInterpolationLength,	
		atl::Optional<float>					inMaxDeviationDelta,		
		float									inMaxIncompleteness,	
		atl::Conditional<atl::Array<avl::Point3D> >& 	outPath,		
		atl::Conditional<atl::Array<avl::Point3D> >& 	outLeftPath,	
		atl::Conditional<atl::Array<avl::Point3D> >& 	outRightPath,	
		atl::Optional<atl::Array<atl::Conditional<avl::SurfaceStripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::PathFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagHeightProfiles = atl::Dummy< atl::Array<avl::Profile> >(),		
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	typedef avl::ScanMapArrayState MeasureObjectWidth3DState;


	/// <summary>Measures the width of an object using stripe detection.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanField">Field in which measurement scans are performed.</param>
	/// <param name="inScanFieldAlignment">Adjusts the scan field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">Number of scans to be performed. Default value: 5.</param>
	/// <param name="inScanWidth">Width of each single scan. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the object stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil MinStripeWidth: 0.0f MaxStripeWidth: Nil StripePolarity: High ).</param>
	/// <param name="inMeasureMethod">Method used to measure the object.</param>
	/// <param name="inStripeSelection">Selection mode of edges of the object.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="inOutlierCount">Determines how many points are not count when object width is measured.</param>
	/// <param name="outObjectWidth">Width of the object.</param>
	/// <param name="outSegment1">First edge of the object.</param>
	/// <param name="outSegment2">Second edge of the object.</param>
	/// <param name="outAlignedScanField">Field in which the scans are performed.</param>
	/// <param name="diagScanSegments">Segments along which the scans are performed.</param>
	/// <param name="diagPoints1">Detected edge points on the first side.</param>
	/// <param name="diagPoints2">Detected edge points on the second side.</param>
	AVL_FUNCTION void AvsFilter_MeasureObjectWidth3D
	(
		MeasureObjectWidth3DState&				ioState,
		const avl::Surface&						inSurface,							
		const avl::SegmentScanField&			inScanField,						
		atl::Optional<const avl::CoordinateSystem2D&>	inScanFieldAlignment,		
		int										inScanCount,						
		int										inScanWidth,						
		avl::InterpolationMethod::Type			inSurfaceInterpolation,				
		const avl::StripeScanParams3D&			inStripeScanParams,					
		avl::MeasureObjectMethod::Type			inMeasureMethod,					
		avl::Selection::Type					inStripeSelection,					
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,				
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,				
		int										inOutlierCount,						
		atl::Conditional<float>&				outObjectWidth,						
		atl::Conditional<avl::Segment2D>&		outSegment1,						
		atl::Conditional<avl::Segment2D>&		outSegment2,						
		atl::Optional<avl::SegmentScanField&>	outAlignedScanField = atl::NIL,		
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),					
		atl::Array<avl::Point3D>&				diagPoints1 = atl::Dummy< atl::Array<avl::Point3D> >(),						
		atl::Array<avl::Point3D>&				diagPoints2 = atl::Dummy< atl::Array<avl::Point3D> >()							
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_SHAPEFITTING3D_H

