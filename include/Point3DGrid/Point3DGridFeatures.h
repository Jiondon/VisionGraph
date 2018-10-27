//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_POINT3DGRIDFEATURES_H
#define AVL_POINT3DGRIDFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "Enums/CircleFittingMethod.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Computes region of locations where points are valid in a points 3D grid and where they are invalid.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outValidPointsRegion">Region of locations where points are valid.</param>
	/// <param name="outInvalidPointsRegion">Region of locations where points are invalid.</param>
	AVL_FUNCTION void Point3DGridValidPointsRegion
	(
		const avl::Point3DGrid&				inPoint3DGrid,
		atl::Optional<const avl::Region&>	inRoi,
		avl::Region&						outValidPointsRegion,	
		avl::Region&						outInvalidPointsRegion	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds a biggest hole in a given section of point cloud.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialPlane">Initial approximation of a plane (if available). Default value: atl::NIL.</param>
	/// <param name="outHoleRegion">Region of the found hole.</param>
	/// <param name="outHoleCenter">Center of the found hole.</param>
	/// <param name="outInliers">Points matching the computed plane.</param>
	/// <param name="outDistances">Distances of the input points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input points to a resulting plane.</param>
	AVL_FUNCTION void Point3DGridHole
	(
		const avl::Point3DGrid&					inPointGrid,
		atl::Optional<const avl::Region&>		inRoi,
		avl::MEstimator::Type					inPlaneOutlierSuppression,
		float									inClippingFactor,		
		int										inIterationCount,		
		atl::Optional<avl::Plane3D&>			inInitialPlane,			
		atl::Conditional<avl::Region>&			outHoleRegion,			
		atl::Conditional<avl::Point3D>&			outHoleCenter,			
		avl::Plane3D&							outPlane,
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL,	
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,			
		atl::Optional<float&>					outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>					outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>		outSquaredDistances = atl::NIL,		
		atl::Optional<float&>					outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Fits a circle to a hole in a plane.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialPlane">Initial approximation of a plane (if available). Default value: atl::NIL.</param>
	/// <param name="outCircle3D">Circle fitted to a hole.</param>
	/// <param name="outInliers">Points matching the computed plane.</param>
	/// <param name="outDistances">Distances of the input points to a resulting plane.</param>
	/// <param name="outSignedDistanceSum">Sum of signed distances of the input points to a resulting plane.</param>
	/// <param name="outDistanceSum">Sum of distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistances">Squared distances of the input points to a resulting plane.</param>
	/// <param name="outSquaredDistanceSum">Sum of squared distances of the input points to a resulting plane.</param>
	AVL_FUNCTION void FitCircle3DToHole
	(
		const avl::Point3DGrid&						inPointGrid,
		atl::Optional<const avl::Region&>			inRoi,
		avl::MEstimator::Type						inPlaneOutlierSuppression,
		float									inClippingFactor,		
		int											inIterationCount,		
		atl::Optional<avl::Plane3D&>				inInitialPlane,			
		avl::CircleFittingMethod::Type				inCircleFittingMethod,
		atl::Optional<avl::MEstimator::Type>		inCircleOutlierSuppression,
		atl::Conditional<avl::Circle3D>&			outCircle3D,			
		avl::Plane3D&								outPlane,
		atl::Optional<atl::Array<avl::Point3D>&>	outInliers = atl::NIL,	
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,			
		atl::Optional<float&>					outSignedDistanceSum = atl::NIL,	
		atl::Optional<float&>					outDistanceSum = atl::NIL,			
		atl::Optional<atl::Array<float>&>		outSquaredDistances = atl::NIL,		
		atl::Optional<float&>					outSquaredDistanceSum = atl::NIL	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_POINT3DGRIDFEATURES_H

