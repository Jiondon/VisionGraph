//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SUPPORTVECTORMACHINES_H
#define AVL_SUPPORTVECTORMACHINES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Array.h"

namespace avl
{


	class SvmModel;
	class SvmModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructSvmModel(SvmModel&);
		AVL_FUNCTION void CopySvmModel(const SvmModel&, SvmModel&);
		AVL_FUNCTION bool TestSvmModelEqual(const SvmModel&, const SvmModel&);
	}

	class SvmModel
	{
	public:
		SvmModel() : pImpl(0) {}

		~SvmModel()
		{
			pImpl_helpers::DestructSvmModel(*this);
		}

		SvmModel(const SvmModel& inSvmModel) : pImpl(0)
		{
			pImpl_helpers::CopySvmModel(inSvmModel, *this);
		}

		SvmModel& operator=(const SvmModel& inSvmModel)
		{
			pImpl_helpers::CopySvmModel(inSvmModel, *this);
			return *this;
		}

		bool operator == (const SvmModel& rhs) const
		{
			return pImpl_helpers::TestSvmModelEqual(*this, rhs);
		}
		
		bool operator != (const SvmModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		SvmModelImpl* pImpl;
	};


	/// <summary>Initializes SVM model</summary>
	/// <param name="inKernelGamma">Gamma parameter for Rbf kernel. Default value: 0.0001f.</param>
	/// <param name="inKernelGammaScale">Gamma parameter scale. Default value: 1.0f.</param>
	/// <param name="inRegularizationConstant">Preventing overfitting. Default value: 1.0f.</param>
	/// <param name="inNu">Tradeoff between training accuracy and number of SV. Default value: atl::NIL.</param>
	/// <param name="inStoppingEpsilon">Epsilon for stopping criterium. Default value: 0.001f.</param>
	/// <param name="inUseShrinkingHeuristics">May speed up computations. Default value: True.</param>
	/// <param name="outSvmModel">Output model.</param>
	AVL_FUNCTION void SVM_Init
	(
		atl::Optional<float>	inKernelGamma,				
		float					inKernelGammaScale,			
		float					inRegularizationConstant,	
		atl::Optional<float>	inNu,						
		float					inStoppingEpsilon,			
		bool						inUseShrinkingHeuristics,	
		avl::SvmModel&				outSvmModel					
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains SVM model</summary>
	/// <param name="inSvmModel">Initialized SVM model.</param>
	/// <param name="inVectorArray">Training data vector array.</param>
	/// <param name="inAnswerArray">Correct classes for data vectors.</param>
	/// <param name="outSvmModel">Trained model.</param>
	/// <param name="outTrainingAccuracy">Accuracy of prediction on training set.</param>
	AVL_FUNCTION void SVM_Train
	(
		const avl::SvmModel&						inSvmModel,			
		const atl::Array<atl::Array<float> >&	inVectorArray,		
		const atl::Array< int >&					inAnswerArray,		
		avl::SvmModel&								outSvmModel,		
		float&									outTrainingAccuracy 
	)
	THROW_AVL_ERRORS;

	/// <summary>Classifies input features based on a trained model</summary>
	/// <param name="inSvmModel">Input trained model.</param>
	/// <param name="inVector">Data vector of unknown class.</param>
	/// <param name="outPrediction">Predicted classes.</param>
	/// <param name="outModelClasses">All known model classes in order.</param>
	/// <param name="outClassProbabilities">For each data vector the probability of belonging to each class.</param>
	AVL_FUNCTION void SVM_ClassifySingle
	(
		const avl::SvmModel&								inSvmModel,				
		const atl::Array<float>&						inVector,				
		int&												outPrediction,			
		atl::Optional<atl::Array< int >& >					outModelClasses,		
		atl::Optional<atl::Array<float>& >				outClassProbabilities	
	)
	THROW_AVL_ERRORS;

	/// <summary>Classifies input points based on trained model</summary>
	/// <param name="inSvmModel">Input trained model.</param>
	/// <param name="inVectorArray">Data vector array of unknown classes.</param>
	/// <param name="outPredictions">Predicted classes.</param>
	/// <param name="outModelClasses">All known model classes in order.</param>
	/// <param name="outClassProbabilities">For each data vector the probability of belonging to each class.</param>
	AVL_FUNCTION void SVM_ClassifyMultiple
	(
		const avl::SvmModel&								inSvmModel,				
		const atl::Array<atl::Array<float> >&			inVectorArray,			
		atl::Array< int >&									outPredictions,			
		atl::Optional<atl::Array< int >& >					outModelClasses,		
		atl::Optional<atl::Array<atl::Array<float>>& >	outClassProbabilities	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SUPPORTVECTORMACHINES_H

