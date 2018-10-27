//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYNORMALIZATIONS_H
#define AVL_GEOMETRYNORMALIZATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"
#include "Enums/RectangleOrientation.h"
#include "Enums/Axis.h"

namespace avl
{


	/// <summary>Removes invalid points from an array (i.e. points with NaN or INF coordinates).</summary>
	AVL_FUNCTION void RemoveInvalidPoints
	(
		const atl::Array<avl::Point2D>& inPoints,
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes orientation of the given rectangle according to parameters.</summary>
	/// <param name="inRectangle">Input rectangle.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	AVL_FUNCTION void NormalizeRectangleOrientation
	(
		const avl::Rectangle2D&	inRectangle,	
		const float				inReferenceAngle,	
		const avl::RectangleOrientation::Type	inRectangleOrientation,	
		avl::Rectangle2D&		outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes orientation of the given segment according to base orientation.</summary>
	/// <param name="inBaseOrientation">Default value: 0.0f.</param>
	AVL_FUNCTION void NormalizeSegmentOrientation_ByBaseOrientation
	(
		const avl::Segment2D&		inSegment,
		const float					inBaseOrientation,
		avl::Segment2D&				outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes orientation of the given segment according to distance to the given point.</summary>
	/// <param name="inReferencePoint">A point relative to which distances are measured.</param>
	/// <param name="outSegment">A segment in which the first point is closer to inReferencePoint.</param>
	AVL_FUNCTION void NormalizeSegmentOrientation_ByPointDistance
	(
		const avl::Segment2D&			inSegment,
		const avl::Point2D&				inReferencePoint,		
		avl::Segment2D&					outSegment				
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes orientation of the given segment according to coordinates along selected axis.</summary>
	/// <param name="inAxis">Default value: X.</param>
	/// <param name="outSegment">A segment in which the first point will have smaller coordinate along the selected axis.</param>
	AVL_FUNCTION void NormalizeSegmentOrientation_ByCoordinate
	(
		const avl::Segment2D&			inSegment,
		const avl::Axis::Type			inAxis,
		avl::Segment2D&					outSegment				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYNORMALIZATIONS_H

