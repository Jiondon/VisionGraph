//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_SHAPEFITTING_H
#define AVS_SHAPEFITTING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Enums/EdgeTransition.h"
#include "Enums/Polarity.h"
#include "Enums/Selection.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/CircleFittingMethod.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"
#include "ComputerVision/1DEdgeDetection/ScanStructs.h"
#include "ComputerVision/ShapeFitting/FittingMap.h"
#include "ComputerVision/ShapeFitting/FittingFields.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Path/Path.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Fits the given contour to the edges of the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMaxDeviation">Maximal distance between the fitted and the expected contours. Default value: 15.</param>
	/// <param name="inMaxSlant">Maximal angle between corresponding tangents of the fitted and the expected contours. Default value: 45.0f.</param>
	/// <param name="inStep">Distance between consecutive fitted points measured along the expected contour. Default value: 6.</param>
	/// <param name="inMinEdgeMagnitude">Default value: 0.</param>
	/// <param name="inMaxEdgeMagnitude">Default value: 255.</param>
	/// <param name="inGammaFactor">Default value: 1.0f.</param>
	/// <param name="inSmoothingStdDev">Default value: 0.0f.</param>
	AVL_FUNCTION void FitContour_Adaptive_Experimental
	(
		const avl::Image&				inImage,
		const avl::Path&				inExpectedContour,
		int								inMaxDeviation,			
		float							inMaxSlant,				
		int								inStep,					
		avl::EdgeTransition::Type		inEdgeTransition,
		int								inMinEdgeMagnitude,
		int								inMaxEdgeMagnitude,
		float							inGammaFactor,
		avl::InterpolationMethod::Type	inInterpolationMethod,
		float							inSmoothingStdDev,
		avl::Path&						outContour,
		avl::Image&						diagEdgeImage = atl::Dummy<avl::Image>(),
		avl::Path&						diagEdgeContour = atl::Dummy<avl::Path>()
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inStep">Default value: 5.</param>
	/// <param name="inMaxAngleDeviation">Default value: 45.0f.</param>
	AVL_FUNCTION void ImageShortestPath_Experimental
	(
		const avl::Image&			inImage,
		int							inStep,
		float						inMaxAngleDeviation,
		atl::Array<avl::Location>&	outLocations
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast circle fitting on images.</summary>
	/// <param name="inImageFormat">Dimensions, depth and pixel type of the images on which fitting will be performed.</param>
	/// <param name="inFittingField">Defines a ring in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for circle fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreateCircleFittingMap
	(
		const avl::ImageFormat&							inImageFormat,			
		const avl::CircleFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		const int										inScanCount,			
		const int										inScanWidth,			
		avl::InterpolationMethod::Type					inImageInterpolation,	
		avl::CircleFittingMap&							outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast arc fitting on images.</summary>
	/// <param name="inImageFormat">Dimensions, depth and pixel type of the images on which fitting will be performed.</param>
	/// <param name="inFittingField">Defines a ring section in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the arc. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for arc fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreateArcFittingMap
	(
		const avl::ImageFormat&							inImageFormat,			
		const avl::ArcFittingField&						inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		const int										inScanCount,			
		const int										inScanWidth,			
		avl::InterpolationMethod::Type					inImageInterpolation,	
		avl::ArcFittingMap&								outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast segment fitting on images.</summary>
	/// <param name="inImageFormat">Dimensions, depth and pixel type of the images on which fitting will be performed.</param>
	/// <param name="inFittingField">Defines a rectangle in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for segment fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreateSegmentFittingMap
	(
		const avl::ImageFormat&							inImageFormat,			
		const avl::SegmentFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		const int										inScanCount,			
		const int										inScanWidth,			
		avl::InterpolationMethod::Type					inImageInterpolation,	
		SegmentFittingMap&								outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Precomputes a data object that is required for fast path fitting on images.</summary>
	/// <param name="inImageFormat">Dimensions, depth and pixel type of the images on which fitting will be performed.</param>
	/// <param name="inFittingField">Defines a stripe in which scan segments will be created.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: avl::InterpolationMethod::NearestNeighbour.</param>
	/// <param name="outFittingMap">Optimized data required for path fitting.</param>
	/// <param name="diagScanSegments">Segments along which the scans will be run.</param>
	/// <param name="diagSamplingAreas">Scan fields created for point detection.</param>
	AVL_FUNCTION void CreatePathFittingMap
	(
		const avl::ImageFormat&							inImageFormat,			
		const avl::PathFittingField&					inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>						inScanStep,				
		const int										inScanWidth,			
		avl::InterpolationMethod::Type					inImageInterpolation,	
		avl::PathFittingMap&							outFittingMap,			
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::SelectionBest.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitCircleToEdges
	(
		const avl::Image&					inImage,				
		const CircleFittingMap&				inFittingMap,			
		const EdgeScanParams&				inEdgeScanParams,		
		avl::Selection::Type				inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>& 	outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeSelection">Selection mode of ridges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void FitCircleToRidges
	(
		const avl::Image&					inImage,				
		const avl::CircleFittingMap&		inFittingMap,			
		const RidgeScanParams&				inRidgeScanParams,		
		avl::Selection::Type				inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>& 	outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series 1D stripe detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle in the middle of found stripe.</param>
	/// <param name="outInnerCircle">Fitted inner circle.</param>
	/// <param name="outOuterCircle">Fitted outer circle.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle circle of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitCircleToStripe
	(
		const avl::Image&				inImage,				
		const avl::CircleFittingMap&	inFittingMap,			
		const StripeScanParams&			inStripeScanParams,		
		avl::Selection::Type			inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float						inMaxIncompleteness,	
		avl::CircleFittingMethod::Type	inFittingMethod,		
		atl::Optional<MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>&	outCircle,				
		atl::Conditional<avl::Circle2D>&	outInnerCircle,			
		atl::Conditional<avl::Circle2D>&	outOuterCircle,			
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitArcToEdges
	(
		const avl::Image&				inImage,				
		const avl::ArcFittingMap&		inFittingMap,			
		const EdgeScanParams&			inEdgeScanParams,		
		avl::Selection::Type			inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float						inMaxIncompleteness,	
		avl::CircleFittingMethod::Type	inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>& 	outArc,					
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeSelection">Selection mode of ridges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void FitArcToRidges
	(
		const avl::Image&				inImage,				
		const avl::ArcFittingMap&		inFittingMap,			
		const RidgeScanParams&			inRidgeScanParams,		
		avl::Selection::Type			inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float						inMaxIncompleteness,	
		avl::CircleFittingMethod::Type	inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>& 	outArc,					
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc in the middle of found stripe.</param>
	/// <param name="outInnerArc">Fitted inner arc.</param>
	/// <param name="outOuterArc">Fitted outer arc.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle arc of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitArcToStripe
	(
		const avl::Image&				inImage,				
		const avl::ArcFittingMap&		inFittingMap,			
		const StripeScanParams&			inStripeScanParams,		
		avl::Selection::Type			inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float						inMaxIncompleteness,	
		avl::CircleFittingMethod::Type	inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>&	outArc,					
		atl::Conditional<avl::Arc2D>&	outInnerArc,			
		atl::Conditional<avl::Arc2D>&	outOuterArc,			
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitSegmentToEdges
	(
		const avl::Image&				inImage,				
		const avl::SegmentFittingMap&	inFittingMap,			
		const EdgeScanParams&			inEdgeScanParams,		
		avl::Selection::Type			inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float						inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>&	outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&		diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&		diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeSelection">Selection mode of ridges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void FitSegmentToRidges
	(
		const avl::Image&					inImage,				
		const avl::SegmentFittingMap&		inFittingMap,			
		const RidgeScanParams&				inRidgeScanParams,		
		avl::Selection::Type				inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		atl::Optional<MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>& 	outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL, 
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment in the middle of found stripe.</param>
	/// <param name="outLeftSegment">Fitted left segment.</param>
	/// <param name="outRightSegment">Fitted right segment.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle segment of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitSegmentToStripe
	(
		const avl::Image&					inImage,				
		const avl::SegmentFittingMap&		inFittingMap,			
		const StripeScanParams&				inStripeScanParams,		
		avl::Selection::Type				inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>& 	outSegment,				
		atl::Conditional<avl::Segment2D>& 	outLeftSegment,			
		atl::Conditional<avl::Segment2D>& 	outRightSegment,		
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of edges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: atl::NIL.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitPathToEdges
	(
		const avl::Image&							inImage,			
		const PathFittingMap&						inFittingMap,		
		const EdgeScanParams&						inEdgeScanParams,	
		avl::Selection::Type						inEdgeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>							inMaxInterpolationLength,	
		atl::Optional<float>					inMaxDeviationDelta,		
		float									inMaxIncompleteness,	
		atl::Conditional<avl::Path>&				outPath,			
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Array<avl::Profile>&					diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&					diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process.</param>
	/// <param name="inRidgeSelection">Selection mode of ridges. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: atl::NIL.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void FitPathToRidges
	(
		const avl::Image&							inImage,			
		const avl::PathFittingMap&					inFittingMap,		
		const RidgeScanParams&						inRidgeScanParams,	
		avl::Selection::Type						inRidgeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>							inMaxInterpolationLength,	
		atl::Optional<float>					inMaxDeviationDelta,		
		float									inMaxIncompleteness,	
		atl::Conditional<avl::Path>&				outPath,			
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Array<avl::Profile>&					diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&					diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingMap">Input fitting map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: atl::NIL.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path in the middle of found stripe.</param>
	/// <param name="outLeftPath">Fitted left path.</param>
	/// <param name="outRightPath">Fitted right path.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void FitPathToStripe
	(
		const avl::Image&								inImage,			
		const avl::PathFittingMap&						inFittingMap,		
		const StripeScanParams&							inStripeScanParams,		
		avl::Selection::Type							inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,		
		atl::Optional<int>								inMaxInterpolationLength,	
		atl::Optional<float>							inMaxDeviationDelta,		
		float											inMaxIncompleteness,	
		atl::Conditional<avl::Path>&					outPath,			
		atl::Conditional<avl::Path>&					outLeftPath,		
		atl::Conditional<avl::Path>&					outRightPath,		
		atl::Array<atl::Conditional<avl::Stripe1D> >&	outStripes,			
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Array<avl::Profile>&						diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&						diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	struct CircleFittingState : public avl::BaseState
	{
		avl::CircleFittingMap fittingMap;
	};

	struct ArcFittingState : public avl::BaseState
	{
		avl::ArcFittingMap fittingMap;
	};

	struct SegmentFittingState : public avl::BaseState
	{
		avl::SegmentFittingMap fittingMap;
	};

	struct PathFittingState : public avl::BaseState
	{
		avl::PathFittingMap fittingMap;
	};

	typedef CircleFittingState	FitCircleToEdgesState;
	typedef CircleFittingState	FitCircleToRidgesState;
	typedef CircleFittingState	FitCircleToStripeState;
	typedef ArcFittingState		FitArcToEdgesState;
	typedef ArcFittingState		FitArcToRidgesState;
	typedef ArcFittingState		FitArcToStripeState;
	typedef SegmentFittingState FitSegmentToEdgesState;
	typedef SegmentFittingState FitSegmentToRidgesState;
	typedef SegmentFittingState FitSegmentToStripeState;
	typedef PathFittingState	FitPathToEdgesState;
	typedef PathFittingState	FitPathToRidgesState;
	typedef PathFittingState	FitPathToStripeState;


	/// <summary>Performs a series of 1D edge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingField">Circle fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitCircleToEdges
	(
		FitCircleToEdgesState&						ioState,
		const avl::Image&							inImage,				
		const avl::CircleFittingField&				inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>		inFittingFieldAlignment,
		int											inScanCount,			
		int											inScanWidth,			
		const avl::InterpolationMethod::Type		inImageInterpolation,	
		const avl::EdgeScanParams&					inEdgeScanParams,		
		avl::Selection::Type						inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,		
		float									inMaxIncompleteness,	
		avl::CircleFittingMethod::Type				inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>		inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>& 			outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::CircleFittingField&>		outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&					diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&				diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&					diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&					diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingField">Circle fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeSelection">Selection mode of ridges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void AvsFilter_FitCircleToRidges
	(
		FitCircleToRidgesState&					ioState,
		const avl::Image&						inImage,				
		const avl::CircleFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::RidgeScanParams&				inRidgeScanParams,		
		avl::Selection::Type					inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float								inMaxIncompleteness,	
		avl::CircleFittingMethod::Type			inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>& 		outCircle,				
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::CircleFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series 1D stripe detections and finds a circle that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit the circle to.</param>
	/// <param name="inFittingField">Circle fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  circle. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit a circle. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outCircle">Fitted circle in the middle of found stripe.</param>
	/// <param name="outInnerCircle">Fitted inner circle.</param>
	/// <param name="outOuterCircle">Fitted outer circle.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle circle of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual circle points and the corresponding reference circle points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitCircleToStripe
	(
		FitCircleToStripeState&					ioState,
		const avl::Image&						inImage,				
		const avl::CircleFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::StripeScanParams&			inStripeScanParams,		
		avl::Selection::Type					inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float								inMaxIncompleteness,	
		avl::CircleFittingMethod::Type			inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Circle2D>&		outCircle,				
		atl::Conditional<avl::Circle2D>&		outInnerCircle,			
		atl::Conditional<avl::Circle2D>&		outOuterCircle,			
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,		
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::CircleFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingField">Arc fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  arc. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitArcToEdges
	(
		FitArcToEdgesState&						ioState,
		const avl::Image&						inImage,				
		const avl::ArcFittingField&				inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::EdgeScanParams&				inEdgeScanParams,		
		avl::Selection::Type					inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float								inMaxIncompleteness,	
		avl::CircleFittingMethod::Type			inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>& 			outArc,					
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::ArcFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingField">Arc fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  arc. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeSelection">Selection mode of ridges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void AvsFilter_FitArcToRidges
	(
		FitArcToRidgesState&				ioState,
		const avl::Image&					inImage,				
		const avl::ArcFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int									inScanCount,			
		int									inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::RidgeScanParams&			inRidgeScanParams,		
		avl::Selection::Type				inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>& 		outArc,					
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::ArcFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&			diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&		diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and finds an arc that best matches the detected points.</summary>
	/// <param name="inImage">Input image to fit arc to.</param>
	/// <param name="inFittingField">Arc fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  arc. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inFittingMethod">Method used to fit an arc. Default value: AlgebraicTaubin.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outArc">Fitted arc in the middle of found stripe.</param>
	/// <param name="outInnerArc">Fitted inner arc.</param>
	/// <param name="outOuterArc">Fitted outer arc.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle arc of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual arc points and the corresponding reference arc points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitArcToStripe
	(
		FitArcToStripeState&				ioState,
		const avl::Image&					inImage,				
		const avl::ArcFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int									inScanCount,			
		int									inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::StripeScanParams&		inStripeScanParams,		
		avl::Selection::Type				inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		avl::CircleFittingMethod::Type		inFittingMethod,		
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Arc2D>&		outArc,					
		atl::Conditional<avl::Arc2D>&		outInnerArc,			
		atl::Conditional<avl::Arc2D>&		outOuterArc,			
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,	
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::ArcFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&			diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&		diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingField">Segment fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitSegmentToEdges
	(
		FitSegmentToEdgesState&					ioState,
		const avl::Image&						inImage,				
		const avl::SegmentFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::EdgeScanParams&				inEdgeScanParams,		
		avl::Selection::Type					inEdgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float								inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>& 		outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::SegmentFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingField">Segment fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 1.0f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeSelection">Selection mode of ridges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment or nothing if the fitting fails.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void AvsFilter_FitSegmentToRidges
	(
		FitSegmentToRidgesState&			ioState,
		const avl::Image&					inImage,				
		const avl::SegmentFittingField&		inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int									inScanCount,			
		int									inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::RidgeScanParams&			inRidgeScanParams,		
		avl::Selection::Type				inRidgeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float							inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>& 	outSegment,				
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::SegmentFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&			diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&		diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&			diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&			diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and finds a segment that best matches the detected points.</summary>
	/// <param name="inImage">Image to fit segment to.</param>
	/// <param name="inFittingField">Segment fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">The number of points that will be searched to estimate the position of the  segment. Default value: 10.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="outSegment">Fitted segment in the middle of found stripe.</param>
	/// <param name="outLeftSegment">Fitted left segment.</param>
	/// <param name="outRightSegment">Fitted right segment.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outStripePoints">Extracted points of middle segment of an image stripe.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual segment points and the corresponding reference segment points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitSegmentToStripe
	(
		FitSegmentToStripeState&				ioState,
		const avl::Image&						inImage,				
		const avl::SegmentFittingField&			inFittingField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		int										inScanCount,			
		int										inScanWidth,			
		const avl::InterpolationMethod::Type	inImageInterpolation,	
		const avl::StripeScanParams&			inStripeScanParams,		
		avl::Selection::Type					inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		float								inMaxIncompleteness,	
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression, 
		atl::Conditional<avl::Segment2D>& 		outSegment,				
		atl::Conditional<avl::Segment2D>& 		outLeftSegment,			
		atl::Conditional<avl::Segment2D>& 		outRightSegment,		
		atl::Optional<atl::Array<atl::Conditional<avl::Stripe1D> >&>	outStripes = atl::NIL,		
		atl::Optional<atl::Array<avl::Point2D>&>	outStripePoints = atl::NIL,		
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,	
		atl::Optional<avl::SegmentFittingField&>	outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),		
		atl::Array<avl::Rectangle2D>&			diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Profile>&				diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&				diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D edge detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingField">Path fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: 5.0f.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inEdgeSelection">Selection mode of edges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: 1.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of edge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitPathToEdges
	(
		FitPathToEdgesState&							ioState,
		const avl::Image&								inImage,			
		const avl::PathFittingField&					inFittingField,		
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>						inScanStep,			
		int												inScanWidth,		
		const avl::InterpolationMethod::Type			inImageInterpolation,	
		const avl::EdgeScanParams&						inEdgeScanParams,	
		avl::Selection::Type							inEdgeSelection,	
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Optional<int>								inMaxInterpolationLength,	
		atl::Optional<float>						inMaxDeviationDelta,		
		float										inMaxIncompleteness,	
		atl::Conditional<avl::Path>&					outPath,			
		atl::Optional<atl::Array<atl::Conditional<avl::Edge1D> >&>	outEdges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Optional<avl::PathFittingField&>			outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),	
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),	
		atl::Array<avl::Profile>&						diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&						diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D ridge detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingField">Path fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: 5.0f.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Dark ).</param>
	/// <param name="inRidgeSelection">Selection mode of ridges.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: 1.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of ridge points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path or nothing if the fitting failed.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the ridge operator response.</param>
	AVL_FUNCTION void AvsFilter_FitPathToRidges
	(
		FitPathToRidgesState&							ioState,
		const avl::Image&								inImage,			
		const avl::PathFittingField&					inFittingField,		
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>						inScanStep,			
		int												inScanWidth,		
		const avl::InterpolationMethod::Type			inImageInterpolation,	
		const avl::RidgeScanParams&						inRidgeScanParams,	
		avl::Selection::Type							inRidgeSelection,	
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Optional<int>								inMaxInterpolationLength,	
		atl::Optional<float>						inMaxDeviationDelta,		
		float										inMaxIncompleteness,	
		atl::Conditional<avl::Path>&					outPath,			
		atl::Optional<atl::Array<atl::Conditional<avl::Ridge1D> >&>	outRidges = atl::NIL,	
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Optional<avl::PathFittingField&>			outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),	
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),	
		atl::Array<avl::Profile>&						diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&						diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a series of 1D stripe detections and creates a path from the detected points.</summary>
	/// <param name="inImage">Image to fit the path to.</param>
	/// <param name="inFittingField">Path fitting field.</param>
	/// <param name="inFittingFieldAlignment">Adjusts the fitting field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanStep">Optional implicit conversion of the input path to an equidistant one. Default value: 5.0f.</param>
	/// <param name="inScanWidth">The width of each scan field (in pixels). Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used for extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive points not found. Default value: 1.</param>
	/// <param name="inMaxDeviationDelta">Maximal difference between deviations of consecutive path points. Default value: atl::NIL.</param>
	/// <param name="inMaxIncompleteness">Maximal fraction of stripe points not found. Default value: 0.1f.</param>
	/// <param name="outPath">Fitted path in the middle of found stripe.</param>
	/// <param name="outLeftPath">Fitted left path.</param>
	/// <param name="outRightPath">Fitted right path.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outDeviationProfile">Profile of distances between the actual path points and the corresponding reference path points.</param>
	/// <param name="outAlignedFittingField">Fitting field used; in the image coordinate system.</param>
	/// <param name="diagScanSegments">Segments along which the scans were run.</param>
	/// <param name="diagSamplingAreas">Areas from which the input image is sampled.</param>
	/// <param name="diagBrightnessProfiles">Extracted image profiles.</param>
	/// <param name="diagResponseProfiles">Profiles of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_FitPathToStripe
	(
		FitPathToStripeState&							ioState,
		const avl::Image&								inImage,			
		const avl::PathFittingField&					inFittingField,		
		atl::Optional<const avl::CoordinateSystem2D&>	inFittingFieldAlignment,
		atl::Optional<float>						inScanStep,			
		int												inScanWidth,		
		const avl::InterpolationMethod::Type			inImageInterpolation,	
		const avl::StripeScanParams&					inStripeScanParams,	
		avl::Selection::Type							inStripeSelection,		
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Optional<int>								inMaxInterpolationLength,	
		atl::Optional<float>							inMaxDeviationDelta,		
		float											inMaxIncompleteness,	
		atl::Conditional<avl::Path>&					outPath,			
		atl::Conditional<avl::Path>&					outLeftPath,		
		atl::Conditional<avl::Path>&					outRightPath,		
		atl::Array<atl::Conditional<avl::Stripe1D> >&	outStripes,			
		atl::Optional<atl::Conditional<avl::Profile>&>	outDeviationProfile = atl::NIL,
		atl::Optional<avl::PathFittingField&>			outAlignedFittingField = atl::NIL,	
		atl::Array<avl::Segment2D>&						diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),	
		atl::Array<avl::Rectangle2D>&					diagSamplingAreas = atl::Dummy< atl::Array<avl::Rectangle2D> >(),	
		atl::Array<avl::Profile>&						diagBrightnessProfiles = atl::Dummy< atl::Array<avl::Profile> >(),	
		atl::Array<avl::Profile>&						diagResponseProfiles = atl::Dummy< atl::Array<avl::Profile> >()	
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_SHAPEFITTING_H

