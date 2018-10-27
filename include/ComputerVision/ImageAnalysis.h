//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_IMAGEANALYSIS_H
#define AVS_IMAGEANALYSIS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "Enums/ImageLocalTransformsEnums.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/MeasureObjectMethod.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Enums/RegionConnectivity.h"
#include "Enums/Selection.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "Enums/HSxColorModel.h"
#include "ComputerVision/1DEdgeDetection/ScanMapState.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"
#include "ComputerVision/ImageAnalysis/ScanFields.h"
#include "ComputerVision/ImageAnalysis/ShapeRegion.h"
#include "ComputerVision/GoldenTemplate/GrayGoldenTemplate.h"
#include "ComputerVision/GoldenTemplate/EdgeGoldenTemplate.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Profile/Profile.h"
#include "Region/Region.h"
#include "ComputerVision/GoldenTemplate2/GoldenTemplate2Model_Intensity.h"

namespace avl
{


	/// <summary>Detects corners using the Foerstner algorithm.</summary>
	/// <param name="inMonoImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inCornerQuality">Threshold on regularity of the corner. Default value: 0.8f.</param>
	/// <param name="inStrengthThreshold">Threshold on contrast of gradients forming the corner. Default value: 50.0f.</param>
	/// <param name="inLocalness">How big-scaled the corners should be. Default value: 3.</param>
	/// <param name="outPoints">Found corner points.</param>
	/// <param name="diagRoundnessImage">Calculated roundness for each input pixel.</param>
	/// <param name="diagStrengthImage">Calculated strength for each pixel.</param>
	AVL_FUNCTION void DetectCorners_Foerstner
	(
		const avl::Image&			inMonoImage,				
		atl::Optional<const avl::Region&>	inRoi,
		const float				inCornerQuality,			
		const float				inStrengthThreshold,		
		const int					inLocalness,				
		atl::Array<avl::Point2D>&	outPoints,					
		avl::Image&					diagRoundnessImage = atl::Dummy<avl::Image>(),			
		avl::Image&					diagStrengthImage = atl::Dummy<avl::Image>()			
	)
	THROW_AVL_ERRORS;

	namespace CornerResponseMethod
	{
		enum Type
		{
			KanadeTomasi,
			Harris
		};
	}


	/// <summary>Detects corners using corner response method.</summary>
	/// <param name="inMonoImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inCornerResponseMethod">Method for computing corner response.</param>
	/// <param name="inKernelSize">Method kernel size. Default value: 3.</param>
	/// <param name="inThreshold">Threshold for corner response value, between 0 and 255, default value is taken from SelectThresholdValue on outCornerResponseImage and entropy method. Default value: 50.0f.</param>
	/// <param name="outCorners">Found corner points.</param>
	AVL_FUNCTION void DetectCorners_CornerResponse
	(
		const avl::Image&							inMonoImage,			
		atl::Optional<const avl::Region&>			inRoi,
		const avl::CornerResponseMethod::Type		inCornerResponseMethod, 
		const int									inKernelSize,			
		atl::Optional<float>					inThreshold,			
		atl::Optional<atl::Array<avl::Point2D>&>	outCorners,				
		atl::Optional<avl::Image&>					outCornerResponseImage = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Verifies object presence by analysing pixel intensities in the specified region.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Location at which object presence is being checked.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inMinIntensity">Lowest acceptable value for the average pixel value. Default value: atl::NIL.</param>
	/// <param name="inMaxIntensity">Highest acceptable value for the average pixel value. Default value: atl::NIL.</param>
	/// <param name="inMinContrast">Lowest acceptable value for the standard deviation of the pixel values.</param>
	/// <param name="inMaxContrast">Highest acceptable value for the standard deviation of the pixel values. Default value: atl::NIL.</param>
	/// <param name="outIsPresent">Flag indicating whether the object is present or not.</param>
	/// <param name="outIntensity">Average pixel value.</param>
	/// <param name="outContrast">Standard deviation of the pixel values.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void CheckPresence_Intensity
	(
		const avl::Image&								inImage,
		const avl::ShapeRegion&							inRoi,						
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,				
		atl::Optional<float>						inMinIntensity,				
		atl::Optional<float>						inMaxIntensity,				
		float										inMinContrast,				
		atl::Optional<float>						inMaxContrast,				
		bool&											outIsPresent,				
		atl::Optional<float&>						outIntensity = atl::NIL,	
		atl::Optional<float&>						outContrast = atl::NIL,		
		atl::Optional<avl::ShapeRegion&>				outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Verifies object presence by analysing the amount of pixels that meet the specified criteria.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Location at which object presence is being checked.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inColorModel">Selected color model.</param>
	/// <param name="inBeginHue">Begin of the range of acceptable hue. Default value: 0.</param>
	/// <param name="inEndHue">End of the range of acceptable hue. Default value: 255.</param>
	/// <param name="inMinSaturation">Lowest acceptable saturation. Default value: 128.</param>
	/// <param name="inMaxSaturation">Highest acceptable saturation. Default value: atl::NIL.</param>
	/// <param name="inMinBrightness">Lowest acceptable brightness. Default value: 128.0f.</param>
	/// <param name="inMaxBrightness">Highest acceptable brightness. Default value: atl::NIL.</param>
	/// <param name="inMinAmount">Lowest acceptable fraction of pixels meeting the criteria. Default value: 0.5f.</param>
	/// <param name="inMaxAmount">Highest acceptable fraction of pixels meeting the criteria. Default value: 1.0f.</param>
	/// <param name="outIsPresent">Flag indicating whether the object is present or not.</param>
	/// <param name="outAmount">Fraction of pixels meeting the criteria.</param>
	/// <param name="outForeground">Region of pixels meeting the criteria.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	/// <param name="diagHsxImage">Image represented in chosen color model.</param>
	AVL_FUNCTION void CheckPresence_PixelAmount
	(
		const avl::Image&								inImage,
		const avl::ShapeRegion&							inRoi,						
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,				
		avl::HSxColorModel::Type						inColorModel,				
		int												inBeginHue,					
		int												inEndHue,					
		int												inMinSaturation,			
		atl::Optional<int>								inMaxSaturation,			
		atl::Optional<float>							inMinBrightness,			
		atl::Optional<float>							inMaxBrightness,			
		float										inMinAmount,				
		float										inMaxAmount,				
		bool&											outIsPresent,				
		atl::Optional<float&>						outAmount = atl::NIL,		
		atl::Optional<avl::Region&>						outForeground = atl::NIL,	
		atl::Optional<avl::ShapeRegion&>				outAlignedRoi = atl::NIL,	
		avl::Image&										diagHsxImage = atl::Dummy<avl::Image>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Verifies object presence by analysing the amount of edges in the specified region.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Location at which object presence is being checked.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inEdgeOperator">Selected gradient operator.</param>
	/// <param name="inEdgeMeasure">Selected method of gradient magnitude computation. Default value: Sum.</param>
	/// <param name="inEdgeScale">Scales the resulting gradient magnitudes. Default value: 1.</param>
	/// <param name="inMinStrength">Lowest acceptable edge magnitude. Default value: 15.</param>
	/// <param name="inMinAmount">Lowest acceptable fraction of pixels meeting the criteria. Default value: 0.2f.</param>
	/// <param name="inMaxAmount">Highest acceptable fraction of pixels meeting the criteria. Default value: 1.0f.</param>
	/// <param name="outIsPresent">Flag indicating whether the object is present or not.</param>
	/// <param name="outAmount">Fraction of pixels from meeting the criteria.</param>
	/// <param name="outForeground">Region of pixels meeting the criteria.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void CheckPresence_EdgeAmount
	(
		const avl::Image&								inImage,
		const avl::ShapeRegion&							inRoi,						
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,				
		avl::GradientMaskOperator::Type					inEdgeOperator,				
		avl::MagnitudeMeasure::Type						inEdgeMeasure,				
		const int										inEdgeScale,				
		int												inMinStrength,				
		float										inMinAmount,				
		float										inMaxAmount,				
		bool&											outIsPresent,				
		atl::Optional<float&>						outAmount = atl::NIL,		
		atl::Optional<avl::Region&>						outForeground = atl::NIL,	
		atl::Optional<avl::ShapeRegion&>				outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

	struct CompareGoldenTemplate_IntensityState : public BaseState
	{
		Image goldenImage;
		Region goldenImageEdgeRegion;
	};

	struct CompareGoldenTemplate_EdgesState : public BaseState
	{
		Region goldenEdges;
	};


	/// <summary>Creates golden template for application in CompareGoldenTemplate_Intensity filter.</summary>
	/// <param name="inTemplateImage">Template image containing an object with no defects.</param>
	/// <param name="inTemplateArea">Desired area to compare. Default value: atl::NIL.</param>
	/// <param name="inMask">Range of pixels to compare. Default value: atl::NIL.</param>
	/// <param name="inTemplateAreaAlignment">Alignment of template bounded by inTemplateArea. Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Minimum strength of edges on the golden image near which comparison is NOT performed. Default value: 10.0f.</param>
	/// <param name="inEdgeDilation">Defines for how far from the detected edges comparison is NOT performed. Default value: 1.</param>
	/// <param name="outGoldenTemplate">The output golden template structure.</param>
	/// <param name="diagCroppedImage">Cropped image to be analyzed.</param>
	/// <param name="diagCroppedEdgeRegion">Region of pixels that will not be compared.</param>
	/// <param name="diagEdgeRegion">Edges projected onto the input image.</param>
	AVL_FUNCTION void CreateGoldenTemplate_Intensity
	(
		const avl::Image&								inTemplateImage,			
		atl::Optional<const avl::Rectangle2D&>			inTemplateArea,				
		atl::Optional<const avl::Region&>				inMask,						
		atl::Optional<const avl::CoordinateSystem2D&>	inTemplateAreaAlignment,	 
		const float									inEdgeThreshold,  			
		const int										inEdgeDilation,	  			
		avl::GrayGoldenTemplate&						outGoldenTemplate,			
		avl::Image&										diagCroppedImage = atl::Dummy<avl::Image>(),			
		avl::Region&									diagCroppedEdgeRegion = atl::Dummy<avl::Region>(),		
		avl::Region&									diagEdgeRegion = atl::Dummy<avl::Region>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares an image with a template image considered to have no defects.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inGoldenTemplate">Golden gray template containing image of an object with no defects.</param>
	/// <param name="inGoldenTemplateAlignment">Adjusts the golden template to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inMaxDifference">Maximal allowed difference between corresponding pixels of the input and golden images. Default value: 20.0f.</param>
	/// <param name="inMinDefectRadius">Minimal radius of a defect. Default value: 1.</param>
	/// <param name="outDefects">Region of detected defects.</param>
	/// <param name="outDifferenceRegion">Region of pixels differing too much between the golden image and the input image.</param>
	/// <param name="outDefectsPresent">Flag indicating whether any defects were detected.</param>
	/// <param name="outEdgeRegion">Region of pixels that will not be compared.</param>
	/// <param name="outObjectPosition">Position of the object being compared.</param>
	AVL_FUNCTION void CompareGoldenTemplate_Intensity
	(
		const avl::Image&						inImage,		  			
		const avl::GrayGoldenTemplate&			inGoldenTemplate,	  		
		atl::Optional<const avl::CoordinateSystem2D&>	inGoldenTemplateAlignment,	
		float								inMaxDifference,  			
		int										inMinDefectRadius,			
		avl::Region&							outDefects,		  			
		avl::Region&							outDifferenceRegion,		
		bool&									outDefectsPresent,			
		avl::Region&							outEdgeRegion,				
		atl::Optional<avl::Rectangle2D&>		outObjectPosition = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares an image with a template image considered to have no defects.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inGoldenImage">Reference image containing no defects.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Minimum strength of edges on the golden image near which comparison is NOT performed. Default value: 10.0f.</param>
	/// <param name="inEdgeDilation">Defines for how far from the detected edges comparison is NOT performed. Default value: 1.</param>
	/// <param name="inStaticModel">Flag indicating whether model should be created only in the first iteration. Default value: True.</param>
	/// <param name="inMaxDifference">Maximal allowed difference between corresponding pixels of the input and golden images. Default value: 20.0f.</param>
	/// <param name="inMinDefectRadius">Minimal radius of a defect. Default value: 1.</param>
	/// <param name="outDefects">Region of detected defects.</param>
	/// <param name="outDifferenceRegion">Region of pixels differing too much between the golden image and the input image.</param>
	/// <param name="outDefectsPresent">Flag indicating whether any defects were detected.</param>
	/// <param name="outEdgeRegion">Region of pixels that will not be compared.</param>
	AVL_FUNCTION void AvsFilter_CompareGoldenTemplate_Intensity_Deprecated
	(
		CompareGoldenTemplate_IntensityState&	ioState,
		const avl::Image&						inImage,		  		
		const avl::Image&						inGoldenImage,	  		
		atl::Optional<const avl::Region&>		inRoi,
		float								inEdgeThreshold,  		
		int										inEdgeDilation,	  		
		bool									inStaticModel,	  		
		float								inMaxDifference,  		
		int										inMinDefectRadius,		
		avl::Region&							outDefects,		  		
		avl::Region&							outDifferenceRegion,	
		bool&									outDefectsPresent,		
		avl::Region&							outEdgeRegion			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates golden template for application in CompareGoldenTemplate_Edges filter.</summary>
	/// <param name="inTemplateImage">Template image containing an object with no defects.</param>
	/// <param name="inTemplateArea">Desired area to compare. Default value: atl::NIL.</param>
	/// <param name="inMask">Range of pixels to compare. Default value: atl::NIL.</param>
	/// <param name="inTemplateAreaAlignment">Alignment of template bounded by inTemplateArea. Default value: atl::NIL.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter (Auto = inStdDevX). Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected on the template image. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 15.0f.</param>
	/// <param name="outGoldenTemplate">The output golden template structure.</param>
	/// <param name="diagCroppedImage">Cropped image to be analyzed.</param>
	/// <param name="diagCroppedEdges">Edges found on the cropped image.</param>
	/// <param name="diagEdges">Edges projected onto the input image.</param>
	AVL_FUNCTION void CreateGoldenTemplate_Edges
	(
		const avl::Image&								inTemplateImage,			
		atl::Optional<const avl::Rectangle2D&>			inTemplateArea,				
		atl::Optional<const avl::Region&>				inMask,						
		atl::Optional<const avl::CoordinateSystem2D&>	inTemplateAreaAlignment,	
		float										inStdDevX,					
		atl::Optional<float>						inStdDevY,					
		float										inEdgeThreshold,			
		float										inEdgeHysteresis,			
		avl::EdgeGoldenTemplate&						outGoldenTemplate,			
		avl::Image&										diagCroppedImage = atl::Dummy<avl::Image>(),           
		avl::Region&									diagCroppedEdges = atl::Dummy<avl::Region>(),           
		avl::Region&									diagEdges = atl::Dummy<avl::Region>()					
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares image edges with the edges of a perfect template. Significant differences are considered defects.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inGoldenTemplate">Golden edge template containing image with no defects.</param>
	/// <param name="inGoldenTemplateAlignment">Adjusts the golden template to the position of the inspected object.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter (Auto = inStdDevX). Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected on the input image. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 15.0f.</param>
	/// <param name="inMaxDistance">Maximal allowed distance between corresponding edges on the input and golden image. Default value: 3.</param>
	/// <param name="outDefects">Region of detected defects.</param>
	/// <param name="outDefectsPresent">Flag indicating whether any defects were detected.</param>
	/// <param name="outMissingEdges">Edges present on the golden image that are missing on the input image.</param>
	/// <param name="outExcessiveEdges">Edges that are not present on the golden image.</param>
	/// <param name="outImageEdges">Edges on the input image.</param>
	/// <param name="outGoldenEdges">Edges on the golden image.</param>
	/// <param name="outMatchingEdges">Golden edges present on the input image.</param>
	/// <param name="outObjectPosition">Position of the object being compared.</param>
	AVL_FUNCTION void CompareGoldenTemplate_Edges
	(
		const avl::Image&					inImage,					
		const avl::EdgeGoldenTemplate&		inGoldenTemplate,			
		const avl::CoordinateSystem2D&		inGoldenTemplateAlignment,	
		float							inStdDevX,					
		atl::Optional<float>			inStdDevY,					
		float							inEdgeThreshold,			
		float							inEdgeHysteresis,			
		int									inMaxDistance,				
		avl::Region&						outDefects,					
		bool&								outDefectsPresent,			
		avl::Region&						outMissingEdges,			
		avl::Region&						outExcessiveEdges,			
		atl::Optional<avl::Region&>			outImageEdges = atl::NIL,	
		atl::Optional<avl::Region&>			outGoldenEdges = atl::NIL,	
		atl::Optional<avl::Region&>			outMatchingEdges = atl::NIL,
		atl::Optional<avl::Rectangle2D&>	outObjectPosition = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares image edges with the edges of a perfect template. Significant differences are considered defects.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inGoldenImage">Reference image containing no defects.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inStaticModel">Flag indicating whether the model should be created only in the first iteration. Default value: True.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter (Auto = inStdDevX). Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 15.0f.</param>
	/// <param name="inMaxDistance">Maximal allowed distance between corresponding edges on the input and golden image. Default value: 2.</param>
	/// <param name="outDefects">Region of detected defects.</param>
	/// <param name="outDefectsPresent">Flag indicating whether any defects were detected.</param>
	/// <param name="outMissingEdges">Edges present on the golden image that are missing on the input image.</param>
	/// <param name="outExcessiveEdges">Edges that are not present on the golden image.</param>
	/// <param name="outImageEdges">Edges on the input image.</param>
	/// <param name="outGoldenEdges">Edges on the golden image.</param>
	/// <param name="outMatchingEdges">Golden edges present on the input image.</param>
	AVL_FUNCTION void AvsFilter_CompareGoldenTemplate_Edges_Deprecated
	(
		CompareGoldenTemplate_EdgesState&	ioState,
		const avl::Image&					inImage,					
		const avl::Image&					inGoldenImage,				
		atl::Optional<const avl::Region&>	inRoi,
		bool								inStaticModel,				
		float							inStdDevX,					
		atl::Optional<float>			inStdDevY,					
		float							inEdgeThreshold,			
		float							inEdgeHysteresis,			
		int									inMaxDistance,			
		avl::Region&						outDefects,					
		bool&								outDefectsPresent,			
		avl::Region&						outMissingEdges,			
		avl::Region&						outExcessiveEdges,			
		atl::Optional<avl::Region&>			outImageEdges = atl::NIL,	
		atl::Optional<avl::Region&>			outGoldenEdges = atl::NIL,	
		atl::Optional<avl::Region&>			outMatchingEdges = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>(Pre)computes image sampling locations used by MeasureObjectWidth function.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the scan image.</param>
	/// <param name="inScanField">Field in which scans will be performed.</param>
	/// <param name="inScanFieldAlignment">Adjusts the scan field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">Number of scans to be performed. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the scan area. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outAlignedScanField">Field in which the scans will be performed.</param>
	/// <param name="diagScanSegments">Array of scan segments.</param>
	AVL_FUNCTION void CreateMeasurementMap
	(
		const avl::ImageFormat&			inImageFormat,			
		const avl::SegmentScanField&	inScanField,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanFieldAlignment,
		int								inScanCount,			
		int								inScanWidth,			
		avl::InterpolationMethod::Type	inImageInterpolation,	
		atl::Array<avl::ScanMap>&		outMeasurementMap,
		atl::Optional<avl::SegmentScanField&>	outAlignedScanField = atl::NIL,	
		atl::Array<avl::Segment2D>&		diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the width of an object using stripe detection.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMeasurementMap">Input measurement map.</param>
	/// <param name="inStripeScanParams">Parameters controlling the object stripe extraction process.</param>
	/// <param name="inMeasureMethod">Method used to measure the object.</param>
	/// <param name="inStripeSelection">Selection mode of edges of the object. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="inOutlierCount">Determines how many outlying points are rejected before the width is measured.</param>
	/// <param name="outObjectWidth">Width of the object.</param>
	/// <param name="outSegment1">First edge of the object.</param>
	/// <param name="outSegment2">Second edge of the object.</param>
	/// <param name="diagPoints1">Detected edge points on the first side.</param>
	/// <param name="diagPoints2">Detected edge points on the second side.</param>
	AVL_FUNCTION void MeasureObjectWidth
	(
		const avl::Image&				inImage,									
		const atl::Array<avl::ScanMap>&	inMeasurementMap,							
		const avl::StripeScanParams&	inStripeScanParams,							
		avl::MeasureObjectMethod::Type	inMeasureMethod,							
		avl::Selection::Type			inStripeSelection,							
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,				
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,				
		int									inOutlierCount,							
		atl::Conditional<float>&		outObjectWidth,							
		atl::Conditional<avl::Segment2D>&	outSegment1,							
		atl::Conditional<avl::Segment2D>&	outSegment2,							
		atl::Array<avl::Point2D>&			diagPoints1 = atl::Dummy< atl::Array<avl::Point2D> >(),							
		atl::Array<avl::Point2D>&			diagPoints2 = atl::Dummy< atl::Array<avl::Point2D> >()								
	)
	THROW_AVL_ERRORS;

	namespace LinePeakDetectionMethod
	{
		enum Type
		{
			FirstBrightPixel,
			LastBrightPixel,
			MaximalPixel,
			BrightRegionCenter,
			BrightMassCenter
		};
	}


	/// <summary>Finds line peaks on an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDetectionMethod">Method used to determine exact line peak position. Default value: MaximalPixel.</param>
	/// <param name="inThreshold">Minimal value of a bright pixel. Default value: 128.0f.</param>
	/// <param name="outLinePeakPoints">Line peak positions.</param>
	/// <param name="diagLinePeakProfile">Profile of line peak positions.</param>
	AVL_FUNCTION void DetectLinePeak
	(
		const avl::Image&				inImage,				
		avl::LinePeakDetectionMethod::Type	inDetectionMethod,	
		const float					inThreshold,			
		atl::Array<atl::Conditional<avl::Point2D> >&	outLinePeakPoints,	
		avl::Profile&					diagLinePeakProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds line peaks on an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inStdDev">Standard deviation of the gaussian kernel. Default value: 4.0f.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 2.0f.</param>
	/// <param name="inThreshold">Minimal value of a bright pixel. Default value: 128.0f.</param>
	/// <param name="outLinePeakPoints">Line peak positions.</param>
	/// <param name="diagLinePeakProfile">Profile of line peak positions.</param>
	AVL_FUNCTION void DetectLinePeak_Gauss
	(
		const avl::Image&			inImage,				
		const float				inStdDev,				
		const float				inKernelRelativeSize,	
		const float				inThreshold,			
		atl::Array<atl::Conditional<avl::Point2D> >&	outLinePeakPoints,	
		avl::Profile&				diagLinePeakProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Extract GT2 model fields</summary>
	AVL_FUNCTION void InspectModelGoldenTemplate2_Intensity
	(
		const avl::GoldenTemplate2Model_Intensity& inModel,
		atl::Array<atl::String>&			outDiagFeatureNames,
		atl::Array<avl::Image>&				outBrightImages,
		atl::Array<avl::Image>&				outDarkImages,
		atl::Array<int>&				outBrightThresholds,
		atl::Array<int>&				outDarkThresholds,
		avl::Rectangle2D&		outCroppingRectangle,
		avl::Region&				outObjectRoi,
		avl::Region&				outErodedObjectRoi,
		atl::Array<avl::Image>&				outDiagMaxImages,
		atl::Array<avl::Image>&				outDiagMinImages,
		atl::Array<avl::Location>&			outDiagBrightLocations,
		atl::Array<avl::Location>&			outDiagDarkLocations
	)
	THROW_AVL_ERRORS;

	/// <summary>Create a model to be used with CompareGoldenTemplate2_Intensity filter</summary>
	/// <param name="inMaxDisplacement">Error in object positioning. If in doubt, it is better to set this value too high. If set too low, subtle defects won't be detected, or no defects may not be detected at all. High values may impair detection of small defects, especially near edges. Default value: 2.</param>
	/// <param name="inDeviationMultiplier">Default value: 1.2f.</param>
	/// <param name="inIdentityFeature">Default value: True.</param>
	/// <param name="inSmoothedFeatures">Default value: True.</param>
	/// <param name="inGradientFeatures">Default value: True.</param>
	/// <param name="inDogFeatures">Default value: True.</param>
	/// <param name="inStddevFeatures">Default value: True.</param>
	AVL_FUNCTION void CreateGoldenTemplate2_Intensity
	(
		const atl::Array<avl::Image>& inImages,
		const avl::Region& inObjectMask,
		const int inMaxDisplacement,	
		const float inDeviationMultiplier,
		bool inIdentityFeature,
		bool inSmoothedFeatures,
		bool inGradientFeatures,
		bool inDogFeatures,
		bool inStddevFeatures,
		avl::GoldenTemplate2Model_Intensity& outModel
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares an image with a template image considered to have no defects.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSensitivityA">Usually influences small, distinctive defects. Default value: 1.0f.</param>
	/// <param name="inSensitivityB">Usually influences bigger, extensive defects. Default value: 0.95f.</param>
	/// <param name="inIdentityFeature">Default value: True.</param>
	/// <param name="inSmoothedFeatures">Default value: True.</param>
	/// <param name="inGradientFeatures">Default value: True.</param>
	/// <param name="inDogFeatures">Default value: True.</param>
	/// <param name="inStddevFeatures">Default value: True.</param>
	/// <param name="diagProcessedInput">Array of images of features.</param>
	/// <param name="diagDarkDefects">For each feature, defects detected - below lower threshold.</param>
	/// <param name="diagBrightDefects">For each feature, defects detected - above higher threshold.</param>
	AVL_FUNCTION void CompareGoldenTemplate2_Intensity
	(
		const avl::GoldenTemplate2Model_Intensity& inModel,
		const avl::Image& inImage,
		float inSensitivityA, 
		float inSensitivityB, 
		bool inIdentityFeature,
		bool inSmoothedFeatures,
		bool inGradientFeatures,
		bool inDogFeatures,
		bool inStddevFeatures,
		avl::Region& outDefects,
		atl::Optional<atl::Array<avl::Image>&> diagProcessedInput = atl::NIL, 
		atl::Optional<atl::Array<avl::Image>&> diagDarkDefects = atl::NIL, 
		atl::Optional<atl::Array<avl::Image>&> diagBrightDefects = atl::NIL 
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	typedef avl::ScanMapArrayState MeasureObjectWidthState;


	/// <summary>Measures the width of an object using stripe detection.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScanField">Field in which measurement scans are performed.</param>
	/// <param name="inScanFieldAlignment">Adjusts the scan field to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanCount">Number of scans to be performed. Default value: 5.</param>
	/// <param name="inScanWidth">Width of each single scan. Default value: 5.</param>
	/// <param name="inImageInterpolation">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the object stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Dark MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inMeasureMethod">Method used to measure the object.</param>
	/// <param name="inStripeSelection">Selection mode of edges of the object.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inOutlierSuppression">Selects a method for ignoring incorrectly detected points. Default value: atl::NIL.</param>
	/// <param name="inOutlierCount">Determines how many points are not count when object width is measured.</param>
	/// <param name="outObjectWidth">Width of the object.</param>
	/// <param name="outSegment1">First edge of the object.</param>
	/// <param name="outSegment2">Second edge of the object.</param>
	/// <param name="outAlignedScanField">Field in which the scans are performed.</param>
	/// <param name="diagScanSegments">Segments along which the scans are performed.</param>
	/// <param name="diagPoints1">Detected edge points on the first side.</param>
	/// <param name="diagPoints2">Detected edge points on the second side.</param>
	AVL_FUNCTION void AvsFilter_MeasureObjectWidth
	(
		MeasureObjectWidthState&				ioState,
		const avl::Image&						inImage,							
		const avl::SegmentScanField&			inScanField,						
		atl::Optional<const avl::CoordinateSystem2D&>	inScanFieldAlignment,		
		int										inScanCount,						
		int										inScanWidth,						
		avl::InterpolationMethod::Type			inImageInterpolation,				
		const avl::StripeScanParams&			inStripeScanParams,					
		avl::MeasureObjectMethod::Type			inMeasureMethod,					
		avl::Selection::Type					inStripeSelection,					
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,				
		atl::Optional<avl::MEstimator::Type>	inOutlierSuppression,				
		int										inOutlierCount,						
		atl::Conditional<float>&			outObjectWidth,						
		atl::Conditional<avl::Segment2D>&		outSegment1,						
		atl::Conditional<avl::Segment2D>&		outSegment2,						
		atl::Optional<avl::SegmentScanField&>	outAlignedScanField = atl::NIL,		
		atl::Array<avl::Segment2D>&				diagScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >(),					
		atl::Array<avl::Point2D>&				diagPoints1 = atl::Dummy< atl::Array<avl::Point2D> >(),						
		atl::Array<avl::Point2D>&				diagPoints2 = atl::Dummy< atl::Array<avl::Point2D> >()							
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_IMAGEANALYSIS_H

