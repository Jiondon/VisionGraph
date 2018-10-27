//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MATHBASICS_H
#define AVL_MATHBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"

namespace avl
{


	/// <summary>Computes the sine of an angle.</summary>
	AVL_FUNCTION void Sine
	(
		const float&	inAngle,
		float&		outSine
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the cosine of an angle.</summary>
	AVL_FUNCTION void Cosine
	(
		const float&	inAngle,
		float&		outCosine
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the tangent of an angle.</summary>
	AVL_FUNCTION void Tangent
	(
		const float&	inAngle,
		float&		outTangent
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the cotangent of an angle.</summary>
	AVL_FUNCTION void Cotangent
	(
		const float&	inAngle,
		float&		outCotangent
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the power of a number.</summary>
	/// <param name="inBase">Default value: 1.0f.</param>
	/// <param name="inExponent">Default value: 1.0f.</param>
	AVL_FUNCTION void Power
	(
		const float	inBase,
		const float	inExponent,
		float&		outPower
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the square root of a number.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	AVL_FUNCTION void SquareRoot
	(
		const float	inA,
		float&		outRoot
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the logarithm of a number in a given base.</summary>
	/// <param name="inBase">Default value: 2.0f.</param>
	/// <param name="inValue">Default value: 1.0f.</param>
	AVL_FUNCTION void Logarithm
	(
		const float	inBase,
		const float inValue,
		float&		outLogarithm
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the floor of a number.</summary>
	AVL_FUNCTION void Floor
	(
		const float	inValue,
		int&		outFloor
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the ceil of a number.</summary>
	AVL_FUNCTION void Ceil
	(
		const float	inValue,
		int&		outCeil
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes rounded value of a number.</summary>
	AVL_FUNCTION void Round
	(
		const float	inValue,
		int&		outRound
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sign of a number.</summary>
	AVL_FUNCTION void Signum
	(
		const float	inValue,
		int&		outSign
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MATHBASICS_H

