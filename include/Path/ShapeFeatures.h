//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SHAPEFEATURES_H
#define AVL_SHAPEFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/CircularityMeasure.h"
#include "Path/Path.h"

namespace avl
{


	namespace ShapeMomentType
	{
		enum Type
		{
			_02,
			_11,
			_20
		};
	}


	/// <summary>Computes the selected second-order moment of a shape in regular and normalized ( divided by shape area ) variant.</summary>
	AVL_FUNCTION void ShapeMoment
	(
		const avl::Path& inShape,
		avl::ShapeMomentType::Type inMomentType,
		bool inCentral,
		float& outMoment,
		float& outNormMoment
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a shape.</summary>
	AVL_FUNCTION void ShapeArea
	(
		const avl::Path& inShape,
		float& outArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the mass center of a shape.</summary>
	AVL_FUNCTION void ShapeMassCenter
	(
		const avl::Path& inShape,
		avl::Point2D& outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the shape orientation as angle with value in range 0.0 - 180.0.</summary>
	AVL_FUNCTION void ShapeOrientation
	(
		const avl::Path& inShape,
		float& outOrientationAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the elongation factor of a shape (perfect circle has minimal elongation equal 1.0).</summary>
	AVL_FUNCTION void ShapeElongation
	(
		const avl::Path& inShape,
		float& outElongation
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes axes of an ellipse having the same first and second order moments as the given shape.</summary>
	AVL_FUNCTION void ShapeEllipticAxes
	(
		const avl::Path& inShape,
		avl::Segment2D& outMajorAxis,
		avl::Segment2D& outMinorAxis
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a shape divided by the area of a circle having the same feature.</summary>
	/// <param name="inCircularityMeasure">Default value: RadiusPreserving.</param>
	AVL_FUNCTION void ShapeCircularity
	(
		const avl::Path&						inShape,
		const avl::CircularityMeasure::Type	inCircularityMeasure,
		float&							outCircularity
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a shape divided by the area of its convex hull.</summary>
	AVL_FUNCTION void ShapeConvexity
	(
		const avl::Path& inShape,
		float& outConvexity
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a shape divided by the area of its bounding rectangle.</summary>
	AVL_FUNCTION void ShapeRectangularity
	(
		const avl::Path& inShape,
		float& outRectangularity
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SHAPEFEATURES_H

