//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_OPTICALCHARACTERRECOGNITION_H
#define AVL_OPTICALCHARACTERRECOGNITION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/MlpPreprocessing.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "ComputerVision/TextThresholdingMethod.h"
#include "Profile/Profile.h"
#include "TextSegmentation.h"

namespace avl
{


	class CharacterSample
	{
		public:
			
			atl::String		character;
			avl::Region		sample;

			explicit CharacterSample(const atl::String& inCharacter = "", const Region& inSample = Region())
				: character(inCharacter), sample(inSample)
			{}

			bool operator == (const CharacterSample& rhs) const
			{
				return character == rhs.character && sample == rhs.sample;
			}

			bool operator != (const CharacterSample& rhs) const
			{
				return !(operator==(rhs));
			}

			// Character sample consist of single character and a non-empty region
			bool Valid() const
			{
				return character.Length() == 1 && sample.Size() != 0;
			}
	};

	class OcrModel;
	class OcrModelImpl;

	class OcrMlpModel;
	class OcrMlpModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructOcrMlpModel(OcrMlpModel&);
		AVL_FUNCTION void CopyOcrMlpModel(const OcrMlpModel&, OcrMlpModel&);
		AVL_FUNCTION bool TestOcrMlpModelEqual(const OcrMlpModel&, const OcrMlpModel&);

		AVL_FUNCTION void DestructOcrModel(OcrModel&);
		AVL_FUNCTION void CopyOcrModel(const OcrModel&, OcrModel&);
		AVL_FUNCTION bool TestOcrModelEqual(const OcrModel&, const OcrModel&);

		AVL_FUNCTION int GetOcrModelType(const OcrModel&);
		AVL_FUNCTION bool GetOcrModelIsTrained(const OcrModel&);	
	}

	class OcrMlpModel
	{
	public:
		OcrMlpModel() : pImpl(0) {}

		~OcrMlpModel()
		{
			pImpl_helpers::DestructOcrMlpModel(*this);
		}

		OcrMlpModel(const OcrMlpModel& inOcrMlpModel) : pImpl(0)
		{
			pImpl_helpers::CopyOcrMlpModel(inOcrMlpModel, *this);
		}

		OcrMlpModel& operator=(const OcrMlpModel& inOcrMlpModel)
		{
			pImpl_helpers::CopyOcrMlpModel(inOcrMlpModel, *this);
			return *this;
		}

		bool operator == (const OcrMlpModel& rhs) const
		{
			return pImpl_helpers::TestOcrMlpModelEqual(*this, rhs);
		}
		
		bool operator != (const OcrMlpModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		OcrMlpModelImpl* pImpl;
	};

	namespace CharacterFeaturesType
	{
		enum Type 
		{
			Pixels = 0, 
			NormalizedPixels, 
			Convexity, 
			Circularity, 
			NumberOfHoles, 
			AspectRatio, 
			Width, 
			Height, 
			AreaRatio, 
			DiameterRatio, 
			Elongation,
			Orientation, 
			HorizontalProjection, 
			VerticalProjection, 
			HoughCircles, 
			Zoning4x4,
			Moment_11,
			Moment_02,
			Moment_20
		};
	}

	class CharacterFeatures
	{
	public:
		static const int CharacterFeatures_Count = 19;
		bool States[CharacterFeatures_Count];

		CharacterFeatures()
		{
			for (int i = 0; i < CharacterFeatures_Count; ++i)
				States[i] = false;
		}

		CharacterFeatures(bool s0, bool s1, bool s2, bool s3, bool s4, bool s5, bool s6, bool s7, bool s8, bool s9, bool s10, bool s11, bool s12, bool s13, bool s14, bool s15, bool s16, bool s17, bool s18)
		{
			bool states[CharacterFeatures_Count] = { s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18 };
			for (int i = 0; i < CharacterFeatures_Count; ++i)
			{
				States[i] = states[i];
			}
		}

		CharacterFeatures(const CharacterFeatures& old)
		{
			for (int i = 0; i < CharacterFeatures_Count; ++i)
				States[i] = old.States[i];
		}

		avl::CharacterFeatures& operator=(const CharacterFeatures& features)
		{
			if (this == &features)
				return *this;

			for (int i = 0; i < CharacterFeatures_Count; ++i)
				States[i] = features.States[i];

			return *this;
		}

		bool operator == (const CharacterFeatures& rhs) const
		{
			for (int i = 0; i < CharacterFeatures_Count; ++i)
			{
				if (States[i] != rhs.States[i])
				{
					return false;
				}
			}
			return true;
		}

		bool operator != (const CharacterFeatures& rhs) const
		{
			return !(operator==(rhs));
		}

		bool HasState(CharacterFeaturesType::Type feature) const
		{
			if ((int)feature >= CharacterFeatures_Count || (int)feature < 0)
				return false;

			return States[(int)feature];
		}

		void SetState(CharacterFeaturesType::Type feature, bool value)
		{
			if ((int)feature >= CharacterFeatures_Count || (int)feature < 0)
				return;

			States[(int)feature] = value;
		}

		bool IsEmpty() const
		{
			for (int i = 0; i < CharacterFeatures_Count; ++i)
			{
				if (States[i]) 
					return false;
			}

			return true;
		}
	};
	
	class OcrCandidate
	{
	public:
		float score;
		atl::String name;

		float Score() const
		{
			return score;
		}

		atl::String Name() const
		{
			return name;
		}

		explicit OcrCandidate(atl::String name = "", float score = 0.0f)
			: score(score), name(name)
		{}

		bool operator < (const OcrCandidate& left) const
		{
			return score < left.score;
		}

		bool operator == (const OcrCandidate& left) const
		{
			return	score == left.score && 
					name == left.name;
		}

		bool operator != (const OcrCandidate& left) const
		{
			return !(operator==(left));
		}
	};

	namespace OcrModelType
	{
		enum Type
		{
			None = 0,
			MLP = 1,
			SVM = 2
		};
	}

	class OcrModel
	{
		public:

			OcrModel():pImpl(0) {}

			~OcrModel()
			{
				pImpl_helpers::DestructOcrModel(*this);
			}

			bool operator == (const OcrModel& rhs) const
			{
				return pImpl_helpers::TestOcrModelEqual(*this, rhs);
			}
		
			bool operator != (const OcrModel& rhs) const
			{
				return !(operator==(rhs));
			}

			OcrModel(const OcrModel& inOcrModel) : pImpl(0)
			{
				pImpl_helpers::CopyOcrModel(inOcrModel, *this);
			}

			OcrModel& operator=(const OcrModel& inOcrModel)
			{
				pImpl_helpers::CopyOcrModel(inOcrModel, *this);
				return *this;
			}

			OcrModelType::Type ModelType() const
			{
				return (OcrModelType::Type)pImpl_helpers::GetOcrModelType(*this);
			}

			bool IsTrained()
			{
				return pImpl_helpers::GetOcrModelIsTrained(*this);
			}

			void Reset()
			{
				if (pImpl != NULL)
				{
					pImpl_helpers::DestructOcrModel(*this);
					pImpl = 0;
				}
			}

			OcrModelImpl * pImpl;
	};



	/// <summary>Returns fields of OcrCandidate structure.</summary>
	/// <param name="inCandidate">Input OcrCandidate structure.</param>
	/// <param name="outCharacter">Result of character recognition.</param>
	/// <param name="outScore">Score of recognized character.</param>
	AVL_FUNCTION void AccessOcrCandidate
	(
		const avl::OcrCandidate&	inCandidate,	
		atl::String&				outCharacter,	
		float&					outScore		
	)
	THROW_AVL_ERRORS;

	/// <summary>Provides access to internal data of the CharacterSample structure.</summary>
	/// <param name="inSample">The character sample from which data will be accessed.</param>
	/// <param name="outCharacter">Character textual representation.</param>
	/// <param name="outCharacterRegion">Character graphical representation.</param>
	AVL_FUNCTION void AccessCharacterSample
	(
		const avl::CharacterSample&		inSample,			
		atl::String&					outCharacter,		
		avl::Region&					outCharacterRegion	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates training font samples from the provided regions.</summary>
	/// <param name="inCharacterRegions">Array of character regions.</param>
	/// <param name="inCharacters">Character that should be assigned to corresponding regions.</param>
	/// <param name="outCharacterSamples">Array of CharacterSamples.</param>
	AVL_FUNCTION void MakeCharacterSamples
	(
		const atl::Array<avl::Region>&			inCharacterRegions,	
		const atl::String&						inCharacters,		
		atl::Array<avl::CharacterSample>&		outCharacterSamples	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an OCR multilayer perceptron model.</summary>
	/// <param name="inNormalizationSize">The character size after normalization. Default value: (Width: 16, Height: 16).</param>
	/// <param name="inHiddenLayerSizes">Internal structure of neuron layers used in classifier. Default value: atl::NIL.</param>
	/// <param name="inRandomSeed">Random seed used by MLP classifier. Default value: atl::NIL.</param>
	/// <param name="inPreprocessing">Input preprocessing method performed before calculations.</param>
	/// <param name="inCharacterFeatures">Character features used to distinguish characters from each other. Default value: (Pixels: True).</param>
	/// <param name="outOcrModel">Result OcrMlpModel used to recognize characters.</param>
	AVL_FUNCTION void InitOcr_MLP_Deprecated
	(
		const avl::Size&						inNormalizationSize,	
		atl::Optional<const atl::Array<int>& >	inHiddenLayerSizes,		
		atl::Optional<int>						inRandomSeed,			
		avl::MlpPreprocessing::Type				inPreprocessing,		
		const avl::CharacterFeatures&			inCharacterFeatures,	
		avl::OcrMlpModel&						outOcrModel				
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains an OCR multilayer perceptron classifier.</summary>
	/// <param name="inOcrModel">Initialized OcrMlpModel to train.</param>
	/// <param name="inCharacterSamples">Training font created from sample regions.</param>
	/// <param name="inLearningRate">Suppression level of changes during learning process. Default value: 0.6f.</param>
	/// <param name="inMomentum">Value of classifier learning momentum. Default value: 0.75f.</param>
	/// <param name="inIterationCount">Learning iteration count. Default value: 100.</param>
	/// <param name="inCharacterSize">Size of fixed width font. Default value: atl::NIL.</param>
	/// <param name="outOcrModel">Trained OcrMlpModel used to recognize characters.</param>
	/// <param name="diagError">Changes of mean error level progress during learning process.</param>
	/// <param name="diagTrainingAccuracy">The overall training score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used to train classifier.</param>
	AVL_FUNCTION void TrainOcr_MLP_Deprecated
	(
		const avl::OcrMlpModel&					inOcrModel,					
		const atl::Array<avl::CharacterSample>&	inCharacterSamples,			
		float								inLearningRate,				
		float								inMomentum,					
		int										inIterationCount,			
		atl::Optional<const avl::Size&>			inCharacterSize,			
		avl::OcrMlpModel&						outOcrModel,				
		avl::Profile&							diagError = atl::Dummy<avl::Profile>(),					
		float&								diagTrainingAccuracy = atl::Dummy<float>(),		
		atl::Array<avl::Image>&					diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains an OCR multilayer perceptron classifier.</summary>
	/// <param name="inCharacterSamples">Training font created from sample regions.</param>
	/// <param name="inNormalizationSize">The character size after normalization. Default value: (Width: 16, Height: 16).</param>
	/// <param name="inHiddenLayerSizes">Internal structure of neuron layers used in classifier. Default value: atl::NIL.</param>
	/// <param name="inRandomSeed">Random seed used by MLP classifier. Default value: atl::NIL.</param>
	/// <param name="inCharacterFeatures">Character features used to distinguish characters from each other. Default value: (Pixels: True).</param>
	/// <param name="inLearningRate">Suppression level of changes during learning process. Default value: 0.6f.</param>
	/// <param name="inMomentum">Value of classifier learning momentum. Default value: 0.75f.</param>
	/// <param name="inIterationCount">Learning iteration count. Default value: 100.</param>
	/// <param name="inCharacterSize">Size of fixed width font. Default value: atl::NIL.</param>
	/// <param name="outOcrModel">Trained OcrMlpModel used to recognize characters.</param>
	/// <param name="outTrainingAccuracy">The overall training score.</param>
	/// <param name="diagError">Changes of mean error level progress during learning process.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used to train classifier.</param>
	AVL_FUNCTION void TrainOcr_MLP
	(
		const atl::Array<avl::CharacterSample>&	inCharacterSamples,			
		const avl::Size&						inNormalizationSize,		
		atl::Optional<const atl::Array<int>& >	inHiddenLayerSizes,			
		atl::Optional<int>						inRandomSeed,				
		const avl::CharacterFeatures&			inCharacterFeatures,		
		float								inLearningRate,				
		float								inMomentum,					
		int										inIterationCount,			
		atl::Optional<const avl::Size&>			inCharacterSize,			
		avl::OcrModel&							outOcrModel,				
		float&								outTrainingAccuracy,		
		avl::Profile&							diagError = atl::Dummy<avl::Profile>(),					
		atl::Array<avl::Image>&					diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized OcrMlpModel object as avdata file.</summary>
	/// <param name="inOcrModel">Model to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveOcrMlpModel
	(
		const avl::OcrMlpModel&		inOcrModel,	
		const atl::File&			inFilename	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized OcrMlpModel object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outOcrModel">Deserialized OcrMlpModel.</param>
	AVL_FUNCTION void LoadOcrMlpModel
	(
		const atl::File&		inFilename,	
		avl::OcrMlpModel&		outOcrModel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Classifies input regions into characters. Based on the Multi-Layer Perceptron model.</summary>
	/// <param name="inCharacterRegions">Array of character regions to recognize.</param>
	/// <param name="inOcrModel">Trained OcrMlpModel used to recognize characters.</param>
	/// <param name="inCharacterSize">Size of single monospaced character if needed. Default value: atl::NIL.</param>
	/// <param name="inDotPrint">Dot-printed characters preprocessing.</param>
	/// <param name="inCharacterSorting">Sorting order of input characters. Default value: LeftToRight.</param>
	/// <param name="inMinScore">Minimal value of accepted result. Otherwise char '*' will be placed. Default value: atl::NIL.</param>
	/// <param name="inMinSpaceWidth">Minimal distance between characters where space character will be inserted. Default value: atl::NIL.</param>
	/// <param name="outCharacters">Result of characters recognition.</param>
	/// <param name="outScores">Classification result score.</param>
	/// <param name="outCandidates">Array of a character classification results and their score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used in character recognition.</param>
	/// <param name="diagCharactersBoxes">Bounding boxes of characters.</param>
	AVL_FUNCTION void RecognizeCharacters_MLP_Deprecated
	(
		const atl::Array<avl::Region>&				inCharacterRegions,			
		const avl::OcrMlpModel&						inOcrModel,					
		atl::Optional<const avl::Size&>				inCharacterSize,			
		const bool									inDotPrint,					
		const avl::CharacterSortingOrder::Type		inCharacterSorting,			
		atl::Optional<float>					inMinScore,					
		atl::Optional<int>							inMinSpaceWidth,			
		atl::String&								outCharacters,				
		atl::Array<float>&						outScores,					
		atl::Array<atl::Array<avl::OcrCandidate> >&	outCandidates,				
		atl::Array<avl::Image>&						diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<avl::Box>&						diagCharactersBoxes = atl::Dummy< atl::Array<avl::Box> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Classifies input regions into characters. Based on the Multi-Layer Perceptron model.</summary>
	/// <param name="inCharacterRegions">Array of character regions to recognize.</param>
	/// <param name="inOcrModel">Trained OcrMlpModel used to recognize characters.</param>
	/// <param name="inCharacterSize">Size of single monospaced character if needed. Default value: atl::NIL.</param>
	/// <param name="inDotPrint">Dot-printed characters preprocessing.</param>
	/// <param name="inCharacterSorting">Sorting order of input characters. Default value: LeftToRight.</param>
	/// <param name="inMinScore">Minimal value of accepted result. Otherwise char '*' will be placed. Default value: atl::NIL.</param>
	/// <param name="inMinSpaceWidth">Minimal distance between characters where space character will be inserted. Default value: atl::NIL.</param>
	/// <param name="outCharacters">Result of characters recognition.</param>
	/// <param name="outScores">Classification result score.</param>
	/// <param name="outCandidates">Array of a character classification results and their score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used in character recognition.</param>
	/// <param name="diagCharactersBoxes">Bounding boxes of characters.</param>
	AVL_FUNCTION void RecognizeCharacters
	(
		const atl::Array<avl::Region>&				inCharacterRegions,			
		const avl::OcrModel&						inOcrModel,					
		atl::Optional<const avl::Size&>				inCharacterSize,			
		const bool									inDotPrint,					
		const avl::CharacterSortingOrder::Type		inCharacterSorting,			
		atl::Optional<float>					inMinScore,					
		atl::Optional<int>							inMinSpaceWidth,			
		atl::String&								outCharacters,				
		atl::Array<float>&						outScores,					
		atl::Array<atl::Array<avl::OcrCandidate> >&	outCandidates,				
		atl::Array<avl::Image>&						diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<avl::Box>&						diagCharactersBoxes = atl::Dummy< atl::Array<avl::Box> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits the input region into an array of regions corresponding to individual characters.</summary>
	/// <param name="inRegion">Input region containing characters.</param>
	/// <param name="inProjectionSmooth">Value of smooth applied to region projection before splitting into separated characters. Default value: 1.0f.</param>
	/// <param name="inCharacterWidth">Single character width. Default value: 15.</param>
	/// <param name="outRegions">Array or regions containing single characters.</param>
	/// <param name="diagClasses">Regions in which characters parts will be connected into a single character region.</param>
	/// <param name="diagProjection">Profile of region projection used to distinguish characters.</param>
	AVL_FUNCTION void SplitRegionIntoMultipleCharacters
	(
		const avl::Region&			inRegion,			
		const float&			inProjectionSmooth,	
		const int&					inCharacterWidth,	
		atl::Array<avl::Region>&	outRegions,			
		atl::Array<avl::Region>&	diagClasses = atl::Dummy< atl::Array<avl::Region> >(),		
		avl::Profile&				diagProjection = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits the input region into a fixed-size array of regions corresponding to individual characters.</summary>
	/// <param name="inRegion">Region which contains characters.</param>
	/// <param name="inCharacterCount">Character count in provided region.</param>
	/// <param name="inCharacterSpacing">Spacing size between characters.</param>
	/// <param name="inProjectionSmooth">Projection smoothing value used to remove noises from character region. Default value: 1.0f.</param>
	/// <param name="outRegions">Output array of regions containing separated characters.</param>
	/// <param name="diagClasses">Regions that contain location of split characters.</param>
	/// <param name="diagProjection">Profile of region projection used to distinguish characters.</param>
	AVL_FUNCTION void SplitRegionIntoExactlyNCharacters
	(
		const avl::Region&							inRegion,				
		const int&									inCharacterCount,		
		const int&									inCharacterSpacing,		
		const float&							inProjectionSmooth,		
		atl::Conditional<atl::Array<avl::Region> >&	outRegions,				
		atl::Array<avl::Region>&					diagClasses = atl::Dummy< atl::Array<avl::Region> >(),			
		avl::Profile&								diagProjection = atl::Dummy<avl::Profile>()			
	)
	THROW_AVL_ERRORS;

	class OcrSvmModel;
	class OcrSvmModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructOcrSvmModel(OcrSvmModel&);
		AVL_FUNCTION void CopyOcrSvmModel(const OcrSvmModel&, OcrSvmModel&);
		AVL_FUNCTION bool TestOcrSvmModelEqual(const OcrSvmModel&, const OcrSvmModel&);
	}

	class OcrSvmModel
	{
	public:
		OcrSvmModel() : pImpl(0) {}

		~OcrSvmModel()
		{
			pImpl_helpers::DestructOcrSvmModel(*this);
		}

		OcrSvmModel(const OcrSvmModel& inOcrSvmModel) : pImpl(0)
		{
			pImpl_helpers::CopyOcrSvmModel(inOcrSvmModel, *this);
		}

		OcrSvmModel& operator=(const OcrSvmModel& inOcrSvmModel)
		{
			pImpl_helpers::CopyOcrSvmModel(inOcrSvmModel, *this);
			return *this;
		}

		bool operator == (const OcrSvmModel& rhs) const
		{
			return pImpl_helpers::TestOcrSvmModelEqual(*this, rhs);
		}
		
		bool operator != (const OcrSvmModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		OcrSvmModelImpl* pImpl;
	};


	/// <summary>Creates an OCR model based on support vector machines classifier.</summary>
	/// <param name="inNu">Trade-off between training accuracy and number of supported vectors. Default value: atl::NIL.</param>
	/// <param name="inKernelGamma">Gamma parameter for RBF kernel. Default value: 0.01f.</param>
	/// <param name="inRegularizationConstant">Preventing overfitting. Default value: 1.0f.</param>
	/// <param name="inStopEpsilon">Epsilon for stopping criterion. Default value: 0.001f.</param>
	/// <param name="inUseShrinkingHeuristics">Heuristics may speed up computations. Default value: True.</param>
	/// <param name="inNormalizationSize">The character size after normalization. Default value: (Width: 16, Height: 16).</param>
	/// <param name="inRandomSeed">Random seed used to train classifier. Default value: atl::NIL.</param>
	/// <param name="inCharacterFeatures">Character features used to identify characters. Default value: (Pixels: True).</param>
	/// <param name="outOcrModel">Result OcrSvmModel used to recognize characters.</param>
	AVL_FUNCTION void InitOcr_SVM_Deprecated
	(
		const atl::Optional<float>&		inNu,						
		const atl::Optional<float>&		inKernelGamma,				
		const float&					inRegularizationConstant,	
		const float&					inStopEpsilon,				
		bool								inUseShrinkingHeuristics,	
		const avl::Size&					inNormalizationSize,		
		atl::Optional<int>					inRandomSeed,				
		const avl::CharacterFeatures&		inCharacterFeatures,		
		avl::OcrSvmModel&					outOcrModel					
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains an OCR support vector machines classifier.</summary>
	/// <param name="inOcrModel">Initialized OcrSvmModel to train.</param>
	/// <param name="inCharacterSamples">Training font created from sample regions.</param>
	/// <param name="inCharacterSize">Size of fixed width font. Default value: atl::NIL.</param>
	/// <param name="outOcrModel">Trained OcrSvmModel used to recognize characters.</param>
	/// <param name="diagTrainingAccuracy">The overall training score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used to train classifier.</param>
	AVL_FUNCTION void TrainOcr_SVM_Deprecated
	(
		const avl::OcrSvmModel&					inOcrModel,					
		const atl::Array<avl::CharacterSample>&	inCharacterSamples,			
		atl::Optional<const avl::Size&>			inCharacterSize,			
		avl::OcrSvmModel&						outOcrModel,				
		float&								diagTrainingAccuracy = atl::Dummy<float>(),		
		atl::Array<avl::Image>&					diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains an OCR support vector machines classifier.</summary>
	/// <param name="inCharacterSamples">Training font created from sample regions.</param>
	/// <param name="inNormalizationSize">The character size after normalization. Default value: (Width: 16, Height: 16).</param>
	/// <param name="inNu">Trade-off between training accuracy and number of supported vectors. Default value: atl::NIL.</param>
	/// <param name="inKernelGamma">Gamma parameter for RBF kernel. Default value: atl::NIL.</param>
	/// <param name="inRegularizationConstant">Preventing overfitting. Default value: 1.0f.</param>
	/// <param name="inStopEpsilon">Epsilon for stopping criterion. Default value: 0.001f.</param>
	/// <param name="inUseShrinkingHeuristics">Heuristics may speed up computations. Default value: True.</param>
	/// <param name="inCharacterSize">Size of fixed width font. Default value: atl::NIL.</param>
	/// <param name="inRandomSeed">Random seed used to train classifier. Default value: atl::NIL.</param>
	/// <param name="inCharacterFeatures">Character features used to identify characters. Default value: (Pixels: True).</param>
	/// <param name="outOcrModel">Trained OcrSvmModel used to recognize characters.</param>
	/// <param name="outTrainingAccuracy">The overall training score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used to train classifier.</param>
	AVL_FUNCTION void TrainOcr_SVM
	(
		const atl::Array<avl::CharacterSample>&	inCharacterSamples,			
		const avl::Size&						inNormalizationSize,		
		const atl::Optional<float>&				inNu,						
		const atl::Optional<float>&				inKernelGamma,				
		const float&							inRegularizationConstant,	
		const float&							inStopEpsilon,				
		bool									inUseShrinkingHeuristics,	
		atl::Optional<const avl::Size&>			inCharacterSize,			
		atl::Optional<int>						inRandomSeed,				
		const avl::CharacterFeatures&			inCharacterFeatures,		
		avl::OcrModel&							outOcrModel,				
		float&									outTrainingAccuracy,		
		atl::Array<avl::Image>&					diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Classifies input regions into characters. Based on the Support Vector Machines model.</summary>
	/// <param name="inCharacterRegions">Array of character regions to recognize.</param>
	/// <param name="inOcrModel">Trained OcrSvmModel used to recognize characters.</param>
	/// <param name="inCharacterSize">Size of single monospaced character if needed. Default value: atl::NIL.</param>
	/// <param name="inDotPrint">Dot-printed characters preprocessing.</param>
	/// <param name="inCharacterSorting">Sorting order of input characters. Default value: LeftToRight.</param>
	/// <param name="inMinScore">Minimal value of accepted result. Otherwise char '*' will be placed. Default value: atl::NIL.</param>
	/// <param name="inMinSpaceWidth">Minimal distance between characters where space character will be inserted. Default value: atl::NIL.</param>
	/// <param name="outCharacters">Result of characters recognition.</param>
	/// <param name="outScores">Classification result score.</param>
	/// <param name="outCandidates">Array of a character classification results and their score.</param>
	/// <param name="diagNormalizedCharacters">Images of normalized characters used in character recognition.</param>
	/// <param name="diagCharactersBoxes">Bounding boxes of characters.</param>
	AVL_FUNCTION void RecognizeCharacters_SVM_Deprecated
	(
		const atl::Array<avl::Region>&				inCharacterRegions,			
		const avl::OcrSvmModel&						inOcrModel,					
		atl::Optional<const avl::Size&>				inCharacterSize,			
		const bool									inDotPrint,					
		const avl::CharacterSortingOrder::Type		inCharacterSorting,			
		atl::Optional<float>					inMinScore,					
		atl::Optional<int>							inMinSpaceWidth,			
		atl::String&								outCharacters,				
		atl::Array<float>&						outScores,					
		atl::Array<atl::Array<avl::OcrCandidate>>&	outCandidates,				
		atl::Array<avl::Image>&						diagNormalizedCharacters = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<avl::Box>&						diagCharactersBoxes = atl::Dummy< atl::Array<avl::Box> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized OcrSvmModel object as avdata file.</summary>
	/// <param name="inOcrModel">Model to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveOcrSvmModel
	(
		const avl::OcrSvmModel&		inOcrModel,	
		const atl::File&			inFilename	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized OcrSvmModel object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outOcrModel">Deserialized OcrSvmModel.</param>
	AVL_FUNCTION void LoadOcrSvmModel
	(
		const atl::File&		inFilename,	
		avl::OcrSvmModel&		outOcrModel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sorts characters regions by selected text order</summary>
	AVL_FUNCTION void SortCharacterRegions
	(
		const atl::Array<avl::Region>&		inCharacters,
		avl::CharacterSortingOrder::Type	inSortingOrder,
		atl::Array<avl::Region>&			outCharacters
	)
	THROW_AVL_ERRORS;

	/// <summary>Ready-to-use tool for extracting and splitting character to single characters.</summary>
	/// <param name="inImage">An input image with text.</param>
	/// <param name="inRoi">Location of the text.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object.</param>
	/// <param name="inSegmentationModel">Model used for separating text from background.</param>
	/// <param name="outCharacters">Split characters aligned to ROI.</param>
	/// <param name="diagTextRegion">Region of text after extraction.</param>
	/// <param name="diagAlignedCharacters">Character regions preserving original image orientation.</param>
	/// <param name="diagAlignedRoi">ROI rectangle after alignment.</param>
	AVL_FUNCTION void ExtractText
	(
		const avl::Image&					inImage,					
		const avl::Rectangle2D&				inRoi,						
		const avl::CoordinateSystem2D&		inRoiAlignment,				
		const avl::TextSegmentation&		inSegmentationModel,		
		atl::Array<avl::Region>&			outCharacters,				
		avl::Region&						diagTextRegion = atl::Dummy<avl::Region>(),				
		atl::Array<avl::Region>&			diagAlignedCharacters = atl::Dummy< atl::Array<avl::Region> >(),		
		avl::Rectangle2D&					diagAlignedRoi = atl::Dummy<avl::Rectangle2D>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Ready-to-use tool for reading text from images using the OCR technique.</summary>
	/// <param name="inCharacters">Character regions.</param>
	/// <param name="inOcrModel">OCR model specific to a particular font.</param>
	/// <param name="inMinScore">Minimal score of reading a character.</param>
	/// <param name="outText">Read text.</param>
	/// <param name="outCharacters">Array of characters. NIL indicates invalid read when inMinScore is set,.</param>
	/// <param name="outScores">Reading scores for each character.</param>
	/// <param name="outIsTextValid">Returns False if any ad score smaller than inMinScore.</param>
	AVL_FUNCTION void ReadText
	(
		const atl::Array<avl::Region>&				inCharacters,			
		const avl::OcrModel&						inOcrModel,				
		const float									inMinScore,				
		atl::String&								outText,				
		atl::Array<atl::Conditional<atl::String>>&	outCharacters,			
		atl::Array<float>&							outScores,				
		bool&										outIsTextValid			
	)
	THROW_AVL_ERRORS;

	/// <summary>Ready-to-use tool for reading text from images using the OCR technique.</summary>
	/// <param name="inCharacters">Character regions.</param>
	/// <param name="inOcrModels">OCR model specific to a particular font.</param>
	/// <param name="inFormat">Description of entered text.</param>
	/// <param name="inMinScore">Minimal score of reading a character.</param>
	/// <param name="outText">Read text.</param>
	/// <param name="outCharacters">Array of characters. NIL indicates invalid read when inMinScore is set,.</param>
	/// <param name="outScores">Reading scores for each character.</param>
	AVL_FUNCTION void ReadText_Format
	(
		const atl::Array<avl::Region>&				inCharacters,			
		const atl::Array<avl::OcrModel>&			inOcrModels,			
		const atl::String&							inFormat,				
		const float									inMinScore,				
		atl::String&								outText,				
		atl::Array<atl::Conditional<atl::String>>&	outCharacters,			
		atl::Array<float>&							outScores				
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits an array of blobs by distance to a computed base lines</summary>
	/// <param name="inRegions">Input regions (parts of characters).</param>
	/// <param name="inRoi">Range of character classification.</param>
	/// <param name="inLinesCount">ROI is divided into inLinesCount lines. Default value: 1.</param>
	/// <param name="inLineWidth">Value of line range used if inRemoveOutliers is set to TRUE. Default value: 1.0f.</param>
	/// <param name="inRemoveOutliers">If this flag is set blobs with distance greater than inLineWidth are removed. Default value: False.</param>
	/// <param name="outLines">Lines in single Array.</param>
	/// <param name="diagLines">Segments which indicates the position of lines.</param>
	/// <param name="diagLineRanges">Rectangles represents range of lines which are included if inRemoveOutliers is set.</param>
	/// <param name="diagRegionPoints">Point which indicates region position.</param>
	AVL_FUNCTION void GroupRegionsByLines
	(
		const atl::Array<avl::Region>&							inRegions,			
		const avl::Rectangle2D&									inRoi,				
		const atl::Optional<avl::CoordinateSystem2D>&			inRoiAlignment,		  
		const int												inLinesCount,		
		const float											inLineWidth,		
		const bool												inRemoveOutliers,	
		atl::Array<atl::Array<avl::Region>>&					outLines,			
		atl::Array<avl::Region>&								outLine0,
		atl::Array<avl::Region>&								outLine1,
		atl::Array<avl::Region>&								outLine2,
		atl::Array<avl::Region>&								outLine3,
		avl::Rectangle2D&										outAlignedRoi,
		atl::Array<avl::Segment2D>&								diagLines = atl::Dummy< atl::Array<avl::Segment2D> >(),			
		atl::Array<avl::Rectangle2D>&							diagLineRanges = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Point2D>&								diagRegionPoints = atl::Dummy< atl::Array<avl::Point2D> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts OcrModel to OcrSvmModel</summary>
	AVL_FUNCTION void OcrModelToOcrSvmModel
	(
		const avl::OcrModel&	inOcrModel,
		avl::OcrSvmModel&		outOcrSvmModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts OcrModel to OcrMlpModel</summary>
	AVL_FUNCTION void OcrModelToOcrMlpModel
	(
		const avl::OcrModel&	inOcrModel,
		avl::OcrMlpModel&		outOcrMlpModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts OcrSvmModel(old type) to OcrModel</summary>
	AVL_FUNCTION void OcrSvmModelToOcrModel
	(
		const avl::OcrSvmModel&	inOcrSvmModel,
		avl::OcrModel&			outOcrModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts OcrMlpModel(old type) to OcrModel</summary>
	AVL_FUNCTION void OcrMlpModelToOcrModel
	(
		const avl::OcrMlpModel&	inOcrMlpModel,
		avl::OcrModel&			outOcrModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized OcrMlpModel object as avdata file.</summary>
	/// <param name="inOcrModel">Model to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveOcrModel
	(
		const avl::OcrModel&		inOcrModel,	
		const atl::File&			inFilename	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized OcrMlpModel object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outOcrModel">Deserialized OcrMlpModel.</param>
	AVL_FUNCTION void LoadOcrModel
	(
		const atl::File&		inFilename,	
		avl::OcrModel&			outOcrModel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Internal extracting features</summary>
	AVL_FUNCTION void OcrInternal_ExtractFeatures
	(
		const avl::Region&				inCharacterRegion,
		const atl::Array<float>&		inPixels,
		const avl::Image&				inNormalizedImage,
		const avl::CharacterFeatures&	inFlags,
		atl::Array<float>&				outFeatures
	)
	THROW_AVL_ERRORS;

	/// <summary>Internal character normalization</summary>
	AVL_FUNCTION void OcrInternal_NormalizeCharacter
	(
		const avl::Region&				inCharacterRegion,
		const int						inNormalizationWidth,
		const int						inNormalizationHeight,
		atl::Array<float>&				outFeatures,
		avl::Image&						outNormalized,
		float&							outRatioX,
		float&							outRatioY
	)
	THROW_AVL_ERRORS;

	/// <summary>Internal character normalization</summary>
	AVL_FUNCTION void OcrInternal_CutLetter
	(
		const avl::Region&			inCharacterRegion,
		const int&					inCharacterWidth,
		const int&					inCharacterHeight,
		const bool&					inMassCenter,
		avl::Region&				outCharacterRegion,
		avl::Box&					outCharacterBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates variations of input regions</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void CreateCharacterVariants
	(
		const avl::Region&			   inRegion,
		const bool					   inRotation,
		const bool					   inDilation,
		const bool					   inErosion,
		const bool					   inNoises,
		const bool					   inSkew,
		const bool					   inThicken,
		const bool					   inThin,
		atl::Array<avl::Region>&	   outRegions	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_OPTICALCHARACTERRECOGNITION_H

