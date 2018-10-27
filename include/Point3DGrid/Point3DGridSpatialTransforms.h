//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_POINT3DGRIDSPATIALTRANSFORMS_H
#define AVL_POINT3DGRIDSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Region/Region.h"
#include "Enums/Metric3D.h"

namespace avl
{


	/// <summary>Translates a grid of points by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint3DGrid
	(
		const avl::Point3DGrid&	inGrid,
		const avl::Vector3D&	inDelta,	
		bool					inInverse,	
		avl::Point3DGrid&		outGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distances of grid points to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distances will be changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePoint3DGrid
	(
		const avl::Point3DGrid&			inGrid,
		const avl::Point3D&				inReferencePoint,	
		float							inScale,			
		bool							inInverse,			
		avl::Point3DGrid&				outGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a grid of 3D points around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint3DGrid
	(
		const avl::Point3DGrid&	inGrid,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Point3DGrid&		outGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies a general transformation expressed by a matrix to a grid of 3D points.</summary>
	/// <param name="inTransform">Transformation 3x3 matrix.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TransformPoint3DGrid
	(
		const avl::Point3DGrid&	inGrid,
		const avl::Matrix&		inTransform,	
		bool					inInverse,		
		avl::Point3DGrid&		outGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes points that are not represented in a given region of the input grid.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void CropPoint3DGridToRegion
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		const avl::Region&			inRegion,
		avl::Point3DGrid&			outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the grid points that are not contained in a given rectangular box.</summary>
	AVL_FUNCTION void CropPoint3DGrid
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		atl::Optional<float>		inMinX,
		atl::Optional<float>		inMaxX,
		atl::Optional<float>		inMinY,
		atl::Optional<float>		inMaxY,
		atl::Optional<float>		inMinZ,
		atl::Optional<float>		inMaxZ,
		avl::Point3DGrid&			outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the grid points that are too distant from a given plane.</summary>
	/// <param name="inMaxDistance">Maximal distance from a given plane.</param>
	AVL_FUNCTION void CropPoint3DGridByPlaneProximity
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		const avl::Plane3D&			inPlane,
		const float					inMaxDistance,	
		avl::Point3DGrid&			outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the grid points that are too distant from their neighbor points.</summary>
	/// <param name="inNeighborRadius">Radius of neighbors to search for real neighbors. Default value: 1.</param>
	/// <param name="inMaxDistance">Maximal distance from another point to consider them real neighbors. Default value: 2.0f.</param>
	/// <param name="inMetric">Metric used for measuring distance between points. Default value: Z.</param>
	/// <param name="inMinNeighborRatio">Fraction of valid neighbors in a given radius that have to be real neighbors. Default value: 1.0f.</param>
	AVL_FUNCTION void CropPoint3DGridByNeighborsProximity
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		const int					inNeighborRadius,	
		const float					inMaxDistance,		
		avl::Metric3D::Type			inMetric,			
		const float					inMinNeighborRatio,	
		avl::Point3DGrid&			outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines two point grids into one.</summary>
	/// <param name="inDeltaX">Default value: 0.</param>
	/// <param name="inDeltaY">Default value: 0.</param>
	AVL_FUNCTION void JoinPoint3DGrids
	(
		const avl::Point3DGrid&		inPoint3DGrid1,
		const avl::Point3DGrid&		inPoint3DGrid2,
		const int					inDeltaX,
		const int					inDeltaY,
		avl::Point3DGrid&			outPoint3DGrid
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_POINT3DGRIDSPATIALTRANSFORMS_H

