//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYSPATIALTRANSFORMS_H
#define AVL_GEOMETRYSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Basic/Types.h"
#include "Path/Path.h"
#include "Enums/Axis.h"
#include "Enums/AngleRange.h"
#include "Enums/Anchor2D.h"

namespace avl
{


	/// <summary>Translates a point by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint
	(
		const avl::Point2D&		inPoint,
		const avl::Vector2D&	inDelta,	
		bool					inInverse,	
		avl::Point2D&			outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a point towards another point by a specified distance.</summary>
	/// <param name="inTargetPoint">Defines the direction of the translation.</param>
	/// <param name="inDistance">The distance between inPoint and outPoint.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint_Toward
	(
		const avl::Point2D&	inPoint,
		const avl::Point2D&	inTargetPoint,		
		float			inDistance,			
		bool				inInverse,			
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a point clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint
	(
		const avl::Point2D&	inPoint, 
		const avl::Point2D&	inCenter,	
		float			inAngle,	
		bool				inInverse,			
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a point from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignPoint
	(
		const avl::Point2D&		inPoint,
		const avl::CoordinateSystem2D&	inAlignment,		
		bool					inInverse,			
		avl::Point2D&			outAlignedPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distance of a point to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distance will be changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePoint
	(
		const avl::Point2D&	inPoint,
		const avl::Point2D&	inReferencePoint,	
		float			inScale,			
		bool				inInverse,			
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an array of points by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePointArray
	(
		const atl::Array<avl::Point2D>&	inPoints,
		const avl::Vector2D&			inDelta,	
		bool							inInverse,	
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an array of points clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePointArray
	(
		const atl::Array<avl::Point2D>&	inPoints, 
		atl::Optional<const avl::Point2D&>	inCenter,	
		float						inAngle,	
		bool							inInverse,	
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves an array of points from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignPointArray
	(
		const atl::Array<avl::Point2D>&	inPoints,
		const avl::CoordinateSystem2D&	inAlignment,		
		bool							inInverse,			
		atl::Array<avl::Point2D>&		outAlignedPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distances of points from an array to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distances will be changed (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePointArray
	(
		const atl::Array<avl::Point2D>&	inPoints,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float						inScale,			
		bool							inInverse,			
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes points not contained in a box from an array.</summary>
	AVL_FUNCTION void CropPointArray
	(
		const atl::Array<avl::Point2D>&	inPoints,
		const avl::Box&					inBox,
		atl::Array<avl::Point2D>&		outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a segment by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateSegment
	(
		const avl::Segment2D&	inSegment,
		const avl::Vector2D&	inDelta,	
		bool					inInverse,	
		avl::Segment2D&			outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a segment clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation (by default the mass center). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateSegment
	(
		const avl::Segment2D&				inSegment,
		atl::Optional<const avl::Point2D&>	inCenter,	
		float							inAngle,	
		bool								inInverse,			
		avl::Segment2D&						outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment contained in a box from another segment.</summary>
	AVL_FUNCTION void CropSegment
	(
		const avl::Segment2D&				inSegment,
		const avl::Box&						inBox,
		atl::Conditional<avl::Segment2D>&	outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a segment from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignSegment
	(
		const avl::Segment2D&			inSegment,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool							inInverse,		
		avl::Segment2D&					outAlignedSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a segment to a new length preserving its orientation and center point.</summary>
	/// <param name="inNewLength">Default value: 1.0f.</param>
	/// <param name="inAnchor">Default value: 0.5f.</param>
	AVL_FUNCTION void ResizeSegment
	(
		const avl::Segment2D&		inSegment,
		float					inNewLength,
		float					inAnchor,
		avl::Segment2D&				outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes length of a segment by adding a value preserving its orientation and center point.</summary>
	/// <param name="inDelta">Value added to segment length. Default value: 0.0f.</param>
	/// <param name="inAnchor">Default value: 0.5f.</param>
	AVL_FUNCTION void ResizeSegment_Delta
	(
		const avl::Segment2D&		inSegment,
		float					inDelta,	
		float					inAnchor,
		avl::Segment2D&				outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a segment relatively.</summary>
	/// <param name="inReferencePoint">The point to which all distances change linearly (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor (negative values invert the segment). Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleSegment
	(
		const avl::Segment2D&				inSegment,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float							inScale,			
		bool								inInverse,			
		avl::Segment2D&						outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Swaps the two endpoints of a segment.</summary>
	AVL_FUNCTION void ReverseSegment
	(
		const avl::Segment2D&	inSegment,
		avl::Segment2D&			outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a line by a vector.</summary>
	/// <param name="inDelta">Vector of translation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateLine
	(
		const avl::Line2D&		inLine, 
		const avl::Vector2D&	inDelta,	
		bool					inInverse,	
		avl::Line2D&			outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a line clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateLine
	(
		const avl::Line2D&	inLine, 
		const avl::Point2D&	inCenter,	
		float			inAngle,	
		bool				inInverse,	
		avl::Line2D&		outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment contained in a box from a line.</summary>
	/// <param name="inBox">Box defining a region the input line will be cropped to.</param>
	AVL_FUNCTION void CropLine
	(
		const avl::Line2D&					inLine,
		const avl::Box&						inBox,		
		atl::Conditional<avl::Segment2D>&	outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment contained in a rectangle from a line.</summary>
	/// <param name="inRectangle">Rectangle defining a region the input line will be cropped to.</param>
	AVL_FUNCTION void CropLineToRectangle
	(
		const avl::Line2D&					inLine,
		const avl::Rectangle2D&				inRectangle,	
		atl::Conditional<avl::Segment2D>&	outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a line from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignLine
	(
		const avl::Line2D&		inLine,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool					inInverse,		
		avl::Line2D&			outAlignedLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distance of a line to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which all distances change linearly.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleLine
	(
		const avl::Line2D&	inLine,
		const avl::Point2D&	inReferencePoint,	
		float			inScale,			
		bool				inInverse,			
		avl::Line2D&		outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a circle by a vector.</summary>
	/// <param name="inDelta">Vector of translation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateCircle
	(
		const avl::Circle2D&	inCircle, 
		const avl::Vector2D&	inDelta,	
		bool					inInverse,	
		avl::Circle2D&			outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a circle clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateCircle
	(
		const avl::Circle2D&	inCircle, 
		const avl::Point2D&		inCenter,	
		float				inAngle,	
		bool					inInverse,	
		avl::Circle2D&			outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a circle from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignCircle
	(
		const avl::Circle2D&		inCircle,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool						inInverse,		
		avl::Circle2D&				outAlignedCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle and translates its center in relation to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which the distance of the circle center is changed (no change by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleCircle
	(
		const avl::Circle2D&				inCircle,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float							inScale,			
		bool								inInverse,			
		avl::Circle2D&						outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle.</summary>
	/// <param name="inNewSize">New value for radius. Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeCircle
	(
		const avl::Circle2D&		inCircle,
		float					inNewSize,	
		avl::Circle2D&				outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle by adding a value.</summary>
	/// <param name="inDelta">Value added to circle radius. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeCircle_Delta
	(
		const avl::Circle2D&		inCircle,
		float					inDelta,	
		avl::Circle2D&				outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a vector preserving its direction.</summary>
	/// <param name="inNewLength">Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeVector
	( 
		const avl::Vector2D&	inVector, 
		float				inNewLength,
		avl::Vector2D&			outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Extends length of a vector by adding a value preserving its direction.</summary>
	/// <param name="inDelta">Value added to vector length. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeVector_Delta
	( 
		const avl::Vector2D&	inVector, 
		float				inDelta,	
		avl::Vector2D&			outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a vector relatively preserving its direction.</summary>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleVector
	( 
		const avl::Vector2D&	inVector, 
		float				inScale,	
		bool					inInverse,	
		avl::Vector2D&				outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a vector clockwise.</summary>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateVector
	( 
		const avl::Vector2D&	inVector,
		float				inAngle,		
		bool					inInverse,		
		avl::Vector2D&			outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds two angles.</summary>
	AVL_FUNCTION void RotateAngle
	(
		float				inAngle,
		float				inRotationAngle,
		avl::AngleRange::Type	inAngleRange,
		bool					inInverse,
		float&				outAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the input direction in the direction of minimum rotation toward the target direction.</summary>
	AVL_FUNCTION void RotateAngle_Toward
	(
		float				inAngle,			
		float				inTargetAngle,	
		avl::AngleRange::Type	inAngleRange,
		float				inRotationAngle,
		bool					inInverse,
		float&				outAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a rectangle by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateRectangle
	(
		const avl::Rectangle2D&	inRectangle, 
		const avl::Vector2D&	inDelta,		
		bool					inInverse,		
		avl::Rectangle2D&		outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a rectangle clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation (the rectangle's point by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateRectangle
	(
		const avl::Rectangle2D&				inRectangle, 
		atl::Optional<const avl::Point2D&>	inCenter,	
		float								inAngle,	
		bool								inInverse,			
		avl::Rectangle2D&					outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a rectangle from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignRectangle
	(
		const avl::Rectangle2D&	inRectangle,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool					inInverse,		
		avl::Rectangle2D&		outAlignedRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the corners and the dimensions of a rectangle.</summary>
	/// <param name="inReferencePoint">The point, to which all distance will be changed proportionally. Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleRectangle
	(
		const avl::Rectangle2D&				inRectangle,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float								inScale,			
		bool								inInverse,			
		avl::Rectangle2D&					outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes dimensions of a rectangle.</summary>
	/// <param name="inAnchor">Default value: TopLeft.</param>
	AVL_FUNCTION void ResizeRectangle
	(
		const avl::Rectangle2D&	inRectangle,
		avl::Anchor2D::Type		inAnchor,
		atl::Optional<float>	inNewWidth,
		atl::Optional<float>	inNewHeight,
		avl::Rectangle2D&		outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes dimensions of a rectangle relatively.</summary>
	/// <param name="inAnchor">Default value: TopLeft.</param>
	/// <param name="inWidthScale">Default value: 1.0f.</param>
	/// <param name="inHeightScale">Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeRectangle_Relative
	(
		const avl::Rectangle2D&	inRectangle,
		avl::Anchor2D::Type		inAnchor,
		float				inWidthScale,
		float				inHeightScale,
		avl::Rectangle2D&		outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes dimensions of a rectangle by adding some values.</summary>
	/// <param name="inAnchor">Default value: TopLeft.</param>
	/// <param name="inWidthDelta">Value added to width of the rectangle. Default value: 0.0f.</param>
	/// <param name="inHeightDelta">Value added to height of the rectangle. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeRectangle_Delta
	(
		const avl::Rectangle2D&		inRectangle,
		avl::Anchor2D::Type			inAnchor,
		float					inWidthDelta,	
		float					inHeightDelta,	
		avl::Rectangle2D&			outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Inverts the direction of the arc.</summary>
	AVL_FUNCTION void ReverseArc
	(
		const avl::Arc2D&	inArc,
		avl::Arc2D&			outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of an arc.</summary>
	/// <param name="inNewSize">Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeArc
	(
		const avl::Arc2D&	inArc,
		const float		inNewSize,
		avl::Arc2D&			outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of an arc by adding a value.</summary>
	/// <param name="inDelta">Value added to arc radius. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeArc_Delta
	(
		const avl::Arc2D&	inArc,
		const float		inDelta,	
		avl::Arc2D&			outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an arc by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateArc
	(
		const avl::Arc2D&		inArc,
		const avl::Vector2D&	inDelta,		
		bool					inInverse,			
		avl::Arc2D&				outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an arc clockwise around center point.</summary>
	/// <param name="inCenter">Center of rotation (the arc's center by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateArc
	(
		const avl::Arc2D&					inArc,
		atl::Optional<const avl::Point2D&>	inCenter,	
		float							inAngle,	
		bool								inInverse,	
		avl::Arc2D&							outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves an arc from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignArc
	(
		const avl::Arc2D&		inArc,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool					inInverse,		
		avl::Arc2D&				outAlignedArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of an arc and translates its center in relation to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which the distance of the arc center is changed (no change by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleArc
	(
		const avl::Arc2D&					inArc,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float							inScale,			
		bool								inInverse,			
		avl::Arc2D&							outArc
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a coordinate system by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslateCoordinateSystem
	(
		const avl::CoordinateSystem2D&	inCoordinateSystem, 
		const avl::Vector2D&		inDelta,		
		bool						inInverse,		
		avl::CoordinateSystem2D&	outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a coordinate system around a center point.</summary>
	/// <param name="inCenter">Center of rotation (the coordinate system's center by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateCoordinateSystem
	(
		const avl::CoordinateSystem2D&		inCoordinateSystem, 
		atl::Optional<const avl::Point2D&>	inCenter,	
		float							inAngle,	
		bool								inInverse,	
		avl::CoordinateSystem2D&			outCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a nested coordinate system from its local coordinate system to the absolute one.</summary>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void AlignCoordinateSystem
	(
		const avl::CoordinateSystem2D&	inCoordinateSystem,
		const avl::CoordinateSystem2D&	inAlignment,
		bool							inInverse,	
		avl::CoordinateSystem2D&		outAlignedCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Inverts a coordinate system.</summary>
	AVL_FUNCTION void InvertCoordinateSystem
	(
		const avl::CoordinateSystem2D&	inCoordinateSystem,
		avl::CoordinateSystem2D&		outInvertedCoordinateSystem
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms a point to a coordinate system in which the 'axis' path is vertical or horizontal.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="inAxis">Input axis path.</param>
	/// <param name="inAxisType">Type of axis the input axis path is parallel to. Default value: Y.</param>
	/// <param name="inAxisCoordinate">Coordinate of the axis path. Default value: 0.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation. Default value: True.</param>
	/// <param name="outPoint">Transformed point.</param>
	AVL_FUNCTION void PointAlongPath
	(
		const avl::Point2D&	inPoint,			
		const avl::Path&	inAxis,				
		avl::Axis::Type		inAxisType,			
		float				inAxisCoordinate,	
		bool				inInverse,			
		avl::Point2D&		outPoint			
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms a point to a coordinate system in which the 'axis' arc is vertical or horizontal.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="inAxis">Input axis arc.</param>
	/// <param name="inAxisType">Type of axis the input axis arc is parallel to. Default value: Y.</param>
	/// <param name="inAxisCoordinate">Coordinate of the axis arc. Default value: 0.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation. Default value: True.</param>
	/// <param name="outPoint">Transformed point.</param>
	AVL_FUNCTION void PointAlongArc
	(
		const avl::Point2D&	inPoint,			
		const avl::Arc2D&	inAxis,				
		avl::Axis::Type		inAxisType,			
		float				inAxisCoordinate,	
		bool				inInverse,			
		avl::Point2D&		outPoint			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYSPATIALTRANSFORMS_H

