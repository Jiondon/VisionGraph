//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMFEATURES_H
#define AVL_HISTOGRAMFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Computes the average of histogram bin values.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outAverage">Output average.</param>
	AVL_FUNCTION void HistogramAverage
	(
		const avl::Histogram&	inHistogram,	
		float&				outAverage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes histogram bar values maximum - its location and value.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMaximumLocation">Output maximum location.</param>
	/// <param name="outMaximumValue">Output maximum value.</param>
	AVL_FUNCTION void HistogramMaximum
	(
		const avl::Histogram&	inHistogram,		
		int&					outMaximumLocation,	
		int&					outMaximumValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes histogram bar values minimum - its location and value.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMinimumLocation">Output minimum location.</param>
	/// <param name="outMinimumValue">Output minimum value.</param>
	AVL_FUNCTION void HistogramMinimum
	(
		const avl::Histogram&	inHistogram,		
		int&					outMinimumLocation,	
		int&					outMinimumValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of histogram bin values.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outSum">Output sum.</param>
	AVL_FUNCTION void HistogramSum
	(
		const avl::Histogram&	inHistogram,	
		int&					outSum			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the number of histogram bins.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outSize">Output size.</param>
	AVL_FUNCTION void HistogramSize
	(
		const avl::Histogram&	inHistogram,	
		int&					outSize			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the histogram local maxima.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMaximaLocations">Output maxima locations.</param>
	/// <param name="outMaximaValues">Output maxima values.</param>
	AVL_FUNCTION void HistogramLocalMaxima
	(
		const avl::Histogram&	inHistogram,			
		atl::Optional<int>		inMinValue,			
		atl::Array<int>&		outMaximaLocations,	
		atl::Array<int>&		outMaximaValues		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the histogram local minima.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outMinimaLocations">Output minima locations.</param>
	/// <param name="outMinimaValues">Output minima values.</param>
	AVL_FUNCTION void HistogramLocalMinima
	(
		const avl::Histogram&	inHistogram,			
		atl::Optional<int>		inMaxValue,			
		atl::Array<int>&		outMinimaLocations,	
		atl::Array<int>&		outMinimaValues		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMFEATURES_H

