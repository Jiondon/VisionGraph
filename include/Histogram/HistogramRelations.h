//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMRELATIONS_H
#define AVL_HISTOGRAMRELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Checks whether values in the first histogram are greater or equal than corresponding values in the second histogram</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	AVL_FUNCTION void TestHistogramDominatesHistogram
	(
		const avl::Histogram&	inHistogram1,
		const avl::Histogram&	inHistogram2,
		bool&				outDominates
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMRELATIONS_H

