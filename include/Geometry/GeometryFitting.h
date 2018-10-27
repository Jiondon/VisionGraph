//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYFITTING_H
#define AVL_GEOMETRYFITTING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/CircleFittingMethod.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "AVLCommon/Enums/TheilSenVariant.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Approximates points with a line using the Least Squares method.</summary>
	AVL_FUNCTION void FitLineToPoints
	(
		const atl::Array<avl::Point2D>&	inPoints,
		avl::Line2D&					outLine,
		atl::Optional<float&>		outError = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a line using selected M-estimator for outlier suppression.</summary>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialLine">Initial approximation (if available). Default value: atl::NIL.</param>
	/// <param name="outInliers">Points matching the computed line.</param>
	AVL_FUNCTION void FitLineToPoints_M
	(
		const atl::Array<avl::Point2D>&				inPoints,
		avl::MEstimator::Type						inOutlierSuppression,
		float										inClippingFactor,		
		int											inIterationCount,		
		atl::Optional<avl::Line2D&>					inInitialLine,			
		avl::Line2D&								outLine,
		atl::Optional<atl::Array<avl::Point2D>&>	outInliers = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a segment using selected outliers suppression method.</summary>
	AVL_FUNCTION void FitSegmentToPoints
	(
		const atl::Array<avl::Point2D>&			inPoints,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		avl::Segment2D&							outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a circle using selected outliers suppression method.</summary>
	/// <param name="outCircle">Fitted circle or nothing if method failed to converge.</param>
	AVL_FUNCTION void FitCircleToPoints
	(
		const atl::Array<avl::Point2D>&			inPoints,
		avl::CircleFittingMethod::Type			inFittingMethod,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		atl::Conditional<avl::Circle2D>&		outCircle			
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with an arc using the selected outliers suppression method.</summary>
	/// <param name="outArc">Fitted arc or nothing if the computations failed to converge.</param>
	AVL_FUNCTION void FitArcToPoints
	(
		const atl::Array<avl::Point2D>&			inPoints,
		avl::CircleFittingMethod::Type			inFittingMethod,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		atl::Conditional<avl::Arc2D>&			outArc				
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates path by an arc using the selected outliers suppression method and considering path's start and end.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outArc">Fitted arc or nothing if the computations failed to converge.</param>
	AVL_FUNCTION void FitArcToPath
	(
		const avl::Path&						inPath,
		avl::CircleFittingMethod::Type			inFittingMethod,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		atl::Conditional<avl::Arc2D>&			outArc				
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a line using a RANSAC algorithm.</summary>
	/// <param name="inMaxOutlierCount">Determines how many outlier points can be present to end the search. Default value: 0.</param>
	/// <param name="inMaxInlierDistance">Distance from the output line for a point to be considered an inlier. Default value: 3.0f.</param>
	/// <param name="inIterationCount">Number of iterations; Auto means that all point pairs will be used. Default value: 42.</param>
	AVL_FUNCTION void FitLineToPoints_RANSAC
	(
		const atl::Array<avl::Point2D>&	inPoints,
		atl::Optional<int>				inMaxOutlierCount,		
		float						inMaxInlierDistance,	
		atl::Optional<int>				inIterationCount,		
		atl::Conditional<avl::Line2D>&	outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a line using TheilSen algorithm, optionally with Siegel's improvement.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inVariant">Switches between Theil-Sen and Siegel methods.</param>
	/// <param name="outLine">Fitted line.</param>
	AVL_FUNCTION void FitLineToPoints_TheilSen
	(
		const atl::Array<avl::Point2D>&	inPoints,	
		avl::TheilSenVariant::Type		inVariant,	
		avl::Line2D&					outLine		
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a line using Least Trimmed Error algorithm.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inSeedSubsetSize">Number of points in one combination for getting a sample line. Default value: 3.</param>
	/// <param name="inEvalSubsetSize">Number of closest points used for evaluation of a sample line, or Auto if seed points are to be used. Default value: atl::NIL.</param>
	/// <param name="outLine">Fitted line.</param>
	/// <param name="outLTInliers">Inlying points of the best LTE line.</param>
	/// <param name="outLTError">The Least Trimmed Error.</param>
	/// <param name="diagIterationCount">Number of combinations considered.</param>
	AVL_FUNCTION void FitLineToPoints_LTE
	(
		const atl::Array<avl::Point2D>&						inPoints,						
		int													inSeedSubsetSize,				
		atl::Optional<int>									inEvalSubsetSize,				
		avl::Line2D&										outLine,						
		atl::Optional<atl::Array<avl::Point2D>&>			outLTInliers = atl::NIL,		
		atl::Optional<float&>							outLTError = atl::NIL,			
		int&												diagIterationCount = atl::Dummy<int>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detect points that lie along multiple segments.</summary>
	/// <param name="inPoints">Points to connect.</param>
	/// <param name="inMaxDistance">Maximum distance between connected points. Default value: 10.0f.</param>
	/// <param name="inMaxRank">Maximum number of neighbour candidates considered when joining points. Default value: 4.</param>
	/// <param name="inMaxRelativeDistance">Maximum distance in relation to the shortest distance for a point. Default value: 2.0f.</param>
	/// <param name="inMaxTurnAngle">Maximum angle between consecutive path segments. Default value: 5.0f.</param>
	/// <param name="inMinPointCount">Minimum number of points in one path. Default value: 3.</param>
	/// <param name="outPointSegments">Segments connecting first and last point of each path.</param>
	/// <param name="outPaths">Paths of connected points.</param>
	AVL_FUNCTION void DetectPointSegments
	(
		const atl::Array<avl::Point2D>&			inPoints,				
		const float							inMaxDistance,			
		const int								inMaxRank,				
		atl::Optional<float>				inMaxRelativeDistance,	
		const float							inMaxTurnAngle,			
		const int								inMinPointCount,		
		atl::Array<avl::Segment2D>&				outPointSegments,		
		atl::Array<avl::Path>&					outPaths				
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds an occurrence of the pattern in the input points.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inPattern">Points to be fitted.</param>
	/// <param name="inMaxDeviation">Maximal pixel distance between two points considered matched. Default value: 2.0f.</param>
	/// <param name="inMinScore">The minimum proportion of points correctly matched. Default value: 1.0f.</param>
	/// <param name="diagRotationCount">Number of rotation tried.</param>
	AVL_FUNCTION void LocateSingleObject_Points
	(
		const atl::Array<avl::Point2D>&	inPoints,			
		const atl::Array<avl::Point2D>&	inPattern,			
		const bool						inAllowRotation,
		const float						inMaxDeviation,		
		const float						inMinScore,			
		atl::Conditional<avl::CoordinateSystem2D>&		outAlignment,
		atl::Conditional<atl::Array<avl::Point2D> >&	outAlignedPattern,
		atl::Conditional<atl::Array<avl::Point2D> >&	outAlignedMatchedPoints,
		int&											diagRotationCount = atl::Dummy<int>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the alignment that maps input model points to data points with minimum error.</summary>
	AVL_FUNCTION void PointsBestAlignment
	(
		const atl::Array<avl::Point2D>&	inM,
		const atl::Array<avl::Point2D>&	inD,
		const bool						inAllowRotation,
		const bool						inAllowScale,
		avl::CoordinateSystem2D&		outT,
		atl::Optional<atl::Array<avl::Point2D>&>	outAligned = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds an occurrence of the pattern in the input points.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inPattern">Points to be fitted.</param>
	/// <param name="inAllowRotation">Default value: True.</param>
	/// <param name="inAllowScale">Default value: False.</param>
	/// <param name="inMaxIterationCount">Maximal number of iteration for ICP. Default value: 10.</param>
	/// <param name="inMatchFraction">Defines fraction of points that is being fitted in every iteration. Default value: 0.5f.</param>
	/// <param name="inInitialTransformCount">Number of initial transforms for ICP. Default value: 10.</param>
	AVL_FUNCTION void LocateSingleObject_Points_ICP
	(
		const atl::Array<avl::Point2D>&	inPoints,			
		const atl::Array<avl::Point2D>&	inPattern,			
		const bool						inAllowRotation,
		const bool						inAllowScale,
		const int						inMaxIterationCount,	
		const float						inMatchFraction,	
		const int						inInitialTransformCount,	
		atl::Conditional<avl::CoordinateSystem2D>&		outAlignment,
		atl::Conditional<atl::Array<avl::Point2D> >&	outAlignedPattern
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds an occurrence of the pattern in the input points.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inPattern">Points to be fitted.</param>
	/// <param name="inAllowRotation">Default value: True.</param>
	/// <param name="inAllowScale">Default value: False.</param>
	/// <param name="inTileSize">Defines size of the square tile on the plane. Default value: 0.01f.</param>
	/// <param name="inInitialDetectionThreshold">Defines how many points have to be matched during initial detection. Default value: 0.75f.</param>
	/// <param name="inMaxDeviation">Maximal pixel distance between two points considered matched. Default value: 1.0f.</param>
	/// <param name="inMinScore">The minimum proportion of points correctly matched. Default value: 0.75f.</param>
	/// <param name="inMinDistance">Minimal distance between two found occurrences. Default value: 10.0f.</param>
	AVL_FUNCTION void LocateMultipleObjects_Points_GeoHash
	(
		const atl::Array<avl::Point2D>&	inPoints,			
		const atl::Array<avl::Point2D>&	inPattern,			
		const bool						inAllowRotation,
		const bool						inAllowScale,
		const float						inTileSize,			
		const float						inInitialDetectionThreshold,	
		const float						inMaxDeviation,		
		const float						inMinScore,			
		const float						inMinDistance,		
		atl::Array<avl::CoordinateSystem2D>&	outAlignments,
		atl::Array<atl::Array<avl::Point2D> >&	outAlignedPatterns
	)
	THROW_AVL_ERRORS;

	/// <summary>Detect points that lie along multiple segments.</summary>
	/// <param name="inPoints">Points to connect.</param>
	/// <param name="inMaxDistance">Maximum distance between connected points. Default value: 10.0f.</param>
	/// <param name="inMaxRank">Maximum number of neighbour candidates considered when joining points. Default value: 4.</param>
	/// <param name="inMaxRelativeDistance">Maximum distance in relation to the shortest distance for a point. Default value: 2.0f.</param>
	/// <param name="inMaxTurnAngle">Maximum angle between consecutive path segments. Default value: 5.0f.</param>
	/// <param name="inMinPointCount">Minimum number of points in one path. Default value: 3.</param>
	/// <param name="outPointSegments">Segments connecting first and last point of each path.</param>
	/// <param name="outPaths">Paths of connected points.</param>
	AVL_FUNCTION void DetectPointSegments_Ex
	(
		const atl::Array<avl::Point2D>&			inPoints,				
		const float							inMaxDistance,			
		const int								inMaxRank,				
		atl::Optional<float>				inMaxRelativeDistance,	
		const float							inMaxTurnAngle,			
		const int								inMinPointCount,		
		atl::Array<avl::Segment2D>&				outPointSegments,		
		atl::Array<avl::Path>&					outPaths				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYFITTING_H

