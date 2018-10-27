//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DCONSTRUCTIONS_H
#define AVL_GEOMETRY3DCONSTRUCTIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Computes a vector representing distance from one point in 3D to another.</summary>
	AVL_FUNCTION void VectorBetweenPoints3D
	(
		const avl::Point3D&	inFrom, 
		const avl::Point3D&	inTo,
		avl::Vector3D&		outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a plane passing through three distinct points in 3D.</summary>
	AVL_FUNCTION void PlaneThroughPoints3D
	(
		const avl::Point3D&	inPoint1, 
		const avl::Point3D&	inPoint2,
		const avl::Point3D& inPoint3,
		avl::Plane3D&		outPlane
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a plane passing through a line and a point in 3D.</summary>
	AVL_FUNCTION void PlaneThroughLineAndPoint3D
	(
		const avl::Line3D&	inLine3D, 
		const avl::Point3D&	inPoint3D,
		avl::Plane3D&		outPlane
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a line in 3D passing through a point with given direction.</summary>
	/// <param name="inPoint3D">A point on the created line.</param>
	/// <param name="inDirectionVector">Desired direction of the line.</param>
	/// <param name="outLine3D">The resulting line in 3D.</param>
	AVL_FUNCTION void LineThroughPoint3D
	(
		const avl::Point3D&		inPoint3D,			
		const avl::Vector3D&	inDirectionVector,	
		avl::Line3D&			outLine3D			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a line in 3D passing through two points.</summary>
	/// <param name="inPoint1">A point on the created line.</param>
	/// <param name="inPoint2">Another point on the created line.</param>
	/// <param name="outLine3D">The resulting line in 3D.</param>
	AVL_FUNCTION void LineThroughPoints3D
	(
		const avl::Point3D&		inPoint1,			
		const avl::Point3D&		inPoint2,			
		avl::Line3D&			outLine3D			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a circle in 3D passing through three noncollinear 3D points.</summary>
	/// <param name="outCircle3D">Circle in 3D passing through the specified 3D points; or Nil if the points are collinear.</param>
	AVL_FUNCTION void CircleThroughPoints3D
	(
		const avl::Point3D&					inPoint1,
		const avl::Point3D&					inPoint2,
		const avl::Point3D&					inPoint3,
		atl::Conditional<avl::Circle3D>&	outCircle3D	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DCONSTRUCTIONS_H

