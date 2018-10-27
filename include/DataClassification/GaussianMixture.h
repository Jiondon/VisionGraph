//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GAUSSIANMIXTURE_H
#define AVL_GAUSSIANMIXTURE_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/MatrixTypes.h"
#include "DataClassification/Gaussian.h"

namespace avl
{


	/// <summary>Intializes Gaussian Mixture Model using Expectation-Maximization method</summary>
	/// <param name="inMixtureCount">Default value: 2.</param>
	/// <param name="inMaxIterations">Default value: 200.</param>
	/// <param name="inSeed">Default value: 5489.</param>
	AVL_FUNCTION void GMM_Train
	(
		const avl::Matrix&					inData,
		const int							inMixtureCount,
		const int							inMaxIterations,
		const int							inSeed,
		atl::Array<avl::Gaussian>&			outModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns pseudorandom point drawn from multinomial gaussian distribution.</summary>
	/// <param name="inSeed">Default value: 5489.</param>
	AVL_FUNCTION void SamplePointFromGaussian
	(
		const avl::Gaussian&	inGaussian,
		const int				inSeed,
		atl::Array<double>&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Queries previously trained GMM about log probability of some data being described by that gaussian mixture.</summary>
	AVL_FUNCTION void GMM_LogProb
	(
		const avl::Matrix&					inData,
		const atl::Array<avl::Gaussian>&	inModel,
		float&							outLogProbability
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GAUSSIANMIXTURE_H

