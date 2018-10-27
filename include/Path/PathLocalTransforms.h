//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHLOCALTRANSFORMS_H
#define AVL_PATHLOCALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Smooths a path by averaging its characteristic points within a kernel.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inKernelRadius">Default value: 3.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void SmoothPath_Mean
	(
		const avl::Path& inPath,
		int	inKernelRadius,
		avl::Path& outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths a path by averaging its characteristic points within a kernel using gaussian-weighted average.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inStdDev">Smoothing standard deviation. Default value: 0.6f.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 3.0f.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void SmoothPath_Gauss
	(
		const avl::Path&	inPath,
		const float		inStdDev,				
		const float		inKernelRelativeSize,	
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHLOCALTRANSFORMS_H

