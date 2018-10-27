//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_BENCHMARKS_H
#define AVL_BENCHMARKS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/AtlString.h"

namespace avl
{


	/// <summary>Tests CPU performance for simple arithmetic operations</summary>
	/// <param name="inUseMultipleCores">Indicates if all cores of the CPU should be used. Default value: True.</param>
	/// <param name="outScore">Score is the time of filter execution in milliseconds. Smaller value for faster CPUs.</param>
	AVL_FUNCTION void BenchmarkCPU
	(
		bool				inUseMultipleCores,	
		double&		outScore			
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests CPU performance for simple arithmetic operations</summary>
	/// <param name="inUseMultipleCores">Indicates if all cores of the CPU should be used. Default value: True.</param>
	/// <param name="outScore">Score is the time of filter execution in milliseconds. Smaller value for faster CPUs.</param>
	AVL_FUNCTION void BenchmarkCPU_Deprecated
	(
		bool			inUseMultipleCores,	
		float&		outScore			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_BENCHMARKS_H

