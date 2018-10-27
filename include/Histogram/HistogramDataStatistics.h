//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMDATASTATISTICS_H
#define AVL_HISTOGRAMDATASTATISTICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/Enums/SortingOrder.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Computes the average of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outAverage">Average of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataAverage
	(
		const avl::Histogram&	inHistogram,
		float&				outAverage 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the variance of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outVariance">Variance of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataVariance
	(
		const avl::Histogram&	inHistogram,
		float&				outVariance 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the standard deviation of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outStandardDeviation">Standard deviation of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataStandardDeviation
	(
		const avl::Histogram&	inHistogram,	
		float&				outStandardDeviation	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the approximation of the smallest value of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMinimum">Minimum of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataMinimum
	(
		const avl::Histogram&	inHistogram,
		float&				outMinimum	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the approximation of the largest value of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMaximum">Maximum of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataMaximum
	(
		const avl::Histogram&	inHistogram,
		float&				outMaximum	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the number of elements of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outSize">Number of elements of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataSize
	(
		const avl::Histogram& inHistogram,
		int&			 outSize	 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes nth smallest (or largest) value of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outNthValue">Nth smallest (or largest) value of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataNthValue
	(
		const avl::Histogram&			inHistogram,	
		const int						inN,
		const avl::SortingOrder::Type	inSortingOrder,
		float&						outNthValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the median of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMedian">Median of the histogrammed data.</param>
	AVL_FUNCTION void HistogramDataMedian
	(
		const avl::Histogram&	inHistogram,
		float&				outMedian	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the specified quantile of the histogrammed numeric data.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inQuantilePoint">Default value: 0.5f.</param>
	AVL_FUNCTION void HistogramDataQuantile
	(
		const avl::Histogram& inHistogram,
		const float inQuantilePoint,
		float& outQuantileValue
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMDATASTATISTICS_H

