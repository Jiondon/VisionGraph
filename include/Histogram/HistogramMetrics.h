//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMMETRICS_H
#define AVL_HISTOGRAMMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/DistanceMeasure.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Computes the numeric distance between two histograms.</summary>
	/// <param name="inHistogram1">First input histogram.</param>
	/// <param name="inHistogram2">Second input histogram.</param>
	/// <param name="inDistanceMeasure">Measure of distance.</param>
	/// <param name="outDistance">Output distance value.</param>
	AVL_FUNCTION void HistogramDistance
	(
		const avl::Histogram&		inHistogram1,			
		const avl::Histogram&		inHistogram2,			
		avl::DistanceMeasure::Type	inDistanceMeasure,		
		float&					outDistance				
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates normalized histogram intersection norm.</summary>
	/// <param name="inHistogram1">First input histogram.</param>
	/// <param name="inHistogram2">Second input histogram.</param>
	AVL_FUNCTION void HistogramIntersection
	(
		const avl::Histogram&	inHistogram1,			
		const avl::Histogram&	inHistogram2,			
		float&					outHistIntersection
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMMETRICS_H

