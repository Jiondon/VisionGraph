//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SURFACEFITTING_H
#define AVL_SURFACEFITTING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "Enums/CircleFittingMethod.h"
#include "Surface/Surface.h"
#include "Geometry3D/Geometry3D.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Approximates points of the input surface with a plane using the Least Squares method.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outPlane">Fitted plane.</param>
	/// <param name="outDistances">Distances of the input surface points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input surface points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input surface points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input surface points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input surface points to a resulting plane.</param>
	AVL_FUNCTION void FitPlaneToSurface
	(
		const avl::Surface&					inSurface,							
		atl::Optional<const avl::Region&>	inRoi,								
		avl::Plane3D&						outPlane,							
		atl::Optional<atl::Array<float>&>	outDistances = atl::NIL,			
		atl::Optional<float&>				outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>				outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>	outSquaredDistances = atl::NIL,		
		atl::Optional<float&>				outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Approximates points of the input surface with a plane using selected M-estimator for outlier suppression.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring points being much different from the rest.</param>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialPlane">Initial approximation (if available). Default value: atl::NIL.</param>
	/// <param name="outPlane">Fitted plane.</param>
	/// <param name="outInliers">Points matching the computed plane.</param>
	/// <param name="outDistances">Distances of the input points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input points to a resulting plane.</param>
	AVL_FUNCTION void FitPlaneToSurface_M
	(
		const avl::Surface&						inSurface,				
		atl::Optional<const avl::Region&>		inRoi,					
		avl::MEstimator::Type					inOutlierSuppression,	
		float									inClippingFactor,		
		int										inIterationCount,		
		atl::Optional<avl::Plane3D&>			inInitialPlane,			
		avl::Plane3D&							outPlane,				
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL,	
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,			
		atl::Optional<float&>					outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>					outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>		outSquaredDistances = atl::NIL,		
		atl::Optional<float&>					outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Fits a circle to a hole in a surface plane.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inPlaneOutlierSuppression">Selects a method for ignoring points not lying on the fitted plane.</param>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialPlane">Initial approximation of a plane (if available). Default value: atl::NIL.</param>
	/// <param name="inCircleFittingMethod">Select a method for fitting a circle to a set of points.</param>
	/// <param name="inCircleOutlierSuppression">Selects a method for ignoring points not lying on the fitted circle. Default value: atl::NIL.</param>
	/// <param name="outCircle3D">Circle fitted to a surface hole.</param>
	/// <param name="outPlane">Plane fitted to the surface points.</param>
	/// <param name="outInliers">Points matching the computed plane.</param>
	/// <param name="outDistances">Distances of the input surface points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input surface points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input surface points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input surface points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input surface points to a resulting plane.</param>
	AVL_FUNCTION void FitCircleToSurfaceHole
	(
		const avl::Surface&						inSurface,				
		atl::Optional<const avl::Region&>		inRoi,					
		avl::MEstimator::Type					inPlaneOutlierSuppression, 
		float									inClippingFactor,		
		int										inIterationCount,		
		atl::Optional<avl::Plane3D&>			inInitialPlane,			
		avl::CircleFittingMethod::Type			inCircleFittingMethod,	
		atl::Optional<avl::MEstimator::Type>	inCircleOutlierSuppression,	
		atl::Conditional<avl::Circle3D>&		outCircle3D,			
		avl::Plane3D&							outPlane,				
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL,	
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,			
		atl::Optional<float&>					outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>					outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>		outSquaredDistances = atl::NIL,		
		atl::Optional<float&>					outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SURFACEFITTING_H

