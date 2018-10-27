//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYDISTANCEMETRICS_H
#define AVL_GEOMETRYDISTANCEMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Measures the distance between two points.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToPointDistance
	(
		const avl::Point2D&					inPoint1,
		const avl::Point2D&					inPoint2,
		float							inResolution,	
		float&							outDistance,
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a point and a line.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToLineDistance
	(
		const avl::Point2D&				inPoint,
		const avl::Line2D&				inLine,
		float						inResolution,	
		float&						outDistance,
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a point and a line.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToLineDistance_Simple
	(
		const avl::Point2D&				inPoint,
		const avl::Line2D&				inLine,
		float						inResolution,	
		float&						outDistance
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the signed distance between a point and a line with direction.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToLineDistance_Oriented
	(
		const avl::Point2D&				inPoint,
		const avl::Segment2D&			inLineSection,
		float						inResolution,	
		float&						outDistance,
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a point and a segment.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToSegmentDistance
	(
		const avl::Point2D&					inPoint,
		const avl::Segment2D&				inSegment,
		float							inResolution,	
		float&							outDistance,
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between two segments.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void SegmentToSegmentDistance
	(
		const avl::Segment2D&				inSegment1,
		const avl::Segment2D&				inSegment2,
		float							inResolution,	
		float&							outDistance,
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between two circles.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void CircleToCircleDistance
	(
		const avl::Circle2D&				inCircle1,
		const avl::Circle2D&				inCircle2,
		float							inResolution,	
		float&							outDistance,
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a point and a circle.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToCircleDistance
	(
		const avl::Point2D&					inPoint,
		const avl::Circle2D&				inCircle,
		float							inResolution,	
		float&							outDistance,
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distance between a point and an arc.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToArcDistance
	(
		const avl::Point2D&				inPoint,
		const avl::Arc2D&				inArc,
		float						inResolution,	
		float&						outDistance,
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the distances between consecutive points of a point sequence.</summary>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void PointSequenceDistances
	(
		const atl::Array<avl::Point2D>&				inPoints,
		const bool									inCyclic,
		float										inResolution,	
		atl::Array<float>&							outDistances,
		atl::Optional<float&>						outDistanceSum = atl::NIL,
		atl::Optional<atl::Array<avl::Segment2D>&>	outConnectingSegments = atl::NIL
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYDISTANCEMETRICS_H

