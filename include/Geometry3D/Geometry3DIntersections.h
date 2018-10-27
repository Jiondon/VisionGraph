//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DINTERSECTIONS_H
#define AVL_GEOMETRY3DINTERSECTIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Computes the common part of two boxes in 3D.</summary>
	AVL_FUNCTION void BoxIntersection3D
	(
		const avl::Box3D&	inBox3D1,
		const avl::Box3D&	inBox3D2,
		avl::Box3D&			outBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the intersection point of a segment in 3D and a plane.</summary>
	AVL_FUNCTION void SegmentPlaneIntersection3D
	(
		const avl::Segment3D&			inSegment3D,
		const avl::Plane3D&				inPlane,
		atl::Conditional<avl::Point3D>&	outIntersectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the intersection point of a line in 3D and a plane.</summary>
	AVL_FUNCTION void LinePlaneIntersection3D
	(
		const avl::Line3D&				inLine3D,
		const avl::Plane3D&				inPlane,
		atl::Conditional<avl::Point3D>&	outIntersectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes common points of a circle in 3D and a plane.</summary>
	AVL_FUNCTION void CirclePlaneIntersection3D
	(
		const avl::Circle3D&			inCircle3D,
		const avl::Plane3D&				inPlane,
		atl::Conditional<avl::Point3D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point3D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a common line in 3D of two planes.</summary>
	AVL_FUNCTION void PlanePlaneIntersection3D
	(
		const avl::Plane3D&				inPlane1,
		const avl::Plane3D&				inPlane2,
		atl::Conditional<avl::Line3D>&	outIntersectionLine
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DINTERSECTIONS_H

