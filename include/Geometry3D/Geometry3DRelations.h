//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DRELATIONS_H
#define AVL_GEOMETRY3DRELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Tests whether a point in 3D lies in a box in 3D.</summary>
	AVL_FUNCTION void TestPoint3DInBox3D
	(
		const avl::Point3D&	inPoint3D,
		const avl::Box3D&	inBox3D,
		bool&				outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a line in 3D goes through a circle in 3D.</summary>
	AVL_FUNCTION void TestLine3DThroughCircle3D
	(
		const avl::Line3D&		inLine3D,
		const avl::Circle3D&	inCircle3D,
		bool&					outGoesThrough
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DRELATIONS_H

