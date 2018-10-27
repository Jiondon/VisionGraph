//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYINTERSECTIONS_H
#define AVL_GEOMETRYINTERSECTIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Computes common points of two circles.</summary>
	AVL_FUNCTION void CircleCircleIntersection
	(
		const avl::Circle2D&			inCircle1, 
		const avl::Circle2D&			inCircle2,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a common point of two segments.</summary>
	AVL_FUNCTION void SegmentSegmentIntersection
	(
		const avl::Segment2D&			inSegment1,
		const avl::Segment2D&			inSegment2,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a common points or segment of any segments from the set.</summary>
	/// <param name="inSegments">Input segments.</param>
	/// <param name="outIntersectionPoints">Intersection points.</param>
	/// <param name="outFirstIntersectionIndices">First indices of the input segments which corresponds to the intersection points.</param>
	/// <param name="outSecondIntersectionIndices">Second indices of the input segments which corresponds to the intersection points.</param>
	/// <param name="outOverlapSegments">Overlap segments.</param>
	/// <param name="outFirstOverlapIndices">First indices of the input segments which corresponds to the overlap segments.</param>
	/// <param name="outSecondOverlapIndices">Second indices of the input segments which corresponds to the overlap segments.</param>
	AVL_FUNCTION void SegmentArrayIntersections
	(
		const atl::Array<avl::Segment2D>&	inSegments,						
		atl::Array<avl::Point2D>&			outIntersectionPoints,			
		atl::Array<int>&					outFirstIntersectionIndices,	
		atl::Array<int>&					outSecondIntersectionIndices,	
		atl::Array<avl::Segment2D>&			outOverlapSegments,				
		atl::Array<int>&					outFirstOverlapIndices,			
		atl::Array<int>&					outSecondOverlapIndices			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a common point of two lines.</summary>
	AVL_FUNCTION void LineLineIntersection
	(
		const avl::Line2D&				inLine1,
		const avl::Line2D&				inLine2,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a common point of a line and a segment.</summary>
	AVL_FUNCTION void LineSegmentIntersection
	(
		const avl::Line2D&				inLine,
		const avl::Segment2D&			inSegment,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes common points of a circle and a line.</summary>
	AVL_FUNCTION void LineCircleIntersection
	(
		const avl::Line2D&				inLine,
		const avl::Circle2D&			inCircle,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of a circle and a segment.</summary>
	AVL_FUNCTION void SegmentCircleIntersection
	(
		const avl::Segment2D&			inSegment,
		const avl::Circle2D&			inCircle,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of an arc and a line.</summary>
	AVL_FUNCTION void LineArcIntersection
	(
		const avl::Line2D&				inLine,
		const avl::Arc2D&				inArc,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of an arc and a segment.</summary>
	AVL_FUNCTION void SegmentArcIntersection
	(
		const avl::Segment2D&			inSegment,
		const avl::Arc2D&				inArc,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint1,
		atl::Conditional<avl::Point2D>&	outIntersectionPoint2
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests if two rectangles intersect.</summary>
	AVL_FUNCTION void TestRectangleIntersectsWith
	(
		const avl::Rectangle2D&			inRectangle,
		const avl::Rectangle2D&			inReferenceRectangle,
		bool&							outRectanglesIntersect
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYINTERSECTIONS_H

