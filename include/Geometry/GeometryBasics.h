//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_GEOMETRYBASICS_H
#define AVS_GEOMETRYBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"
#include "Enums/Anchor2D.h"
#include "Enums/RectangleOrientation.h"
#include "AVLCommon/RandomTypes.h"
#include "Basic/Types.h"

namespace avl
{


	/// <summary>Creates random point inside given box</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inBox">Bounding box of generated points.</param>
	/// <param name="inSeed">Random seed. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomPoint
	(
		RandomState&		ioState,	
		const avl::Box&		inBox,		
		atl::Optional<int>	inSeed,		
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a circle from an aligned point and radius.</summary>
	/// <param name="inPointAnchor">Alignment of the point relatively to the box of the circle. Default value: MiddleCenter.</param>
	/// <param name="inRadius">Circle radius.</param>
	AVL_FUNCTION void CreateCircle
	(
		const avl::Point2D&		inPoint,
		avl::Anchor2D::Type		inPointAnchor,	
		float				inRadius,			
		avl::Circle2D&			outCircle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an arc from an aligned point, radius, and angle range.</summary>
	/// <param name="inPointAnchor">Alignment of the point relatively to the box of the circle. Default value: MiddleCenter.</param>
	/// <param name="inRadius">Circle radius.</param>
	/// <param name="inStartAngle">Direction at which the arc begins.</param>
	/// <param name="inSweepAngle">Length of the arc (may be negative).</param>
	AVL_FUNCTION void CreateArc
	(
		const avl::Point2D&		inPoint,
		avl::Anchor2D::Type		inPointAnchor,	
		float				inRadius,		
		float				inStartAngle,	
		float				inSweepAngle,	
		avl::Arc2D&				outArc		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a rectangle from an aligned point.</summary>
	/// <param name="inPointAnchor">Alignment of the input point relatively to the box of the position. Default value: TopLeft.</param>
	/// <param name="inAngle">Clock-wise orientation angle.</param>
	/// <param name="inWidth">Width of the created rectangle.</param>
	/// <param name="inHeight">Height of the created rectangle.</param>
	AVL_FUNCTION void CreateRectangle
	(
		const avl::Point2D&	inPoint,
		avl::Anchor2D::Type	inPointAnchor,		
		float				inAngle,			
		float				inWidth,			
		float				inHeight,			
		avl::Rectangle2D&	outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes orientation of the given rectangle according to parameters.</summary>
	/// <param name="inRectangle">Input rectangle.</param>
	/// <param name="inMinAngle">Lower bound of the output rectangle's angle. Default value: -90.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	AVL_FUNCTION void NormalizeRectangleOrientation_Deprecated
	(
		const avl::Rectangle2D&	inRectangle,	
		const float			inMinAngle,		
		const avl::RectangleOrientation::Type	inRectangleOrientation,	
		avl::Rectangle2D&		outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces a vector of given length and direction.</summary>
	/// <param name="inLength">Desired length of the vector in pixels.</param>
	/// <param name="inDirection">Desired direction of the vector in degrees.</param>
	/// <param name="outVector">The resulting vector.</param>
	AVL_FUNCTION void CreateVector
	(
		float		inLength, 
		float		inDirection, 
		avl::Vector2D&	outVector 
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces a segment of given parameters.</summary>
	/// <param name="inPoint">A point on the created segment.</param>
	/// <param name="inPointAnchor">Anchor point, 0 means the beginning, 1 means the end of the segment.</param>
	/// <param name="inDirection">Desired direction of the segment in degrees.</param>
	/// <param name="inLength">Desired length of the segment in pixels.</param>
	/// <param name="outSegment">The resulting segment.</param>
	AVL_FUNCTION void CreateSegment
	(
		const avl::Point2D&	inPoint,		
		float			inPointAnchor,	
		float			inDirection,	
		float			inLength,		
		avl::Segment2D&		outSegment		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a grid of points.</summary>
	/// <param name="inPoint">A starting point of the created grid.</param>
	/// <param name="inAnchor">Anchor of the reference point. Default value: TopLeft.</param>
	/// <param name="inRowCount">Number of rows the grid will have.</param>
	/// <param name="inColumnCount">Number of columns the grid will have.</param>
	/// <param name="inRowStep">Distance between consecutive rows of the created grid. Default value: 1.0f.</param>
	/// <param name="inColumnStep">Distance between consecutive columns of the created grid. Default value: 1.0f.</param>
	/// <param name="outPointGrid">Created point grid.</param>
	AVL_FUNCTION void CreatePointGrid
	(
		const avl::Point2D&			inPoint,			
		avl::Anchor2D::Type			inAnchor,			
		const int					inRowCount,			
		const int					inColumnCount,		
		const float				inRowStep,			
		const float				inColumnStep,		
		atl::Array<avl::Point2D>&	outPointGrid		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a grid of points in a described rectangle.</summary>
	/// <param name="inRectangle">Where points should be inscribed.</param>
	/// <param name="inRowCount">Number of rows the grid will have.</param>
	/// <param name="inColumnCount">Number of columns the grid will have.</param>
	/// <param name="outPointGrid">Output points.</param>
	AVL_FUNCTION void CreateRectangularPointGrid
	(
		const avl::Rectangle2D&			inRectangle,	
		const avl::CoordinateSystem2D&	inAlignment,	
		const int&						inRowCount,		
		const int&						inColumnCount,	
		const float&					inMarginWidth,	
		const float&					inMarginHeight, 
		atl::Array<avl::Point2D>&		outPointGrid,	
		avl::Rectangle2D&				diagAlignedRectangle = atl::Dummy<avl::Rectangle2D>()
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a point structure from individual fields.</summary>
	/// <param name="inX">Horizontal coordinate.</param>
	/// <param name="inY">Vertical coordinate.</param>
	AVL_FUNCTION void AvsFilter_MakePoint
	(
		float		inX,	
		float		inY,	
		avl::Point2D& outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a StringLabel structure from individual fields.</summary>
	AVL_FUNCTION void AvsFilter_MakeStringLabel
	(
		const atl::String&		inText,
		const avl::Point2D&		inPosition,
		avl::StringLabel&		outLabel
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a vector structure from individual fields.</summary>
	/// <param name="inDeltaX">Delta along x-axis.</param>
	/// <param name="inDeltaY">Delta along y-axis.</param>
	AVL_FUNCTION void AvsFilter_MakeVector
	(
		float		inDeltaX,		
		float		inDeltaY,		
		avl::Vector2D&	outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment structure from individual fields.</summary>
	/// <param name="inPoint1">First point of the segment.</param>
	/// <param name="inPoint2">Second point of the segment.</param>
	AVL_FUNCTION void AvsFilter_MakeSegment
	(
		const avl::Point2D&	inPoint1,	
		const avl::Point2D&	inPoint2,	
		avl::Segment2D&		outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a circle structure from individual fields.</summary>
	/// <param name="inCenter">Center of the circle.</param>
	/// <param name="inRadius">Circle radius.</param>
	AVL_FUNCTION void AvsFilter_MakeCircle
	(
		const avl::Point2D&	inCenter,	
		float			inRadius,	
		avl::Circle2D&		outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an arc structure from individual fields.</summary>
	/// <param name="inCenter">Center of the arc.</param>
	/// <param name="inRadius">The arc radius.</param>
	/// <param name="inStartAngle">Direction at which the arc begins.</param>
	/// <param name="inSweepAngle">Length of the arc (may be negative).</param>
	AVL_FUNCTION void AvsFilter_MakeArc
	(
		const avl::Point2D&	inCenter,		
		float			inRadius,		
		float			inStartAngle,	
		float			inSweepAngle,	
		avl::Arc2D&			outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a line structure from individual fields.</summary>
	/// <param name="inA">First linear parameter.</param>
	/// <param name="inB">Second linear parameter.</param>
	/// <param name="inC">Third linear parameter.</param>
	AVL_FUNCTION void AvsFilter_MakeLine
	(
		float inA,				
		float inB,				
		float inC,				
		avl::Line2D& outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a rectangle structure from individual fields.</summary>
	/// <param name="inOrigin">Origin of the rectangle.</param>
	/// <param name="inAngle">Clock-wise orientation angle.</param>
	AVL_FUNCTION void AvsFilter_MakeRectangle
	(
		const avl::Point2D&	inOrigin,	
		float				inAngle,			
		float				inWidth,
		float				inHeight,
		avl::Rectangle2D&	outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a coordinate system structure from individual fields.</summary>
	/// <param name="inOrigin">Origin of the coordinate system.</param>
	/// <param name="inAngle">Clock-wise orientation angle.</param>
	/// <param name="inScale">Default value: 1.0f.</param>
	AVL_FUNCTION void AvsFilter_MakeCoordinateSystem
	(
		const avl::Point2D&			inOrigin,	
		float					inAngle,	
		float					inScale,
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a point.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="outX">Output x-coordinate.</param>
	/// <param name="outY">Output y-coordinate.</param>
	AVL_FUNCTION void AvsFilter_AccessPoint
	(
		const avl::Point2D&	inPoint,
		float&			outX,
		float&			outY
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a StringLabel structure.</summary>
	AVL_FUNCTION void AvsFilter_AccessStringLabel
	(
		const avl::StringLabel&	inLabel,
		atl::String&			outText,
		avl::Point2D&			outPosition
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a vector.</summary>
	/// <param name="inVector">Input vector.</param>
	/// <param name="outDeltaX">Output delta along x-axis.</param>
	/// <param name="outDeltaY">Output delta along y-axis.</param>
	AVL_FUNCTION void AvsFilter_AccessVector
	(
		const avl::Vector2D&	inVector,
		float&				outDeltaX,
		float&				outDeltaY
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a segment.</summary>
	/// <param name="outPoint1">First point of the segment.</param>
	/// <param name="outPoint2">Second point of the segment.</param>
	AVL_FUNCTION void AvsFilter_AccessSegment
	(
		const avl::Segment2D&	inSegment,
		avl::Point2D&			outPoint1,	
		avl::Point2D&			outPoint2	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a circle.</summary>
	/// <param name="inCircle">Input circle.</param>
	/// <param name="outCenter">Center of the circle.</param>
	/// <param name="outRadius">Output radius.</param>
	AVL_FUNCTION void AvsFilter_AccessCircle
	(
		const avl::Circle2D&	inCircle,
		avl::Point2D&			outCenter,
		float&				outRadius
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of an arc.</summary>
	AVL_FUNCTION void AvsFilter_AccessArc
	(
		const avl::Arc2D&	inArc,
		avl::Point2D&		outCenter,
		float&			outRadius,
		float&			outStartAngle,
		float&			outSweepAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a line.</summary>
	/// <param name="inLine">Input line.</param>
	/// <param name="outA">Output line parameter A.</param>
	/// <param name="outB">Output line parameter B.</param>
	/// <param name="outC">Output line parameter C.</param>
	AVL_FUNCTION void AvsFilter_AccessLine
	(
		const avl::Line2D&	inLine,
		float&			outA,
		float&			outB,
		float&			outC
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a rectangle.</summary>
	/// <param name="outOrigin">Origin of the rectangle.</param>
	/// <param name="outAngle">Clock-wise orientation angle.</param>
	AVL_FUNCTION void AvsFilter_AccessRectangle
	(
		const avl::Rectangle2D& inRectangle,
		avl::Point2D&	outOrigin,				
		float& outAngle,					
		float& outWidth,
		float& outHeight
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a coordinate system.</summary>
	/// <param name="outOrigin">Origin of the coordinate system.</param>
	/// <param name="outAngle">Clock-wise orientation angle.</param>
	AVL_FUNCTION void AvsFilter_AccessCoordinateSystem
	(
		const avl::CoordinateSystem2D& inCoordinateSystem,
		avl::Point2D&	outOrigin,				
		float& outAngle,					
		float& outScale
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_GEOMETRYBASICS_H

