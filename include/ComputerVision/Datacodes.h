//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DATACODES_H
#define AVL_DATACODES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Array.h"
#include "ATL/Optional.h"
#include "Image/Image.h"
#include "Region/Region.h"
#include "Path/Path.h"
#include "AVLCommon/MatrixTypes.h"
#include "Enums/DataMatrixCodeType.h"
#include "ComputerVision/Datacodes/DataMatrix.h"
#include "ComputerVision/Datacodes/QRCode.h"
#include "Enums/Polarity.h"
#include "Enums/DataMatrixGapSize.h"
#include "Enums/DataMatrixDetectionMethod.h"
#include "Datacodes/DataCode.h"

namespace avl
{


	/// <summary>Detects and recognizes a single QR code on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inUnitSize">Estimated size of a code unit in pixels. Default value: atl::NIL.</param>
	/// <param name="inContrast">Difference between brightest and darkest pixel within the code. Default value: atl::NIL.</param>
	/// <param name="inPatternQuality">Quality of the code from 1 (extremely deformed) to 3 (perfect). Default value: atl::NIL.</param>
	/// <param name="inCodeDirection">Direction of one of the axes of the code. Default value: atl::NIL.</param>
	/// <param name="inMinLineMagnitude">Strength of an edge within the code; default depends on parameters. Default value: atl::NIL.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadSingleQRCode
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Rectangle2D&>			inRoi,
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		atl::Optional<float>			inUnitSize, 
		atl::Optional<float>			inContrast, 
		atl::Optional<int>					inPatternQuality, 
		atl::Optional<float>			inCodeDirection, 
		atl::Optional<float>			inMinLineMagnitude, 
		atl::Conditional<avl::QRCode>&		outQRCode,
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL 
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes all QR codes on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inResultsExpected">How many results we expect, 0 if as many as possible. Default value: 1.</param>
	/// <param name="inUnitSize">Estimated size of a code unit in pixels. Default value: atl::NIL.</param>
	/// <param name="inContrast">Difference between brightest and darkest pixel within the code. Default value: atl::NIL.</param>
	/// <param name="inPatternQuality">Quality of the code from 1 (extremely deformed) to 3 (perfect). Default value: atl::NIL.</param>
	/// <param name="inCodeDirection">Direction of one of the axes of the code. Default value: atl::NIL.</param>
	/// <param name="inMinLineMagnitude">Strength of an edge within the code; default depends on parameters. Default value: atl::NIL.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadMultipleQRCodes
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Rectangle2D&>			inRoi,
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		int									inResultsExpected, 
		atl::Optional<float>			inUnitSize, 
		atl::Optional<float>			inContrast, 
		atl::Optional<int>					inPatternQuality, 
		atl::Optional<float>			inCodeDirection, 
		atl::Optional<float>			inMinLineMagnitude, 
		atl::Array<avl::QRCode>&			outQRCodes,
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL 
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a matrix of 0 or 1 values to a text in accordance to how QR codes are encoded.</summary>
	/// <param name="inBinaryMatrix">Square matrix of zero (black) and nonzero (white) values.</param>
	/// <param name="outDecodedText">Decoded text, if matrix represents valid code.</param>
	AVL_FUNCTION void DecodeQRCode
	(
		const avl::Matrix&				inBinaryMatrix, 
		atl::Conditional<atl::String>&	outDecodedText	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds candidates for Data Matrix codes in the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inAllowRectangular">Enables detecting rectangular Data Matrices. Default value: False.</param>
	/// <param name="outDataMatrixPositions">Array of possible positions of Data Matrices.</param>
	AVL_FUNCTION void DetectDataMatrices_Deprecated
	(
		const avl::Image&					inImage,				
		atl::Optional<const avl::Region&>	inRoi,					
		bool								inAllowRectangular,		
		atl::Array<avl::Rectangle2D>&		outDataMatrixPositions	
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a matrix of 0 or 1 values to a text in accordance to how DataMatrix codes are encoded.</summary>
	/// <param name="inMatrixValues">Matrix of binary values.</param>
	/// <param name="outText">Decoded text or nothing if decoding failed.</param>
	/// <param name="outType">DataMatrix code type.</param>
	AVL_FUNCTION void DecodeDataMatrix
	(
		const avl::Matrix&								inMatrixValues, 
		atl::Conditional<atl::String>&					outText,		
		atl::Conditional<avl::DataMatrixType::Type>&	outType			
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts information from the first correct Data Matrix code from among the specified positions.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDataMatrixPositions">Candidates for Data Matrix.</param>
	/// <param name="inCodeColumnCount">Optional width of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="inCodeRowCount">Optional height of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="diagValues">Image of decoded Data Matrix used by the reading algorithm.</param>
	AVL_FUNCTION void RecognizeSingleDataMatrix_Deprecated
	(
		const avl::Image&					inImage,				
		const atl::Array<avl::Rectangle2D>&	inDataMatrixPositions,	
		avl::DataMatrixCodeType::Type		inCodeType,
		atl::Optional<int>					inCodeColumnCount,		
		atl::Optional<int>					inCodeRowCount,			
		atl::Conditional<avl::DataMatrix>&	outDataMatrix,
		atl::Conditional<avl::Image>&		diagValues = atl::Dummy< atl::Conditional<avl::Image> >()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts information from multiple Data Matrix codes located at the specified positions.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDataMatrixPositions">Candidates for Data Matrices.</param>
	/// <param name="inCodeColumnCount">Optional width of Data Matrix. Default value: atl::NIL.</param>
	/// <param name="inCodeRowCount">Optional height of Data Matrix. Default value: atl::NIL.</param>
	/// <param name="diagValues">Images of decoded Data Matrices used by the reading algorithm.</param>
	AVL_FUNCTION void RecognizeMultipleDataMatrices_Deprecated
	(
		const avl::Image&							inImage,				
		const atl::Array<avl::Rectangle2D>&			inDataMatrixPositions,	
		avl::DataMatrixCodeType::Type				inCodeType,
		atl::Optional<int>							inCodeColumnCount,		
		atl::Optional<int>							inCodeRowCount,			
		atl::Array<avl::DataMatrix>&				outDataMatrices,
		atl::Array<atl::Conditional<avl::Image> >&	diagValues = atl::Dummy< atl::Array<atl::Conditional<avl::Image> > >()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes a single Data Matrix code.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inAllowRectangular">Enables detecting rectangular Data Matrices. Default value: False.</param>
	/// <param name="inCodeColumnCount">Optional width of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="inCodeRowCount">Optional height of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	/// <param name="diagValues">Image of decoded Data Matrix used by the reading algorithm.</param>
	AVL_FUNCTION void ReadSingleDataMatrix_Deprecated
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Rectangle2D&>			inRoi,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		bool								inAllowRectangular,	
		avl::DataMatrixCodeType::Type		inCodeType,
		atl::Optional<int>					inCodeColumnCount,	
		atl::Optional<int>					inCodeRowCount,		
		atl::Conditional<avl::DataMatrix>&	outDataMatrix,
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL, 
		atl::Conditional<avl::Image>&		diagValues = atl::Dummy< atl::Conditional<avl::Image> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes multiple Data Matrix codes.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inAllowRectangular">Enables detecting rectangular Data Matrices. Default value: False.</param>
	/// <param name="inCodeColumnCount">Optional width of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="inCodeRowCount">Optional height of a Data Matrix. Default value: atl::NIL.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	/// <param name="diagValues">Images of decoded Data Matrices used by the reading algorithm.</param>
	AVL_FUNCTION void ReadMultipleDataMatrices_Deprecated
	(
		const avl::Image&					inImage,				
		atl::Optional<const avl::Rectangle2D&>			inRoi,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		bool								inAllowRectangular,		
		avl::DataMatrixCodeType::Type		inCodeType,
		atl::Optional<int>					inCodeColumnCount,		
		atl::Optional<int>					inCodeRowCount,			
		atl::Array<avl::DataMatrix>&		outDataMatrices,
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL, 
		atl::Array<atl::Conditional<avl::Image> >&	diagValues = atl::Dummy< atl::Array<atl::Conditional<avl::Image> > >()		
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxSlant">Default value: 30.0f.</param>
	AVL_FUNCTION void FinderPatternBoundingRectangle
	(
		const avl::Region&					inRegion,
		float							inMaxSlant,
		atl::Conditional<avl::Rectangle2D>&	outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxSlant">Default value: 30.0f.</param>
	AVL_FUNCTION void FinderPatternOutline
	(
		const avl::Region&					inRegion,
		float							inMaxSlant,
		atl::Conditional<avl::Path>&		outOutline,
		atl::Conditional<atl::Array<avl::Point2D> >&	outCornerPoints
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxSlant">Default value: 30.0f.</param>
	/// <param name="inFittedLineOrientationTolerance">Default value: 10.0f.</param>
	AVL_FUNCTION void FinderPatternOutline_Contours
	(
		const avl::Region&					inRegion,
		float							inMaxSlant,
		float							inFittedLineOrientationTolerance,
		atl::Conditional<avl::Path>&		outOutline,
		atl::Conditional<atl::Array<avl::Point2D> >&	outCornerPoints,
		atl::Conditional<avl::Path>&		outFittedOutline,
		atl::Array<atl::Array<avl::Point2D> >&	diagEdgePoints = atl::Dummy< atl::Array<atl::Array<avl::Point2D> > >()
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxSlant">Default value: 30.0f.</param>
	AVL_FUNCTION void FinderPatternOutline_Fitting
	(
		const avl::Region&								inRegion,
		float										inMaxSlant,
		atl::Conditional<avl::Path>&					outOutline,
		atl::Conditional<atl::Array<avl::Point2D> >&	outCornerPoints
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inPointCount">Default value: 3.</param>
	/// <param name="inMinDistance">Default value: 10.0f.</param>
	AVL_FUNCTION void GetExactlyNFurthestPoints
	(
		const avl::Region&			inRegion,
		const avl::Point2D&			inReferencePoint,
		const int					inPointCount,
		const float				inMinDistance,
		atl::Array<avl::Point2D>&	outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void DetectBorder
	(
		const avl::Image&			inImage,
		atl::Array<avl::Line2D>&	outLines,
		atl::Conditional<avl::Point2D>&	outTopLeft,
		atl::Conditional<avl::Point2D>&	outTopRight,
		atl::Conditional<avl::Point2D>&	outBottomLeft,
		atl::Conditional<avl::Point2D>&	outBottomRight
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes one Data Matrix code.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Coordinate system for the region of interest. Default value: atl::NIL.</param>
	/// <param name="inCodeParams">Specification of codes that can be detected.</param>
	/// <param name="inDetectionParams">Specification of the way the codes are being detected.</param>
	/// <param name="outCandidates">Diagnostic information about detection results.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadSingleDataMatrixCode
	(
		const avl::Image&								inImage,					
		atl::Optional<const avl::Rectangle2D&>			inRoi,						
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,				
		const avl::DataMatrixCodeParams&				inCodeParams,				
		const avl::DataMatrixDetectionParams&			inDetectionParams,			

		atl::Conditional<avl::DataCode>&				outDataMatrixCode,
		atl::Array<avl::Path>&							outCandidates,				
		atl::Optional<avl::Rectangle2D&>				outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes several Data Matrix codes.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Coordinate system for the region of interest. Default value: atl::NIL.</param>
	/// <param name="inCodeParams">Specification of codes that can be detected.</param>
	/// <param name="inDetectionParams">Specification of the way the codes are being detected.</param>
	/// <param name="inMaxCodeCount">Maximum number of codes to be found. Default value: 2.</param>
	/// <param name="inAllowMultipleScales">Specifies whether codes of different module sizes are expected. Default value: False.</param>
	/// <param name="outCandidates">Diagnostic information about detection results.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadMultipleDataMatrixCodes
	(
		const avl::Image&								inImage,					
		atl::Optional<const avl::Rectangle2D&>			inRoi,						
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,				
		const avl::DataMatrixCodeParams&				inCodeParams,				
		const avl::DataMatrixDetectionParams&			inDetectionParams,			
		int												inMaxCodeCount,				
		bool											inAllowMultipleScales,		

		atl::Array<avl::DataCode>&						outDataMatrixCodes,
		atl::Array<avl::Path>&							outCandidates,				
		atl::Optional<avl::Rectangle2D&>				outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes one Data Matrix code.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Coordinate system for the region of interest. Default value: atl::NIL.</param>
	/// <param name="inCodeParams">Specification of codes that can be found.</param>
	/// <param name="inContrastThreshold">Minimal difference between dark and bright modules. Default value: 20.</param>
	/// <param name="inFlags">Undocumented advanced tweaks for difficult cases.</param>
	/// <param name="outCandidates">Diagnostic information about detection results.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadSingleDataMatrixCode_Deprecated
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Rectangle2D&>	inRoi,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		const avl::DataMatrixCodeParams&		inCodeParams,			
		int										inContrastThreshold,	
		int										inFlags,				

		atl::Conditional<avl::DataCode>&		outDataMatrixCode,
		atl::Array<avl::Path>&					outCandidates,			
		atl::Optional<avl::Rectangle2D&>		outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes several Data Matrix codes.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Coordinate system for the region of interest. Default value: atl::NIL.</param>
	/// <param name="inCodeParams">Specification of codes that can be found.</param>
	/// <param name="inMaxCodeCount">Maximum number of codes to be found. Default value: 2.</param>
	/// <param name="inContrastThreshold">Minimal difference between dark and bright modules. Default value: 20.</param>
	/// <param name="inAllowMultipleScales">Specifies whether codes of different module sizes are expected. Default value: False.</param>
	/// <param name="inFlags">Undocumented advanced tweaks for difficult cases.</param>
	/// <param name="outCandidates">Diagnostic information about detection results.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	AVL_FUNCTION void ReadMultipleDataMatrixCodes_Deprecated
	(
		const avl::Image&						inImage,				
		atl::Optional<const avl::Rectangle2D&>	inRoi,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		const avl::DataMatrixCodeParams&		inCodeParams,			
		int										inMaxCodeCount,			
		int										inContrastThreshold,	
		bool									inAllowMultipleScales,	
		int										inFlags,				

		atl::Array<avl::DataCode>&				outDataMatrixCodes,
		atl::Array<avl::Path>&					outCandidates,			
		atl::Optional<avl::Rectangle2D&>		outAlignedRoi = atl::NIL	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_DATACODES_H

