//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMPOINTTRANSFORMS_H
#define AVL_HISTOGRAMPOINTTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Multiplies each bin value by a number.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inValue">Input value. Default value: 2.0f.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MultiplyHistogram
	(
		const avl::Histogram&	inHistogram,	
		const float&			inValue,		
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides each bin value by a number.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inValue">Input value. Default value: 2.0f.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void DivideHistogram
	(
		const avl::Histogram&	inHistogram,	
		const float&			inValue,		
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Increases each bin value by a number.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inValue">Input value. Default value: 0.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void AddToHistogram
	(
		const avl::Histogram&	inHistogram,	
		const int&			inValue,		
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Decreases each bin value by a number.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inValue">Input value. Default value: 2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void SubtractFromHistogram
	(
		const avl::Histogram&	inHistogram,	
		const int&			inValue,		
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Negates each bin value.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void NegateHistogram
	(
		const avl::Histogram&	inHistogram,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms each bin value to its absolute value.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void AbsoluteHistogram
	(
		const avl::Histogram&	inHistogram,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMPOINTTRANSFORMS_H

