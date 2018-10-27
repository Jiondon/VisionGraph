//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_KNTEXEM_H
#define AVL_KNTEXEM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "NDTexem.h"

namespace avl
{


	/// <summary>Test</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void KNTexemModelTest
	(
		const avl::Image& inImage,
		const avl::TexemModel& inModel,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Train</summary>
	/// <param name="inGMMIterations">Default value: 10.</param>
	/// <param name="inGMMDimensions">Default value: 5.</param>
	/// <param name="inTileSize">Default value: 1.</param>
	/// <param name="inStep">Default value: 1.</param>
	/// <param name="inPyramidHeight">Default value: 1.</param>
	/// <param name="inGaussKernel">Default value: 0.</param>
	/// <param name="inLambda">Default value: 2.0f.</param>
	AVL_FUNCTION void KNTexemModelTrain
	(
		atl::Optional<int> inSeed,
		const atl::Array<avl::Image>& inImages,
		int inGMMIterations,
		int inGMMDimensions,
		int inTileSize,
		int inStep,
		int inPyramidHeight,
		int inGaussKernel,
		float inLambda,
		int inModelType,
		avl::TexemModel& outModel
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_KNTEXEM_H

