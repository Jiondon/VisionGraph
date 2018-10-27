//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYRELATIONS_H
#define AVL_GEOMETRYRELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Basic/Types.h"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Tests whether a point lies inside a circle.</summary>
	AVL_FUNCTION void TestPointInCircle
	(
		const avl::Point2D& inPoint,
		const avl::Circle2D& inCircle,
		bool& outIsContained
		)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a point lies in a segment.</summary>
	AVL_FUNCTION void TestPointInSegment_Deprecated
	(
		const avl::Point2D& inPoint,
		const avl::Segment2D& inSegment,
		bool& outIsContained
		)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a point lies in a box.</summary>
	AVL_FUNCTION void TestPointInBox
	(
		const avl::Point2D&	inPoint,
		const avl::Box&		inBox,
		bool&				outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a point lies in a rectangle.</summary>
	AVL_FUNCTION void TestPointInRectangle
	(
		const avl::Point2D&			inPoint,
		const avl::Rectangle2D&		inRectangle,
		bool&					outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a graph of points that lay close to each other.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inMaxRank">Maximum connections going out of one point. Default value: 8.</param>
	/// <param name="inMaxDistance">Maximum distance between adjacent point in the graph. Default value: 10.0f.</param>
	/// <param name="inMaxRelativeDistance">Maximum distance in relation to the shortest distance for a point. Default value: atl::NIL.</param>
	/// <param name="outGraph">Graph of points (adjacency list).</param>
	/// <param name="outDistances">Distances between adjacent points in the graph.</param>
	/// <param name="diagSegments">Graph edges, useful for visualization.</param>
	AVL_FUNCTION void CreatePointGraph
	(
		const atl::Array<avl::Point2D>&		inPoints,				
		const int							inMaxRank,				
		atl::Optional<float>			inMaxDistance,			
		atl::Optional<float>			inMaxRelativeDistance,	
		atl::Array<atl::Array<int> >&		outGraph,				
		atl::Array<atl::Array<float> >&	outDistances,			
		atl::Array<avl::Segment2D>&			diagSegments = atl::Dummy< atl::Array<avl::Segment2D> >()			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYRELATIONS_H

