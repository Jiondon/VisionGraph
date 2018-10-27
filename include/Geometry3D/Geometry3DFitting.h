//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DFITTING_H
#define AVL_GEOMETRY3DFITTING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "Enums/CircleFittingMethod.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Approximates points with a plane using the Least Squares method.</summary>
	/// <param name="outPlane">Fitted plane.</param>
	/// <param name="outDistances">Distances of the input points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input points to a resulting plane.</param>
	AVL_FUNCTION void FitPlaneToPoints
	(
		const atl::Array<avl::Point3D>&	inPoints,
		avl::Plane3D&					outPlane,	
		atl::Optional<atl::Array<float>&>	outDistances = atl::NIL,			
		atl::Optional<float&>				outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>				outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>	outSquaredDistances = atl::NIL,		
		atl::Optional<float&>				outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points with a plane using selected M-estimator for outlier suppression.</summary>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialPlane">Initial approximation (if available). Default value: atl::NIL.</param>
	/// <param name="outInliers">Points matching the computed plane.</param>
	/// <param name="outDistances">Distances of the input points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input points to a resulting plane.</param>
	AVL_FUNCTION void FitPlaneToPoints_M
	(
		const atl::Array<avl::Point3D>&				inPoints,
		avl::MEstimator::Type						inOutlierSuppression,
		float									inClippingFactor,		
		int											inIterationCount,		
		atl::Optional<avl::Plane3D&>				inInitialPlane,			
		avl::Plane3D&								outPlane,
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL,	
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,			
		atl::Optional<float&>					outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>					outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>		outSquaredDistances = atl::NIL,		
		atl::Optional<float&>					outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points in 3D with a line using the Least Squares method.</summary>
	AVL_FUNCTION void FitLineToPoints3D
	(
		const atl::Array<avl::Point3D>&	inPoints,
		avl::Line3D&					outLine,
		atl::Optional<float&>			outError = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points in 3D with a line using selected M-estimator for outlier suppression.</summary>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialLine">Initial approximation (if available). Default value: atl::NIL.</param>
	/// <param name="outInliers">Points matching the computed line.</param>
	AVL_FUNCTION void FitLineToPoints3D_M
	(
		const atl::Array<avl::Point3D>&				inPoints,
		avl::MEstimator::Type						inOutlierSuppression,
		float										inClippingFactor,		
		int											inIterationCount,		
		atl::Optional<avl::Line3D&>					inInitialLine,			
		avl::Line3D&								outLine,
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points in 3D with a segment using selected outliers suppression method.</summary>
	/// <param name="inOutlierSuppression">Default value: Tukey.</param>
	/// <param name="outSegment">Fitted segment or nothing if method failed to converge.</param>
	AVL_FUNCTION void FitSegmentToPoints3D
	(
		const atl::Array<avl::Point3D>&			inPoints,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		atl::Conditional<avl::Segment3D>&		outSegment	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points in 3D with a circle using selected outliers suppression method.</summary>
	/// <param name="outCircle">Fitted circle or nothing if method failed to converge.</param>
	AVL_FUNCTION void FitCircleToPoints3D
	(
		const atl::Array<avl::Point3D>&			inPoints,
		avl::CircleFittingMethod::Type			inFittingMethod,
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,
		atl::Optional<avl::Plane3D&>			inPlane,
		atl::Conditional<avl::Circle3D>&		outCircle			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DFITTING_H

