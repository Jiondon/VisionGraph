//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMSPATIALTRANSFORMS_H
#define AVL_HISTOGRAMSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Confines a histogram to its continuous segment.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inStart">Index of the first element of the input histogram that will be included in the output histogram.</param>
	/// <param name="inLength">Number of bins in the output histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void CropHistogram
	(
		const avl::Histogram&	inHistogram,
		const int			inStart,		
		const int			inLength,		
		avl::Histogram&			outHistogram
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMSPATIALTRANSFORMS_H

