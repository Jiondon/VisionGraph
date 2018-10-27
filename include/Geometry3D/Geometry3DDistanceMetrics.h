//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DDISTANCEMETRICS_H
#define AVL_GEOMETRY3DDISTANCEMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Measures the distance between two 3D points.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToPointDistance3D
	(
		const avl::Point3D&	inPoint1,
		const avl::Point3D&	inPoint2,
		float				inResolution,	
		float&				outDistance	
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a 3D point and a plane.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToPlaneDistance3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Plane3D&		inPlane,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a 3D point and a segment in 3D.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToSegmentDistance3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Segment3D&	inSegment3D,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a 3D point and a line in 3D.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToLineDistance3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Line3D&		inLine3D,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a 3D point and a circle in 3D.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToCircleDistance3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Circle3D&	inCircle3D,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a segment in 3D and a plane.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void SegmentToPlaneDistance3D
	(
		const avl::Segment3D&	inSegment3D,
		const avl::Plane3D&		inPlane,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a circle in 3D and a plane.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void CircleToPlaneDistance3D
	(
		const avl::Circle3D&	inCircle3D,
		const avl::Plane3D&		inPlane,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between two lines in 3D.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void LineToLineDistance3D
	(
		const avl::Line3D&		inLine1,
		const avl::Line3D&		inLine2,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between two segments in 3D.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void SegmentToSegmentDistance3D
	(
		const avl::Segment3D&	inSegment1,
		const avl::Segment3D&	inSegment2,
		float					inResolution,	
		float&					outDistance,
		atl::Optional<avl::Segment3D&>	outConnectingSegment3D = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distances between consecutive points of a point sequence in 3D.</summary>
	AVL_FUNCTION void PointSequenceDistances3D
	(
		const atl::Array<avl::Point3D>&				inPoints,
		const bool									inCyclic,
		atl::Array<float>&							outDistances,
		atl::Optional<float&>						outDistanceSum = atl::NIL,
		atl::Optional<atl::Array<avl::Segment3D>&>	outConnectingSegments = atl::NIL
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DDISTANCEMETRICS_H

