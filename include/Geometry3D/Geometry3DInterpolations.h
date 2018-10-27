//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DINTERPOLATIONS_H
#define AVL_GEOMETRY3DINTERPOLATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Linearly interpolates between two points in 3D.</summary>
	/// <param name="inLambda">Interpolation between the input points where 0.0 value is equal to inPoint0 and 1.0 to inPoint1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpPoints3D
	(
		const avl::Point3D&	inPoint0,
		const avl::Point3D&	inPoint1,
		const float			inLambda,	
		avl::Point3D&		outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two segments in 3D.</summary>
	/// <param name="inLambda">Interpolation between the input segments where 0.0 value is equal to inSegment0 and 1.0 to inSegment. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpSegments3D
	(
		const avl::Segment3D&	inSegment0,
		const avl::Segment3D&	inSegment1,
		float					inLambda,				
		avl::Segment3D&			outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two 3D vectors.</summary>
	/// <param name="inLambda">Interpolation between the input 3D vectors where 0.0 value is equal to inVector0 and 1.0 to inVector1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpVectors3D
	(
		const avl::Vector3D&	inVector0,
		const avl::Vector3D&	inVector1,
		const float				inLambda,	
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DINTERPOLATIONS_H

