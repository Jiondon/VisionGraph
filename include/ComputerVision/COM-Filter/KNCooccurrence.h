//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_KNCOOCCURRENCE_H
#define AVL_KNCOOCCURRENCE_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "Image/Image.h"
#include "NDCooccurrenceParams.h"

namespace avl
{


	/// <summary>Test</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void KNCooccurrenceTest
	(
		const avl::Image& inImage,
		const avl::NDCooccurrenceParams& inModel,
		avl::Image& outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Train</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void KNCooccurrenceTrain
	(
		const atl::Array<avl::Image>& inImage,
		int inStep,
		int inQuant,
		int inPyramidHeight,
		int inMatrixLevels,
		int inMeanBox,
		int inProcessingType,
		avl::NDCooccurrenceParams& outModel
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_KNCOOCCURRENCE_H

