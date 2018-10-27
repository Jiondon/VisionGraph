//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYCONSTRUCTIONS_H
#define AVL_GEOMETRYCONSTRUCTIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"
#include "Enums/Anchor2D.h"
#include "Enums/SplitDirection.h"

namespace avl
{


	/// <summary>Computes a vector representing distance from one point to another.</summary>
	AVL_FUNCTION void VectorBetweenPoints
	(
		const avl::Point2D&	inFrom, 
		const avl::Point2D&	inTo,
		avl::Vector2D&		outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a line passing through two distinct points.</summary>
	AVL_FUNCTION void LineThroughPoints
	(
		const avl::Point2D&	inPoint1, 
		const avl::Point2D&	inPoint2,
		avl::Line2D&		outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a line passing through a point with given angle.</summary>
	AVL_FUNCTION void LineThroughPoint
	(
		const avl::Point2D&	inPoint,
		float			inAngle,
		avl::Line2D&		outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a circle passing through three noncollinear points.</summary>
	/// <param name="outCircle">Circle passing through the specified points; or Nil if the points are collinear.</param>
	AVL_FUNCTION void CircleThroughPoints
	(
		const avl::Point2D&					inPoint1,
		const avl::Point2D&					inPoint2,
		const avl::Point2D&					inPoint3,
		atl::Conditional<avl::Circle2D>&	outCircle	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes circle tangent lines passing through a point.</summary>
	AVL_FUNCTION void CircleTangents
	(
		const avl::Circle2D&			inCircle,
		const avl::Point2D&				inPoint,
		atl::Conditional<avl::Line2D>&	outTangentLine1,
		atl::Conditional<avl::Line2D>&	outTangentLine2
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a point onto a line.</summary>
	AVL_FUNCTION void ProjectPointOnLine
	(
		const avl::Point2D&	inPoint,
		const avl::Line2D&	inLine,
		avl::Point2D&		outProjectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects points onto a line.</summary>
	AVL_FUNCTION void ProjectPointsOnLine
	(
		const atl::Array<avl::Point2D>&						inPoints,
		const avl::Line2D&									inLine,
		atl::Array<avl::Point2D>&							outProjectionPoints,
		atl::Optional<atl::Conditional<avl::Segment2D>&>	outProjectionSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a point onto a circle.</summary>
	AVL_FUNCTION void ProjectPointOnCircle
	(
		const avl::Point2D&		inPoint,
		const avl::Circle2D&	inCircle,
		avl::Point2D&			outProjectionPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects points onto a circle.</summary>
	/// <param name="inPoints">Points to be projected.</param>
	/// <param name="inCircle">Circle the points will be projected on.</param>
	/// <param name="outProjectionPoints">Projected points.</param>
	/// <param name="outProjectionArc">Arc containing the projected points.</param>
	AVL_FUNCTION void ProjectPointsOnCircle
	(
		const atl::Array<avl::Point2D>&	inPoints,			
		const avl::Circle2D&			inCircle,					
		atl::Array<avl::Point2D>&		outProjectionPoints,	
		atl::Conditional<avl::Arc2D>&	outProjectionArc	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system with the specified origin.</summary>
	/// <param name="inPoint">Origin of the created coordinate system.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="inScaleDivisor">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateCoordinateSystemFromPoint
	(
		const avl::Point2D&			inPoint,		
		float					inAngle,
		float					inScale,
		float					inScaleDivisor,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system with two points on its axes.</summary>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="inScaleDivisor">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateCoordinateSystemFromTwoPoints
	(
		const avl::Point2D&			inPoint1,
		const avl::Point2D&			inPoint2,
		float					inAngle,
		float					inScale,
		float					inScaleDivisor,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system from a rectangle.</summary>
	/// <param name="inPointAnchor">Default value: TopLeft.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="inScaleDivisor">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateCoordinateSystemFromRectangle
	(
		const avl::Rectangle2D&		inRectangle,
		const avl::Anchor2D::Type	inPointAnchor,
		float						inRelativeAngle,
		float						inScale,
		float						inScaleDivisor,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system with the origin on a given segment.</summary>
	/// <param name="inPointAnchor">Default value: 0.0f.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="inScaleDivisor">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateCoordinateSystemFromSegment
	(
		const avl::Segment2D&		inSegment,
		float					inPointAnchor,
		float					inRelativeAngle,
		float					inScale,
		float					inScaleDivisor,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system from a vector.</summary>
	/// <param name="inScale">Default value: 1.0f.</param>
	/// <param name="inScaleDivisor">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateCoordinateSystemFromVector
	(
		const avl::Vector2D&		inVector,
		float					inAngle,
		float					inScale,
		float					inScaleDivisor,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits the rectangle into two along the direction.</summary>
	AVL_FUNCTION void SplitRectangle
	(
		const avl::Rectangle2D&				inRectangle,
		const avl::SplitDirection::Type		inSplitDirection,
		avl::Rectangle2D&					outRectangle1,
		avl::Rectangle2D&					outRectangle2
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYCONSTRUCTIONS_H

