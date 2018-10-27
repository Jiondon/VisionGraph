//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DATACLASSIFICATIONCOMMON_H
#define AVL_DATACLASSIFICATIONCOMMON_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/MatrixTypes.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Calculates classification performance metrics for binary problems.</summary>
	AVL_FUNCTION void MeasureClassificationQuality_Binary
	(
		const atl::Array<bool>&		inPredictedClasses,
		const atl::Array<bool>&		inExpectedClasses,
		float&						outAccuracy,
		float&						outPrecision,
		float&						outRecall,
		float&						outF1Score,
		avl::Matrix&				outConfusionMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates classification performance metrics for multiclass problems.</summary>
	AVL_FUNCTION void MeasureClassificationQuality_Multiclass
	(
		const atl::Array<int>&		inPredictedClasses,
		const atl::Array<int>&		inExpectedClasses,
		float&						outAccuracy,
		atl::Array<float>&			outPrecisions,
		atl::Array<float>&			outRecalls,
		atl::Array<float>&			outF1Scores,
		avl::Matrix&				outConfusionMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides input set to test and train set, trying to maintain balance in class distribution in both resulting sets.</summary>
	/// <param name="inTestToTrainingRatio">Default value: 0.75f.</param>
	/// <param name="inRandomSeed">Default value: 0.</param>
	AVL_FUNCTION void CreateDataPartition
	(
		const atl::Array<atl::Array<float>>&		inFeatureSet,
		const atl::Array<int>&						inClassAssignment,
		const float									inTestToTrainingRatio,
		const int									inRandomSeed,
		atl::Array<atl::Array<float>>&				outTrainSet,
		atl::Array<atl::Array<float>>&				outTrainResponse,
		atl::Array<atl::Array<float>>&				outTestSet,
		atl::Array<atl::Array<float>>&				outTestResponse
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_DATACLASSIFICATIONCOMMON_H

