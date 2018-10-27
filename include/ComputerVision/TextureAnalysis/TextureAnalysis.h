//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_TEXTUREANALYSIS_H
#define AVL_TEXTUREANALYSIS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Histogram/Histogram.h"
#include "ComputerVision/TextureModel.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{


	namespace LinearBinaryPatternType
	{
		enum Type
		{
			Plain,
			RotationInvariant,
			Uniform,
			UniformRotationInvariant
		};
	}

	namespace LawsFilterSize
	{
		enum Type
		{
			_3x3,
			_5x5,
			_7x7
		};
	}

	namespace LawsFilterType
	{
		enum Type
		{
			Level,
			Edge,
			Wave,
			Spot,
			Ripple,
			Oscillation,
			Undulation
		};
	}


	/// <summary>Creates histogram and map of Linear Binary Patterns (with radius 1 and size 8) of provided image.</summary>
	/// <param name="inImage">Mono-channel image.</param>
	/// <param name="inRoi">Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inPatternType">Type of LBP to produce.</param>
	/// <param name="outPatternHistogram">Histogram of LBP codes found in inImage.</param>
	/// <param name="outTextureImage">LBP map of input image.</param>
	AVL_FUNCTION void LinearBinaryPattern
	(
		const avl::Image&					inImage,			
		atl::Optional<avl::Region>			inRoi,				
		avl::LinearBinaryPatternType::Type	inPatternType,		
		avl::Histogram&						outPatternHistogram,
		avl::Image&							outTextureImage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Filters image with one of classic LAWS filter</summary>
	/// <param name="inImage">Input mono image.</param>
	/// <param name="inRoi">Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inVerticalFilter">Vertical part of filter. Default value: Level.</param>
	/// <param name="inHorizontalFilter">Horizontal part of filter. Default value: Edge.</param>
	/// <param name="inFilterSize">Filter window size.</param>
	/// <param name="inMacroBlockSize">Macroblock is used to gather generated texture energy. Default value: 15.</param>
	/// <param name="inNormalizeLocalContrast">Whether to normalize image before processing. Default value: False.</param>
	/// <param name="outTextureImage">Filtered image.</param>
	/// <param name="outTextureEnergyImage">Texture energy (AVG).</param>
	AVL_FUNCTION void LawsFilter
	(
		const avl::Image&					inImage,					
		const atl::Optional<avl::Region>&	inRoi,						
		const avl::LawsFilterType::Type		inVerticalFilter,			
		const avl::LawsFilterType::Type		inHorizontalFilter,			
		const avl::LawsFilterSize::Type		inFilterSize,				
		const int							inMacroBlockSize,			
		const bool							inNormalizeLocalContrast,	
		avl::Image&							outTextureImage,			
		avl::Image&							outTextureEnergyImage		
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inFlawlessBaseImage">Image of flawless texture used to devise Texemplars.</param>
	/// <param name="inFlawlessImages">ImageArray of flawless images (different than inFlawlessBaseImage) used to devise anomaly threshold.</param>
	/// <param name="inPatchSize">Size of patch, from witch Texemplars are devised. Default value: 5.</param>
	/// <param name="inOverlapStep">How much the patches should overlap. Default value: 1.</param>
	/// <param name="inPyramidLevels">How many levels of image pyramid to use. Default value: 4.</param>
	/// <param name="inTexemCount">How many Texemplars are expected to be in inspected texture. Default value: 12.</param>
	/// <param name="inMaxIterations">Maximal number of training procedure iterations. Default value: atl::NIL.</param>
	/// <param name="inUseGaussianPyramid">Whether to use gaussian, instead of normal, image pyramid.</param>
	/// <param name="outTextureModel">Trained TextureModel.</param>
	AVL_FUNCTION void CreateTextureModel
	(
		const avl::Image&						inFlawlessBaseImage,	
		const atl::Array<avl::Image>&			inFlawlessImages,		
		const int								inPatchSize,			
		const int								inOverlapStep,			
		const int								inPyramidLevels,		
		const int								inTexemCount,			
		atl::Optional<int>						inMaxIterations,		
		bool									inUseGaussianPyramid,	
		avl::TextureModel&						outTextureModel			
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks image for texture error using previously trained TextureModel.</summary>
	/// <param name="inImage">Texture image to be inspected.</param>
	/// <param name="inTextureModel">Trained texture model.</param>
	/// <param name="outAnomalyRegion">Region of anomalies found - result of merging results from each pyramid level.</param>
	/// <param name="diagInspectedImagePyramid">inImage pyramid used in inspection.</param>
	/// <param name="diagPerLevelDefectCandidates">Anomalies found on each pyramid level.</param>
	AVL_FUNCTION void InspectTexture
	(
		const avl::Image&						inImage,					
		const avl::TextureModel&				inTextureModel,				
		avl::Region&							outAnomalyRegion,			
		atl::Array<avl::Image>&					diagInspectedImagePyramid = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<atl::Array<avl::Region>>&	diagPerLevelDefectCandidates = atl::Dummy< atl::Array<atl::Array<avl::Region>> >(),
		atl::Array<avl::Image>&					diagProbMap = atl::Dummy< atl::Array<avl::Image> >()
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_TEXTUREANALYSIS_H

