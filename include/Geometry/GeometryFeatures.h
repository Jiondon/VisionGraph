//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYFEATURES_H
#define AVL_GEOMETRYFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Enums/Anchor2D.h"
#include "Enums/AngleRange.h"
#include "Enums/BoundingRectangleFeature.h"
#include "Enums/RectangleOrientation.h"
#include "Basic/Types.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Computes the midpoint of an arc.</summary>
	AVL_FUNCTION void ArcMidpoint
	(
		const avl::Arc2D&	inArc,
		avl::Point2D&		outMidpoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes two endpoints of an arc.</summary>
	/// <param name="outPoint1">First endpoint.</param>
	/// <param name="outPoint2">Second endpoint.</param>
	AVL_FUNCTION void ArcEndpoints
	(
		const avl::Arc2D&	inArc,
		avl::Point2D&		outPoint1,	
		avl::Point2D&		outPoint2		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of an arc.</summary>
	AVL_FUNCTION void ArcLength
	(
		const avl::Arc2D&	inArc,
		float&			outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the circle containing an arc.</summary>
	/// <param name="inArc">Input arc.</param>
	/// <param name="outCircle">Circle containing the arc.</param>
	AVL_FUNCTION void ArcCircle
	(
		const avl::Arc2D&	inArc,		
		avl::Circle2D&		outCircle	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the center point of a segment.</summary>
	AVL_FUNCTION void SegmentCenter
	(
		const avl::Segment2D&	inSegment,
		avl::Point2D&			outCenterPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of a segment.</summary>
	AVL_FUNCTION void SegmentLength
	(
		const avl::Segment2D&	inSegment,
		float&				outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a line passing through the center of a segment at a right angle.</summary>
	AVL_FUNCTION void SegmentBisector
	(
		const avl::Segment2D&	inSegment,
		avl::Line2D&			outBisector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an unitary vector perpendicular to the segment.</summary>
	AVL_FUNCTION void SegmentNormalVector
	(
		const avl::Segment2D&	inSegment,
		avl::Vector2D&			outNormalVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the line passing through a segment.</summary>
	/// <param name="inSegment">Input segment.</param>
	/// <param name="outLine">The resulting line.</param>
	AVL_FUNCTION void SegmentLine
	(
		const avl::Segment2D&	inSegment,	
		avl::Line2D&			outLine		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the vector [x2 - x1, y2 - y1]</summary>
	AVL_FUNCTION void SegmentVector
	(
		const avl::Segment2D&	inSegment,
		avl::Vector2D&			outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the orientation of a segment.</summary>
	/// <param name="inAngleRange">Switches between 0-180 or 0-360 degrees. Default value: _0_180.</param>
	AVL_FUNCTION void SegmentOrientation
	(
		const avl::Segment2D&	inSegment,
		avl::AngleRange::Type	inAngleRange,	
		float&				outOrientationAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point (e.g. the top-left) of a box containing the input circle.</summary>
	/// <param name="inPointAnchor">Default value: TopLeft.</param>
	AVL_FUNCTION void CircleCharacteristicPoint
	(
		const avl::Circle2D&		inCircle,
		const avl::Anchor2D::Type	inPointAnchor,
		avl::Point2D&				outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a circle.</summary>
	AVL_FUNCTION void CircleArea
	(
		const avl::Circle2D&	inCircle,
		float&				outArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of a circle perimeter.</summary>
	AVL_FUNCTION void CirclePerimeterLength
	(
		const avl::Circle2D&	inCircle,
		float&				outPerimeterLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an arciform section of the circle perimeter.</summary>
	/// <param name="inCircle">Input circle.</param>
	/// <param name="inStartAngle">Direction at which the arc begins.</param>
	/// <param name="inSweepAngle">Angular length of the arc (may be negative).</param>
	AVL_FUNCTION void CircleSection
	(
		const avl::Circle2D&	inCircle,		
		float				inStartAngle,	
		float				inSweepAngle,	
		avl::Arc2D&				outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a circle.</summary>
	AVL_FUNCTION void CircleBoundingBox
	(
		const avl::Circle2D&	inCircle,
		avl::Box&				outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a circle.</summary>
	/// <param name="inCircle">Input circle.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle. Default value: atl::NIL.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input circle.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void CircleBoundingRectangle
	(
		const avl::Circle2D&			inCircle,					
		atl::Optional<float>		inAngle,					
		avl::Rectangle2D&				outBoundingRectangle,		
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,		
		atl::Optional<float&>		outLongSide = atl::NIL,		
		atl::Optional<float&>		outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the orientation angle of a line as angle in the range from 0 to 180.</summary>
	AVL_FUNCTION void LineOrientation
	(
		const avl::Line2D&	inLine,
		float&			outOrientationAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the normal vector of a line</summary>
	AVL_FUNCTION void LineNormalVector
	(
		const avl::Line2D&	inLine,
		avl::Vector2D&		outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the direction angle of a vector as an angle in range the from 0 to 360.</summary>
	AVL_FUNCTION void VectorDirection
	(
		const avl::Vector2D&	inVector,
		float&				outDirection
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of a vector.</summary>
	AVL_FUNCTION void VectorLength
	(
		const avl::Vector2D&	inVector,
		float&				outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the central point of the input points.</summary>
	AVL_FUNCTION void PointsMassCenter
	(
		const atl::Array<avl::Point2D>&	inPoints,
		avl::Point2D&					outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the central point of the input points; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void PointsMassCenter_OrNil
	(
		const atl::Array<avl::Point2D>&	inPoints,
		atl::Conditional<avl::Point2D>&	outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the geometric median of the input points.</summary>
	/// <param name="inPoints">Input points.</param>
	/// <param name="inWeights">Optional input weights. Default value: atl::NIL.</param>
	/// <param name="inMaxIterationCount">Maximum number of iterations. Default value: 10.</param>
	/// <param name="outGeometricMedian">Geometric median.</param>
	/// <param name="outDistanceSum">Sum of distances from input points to geometric median.</param>
	/// <param name="diagApproximationSteps">Approximate geometric medians calculated during subsequent iterations.</param>
	AVL_FUNCTION void PointsMedian
	(
		const atl::Array<avl::Point2D>&		inPoints,					
		const atl::Optional<const atl::Array<float>&>&	inWeights,		
		const int							inMaxIterationCount,		
		avl::Point2D&						outGeometricMedian,			
		atl::Optional<float&>				outDistanceSum = atl::NIL,	
		atl::Array<avl::Point2D>&			diagApproximationSteps = atl::Dummy< atl::Array<avl::Point2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the geometric median of the input vectors.</summary>
	/// <param name="inVectors">Input vectors.</param>
	/// <param name="inWeights">Optional input weights. Default value: atl::NIL.</param>
	/// <param name="inMaxIterationCount">Maximum number of iterations. Default value: 10.</param>
	/// <param name="outGeometricMedian">Geometric median.</param>
	/// <param name="outDistanceSum">Sum of distances from input vectors to geometric median.</param>
	/// <param name="diagApproximationSteps">Approximate geometric medians calculated during subsequent iterations.</param>
	AVL_FUNCTION void VectorsMedian
	(
		const atl::Array<avl::Vector2D>&				inVectors,					
		const atl::Optional<const atl::Array<float>&>&	inWeights,					
		const int										inMaxIterationCount,		
		avl::Vector2D&									outGeometricMedian,			
		atl::Optional<float&>							outDistanceSum = atl::NIL,	
		atl::Array<avl::Vector2D>&						diagApproximationSteps = atl::Dummy< atl::Array<avl::Vector2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing an array of points.</summary>
	AVL_FUNCTION void PointsBoundingBox
	(
		const atl::Array<avl::Point2D>& inPoints,
		avl::Box&						outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing an array of points; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void PointsBoundingBox_OrNil
	(
		const atl::Array<avl::Point2D>& inPoints,
		atl::Conditional<avl::Box>&		outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle containing an array of points.</summary>
	AVL_FUNCTION void PointsBoundingCircle
	(
		const atl::Array<avl::Point2D>& inPoints,
		avl::Circle2D&					outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle containing an array of points; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void PointsBoundingCircle_OrNil
	(
		const atl::Array<avl::Point2D>&		inPoints,
		atl::Conditional<avl::Circle2D>&	outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest convex shape that contains the given array of points.</summary>
	/// <param name="outConvexHull">A closed path representing the computed convex hull.</param>
	AVL_FUNCTION void PointsConvexHull
	(
		const atl::Array<avl::Point2D>& inPoints,
		avl::Path&						outConvexHull 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing an array of points.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input points.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PointsBoundingRectangle_FixedAngle
	(
		const atl::Array<avl::Point2D>& inPoints,					
		float							inAngle,					
		avl::Rectangle2D&				outBoundingRectangle,		
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,		
		atl::Optional<float&>			outLongSide = atl::NIL,		
		atl::Optional<float&>			outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing an array of points; returns NIL when the array is empty.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input points.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PointsBoundingRectangle_FixedAngle_OrNil
	(
		const atl::Array<avl::Point2D>&		inPoints,				
		float								inAngle,				
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,	
		atl::Conditional<avl::Point2D>&		outCenter,				
		atl::Conditional<float>&			outLongSide,			
		atl::Conditional<float>&			outShortSide			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing an array of points.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input points.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PointsBoundingRectangle
	(
		const atl::Array<avl::Point2D>&		inPoints,					
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		float								inReferenceAngle,			
		avl::RectangleOrientation::Type		inRectangleOrientation,		
		avl::Rectangle2D&					outBoundingRectangle,		
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,		
		atl::Optional<float&>				outLongSide = atl::NIL,		
		atl::Optional<float&>				outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing an array of points; returns NIL when the array is empty.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input points.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PointsBoundingRectangle_OrNil
	(
		const atl::Array<avl::Point2D>&		inPoints,					
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		float								inReferenceAngle,			
		avl::RectangleOrientation::Type		inRectangleOrientation,		
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,		
		atl::Conditional<avl::Point2D>&		outCenter,					
		atl::Conditional<float>&			outLongSide,				
		atl::Conditional<float>&			outShortSide				
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the longest segment connecting two points from a given array.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="outDiameter">Longest segment found.</param>
	/// <param name="outDiameterLength">Length of longest segment found.</param>
	AVL_FUNCTION void PointsDiameter
	(
		const atl::Array<avl::Point2D>& inPoints,						
		atl::Optional<avl::Segment2D&>	outDiameter = atl::NIL,			
		atl::Optional<float&>		outDiameterLength = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the center point of a rectangle.</summary>
	AVL_FUNCTION void RectangleCenter
	(
		const avl::Rectangle2D& inRectangle,
		avl::Point2D&			outCenterPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point (e.g. the top-left) of the input rectangle.</summary>
	/// <param name="inPointAnchor">Default value: TopLeft.</param>
	AVL_FUNCTION void RectangleCharacteristicPoint
	(
		const avl::Rectangle2D&		inRectangle,
		const avl::Anchor2D::Type	inPointAnchor,
		avl::Point2D&				outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a rectangle.</summary>
	AVL_FUNCTION void RectangleArea
	(
		const avl::Rectangle2D& inRectangle,
		float&				outArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the perimeter length of a rectangle.</summary>
	AVL_FUNCTION void RectanglePerimeterLength
	(
		const avl::Rectangle2D&	inRectangle,
		float&				outPerimeterLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a rectangle.</summary>
	AVL_FUNCTION void RectangleBoundingBox
	(
		const avl::Rectangle2D& inRectangle,
		avl::Box&				outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing an array of points.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inRectangleOrientation">Expected orientation of the resulting rectangle. Default value: atl::NIL.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input points.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void PointsBoundingRectangle_Deprecated
	(
		const atl::Array<avl::Point2D>& inPoints,					
		atl::Optional<float>		inRectangleOrientation,		
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		avl::Rectangle2D&				outBoundingRectangle,		
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,		
		atl::Optional<float&>		outLongSide = atl::NIL,		
		atl::Optional<float&>		outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes rectangle's characteristic points.</summary>
	AVL_FUNCTION void RectangleCharacteristicPoints
	(
		const avl::Rectangle2D&						inRectangle,
		atl::Optional<avl::Point2D&>				outTopLeft = atl::NIL,
		atl::Optional<avl::Point2D&>				outTopCenter = atl::NIL,
		atl::Optional<avl::Point2D&>				outTopRight = atl::NIL,
		atl::Optional<avl::Point2D&>				outMiddleLeft = atl::NIL,
		atl::Optional<avl::Point2D&>				outMiddleCenter = atl::NIL,
		atl::Optional<avl::Point2D&>				outMiddleRight = atl::NIL,
		atl::Optional<avl::Point2D&>				outBottomLeft = atl::NIL,
		atl::Optional<avl::Point2D&>				outBottomCenter = atl::NIL,
		atl::Optional<avl::Point2D&>				outBottomRight = atl::NIL,
		atl::Optional<atl::Array<avl::Point2D>&>	outCorners = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest parallelogram containing an array of points.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="inBoundingParallelogramFeature">Determines what kind of bounding parallelogram will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingParallelogram">Smallest bounding parallelogram of the input points.</param>
	/// <param name="outCenter">Center of the bounding parallelogram.</param>
	/// <param name="outLongSide">Length of the bounding parallelogram long side.</param>
	/// <param name="outShortSide">Length of the bounding parallelogram short side.</param>
	/// <param name="outAngle">Angle of the bounding parallelogram.</param>
	AVL_FUNCTION void PointsBoundingParallelogram
	(
		const atl::Array<avl::Point2D>&		inPoints,					
		avl::BoundingRectangleFeature::Type	inBoundingParallelogramFeature,	
		avl::Path&							outBoundingParallelogram,	
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,		
		atl::Optional<float&>				outLongSide = atl::NIL,		
		atl::Optional<float&>				outShortSide = atl::NIL,	
		atl::Optional<float&>				outAngle = atl::NIL			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYFEATURES_H

