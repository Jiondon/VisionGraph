//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHFEATURES_H
#define AVL_PATHFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/BoundingRectangleFeature.h"
#include "Enums/RectangleOrientation.h"
#include "Profile/Profile.h"
#include "Path/Path.h"
#include "Basic/Types.h"

namespace avl
{


	/// <summary>Converts a path to an array of line segments.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathSegments
	(
		const avl::Path&			inPath,
		atl::Array<avl::Segment2D>&	outSegments
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of the path points (all, not only characteristic ones).</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathMassCenter
	(
		const avl::Path&	inPath,
		avl::Point2D&		outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of the path points (all, not only characteristic ones); returns NIL if the path is empty.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathMassCenter_OrNil
	(
		const avl::Path&				inPath,
		atl::Conditional<avl::Point2D>&	outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the number of characteristic points on the input path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathSize
	(
		const avl::Path&	inPath,
		int&				outSize
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the total length of the input path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathLength
	(
		const avl::Path&	inPath,
		float&			outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the two endpoints of a path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathEndpoints
	(
		const avl::Path&	inPath,
		avl::Point2D&		outFirstPoint,
		avl::Point2D&		outLastPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the profile of turn angles at characteristic points of a path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathTurnAngleProfile
	(
		const avl::Path&	inPath,
		avl::Profile&		outTurnAngleProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average absolute turn angle of a path per unit of length.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathAverageTurnAngle
	(
		const avl::Path&	inPath,
		float&			outAverageTurnAngle
	)
	THROW_AVL_ERRORS;

	namespace TurnAngleDirection
	{
		enum Type
		{
			Left,
			Right,
			All
		};
	}

	namespace TurnAnglePrecision
	{
		enum Type
		{
			PointPrecise,
			SubpointPrecise
		};
	}


	/// <summary>Finds the local maxima of the profile of turn angles of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAllowedTurnDirection">Allows to detect only left-turns, only right-turns or both. Default value: All.</param>
	/// <param name="inResultPrecision">Switches between pixel-precise or subpixel-precise detection of the found maxima.</param>
	/// <param name="inMinTurnAngle">Minimal value of a relevant angle. Default value: 30.0f.</param>
	/// <param name="inMinDistance">Minimal distance on the path between two local maxima assuming each path segment has unit length. Default value: 0.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the input path. Default value: 0.6f.</param>
	/// <param name="outTurnAngleMaximaIndices">Indices of found local maxima.</param>
	/// <param name="outTurnAngleMaximaPoints">Found local maxima of turn angle profile of the smoothed input path.</param>
	/// <param name="outTurnAngleMaximaAngles">Turn angles of found local maxima.</param>
	/// <param name="diagSmoothedPath">Input path smoothed with gaussian kernel.</param>
	/// <param name="diagTurnAngleProfile">Profile of turn angles at characteristic points of the smoothed input path.</param>
	AVL_FUNCTION void PathTurnAngleLocalMaxima
	(
		const avl::Path&				inPath,					
		avl::TurnAngleDirection::Type	inAllowedTurnDirection,	
		avl::TurnAnglePrecision::Type	inResultPrecision,		
		const float					inMinTurnAngle,			
		const float					inMinDistance,			
		const float					inSmoothingStdDev,		
		atl::Array<float>&			outTurnAngleMaximaIndices,	
		atl::Array<avl::Point2D>&		outTurnAngleMaximaPoints,	
		atl::Array<float>&			outTurnAngleMaximaAngles,	
		avl::Path&						diagSmoothedPath = atl::Dummy<avl::Path>(),		
		avl::Profile&					diagTurnAngleProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the maximum of the profile of turn angles of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAllowedTurnDirection">Allows to detect only left-turns, only right-turns or both. Default value: All.</param>
	/// <param name="inResultPrecision">Switches between pixel-precise or subpixel-precise detection of the found maximum.</param>
	/// <param name="outMaximumTurnAngleIndex">Index of found maximum.</param>
	/// <param name="outMaximumTurnAnglePoint">Found point of a path with maximum turn angle.</param>
	/// <param name="outMaximumTurnAngleAngle">Maximal turn angle of the input path.</param>
	AVL_FUNCTION void PathTurnAngleMaximum
	(
		const avl::Path&				inPath,						
		avl::TurnAngleDirection::Type	inAllowedTurnDirection,		
		avl::TurnAnglePrecision::Type	inResultPrecision,			
		float&						outMaximumTurnAngleIndex,	
		avl::Point2D&					outMaximumTurnAnglePoint,	
		float&						outMaximumTurnAngleAngle	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the maximum of the profile of turn angles of a path; returns NIL if the path has no turn angles.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAllowedTurnDirection">Allows to detect only left-turns, only right-turns or both. Default value: All.</param>
	/// <param name="inResultPrecision">Switches between pixel-precise or subpixel-precise detection of the found maximum.</param>
	/// <param name="outMaximumTurnAngleIndex">Index of found maximum.</param>
	/// <param name="outMaximumTurnAnglePoint">Found point of a path with maximum turn angle.</param>
	/// <param name="outMaximumTurnAngleAngle">Maximal turn angle of the input path.</param>
	AVL_FUNCTION void PathTurnAngleMaximum_OrNil
	(
		const avl::Path&				inPath,						
		avl::TurnAngleDirection::Type	inAllowedTurnDirection,		
		avl::TurnAnglePrecision::Type	inResultPrecision,			
		atl::Conditional<float>&		outMaximumTurnAngleIndex,	
		atl::Conditional<avl::Point2D>&	outMaximumTurnAnglePoint,	
		atl::Conditional<float>&		outMaximumTurnAngleAngle	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle enclosing a path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathBoundingCircle
	(
		const avl::Path&	inPath,
		avl::Circle2D&		outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle enclosing a path; returns NIL if the path is empty.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathBoundingCircle_OrNil
	(
		const avl::Path&					inPath,
		atl::Conditional<avl::Circle2D>&	outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathBoundingBox
	(
		const avl::Path&	inPath,
		avl::Box&			outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a path; returns NIL if the path is empty.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathBoundingBox_OrNil
	(
		const avl::Path&			inPath,
		atl::Conditional<avl::Box>&	outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input path.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PathBoundingRectangle_FixedAngle
	(
		const avl::Path&				inPath,						
		float							inAngle,					
		avl::Rectangle2D&				outBoundingRectangle,		
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,		
		atl::Optional<float&>			outLongSide = atl::NIL,		
		atl::Optional<float&>			outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing a path; returns NIL when the path is empty.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input path.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PathBoundingRectangle_FixedAngle_OrNil
	(
		const avl::Path&					inPath,					
		float								inAngle,				
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,	
		atl::Conditional<avl::Point2D>&		outCenter,				
		atl::Conditional<float>&			outLongSide,			
		atl::Conditional<float>&			outShortSide			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">The smallest bounding rectangle of the input path.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PathBoundingRectangle
	(
		const avl::Path&					inPath,							
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,		
		float							inReferenceAngle,				
		avl::RectangleOrientation::Type		inRectangleOrientation,			
		avl::Rectangle2D&					outBoundingRectangle,			
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,			
		atl::Optional<float&>			outLongSide = atl::NIL,			
		atl::Optional<float&>			outShortSide = atl::NIL			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a path; returns NIL when the path is empty.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input path.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PathBoundingRectangle_OrNil
	(
		const avl::Path&					inPath,						
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		float								inReferenceAngle,			
		avl::RectangleOrientation::Type		inRectangleOrientation,		
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,		
		atl::Conditional<avl::Point2D>&		outCenter,					
		atl::Conditional<float>&			outLongSide,				
		atl::Conditional<float>&			outShortSide				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest parallelogram containing a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inBoundingParallelogramFeature">Determines what kind of bounding parallelogram will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingParallelogram">Smallest bounding parallelogram of the input points.</param>
	/// <param name="outCenter">Center of the bounding parallelogram.</param>
	/// <param name="outLongSide">Length of the bounding parallelogram long side.</param>
	/// <param name="outShortSide">Length of the bounding parallelogram short side.</param>
	/// <param name="outAngle">Angle of the bounding parallelogram.</param>
	AVL_FUNCTION void PathBoundingParallelogram
	(
		const avl::Path&					inPath,							
		avl::BoundingRectangleFeature::Type	inBoundingParallelogramFeature,	
		avl::Path&							outBoundingParallelogram,	
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,		
		atl::Optional<float&>				outLongSide = atl::NIL,		
		atl::Optional<float&>				outShortSide = atl::NIL,	
		atl::Optional<float&>				outAngle = atl::NIL			
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the longest segment connecting two characteristic points of a path.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathDiameter
	(
		const avl::Path&				inPath,
		atl::Optional<avl::Segment2D&>	outDiameter,
		atl::Optional<float&>		outDiameterLength	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest convex shape that contains the given path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outConvexHull">A closed path representing the computed convex hull.</param>
	AVL_FUNCTION void PathConvexHull
	(
		const avl::Path&	inPath,
		avl::Path&			outConvexHull 
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of paths to an array of points.</summary>
	AVL_FUNCTION void PathArrayPoints
	(
		const atl::Array<avl::Path>&	inPaths,
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a path has any self-intersections and computes all of them.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outFirstSegmentIndices">First indices of the segments of the path which generate found intersection points.</param>
	/// <param name="outSecondSegmentIndices">Second indices of the segments of the path which generate found intersection points.</param>
	AVL_FUNCTION void PathSelfIntersections
	(
		const avl::Path&				inPath,
		atl::Array<avl::Point2D>&		outSelfIntersections,
		atl::Optional<atl::Array<int>&>	outFirstSegmentIndices = atl::NIL,	
		atl::Optional<atl::Array<int>&>	outSecondSegmentIndices = atl::NIL,	
		atl::Optional<bool&>			outIsSelfIntersecting = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle (can be rotated) containing a path.</summary>
	/// <param name="inPath">Input array of points.</param>
	/// <param name="inRectangleOrientation">Expected orientation of the resulting rectangle. Default value: atl::NIL.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingRectangle">The smallest bounding rectangle of the input path.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PathBoundingRectangle_Deprecated
	(
		const avl::Path&				inPath,					
		atl::Optional<float>		inRectangleOrientation, 
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		avl::Rectangle2D&				outBoundingRectangle,	
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,	
		atl::Optional<float&>		outLongSide = atl::NIL,	
		atl::Optional<float&>		outShortSide = atl::NIL	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHFEATURES_H

