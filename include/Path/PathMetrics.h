//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHMETRICS_H
#define AVL_PATHMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Profile/Profile.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Computes the smallest distance between a path and a point.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="inPath">Input path.</param>
	/// <param name="inResolution">Default value: 1.0f.</param>
	/// <param name="outDistance">Minimal distance between input path and input point.</param>
	/// <param name="outConnectingSegment">Segment connecting input path and input point having minimal length.</param>
	AVL_FUNCTION void PathToPointDistance
	(
		const avl::Point2D&				inPoint,						
		const avl::Path&				inPath,							
		float						inResolution,
		float&						outDistance,					
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the profile of distances between the specified point and the characteristic points of a path.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="inPath">Input path.</param>
	/// <param name="inResolution">Default value: 1.0f.</param>
	/// <param name="outDistanceProfile">Profile of distances between input point and consecutive points of input path.</param>
	/// <param name="outDistances">Distances between input point and consecutive points of input path.</param>
	/// <param name="outConnectingSegments">Segments connecting input point and consecutive points of input path.</param>
	AVL_FUNCTION void PathToPointDistanceProfile
	(
		const avl::Point2D&							inPoint,				
		const avl::Path&							inPath,					
		float									inResolution,
		avl::Profile&								outDistanceProfile,		
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,
		atl::Optional<atl::Array<avl::Segment2D>&>	outConnectingSegments = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest distance between a path and a line.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inLine">Input line.</param>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	/// <param name="outDistance">Minimal distance between input path and input line.</param>
	/// <param name="outConnectingSegment">Segment connecting input path and input line having minimal length.</param>
	AVL_FUNCTION void PathToLineDistance
	(
		const avl::Path&				inPath,				
		const avl::Line2D&				inLine,				
		float						inResolution,		
		float&						outDistance,		
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the profile of distances between a line and the characteristic points of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inLine">Input line.</param>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	/// <param name="outDistanceProfile">Profile of distances between input line and consecutive points of input path.</param>
	/// <param name="outDistances">Distances between input line and consecutive points of input path.</param>
	/// <param name="outConnectingSegments">Segments connecting input line and consecutive points of input path having minimal length.</param>
	AVL_FUNCTION void PathToLineDistanceProfile
	(
		const avl::Path&							inPath,					
		const avl::Line2D&							inLine,					
		float									inResolution,			
		avl::Profile&								outDistanceProfile,		
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,
		atl::Optional<atl::Array<avl::Segment2D>&>	outConnectingSegments = atl::NIL	
	)
	THROW_AVL_ERRORS;

	namespace PathDistanceMode
	{
		enum Type
		{
			PointToPoint,
			PointToSegment
		};
	}


	/// <summary>Computes the minimum distance between two paths.</summary>
	/// <param name="inPath1">First input path.</param>
	/// <param name="inPath2">Second input path.</param>
	/// <param name="inPathDistanceMode">Distance measuring method.</param>
	/// <param name="inResolution">Default value: 1.0f.</param>
	/// <param name="outDistance">Minimal distance between input paths.</param>
	/// <param name="outConnectingSegment">Segment connecting input paths having minimal length.</param>
	AVL_FUNCTION void PathToPathDistance
	(
		const avl::Path&					inPath1,			
		const avl::Path&					inPath2,			
		avl::PathDistanceMode::Type			inPathDistanceMode,	
		float								inResolution,
		float&								outDistance,		
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the profile of distances between two paths.</summary>
	/// <param name="inPath1">First input path.</param>
	/// <param name="inPath2">Second input path.</param>
	/// <param name="inPathDistanceMode">Distance measuring method.</param>
	/// <param name="inResolution">Default value: 1.0f.</param>
	/// <param name="outDistanceProfile">Profile of distances between second path and consecutive points of first path.</param>
	/// <param name="outDistances">Distances between second path and consecutive points of first path.</param>
	/// <param name="outConnectingSegments">Segments connecting second path and consecutive points of first path having minimal length.</param>
	AVL_FUNCTION void PathToPathDistanceProfile
	(
		const avl::Path&							inPath1,				
		const avl::Path&							inPath2,				
		avl::PathDistanceMode::Type					inPathDistanceMode,		
		float										inResolution,
		avl::Profile&								outDistanceProfile,		
		atl::Optional<atl::Array<float>&>			outDistances = atl::NIL,
		atl::Optional<atl::Array<avl::Segment2D>&>	outConnectingSegments = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the distance between the farthest point of the input path from the other path.</summary>
	/// <param name="inPath1">First input path.</param>
	/// <param name="inPath2">Second input path.</param>
	/// <param name="inPathDistanceMode">Distance measuring method.</param>
	/// <param name="inResolution">Default value: 1.0f.</param>
	/// <param name="outDistance">Distance between farthest point of the input path the other input path.</param>
	/// <param name="outConnectingSegment">Segment connecting input paths having such distance.</param>
	AVL_FUNCTION void PathToPathMaximumDistance
	(
		const avl::Path&					inPath1,			
		const avl::Path&					inPath2,			
		avl::PathDistanceMode::Type			inPathDistanceMode,	
		float								inResolution,
		float&								outDistance,		
		atl::Optional<avl::Segment2D&>		outConnectingSegment = atl::NIL 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHMETRICS_H

