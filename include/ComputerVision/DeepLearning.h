//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DEEPLEARNING_H
#define AVL_DEEPLEARNING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Profile/Profile.h"
#include "Enums/SamplingDensity.h"

namespace avl
{


	typedef atl::String DeepModel;
	typedef atl::String DeepModel_Classification;
	typedef atl::String DeepModel_FeatureDetection;
	typedef atl::String DeepModel_AnomalyDetection;
	typedef atl::String DeepModel_AnomalyDetection2;
	typedef atl::String DeepModel_InstanceSegmentation;

	struct FeatureClass
	{
		atl::String name;
		avl::Pixel color;

		FeatureClass(const atl::String& inName, const avl::Pixel& inColor)
			: name(inName), color(inColor)
		{
		}

		FeatureClass()
		{
		}

		const atl::String& Name() const
		{
			return name;
		}

		atl::uint8 R() const
		{
			return (atl::uint8)(color.X() >= 0.0f ? (color.X() <= 255.0f ? color.X() : 255) : 0);
		}

		atl::uint8 G() const
		{
			return (atl::uint8)(color.Y() >= 0.0f ? (color.Y() <= 255.0f ? color.Y() : 255) : 0);
		}

		atl::uint8 B() const
		{
			return (atl::uint8)(color.Z() >= 0.0f ? (color.Z() <= 255.0f ? color.Z() : 255) : 0);
		}
	};

	struct ClassConfidence
	{
		atl::String className;
		float confidence;
	};


	/// <summary></summary>
	AVL_FUNCTION void DeepLearning_GetProtocolVersion_Internal
	(
		int&			outVersion
	)
	THROW_AVL_ERRORS;

	/// <summary>Conversion between DeepModel and DeepModel_Classification</summary>
	AVL_FUNCTION void DeepModelToDeepModel_Classification
	(
		const avl::DeepModel&			inDeepModel,
		avl::DeepModel_Classification&	outDeepModel_Classification
	)
	THROW_AVL_ERRORS;

	/// <summary>Conversion between DeepModel and DeepModel_ImageSegmentation</summary>
	AVL_FUNCTION void DeepModelToDeepModel_InstanceSegmentation
	(
		const avl::DeepModel&			inDeepModel,
		avl::DeepModel_InstanceSegmentation&	outDeepModel_InstanceSegmentation
	)
	THROW_AVL_ERRORS;

	/// <summary>Conversion between DeepModel and DeepModel_AnomalyDetection</summary>
	AVL_FUNCTION void DeepModelToDeepModel_AnomalyDetection
	(
		const avl::DeepModel&				inDeepModel,
		avl::DeepModel_AnomalyDetection&	outModel_AnomalyDetection
	)
	THROW_AVL_ERRORS;

	/// <summary>Conversion between DeepModel and DeepModel_AnomalyDetection2</summary>
	AVL_FUNCTION void DeepModelToDeepModel_AnomalyDetection2
	(
		const avl::DeepModel&				inDeepModel,
		avl::DeepModel_AnomalyDetection2&	outModel_AnomalyDetection2
	)
	THROW_AVL_ERRORS;

	/// <summary>Conversion between DeepModel and DeepModel_FeatureDetection</summary>
	AVL_FUNCTION void DeepModelToDeepModel_FeatureDetection
	(
		const avl::DeepModel&				inDeepModel,
		avl::DeepModel_FeatureDetection&	outDeepModel_FeatureDetection
	)
	THROW_AVL_ERRORS;

	/// <summary>Filter is used to change basic Deep Learning configuration.</summary>
	/// <param name="inPort">Number of port used by sever. Default value: 8210.</param>
	/// <param name="inConnectionTimeout">Time which each filter will try to connect to service. Default value: 10000.</param>
	AVL_FUNCTION void DeepLearning_Configure
	(
		const int					inPort,					
		const atl::Optional<int>	inConnectionTimeout		
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	AVL_FUNCTION void DeepLearning_GetConnectedServiceRevision_Internal
	(
		int& outRevision
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DeepLearning_ClearImageOutsideRoi_Internal
	(const avl::Image& inImage, const avl::Region& inRegion, const avl::Pixel& inClearColor, avl::Image& outImage)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DeepLearning_ClearImageInsideRoi_Internal
	(const avl::Image& inImage, const avl::Region& inRegion, const avl::Pixel& inClearColor, avl::Image& outImage)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void DestroyDeepLearningConnectionState
	(
	)
	THROW_AVL_ERRORS;

	struct DeepLearningConnectionState
	{
		DeepLearningConnectionState() 
		{
		}

		~DeepLearningConnectionState() 
		{
			DestroyDeepLearningConnectionState();
		}
	};



	/// <summary></summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DeepLearning_PreprocessImage_Internal
	(
		const avl::Image&	inImage,
		const int inBoundingBoxFrameWidth,
		const int inBoundingBoxFrameHeight,
		const avl::Box& inBoundingBox,
		const atl::Optional<avl::Region>& inRoi,
		const bool			inConvertToGrayscale,
		const bool			inClearWithRoi,
		const int			inWidth,
		const int			inHeight,
		const int			inMarginWidth,
		const int			inMarginValue,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs feature classification using trained deep-learning model.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Area of interest. Default value: atl::NIL.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="inOverlap">Add tiles overlapping to improve results quality. Default value: True.</param>
	/// <param name="outHeatmaps">Returns heatmaps for all classes.</param>
	/// <param name="outFeature1">Returns heatmap for first feature class.</param>
	/// <param name="outFeature2">Returns heatmap for second feature class or empty image if class is not specified.</param>
	/// <param name="outFeature3">Returns heatmap for third feature class or empty image if class is not specified.</param>
	/// <param name="outFeature4">Returns heatmap for fourth feature class or empty image if class is not specified.</param>
	AVL_FUNCTION void DeepLearning_DetectFeatures
	(
		DeepLearningConnectionState&			ioState,
		const avl::Image&						inImage,
		const atl::Optional<avl::Region>&		inRoi,			
		const avl::DeepModel_FeatureDetection&	inDeepModel,	
		const bool&								inOverlap,		
		atl::Array<avl::Image>&					outHeatmaps,	
		atl::Optional<avl::Image&>				outFeature1 = atl::NIL,		
		atl::Optional<avl::Image&>				outFeature2 = atl::NIL,		
		atl::Optional<avl::Image&>				outFeature3 = atl::NIL,		
		atl::Optional<avl::Image&>				outFeature4 = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects anomalies using trained deep-learning model.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="outHeatmap">Image contains heatmaps for each input image channel.</param>
	/// <param name="outIsValid">Returns true if anomaly was not found.</param>
	/// <param name="outScore">Score of classification.</param>
	/// <param name="outIsConfident">Returns "false" if score is between T1 and T2.</param>
	/// <param name="outReconstructedImage">Returns network answer.</param>
	AVL_FUNCTION void DeepLearning_DetectAnomalies
	(
		DeepLearningConnectionState&			ioState,
		const avl::Image&						inImage,
		const avl::DeepModel_AnomalyDetection&	inDeepModel,						
		avl::Image&								outHeatmap,							
		bool&									outIsValid,							
		float&									outScore,							
		bool&									outIsConfident,						
		atl::Optional<avl::Image&>				outReconstructedImage = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects anomalies using trained deep-learning model. EXPERIMENTAL</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="outHeatmap">Image contains heatmaps for each input image channel.</param>
	/// <param name="outIsValid">Returns true if anomaly was not found.</param>
	/// <param name="outScore">Score of classification.</param>
	/// <param name="outIsConfident">Returns "false" if score is between T1 and T2.</param>
	AVL_FUNCTION void DeepLearning_DetectAnomalies2
	(
		DeepLearningConnectionState&			ioState,
		const avl::Image&						inImage,
		const avl::DeepModel_AnomalyDetection2&	inDeepModel,		
		avl::Image&								outHeatmap,			
		bool&									outIsValid,			
		float&									outScore,			
		bool&									outIsConfident		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs whole image classification using a trained deep-learning model.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Area of interest. Default value: atl::NIL.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="outConfidences">Returns confidences for all classes.</param>
	/// <param name="outClassName">Returns name of the class with highest confidence.</param>
	/// <param name="outClassIndex">Returns the index of the class with highest confidence.</param>
	/// <param name="outScore">Returns the value of the highest confidence.</param>
	AVL_FUNCTION void DeepLearning_ClassifyObject
	(
		DeepLearningConnectionState&		 ioState,
		const avl::Image&					 inImage,
		const atl::Optional<avl::Region>&	 inRoi,				
		const avl::DeepModel_Classification& inDeepModel,		
		atl::Array<avl::ClassConfidence>&	 outConfidences,	
		atl::String&						 outClassName,		
		int&								 outClassIndex,		
		float&								 outScore			
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs instance segmentation using a trained deep-learning model.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Area of interest. Default value: atl::NIL.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="inMinDetectionScore">Minimal score of found objects. Default value: atl::NIL.</param>
	/// <param name="inMaxObjectsCount">Maximal number of found objects. Default value: atl::NIL.</param>
	/// <param name="outBoundingBoxes">Bounding boxes of found objects.</param>
	/// <param name="outClassIds">Ids of found objects classes.</param>
	/// <param name="outClassNames">Names of found objects classes.</param>
	/// <param name="outScores">Scores of found objects.</param>
	/// <param name="outMasks">Masks of found objects.</param>
	AVL_FUNCTION void DeepLearning_SegmentInstances
	(
		DeepLearningConnectionState&				ioState,
		const avl::Image&							inImage,
		const atl::Optional<avl::Region>&			inRoi,					
		const avl::DeepModel_InstanceSegmentation&	inDeepModel,			
		const atl::Optional<float>&					inMinDetectionScore,	
		const atl::Optional<int>&					inMaxObjectsCount,		
		atl::Array<avl::Box>&						outBoundingBoxes,		
		atl::Array<int>&							outClassIds,			
		atl::Array<atl::String>&					outClassNames,			
		atl::Array<float>&							outScores,				
		atl::Array<avl::Region>&					outMasks				
	)
	THROW_AVL_ERRORS;

	/// <summary>Obtains default thresholds and saves them to threshold.xml</summary>
	AVL_FUNCTION void DeepLearning_CalculateThresholds
	(
		const atl::Directory&				inDirectory,
		const atl::Array<bool>&				inLabels,
		const atl::Array<float>&			inScores
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads thresholds from threshold.xml file.</summary>
	AVL_FUNCTION void DeepLearning_ReadThresholds
	(
		const atl::Directory&				inDirectory,
		float&								outT1,
		float&								outT2
	)
	THROW_AVL_ERRORS;

	/// <summary>Evalute given score in respect to given thresholds.</summary>
	AVL_FUNCTION void DeepLearning_EvaluateScore
	(
		const float							inScore,
		const float							inT1,
		const float							inT2,
		bool&								outIsValid,
		bool&								outIsConfident
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	AVL_FUNCTION void DeepLearning_ObtainHeatmap_Internal
	(
		const avl::Image&			inOriginalImage,
		const avl::Image&			inReconstructedImage,
		const bool					inOpenHeatmap,
		const bool					inBlurHeatmap,
		const atl::Optional<float>	inThresholdHeatmap,
		avl::Image&					outHeatmap
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	AVL_FUNCTION void DeepLearning_ScoreHeatmap_Internal
	(
		const avl::Image&			inHeatmap,
		float&						outScore
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	AVL_FUNCTION void DeepLearning_ScoreHeatmap2_Internal
	(
		const avl::Image&			inHeatmap,
		float&						outScore
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs deep learning model training using predefined model configuration.</summary>
	AVL_FUNCTION void DeepLearning_Train
	(
		DeepLearningConnectionState&		ioState,
		const atl::Directory&				inModelDirectory,
		const bool							inSendConfiguration,
		const atl::Optional<atl::String>&	inConfig,
		avl::DeepModel&						outModel,
		avl::Profile&						outValidationProfile,
		avl::Profile&						outTrainingProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs deep learning model training using predefined model configuration.</summary>
	/// <param name="inImages">Array of training images paths.</param>
	/// <param name="inRoiImages">Array of ROI images paths.</param>
	/// <param name="inClasses">Array of possible classes.</param>
	/// <param name="inMasks">Array of arrays of masks paths for each class.</param>
	/// <param name="inNetworkDepth">Network depth. Default value: 3.</param>
	/// <param name="inIterationCount">Number of iterations. Default value: 1000.</param>
	/// <param name="inFeatureSize">Feature size. Default value: 48.</param>
	/// <param name="inGrayscale">preprocessing: convert to grayscale.</param>
	/// <param name="inDownsample">Preprocessing: downsample. Default value: 0.</param>
	/// <param name="inBatchSize">Advanced: batch size. Default value: 16.</param>
	/// <param name="inRotationAngle">Augmentation: rotation angle.</param>
	/// <param name="inFlipUpDown">Augmentation: vertical flips.</param>
	/// <param name="inFlipLeftRight">Augmentation: horizontal flips.</param>
	/// <param name="inNoise">Augmentation: noise percentage.</param>
	/// <param name="inLuminance">Augmentation: luminance percentage.</param>
	/// <param name="outModel">Trained model.</param>
	/// <param name="outValidationProfile">Validation graph.</param>
	/// <param name="outTrainingProfile">Training graph.</param>
	AVL_FUNCTION void DeepLearning_TrainFeatureDetection
	(
		DeepLearningConnectionState&				ioState,
		const atl::Directory&						inModelDirectory,
		const atl::Array<atl::File>&				inImages,				
		const atl::Array<atl::File>&				inRoiImages,			
		const atl::Array<avl::FeatureClass>&		inClasses,				
		const atl::Array<atl::Array<atl::File>>&	inMasks,				
		const int&									inNetworkDepth,			
		const int&									inIterationCount,		
		const int&									inFeatureSize,			
		const bool&									inGrayscale,			
		const int&									inDownsample,			
		const int&									inBatchSize,			
		const int&									inRotationAngle,		
		const bool&									inFlipUpDown,			
		const bool&									inFlipLeftRight,		
		const int&									inNoise,				
		const int&									inLuminance,			
		avl::DeepModel&								outModel,				
		avl::Profile&								outValidationProfile,	
		avl::Profile&								outTrainingProfile		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs deep learning model training using predefined model configuration.</summary>
	/// <param name="inImages">Array of training images paths.</param>
	/// <param name="inRoiImages">Array of ROI images paths.</param>
	/// <param name="inLabels">Array of labels.</param>
	/// <param name="inNetworkDepth">Network depth. Default value: 3.</param>
	/// <param name="inIterationCount">Number of iterations. Default value: 1000.</param>
	/// <param name="inGrayscale">preprocessing: convert to grayscale.</param>
	/// <param name="inBatchSize">Advanced: batch size. Default value: 10.</param>
	/// <param name="inFlipUpDown">Augmentation: vertical flips.</param>
	/// <param name="inFlipLeftRight">Augmentation: horizontal flips.</param>
	/// <param name="inNoise">Augmentation: noise percentage.</param>
	/// <param name="inLuminance">Augmentation: luminance percentage.</param>
	/// <param name="outModel">Trained model.</param>
	/// <param name="outValidationProfile">Validation graph.</param>
	/// <param name="outTrainingProfile">Training graph.</param>
	AVL_FUNCTION void DeepLearning_TrainObjectClassification
	(
		DeepLearningConnectionState&				ioState,
		const atl::Directory&						inModelDirectory,
		const atl::Array<atl::File>&				inImages,				
		const atl::Array<atl::File>&				inRoiImages,			
		const atl::Array<atl::String>&				inLabels,				
		const int&									inNetworkDepth,			
		const int&									inIterationCount,		
		const bool&									inGrayscale,			
		const int&									inBatchSize,			
		const bool&									inFlipUpDown,			
		const bool&									inFlipLeftRight,		
		const int&									inNoise,				
		const int&									inLuminance,			
		avl::DeepModel&								outModel,				
		avl::Profile&								outValidationProfile,	
		avl::Profile&								outTrainingProfile		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs deep learning model training using predefined model configuration.</summary>
	/// <param name="inImages">Array of training images paths.</param>
	/// <param name="inRoiImage">Array of ROI image path.</param>
	/// <param name="inLabels">Array of labels.</param>
	/// <param name="inDensity">Sampling density. Default value: Medium.</param>
	/// <param name="inNetworkDepth">Network depth. Default value: 3.</param>
	/// <param name="inIterationCount">Number of iterations. Default value: 1000.</param>
	/// <param name="inFeatureSize">Feature size. Default value: 24.</param>
	/// <param name="inGrayscale">preprocessing: convert to grayscale.</param>
	/// <param name="inDownsample">Preprocessing: downsample. Default value: 0.</param>
	/// <param name="inBatchSize">Advanced: batch size. Default value: 16.</param>
	/// <param name="inRotationAngle">Augmentation: rotation angle.</param>
	/// <param name="inFlipUpDown">Augmentation: vertical flips.</param>
	/// <param name="inFlipLeftRight">Augmentation: horizontal flips.</param>
	/// <param name="inNoise">Augmentation: noise percentage.</param>
	/// <param name="inLuminance">Augmentation: luminance percentage.</param>
	/// <param name="outModel">Trained model.</param>
	/// <param name="outValidationProfile">Validation graph.</param>
	/// <param name="outTrainingProfile">Training graph.</param>
	AVL_FUNCTION void DeepLearning_TrainAnomalyDetection_Local
	(
		DeepLearningConnectionState&		ioState,
		const atl::Directory&				inModelDirectory,
		const avl::ImageFormat&				inImageFormat,
		const atl::Array<atl::File>&		inImages,					
		const atl::File&					inRoiImage,					
		const atl::Array<bool>&				inLabels,					
		const avl::SamplingDensity::Type&	inDensity,					
		const int&							inNetworkDepth,				
		const int&							inIterationCount,			
		const int&							inFeatureSize,				
		const bool&							inGrayscale,				
		const int&							inDownsample,				
		const int&							inBatchSize,				
		const int&							inRotationAngle,			
		const bool&							inFlipUpDown,				
		const bool&							inFlipLeftRight,			
		const int&							inNoise,					
		const int&							inLuminance,				
		avl::DeepModel&						outModel,					
		avl::Profile&						outValidationProfile,		
		avl::Profile&						outTrainingProfile			
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs deep learning model training using predefined model configuration.</summary>
	/// <param name="inImages">Array of training images paths.</param>
	/// <param name="inRoiImage">Array of ROI image path.</param>
	/// <param name="inLabels">Array of labels.</param>
	/// <param name="inNetworkDepth">Network depth. Default value: 3.</param>
	/// <param name="inIterationCount">Number of iterations. Default value: 1000.</param>
	/// <param name="inGrayscale">preprocessing: convert to grayscale.</param>
	/// <param name="inFlipUpDown">Augmentation: vertical flips.</param>
	/// <param name="inFlipLeftRight">Augmentation: horizontal flips.</param>
	/// <param name="inNoise">Augmentation: noise percentage.</param>
	/// <param name="inLuminance">Augmentation: luminance percentage.</param>
	/// <param name="outModel">Trained model.</param>
	/// <param name="outValidationProfile">Validation graph.</param>
	/// <param name="outTrainingProfile">Training graph.</param>
	AVL_FUNCTION void DeepLearning_TrainAnomalyDetection_Global
	(
		DeepLearningConnectionState&		ioState,
		const atl::Directory&				inModelDirectory,
		const avl::ImageFormat&				inImageFormat,
		const atl::Array<atl::File>&		inImages,				
		const atl::File&					inRoiImage,				
		const atl::Array<bool>&				inLabels,				
		const int&							inNetworkDepth,			
		const int&							inIterationCount,		
		const bool&							inGrayscale,			
		const bool&							inFlipUpDown,			
		const bool&							inFlipLeftRight,		
		const int&							inNoise,				
		const int&							inLuminance,			
		avl::DeepModel&						outModel,				
		avl::Profile&						outValidationProfile,	
		avl::Profile&						outTrainingProfile		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads Deep Learning model for further usage.</summary>
	AVL_FUNCTION void DeepLearning_LoadModel
	(
		DeepLearningConnectionState&	ioState,
		const atl::Directory&			inDeepModelLocation,
		avl::DeepModel&					outDeepModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects anomalies using trained deep-learning model.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Area of interest. Default value: atl::NIL.</param>
	/// <param name="inDeepModel">Trained model.</param>
	/// <param name="outHeatmap">Image contains heatmaps for each input image channel.</param>
	/// <param name="outIsValid">Returns true if anomaly was not found.</param>
	/// <param name="outScore">Score of classification.</param>
	/// <param name="outIsConfident">Returns "false" if score is between T1 and T2.</param>
	/// <param name="outReconstructedImage">Returns network answer.</param>
	AVL_FUNCTION void DeepLearning_DetectAnomalies_Deprecated
	(
		DeepLearningConnectionState&		ioState,
		const avl::Image&					inImage,
		const atl::Optional<avl::Region>&	inRoi,					
		const atl::String&					inDeepModel,			
		avl::Image&							outHeatmap,				
		bool&								outIsValid,				
		float&								outScore,				
		bool&								outIsConfident,			
		avl::Image&							outReconstructedImage	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_DEEPLEARNING_H

