//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYANGLEMETRICS_H
#define AVL_GEOMETRYANGLEMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Enums/AngleRange.h"
#include "Enums/RotationDirection.h"

namespace avl
{


	/// <summary>Normalizes an angle to the range <x, x+180) or <x, x+360).</summary>
	/// <param name="inAngleRange">Length of the normalization range - 180 or 360.</param>
	/// <param name="inBaseAngle">The beginning of the normalization range. Default value: 0.0f.</param>
	AVL_FUNCTION void NormalizeAngle
	(
		float				inAngle,
		avl::AngleRange::Type	inAngleRange,		
		float				inBaseAngle,		
		float&				outNormalizedAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the rotation angle from first to second direction.</summary>
	/// <param name="inDirection1">Start direction.</param>
	/// <param name="inDirection2">Target direction.</param>
	/// <param name="inRotationDirection">Clockwise, counter-clockwise or automatic (by smaller angle). Default value: atl::NIL.</param>
	/// <param name="inAngleRange">Switches between ranges <0; 180) and <0; 360).</param>
	/// <param name="outAbsoluteAngle">Angle value used for measurements <0; 360>.</param>
	/// <param name="outDirectedAngle">Angle value used for clockwise transformations <-360; 360>.</param>
	AVL_FUNCTION void AngleBetweenDirections
	(
		float									inDirection1,			
		float									inDirection2,			
		atl::Optional<avl::RotationDirection::Type>	inRotationDirection,	
		avl::AngleRange::Type						inAngleRange,			
		atl::Optional<float&>					outAbsoluteAngle = atl::NIL,		
		atl::Optional<float&>					outDirectedAngle = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the angle between two vectors.</summary>
	/// <param name="inVector1">Start vector.</param>
	/// <param name="inVector2">Target vector.</param>
	/// <param name="inRotationDirection">Clockwise, counter-clockwise or automatic (by smaller angle). Default value: atl::NIL.</param>
	/// <param name="outAbsoluteAngle">Angle value used for measurements <0; 360>.</param>
	/// <param name="outDirectedAngle">Angle value used for clockwise transformations <-360; 360>.</param>
	AVL_FUNCTION void AngleBetweenVectors
	(
		const avl::Vector2D&						inVector1,				
		const avl::Vector2D&						inVector2,				
		atl::Optional<avl::RotationDirection::Type>	inRotationDirection,	
		atl::Optional<float&>						outAbsoluteAngle = atl::NIL,		
		atl::Optional<float&>						outDirectedAngle = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the smaller and the larger angle between two lines.</summary>
	AVL_FUNCTION void AngleBetweenLines
	(
		const avl::Line2D&			inLine1,
		const avl::Line2D&			inLine2,
		atl::Optional<float&>		outSmallerAngle = atl::NIL,
		atl::Optional<float&>		outLargerAngle = atl::NIL
	)
	THROW_AVL_ERRORS;

	namespace AngleMetric
	{
		enum Type
		{
			VectorClockwise,
			VectorCounterClockwise,
			PolygonClockwise,
			PolygonCounterClockwise
		};
	}


	/// <summary>Measures the angle defined by three consecutive points.</summary>
	/// <param name="inPoint1">A point on one arm of an angle.</param>
	/// <param name="inPoint2">The middle point.</param>
	/// <param name="inPoint3">A point on another arm of the angle.</param>
	/// <param name="inRotationDirection">Chooses one of two ways of measuring the angle.</param>
	/// <param name="outAbsoluteAngle">Angle value used for measurements <0; 360>.</param>
	/// <param name="outDirectedAngle">Angle value used for clockwise transformations <-360; 360>.</param>
	/// <param name="outArc">Angle visualization object.</param>
	AVL_FUNCTION void AngleBetweenThreePoints
	(
		const avl::Point2D&				inPoint1,			
		const avl::Point2D&				inPoint2,			
		const avl::Point2D&				inPoint3,			
		avl::RotationDirection::Type	inRotationDirection,	
		atl::Optional<float&>			outAbsoluteAngle = atl::NIL,	
		atl::Optional<float&>			outDirectedAngle = atl::NIL,	
		atl::Optional<avl::Arc2D&>		outArc = atl::NIL				
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the angle between two segments with one of four possible metrics.</summary>
	/// <param name="inSegment1">First segment.</param>
	/// <param name="inSegment2">Second segment.</param>
	/// <param name="inAngleMetric">Chooses one of four possible ways of measuring the angle.</param>
	/// <param name="inAutodetectOrientation">Autodetects orientation of the segments assuming that these are two consecutive sides of a polygon. Default value: True.</param>
	/// <param name="outAbsoluteAngle">Angle value used for measurements <0; 360>.</param>
	/// <param name="outDirectedAngle">Angle value used for clockwise transformations <-360; 360>.</param>
	/// <param name="outArc">Angle visualization object.</param>
	AVL_FUNCTION void AngleBetweenSegments
	(
		const avl::Segment2D&			inSegment1,					
		const avl::Segment2D&			inSegment2,					
		avl::AngleMetric::Type			inAngleMetric,				
		bool							inAutodetectOrientation,	
		atl::Optional<float&>			outAbsoluteAngle = atl::NIL,			
		atl::Optional<float&>			outDirectedAngle = atl::NIL,			
		atl::Optional<avl::Arc2D&>		outArc = atl::NIL						
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the angle between two lines containing the input segments.</summary>
	/// <param name="inSegment1">Segment defining the first line.</param>
	/// <param name="inSegment2">Segment defining the second line.</param>
	/// <param name="outSmallerAngle">The smaller angle <0, 90>.</param>
	/// <param name="outLargerAngle">The larger angle <90, 180>.</param>
	AVL_FUNCTION void AngleBetweenSegmentLines_Deprecated
	(
		const avl::Segment2D&		inSegment1,			
		const avl::Segment2D&		inSegment2,			
		atl::Optional<float&>	outSmallerAngle,	
		atl::Optional<float&>	outLargerAngle		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYANGLEMETRICS_H

