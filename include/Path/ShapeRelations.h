//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SHAPERELATIONS_H
#define AVL_SHAPERELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Tests whether a point lies inside a shape.</summary>
	/// <param name="inPoint">Point the position of which will be tested.</param>
	/// <param name="inShape">Shape against which the position will be tested.</param>
	/// <param name="outIsContained">True if point lies inside the shape, false otherwise.</param>
	AVL_FUNCTION void TestPointInShape
	(
		const avl::Point2D& inPoint, 
		const avl::Path& inShape, 
		bool& outIsContained 
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a shape lies inside another one.</summary>
	/// <param name="inSubShape">Shape the position of which will be tested.</param>
	/// <param name="inShape">Shape against which the position will be tested.</param>
	/// <param name="outIsContained">True if whole shape lies inside the other one, false otherwise.</param>
	AVL_FUNCTION void TestShapeInShape
	(
		const avl::Path& inSubShape,	
		const avl::Path& inShape,		
		bool& outIsContained			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SHAPERELATIONS_H

