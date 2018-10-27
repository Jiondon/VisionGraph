//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMLOCALTRANSFORMS_H
#define AVL_HISTOGRAMLOCALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Smooths a histogram by averaging points within a kernel using gaussian-weighted average.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inStdDev">Smoothing standard deviation. Default value: 0.6f.</param>
	/// <param name="inKernelRelativeSize">Default value: 3.0f.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void SmoothHistogram_Gauss
	(
		const avl::Histogram&	inHistogram,
		const float			inStdDev,				
		const float			inKernelRelativeSize,
		avl::Histogram&			outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths a histogram by averaging points within a kernel.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inKernelRadius">Defines the width of the kernel as 2*R+1. Default value: 3.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void SmoothHistogram_Mean
	(
		const avl::Histogram&	inHistogram,
		const int				inKernelRadius,	
		avl::Histogram&			outHistogram
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMLOCALTRANSFORMS_H

