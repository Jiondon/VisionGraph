//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGERELATIONS_H
#define AVL_IMAGERELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Tests whether a location is contained in the dimensions of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestLocationInImage
	(
		const avl::Image& inImage,
		const avl::Location& inLocation,
		bool& outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a box is contained in the dimensions of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestBoxInImage
	(
		const avl::Image& inImage,
		const avl::Box& inBox,
		bool& outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a point is contained in the dimensions of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestPointInImage
	(
		const avl::Image& inImage,
		const avl::Point2D& inPoint,
		bool& outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a rectangle is contained in the dimensions of an image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestRectangleInImage
	(
		const avl::Image& inImage,
		const avl::Rectangle2D& inRectangle,
		bool& outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a location is contained in the dimensions of a box.</summary>
	AVL_FUNCTION void TestLocationInBox
	(
		const avl::Location& inLocation,
		const avl::Box& inBox,
		bool& outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether two images equal.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestImageEqualTo
	(
		const avl::Image&	inImage,
		const avl::Image&	inReferenceImage,
		bool&				outIsEqual
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGERELATIONS_H

