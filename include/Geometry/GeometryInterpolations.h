//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRYINTERPOLATIONS_H
#define AVL_GEOMETRYINTERPOLATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Enums/RotationDirection.h"
#include "Enums/AngleRange.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Linearly interpolates between two points.</summary>
	/// <param name="inLambda">Interpolation between the input points where 0.0 value is equal to inPoint0 and 1.0 to inPoint1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpPoints
	(
		const avl::Point2D&	inPoint0,
		const avl::Point2D&	inPoint1,
		const float			inLambda,	
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two segments.</summary>
	/// <param name="inLambda">Interpolation between the input segments where 0.0 value is equal to inSegment0 and 1.0 to inSegment1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpSegments
	(
		const avl::Segment2D&	inSegment0,
		const avl::Segment2D&	inSegment1,
		float					inLambda,				
		bool					inIgnoreOrientation,	
		avl::Segment2D&			outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two vectors.</summary>
	/// <param name="inLambda">Interpolation between the input vectors where 0.0 value is equal to inVector0 and 1.0 to inVector1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpVectors
	(
		const avl::Vector2D&	inVector0,
		const avl::Vector2D&	inVector1,
		const float				inLambda,	
		avl::Vector2D&			outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two radial vectors.</summary>
	/// <param name="inRotationDirection">Clockwise, counter-clockwise or auto. Default value: atl::NIL.</param>
	/// <param name="inLambda">Interpolation between the input vectors where 0.0 value is equal to inVector0 and 1.0 to inVector1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpVectors_Radial
	(
		const avl::Vector2D&						inVector0,
		const avl::Vector2D&						inVector1,
		atl::Optional<avl::RotationDirection::Type>	inRotationDirection,	
		const float									inLambda,				
		avl::Vector2D&								outVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two angles in the direction of minimum turn.</summary>
	/// <param name="inRotationDirection">Clockwise, counter-clockwise or auto. Default value: atl::NIL.</param>
	/// <param name="inLambda">Interpolation between the input angles where 0.0 value is equal to inAngle0 and 1.0 to inAngle1.</param>
	AVL_FUNCTION void LerpAngles
	(
		float										inAngle0,
		float										inAngle1,
		atl::Optional<avl::RotationDirection::Type>	inRotationDirection,	
		avl::AngleRange::Type						inAngleRange,
		float										inLambda,				
		bool										inInverse,
		float&									outAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two paths.</summary>
	/// <param name="inPath1">First input path.</param>
	/// <param name="inLambda">Interpolation between the input paths where 0.0 value is equal to inPath0 and 1.0 to inPath1. Default value: 0.5f.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void LerpPaths
	(
		const avl::Path&	inPath0,
		const avl::Path&	inPath1,
		const float			inLambda,	
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the middle point of two input points.</summary>
	AVL_FUNCTION void AveragePoint
	(
		const avl::Point2D&	inPoint1,
		const avl::Point2D&	inPoint2,
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the median angle of the input angles.</summary>
	AVL_FUNCTION void MedianAngle
	(
		const atl::Array<float>&	inAngles,
		avl::AngleRange::Type			inAngleRange,
		float&						outMedianAngle
	)
	THROW_AVL_ERRORS;

	struct AveragePoint_OfLoopState : public BaseState
	{
		float sumX;
		float sumY;
		int count;

		AveragePoint_OfLoopState()
			: sumX(0.0f), sumY(0.0f), count(0)
		{}

		AveragePoint_OfLoopState( float sumX_, float sumY_, int count_)
			: sumX(sumX_), sumY(sumY_), count(count_)
		{ }
	};


	/// <summary>Computes the central point of the points appearing in consecutive iterations</summary>
	AVL_FUNCTION void AveragePoint_OfLoop_Deprecated
	(
		AveragePoint_OfLoopState& ioState,
		const avl::Point2D&	inPoint,
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRYINTERPOLATIONS_H

