//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHCOMBINATORS_H
#define AVL_PATHCOMBINATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Joins two open paths.</summary>
	/// <param name="inPath1">Input path.</param>
	/// <param name="inPath2">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void ConcatenatePaths
	(
		const avl::Path& inPath1, 
		const avl::Path& inPath2, 
		avl::Path& outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins open paths of an array.</summary>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void ConcatenatePaths_OfArray
	(
		const atl::Array<avl::Path>& inPathArray,
		avl::Path& outPath
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct ConcatenatePaths_OfLoopState : public avl::BaseState
	{
		avl::Path stateVariable;
	};
	/// <summary>Joins open paths appearing in consecutive iterations.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void ConcatenatePaths_OfLoop
	(
		ConcatenatePaths_OfLoopState& ioState,
		const avl::Path& inPath,
		avl::Path& outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of two paths (of equal size and type) point by point.</summary>
	/// <param name="inPath1">Input path.</param>
	/// <param name="inPath2">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void AveragePath
	(
		const avl::Path&	inPath1,	
		const avl::Path&	inPath2,	
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of two paths.</summary>
	/// <param name="inPath1">Input path.</param>
	/// <param name="inPath2">Input path.</param>
	/// <param name="outIntersectionPoints">Intersections between the input paths.</param>
	/// <param name="outSegmentIndices1">Indices of the segments of the first path which generate found intersection points.</param>
	/// <param name="outSegmentIndices2">Indices of the segments of the second path which generate found intersection points.</param>
	AVL_FUNCTION void PathPathIntersections
	(
		const avl::Path&				inPath1,						
		const avl::Path&				inPath2,						
		atl::Array<avl::Point2D>&		outIntersectionPoints,			
		atl::Optional<atl::Array<int>&>	outSegmentIndices1 = atl::NIL,	
		atl::Optional<atl::Array<int>&>	outSegmentIndices2 = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of a path and a segment.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inSegment">Input segment.</param>
	/// <param name="outIntersectionPoints">Intersections between the path and the segment.</param>
	/// <param name="outSegmentIndices">Indices of the segments of the path which generate found intersection points.</param>
	AVL_FUNCTION void PathSegmentIntersections
	(
		const avl::Path&				inPath,							
		const avl::Segment2D&			inSegment,						
		atl::Array<avl::Point2D>&		outIntersectionPoints,			
		atl::Optional<atl::Array<int>&>	outSegmentIndices = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common points of a path and a line.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inLine">Input line.</param>
	/// <param name="outIntersectionPoints">Intersections between the path and the line.</param>
	/// <param name="outSegmentIndices">Indices of the segments of the path which generate found intersection points.</param>
	AVL_FUNCTION void PathLineIntersections
	(
		const avl::Path&					inPath,							
		const avl::Line2D&					inLine,							
		atl::Array<avl::Point2D>&			outIntersectionPoints,			
		atl::Optional<atl::Array<int>&>		outSegmentIndices = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins those paths of an array which endpoints lie near enough.</summary>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: 10.0f.</param>
	/// <param name="inMaxJoiningAngle">Maximal allowed angle between edges being joined. Default value: 30.0f.</param>
	/// <param name="inJoiningDistanceBalance">Determines how important distance between paths is according to their angle difference. Default value: 1.0f.</param>
	/// <param name="inJoiningEndingLength">Determines the length of the path end used for path angle computing. Default value: atl::NIL.</param>
	/// <param name="inMinPathLength">Minimal length of a path. Default value: 0.0f.</param>
	AVL_FUNCTION void JoinAdjacentPaths
	(
		const atl::Array<avl::Path>&	inPaths,
		float						inMaxJoiningDistance,		
		float						inMaxJoiningAngle,			
		float						inJoiningDistanceBalance,	
		atl::Optional<float>		inJoiningEndingLength,		
		float						inMinPathLength,			
		atl::Array<avl::Path>&			outPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits path in common points of two paths.</summary>
	/// <param name="inPath1">Path being split.</param>
	/// <param name="inPath2">Path used for splitting.</param>
	/// <param name="outPaths">Paths arisen from splitting the initial path.</param>
	AVL_FUNCTION void SplitPathByPath
	(
		const avl::Path&		inPath1,	
		const avl::Path&		inPath2,	
		atl::Array<avl::Path>&	outPaths	
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits path in common points of a path and a segment.</summary>
	/// <param name="inPath">Path being split.</param>
	/// <param name="inSegment">Segment used for splitting.</param>
	/// <param name="outPaths">Paths arisen from splitting the initial path.</param>
	AVL_FUNCTION void SplitPathBySegment
	(
		const avl::Path&			inPath,		
		const avl::Segment2D&		inSegment,	
		atl::Array<avl::Path>&		outPaths	
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits path in common points of a path and a line.</summary>
	/// <param name="inPath">Path being split.</param>
	/// <param name="inLine">Line used for splitting.</param>
	/// <param name="outPaths">Paths arisen from splitting the initial path.</param>
	AVL_FUNCTION void SplitPathByLine
	(
		const avl::Path&		inPath,		
		const avl::Line2D&		inLine,		
		atl::Array<avl::Path>&	outPaths	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHCOMBINATORS_H

