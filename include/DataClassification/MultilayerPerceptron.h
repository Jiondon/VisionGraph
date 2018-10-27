//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MULTILAYERPERCEPTRON_H
#define AVL_MULTILAYERPERCEPTRON_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/MlpPreprocessing.h"
#include "ATL/Array.h"
#include "Profile/Profile.h"

namespace avl
{


	namespace ActivationFunction
	{
		enum Type
		{
			Sigmoidal = 0,
			Linear,
			Tanh,
			Log,
			ArcTan,
			Gauss,
			Elliot,
			Step,
			FastSigmoidal,
			FastTanh,
			GaussSymmetric
		};
	}

	class MlpModel;
	class MlpModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructMlpModel(MlpModel&);
		AVL_FUNCTION void CopyMlpModel(const MlpModel&, MlpModel&);
		AVL_FUNCTION bool TestMlpModelEqual(const MlpModel&, const MlpModel&);
	}

	class MlpModel
	{
	public:
		MlpModel() : pImpl(0) {}

		~MlpModel()
		{
			pImpl_helpers::DestructMlpModel(*this);
		}

		MlpModel(const MlpModel& inMlpModel) : pImpl(0)
		{
			pImpl_helpers::CopyMlpModel(inMlpModel, *this);
		}

		MlpModel& operator=(const MlpModel& inMlpModel)
		{
			pImpl_helpers::CopyMlpModel(inMlpModel, *this);
			return *this;
		}

		bool operator == (const MlpModel& rhs) const
		{
			return pImpl_helpers::TestMlpModelEqual(*this, rhs);
		}
		
		bool operator != (const MlpModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		MlpModelImpl* pImpl;
	};


	/// <summary>Creates multilayer perceptron model.</summary>
	/// <param name="inHiddenLayers">Internal structure of MLP network. Default value: atl::NIL.</param>
	/// <param name="inActivationFunction">Type of activation function used to calculate neural response.</param>
	/// <param name="inPreprocessing">Method of processing input data before learning.</param>
	/// <param name="inRandomSeed">Number used as starting random seed. Default value: atl::NIL.</param>
	/// <param name="inInputCount">MLP network input count. Default value: 1.</param>
	/// <param name="inOutputCount">MLP network output count. Default value: 1.</param>
	/// <param name="outMlpModel">Initialized MlpModel.</param>
	AVL_FUNCTION void MLP_Init
	(
		atl::Optional<const atl::Array<int>&>	inHiddenLayers,			
		avl::ActivationFunction::Type			inActivationFunction,	
		avl::MlpPreprocessing::Type				inPreprocessing,		
		atl::Optional<int>						inRandomSeed,			
		int										inInputCount,			
		int										inOutputCount,			
		avl::MlpModel&							outMlpModel				
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates and trains multilayer perceptron classifier.</summary>
	/// <param name="inMlpModel">Initialized MLP model.</param>
	/// <param name="inInputVectorArray">Array of features used to train model.</param>
	/// <param name="inResponseVectorArray">Array of answers which classifier should get.</param>
	/// <param name="inTestInputVectorArray">Array of features used to test classifier during training process. Default value: atl::NIL.</param>
	/// <param name="inTestResponseVectorArray">Array of answers used to test classifier during training process. Default value: atl::NIL.</param>
	/// <param name="inIterationCount">Learning iteration count. Default value: 100.</param>
	/// <param name="inLearningRate">Learning factor. Default value: 1.0f.</param>
	/// <param name="inMomentum">Learning momentum ratio. Default value: 0.01f.</param>
	/// <param name="inRandomSeed">Number used as starting random seed. Default value: atl::NIL.</param>
	/// <param name="outMlpModel">Trained MlpModel.</param>
	/// <param name="diagErrorChartLearning">Mean error of testing results data during learning process.</param>
	/// <param name="diagErrorChartTesting">Mean error during learning process.</param>
	AVL_FUNCTION void MLP_Train
	(
		const avl::MlpModel&										inMlpModel,					
		const atl::Array<atl::Array<float>>&					inInputVectorArray,			
		const atl::Array<atl::Array<float>>&					inResponseVectorArray,		
		atl::Optional<const atl::Array<atl::Array<float>>&>		inTestInputVectorArray,		
		atl::Optional<const atl::Array<atl::Array<float>>&>		inTestResponseVectorArray,	
		int															inIterationCount,			
		float													inLearningRate,				
		float													inMomentum,					
		atl::Optional<int>											inRandomSeed,				
		avl::MlpModel&												outMlpModel,				
		avl::Profile&												diagErrorChartLearning = atl::Dummy<avl::Profile>(),		
		avl::Profile&												diagErrorChartTesting = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates multilayer perceptron answer.</summary>
	/// <param name="inMlpModel">Trained MlpModel object.</param>
	/// <param name="inInputVector">Input vector of features used to calculate classifier response.</param>
	/// <param name="outResponseVector">Calculated response.</param>
	AVL_FUNCTION void MLP_Respond
	(
		const avl::MlpModel&				inMlpModel,			
		const atl::Array<float>&		inInputVector,		
		atl::Array<float>&				outResponseVector	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MULTILAYERPERCEPTRON_H

