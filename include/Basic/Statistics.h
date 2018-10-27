//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_STATISTICS_H
#define AVL_STATISTICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"
#include "Basic/LinearFunction.h"

namespace avl
{


	/// <summary>Creates a linear function with given coefficients.</summary>
	/// <param name="inA">Default value: 1.0f.</param>
	AVL_FUNCTION void MakeLinearFunction
	(
		float				inA,
		float				inB,
		avl::LinearFunction&	outLinearFunction
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns coefficients of a linear function.</summary>
	AVL_FUNCTION void AccessLinearFunction
	(
		const avl::LinearFunction&	inLinearFunction,
		float&					outA,
		float&					outB
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the median of an array of real numbers. The array must be not empty. Optional weights, when supplied, must be positive.</summary>
	AVL_FUNCTION void Median
	(
		const atl::Array<float>&	inValues,
		const atl::Optional<const atl::Array<float>&>&	inWeights,
		float&						outMedian
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average of an array of real numbers. The array must be not empty.</summary>
	AVL_FUNCTION void Average
	(
		const atl::Array<float>&	inValues,
		float&						outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the variance of an array of real numbers. The array must be not empty.</summary>
	AVL_FUNCTION void Variance
	(
		const atl::Array<float>&	inValues,
		const bool						inUseSampleFormula,
		float&						outVariance
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the standard deviation of an array of real numbers. The array must be not empty.</summary>
	AVL_FUNCTION void StandardDeviation
	(
		const atl::Array<float>&	inValues,
		const bool						inUseSampleFormula,
		float&						outStandardDeviation
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the specified quantile of an array of real numbers. The array must be not empty.</summary>
	/// <param name="inQuantilePoint">Default value: 0.5f.</param>
	AVL_FUNCTION void Quantile
	(
		const atl::Array<float>&	inValues, 
		float						inQuantilePoint,
		float&						outQuantileValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes n-th smallest value in an array (0-indexed). The array must be not empty.</summary>
	AVL_FUNCTION void NthValue
	(
		const atl::Array<float>& inValues, 
		int inN,
		float& outNthValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes Pearson product-moment correlation coefficient. The array must be not empty.</summary>
	/// <param name="inValues1">Array of values of the first variable.</param>
	/// <param name="inValues2">Array of values of the second variable.</param>
	/// <param name="outCorrelation">Computed correlation coefficient between two variables.</param>
	AVL_FUNCTION void PearsonCorrelation
	(
		const atl::Array<float>& inValues1,	
		const atl::Array<float>& inValues2,	
		float& outCorrelation				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_STATISTICS_H

