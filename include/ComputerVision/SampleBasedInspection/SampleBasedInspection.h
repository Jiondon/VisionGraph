//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SAMPLEBASEDINSPECTION_H
#define AVL_SAMPLEBASEDINSPECTION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/MatrixTypes.h"
#include "ATL/Array.hxx"
#include "Image/Image.h"
#include "DataClassification/PCAModel.h"

namespace avl
{


	namespace DataPreprocessing
	{
		enum Type
		{
			None = 0,
			Normalization,
			PCA
		};
	}

	class OrganicModelImpl;
	class OrganicModel;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructOrganicModel(OrganicModel&);
		AVL_FUNCTION void CopyOrganicModel(const OrganicModel&, OrganicModel&);
		AVL_FUNCTION bool TestOrganicModelEqual(const OrganicModel&, const OrganicModel&);
	}

	class OrganicModel 
	{
	public:
		OrganicModelImpl * pImpl;

		OrganicModel() : pImpl(nullptr) { }

		~OrganicModel()
		{
			pImpl_helpers::DestructOrganicModel(*this);
		}

		OrganicModel(const OrganicModel& rhs)
			: pImpl(0)
		{
			pImpl_helpers::CopyOrganicModel(rhs, *this);
		}

		OrganicModel& operator=(const OrganicModel& rhs)
		{
			pImpl_helpers::CopyOrganicModel(rhs, *this);
			return *this;
		}

		bool operator == (const OrganicModel& rhs) const
		{
			return pImpl_helpers::TestOrganicModelEqual(rhs, *this);
		}

		bool operator != (const OrganicModel& rhs) const
		{
			return !(operator==(rhs));
		}
	};


	/// <summary>Loads images and regions, extracts knowledge from it, and initializes OrganicModel, which can be then trained and used to classify new images.</summary>
	/// <param name="inTrainingImageDirectories">One directory with images and regions per class.</param>
	/// <param name="inTrainingImageExtensions">Extension of image files to use. Default value: \".bmp\".</param>
	/// <param name="outInitializedModel">Pre-trained model, initialized with data.</param>
	AVL_FUNCTION void LoadOrganicTrainingData
	(
		const atl::Array<atl::Directory>&				inTrainingImageDirectories,		
		const atl::String&								inTrainingImageExtensions,		
		avl::OrganicModel&								outInitializedModel				
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains OrganicModel, which has to be previously initialized with LoadOrganicTrainingData.</summary>
	/// <param name="inIterationCount">Number of iteration of internal learning process. Default value: 500.</param>
	/// <param name="inLearningRate">How aggressive the learning should be. Default value: 0.1f.</param>
	/// <param name="inMomentum">Factor that helps to move out of local minima. Default value: 0.1f.</param>
	/// <param name="inModelCapacity">Internal size of model. Default value: 10.</param>
	/// <param name="inPreprocessing">Method of cleaning the data before learning.</param>
	/// <param name="inVarianceToLeave">Value of variance to leave, when PCA preprocessing is done. Default value: 0.99f.</param>
	/// <param name="ioOrganicModel">Resulting model.</param>
	AVL_FUNCTION void TrainOrganicModel
	(

		const int&									inIterationCount,	
		const float&								inLearningRate,		
		const float&								inMomentum,			
		const int									inModelCapacity,	
		const avl::DataPreprocessing::Type			inPreprocessing,	
		const atl::Optional<float>&					inVarianceToLeave,	
		avl::OrganicModel&							ioOrganicModel		
	)
	THROW_AVL_ERRORS;

	/// <summary>Analyzes provided image within given ROI, and classifies selected object with beforehand trained OrganicModel.</summary>
	/// <param name="inOrganicModel">Trained model.</param>
	/// <param name="inImage">Image, which will be classified.</param>
	/// <param name="inRegion">Region, which selects organic object in the image provided.</param>
	/// <param name="outClass">Class number, to which image was assigned.</param>
	/// <param name="outScore">Score of the decision - the greater the better.</param>
	/// <param name="outScores">Scores for all classes known by classifier.</param>
	AVL_FUNCTION void RecognizeOrganicObject
	(
		const avl::OrganicModel&	inOrganicModel,	
		const avl::Image&			inImage,		
		const avl::Region&			inRegion,		
		int&						outClass,		
		float&						outScore,		
		atl::Array<float>&			outScores		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SAMPLEBASEDINSPECTION_H

