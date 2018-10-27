//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_BARCODES_H
#define AVL_BARCODES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Image/Image.h"
#include "Geometry/Geometry.h"
#include "Profile/Profile.h"
#include "ComputerVision/Barcodes/BarcodeGrades.h"
#include "Enums/BarcodesGrading.h"

namespace avl
{


	namespace BarcodeFormat
	{
		enum Type
		{
			EAN13,
			EAN13Addon2,
			EAN13Addon5,
			EAN8,
			EAN8Addon2,
			EAN8Addon5,
			UPCA,
			UPCAAddon2,
			UPCAAddon5,
			UPCE,
			UPCEAddon2,
			UPCEAddon5,
			CODE128,
			CODE39,
			CODE93,
			Interleaved2of5,
			Pharmacode,
			PharmacodeInversed,
		};
	}


	/// <summary>Determines the position of a single barcode on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="inMinGradientLength">Minimal gradient length of edge pixels used for detecting barcodes. Default value: 8.0f.</param>
	/// <param name="inBaseBarWidth">Estimated width of the thinnest bar. Default value: 3.</param>
	/// <param name="inScanCount">Number of scan lines used in detecting barcode. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the single scan. Default value: 5.</param>
	/// <param name="inMinStrength">Minimal strength of an extracted edge. Default value: 5.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the profile extracted in each scan. Default value: 0.25f.</param>
	/// <param name="outBarcodePosition">Position of the found barcode.</param>
	/// <param name="diagGradientImage">Image of gradient directions.</param>
	/// <param name="diagBarcodeCandidates">Places with high gradient values that are further investigated.</param>
	AVL_FUNCTION void DetectSingleBarcode
	(
		const avl::Image&					inImage, 
		atl::Optional<avl::BarcodeFormat::Type>	inFormat,		
		float								inMinGradientLength,
		int									inBaseBarWidth,		
		int									inScanCount,		
		const int							inScanWidth,		
		const float							inMinStrength,		
		const float							inSmoothingStdDev,	
		atl::Conditional<avl::Rectangle2D>&	outBarcodePosition,	
		avl::Image&							diagGradientImage = atl::Dummy<avl::Image>(),	
		atl::Array<avl::Rectangle2D>&		diagBarcodeCandidates = atl::Dummy< atl::Array<avl::Rectangle2D> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Determines the positions of multiple barcodes on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="inMinGradientLength">Minimal gradient length of edge pixels used for detecting barcodes. Default value: 8.0f.</param>
	/// <param name="inBaseBarWidth">Estimated width of the thinnest bar. Default value: 3.</param>
	/// <param name="inScanCount">Number of scan lines used in detecting barcode. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the single scan. Default value: 5.</param>
	/// <param name="inMinStrength">Minimal strength of an extracted edge. Default value: 5.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the profile extracted in each scan. Default value: 0.25f.</param>
	/// <param name="outBarcodePositions">Positions of the found barcodes.</param>
	/// <param name="diagGradientImage">Image of gradient directions.</param>
	/// <param name="diagBarcodeCandidates">Places with high gradient values that are further investigated.</param>
	AVL_FUNCTION void DetectMultipleBarcodes
	(
		const avl::Image&				inImage, 
		atl::Optional<avl::BarcodeFormat::Type>	inFormat,	
		float						inMinGradientLength,
		int								inBaseBarWidth,		
		int								inScanCount,		
		const int						inScanWidth,		
		const float					inMinStrength,		
		const float					inSmoothingStdDev,	
		atl::Array<avl::Rectangle2D>&	outBarcodePositions,
		avl::Image&						diagGradientImage = atl::Dummy<avl::Image>(),	
		atl::Array<avl::Rectangle2D>&	diagBarcodeCandidates = atl::Dummy< atl::Array<avl::Rectangle2D> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts information from a barcode located on the input image at a given position.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBarcodePosition">Position of the input image in which the barcode is located.</param>
	/// <param name="inBarcodePositionAlignment">Adjusts the barcode rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inBarcodeFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="inScanCount">Number of parallel scans run until first successful read. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the single scan. Default value: 5.</param>
	/// <param name="inMinStrength">Minimal strength of an extracted edge. Default value: 5.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the profile extracted in each scan. Default value: 0.25f.</param>
	/// <param name="outDecodedText">Decoded barcode text or nothing if all of the scans failed.</param>
	/// <param name="outBarcodeFormat">Decoded barcode format or nothing if all of the scans failed.</param>
	/// <param name="diagScheduledScanSegments">Scheduled scan segments.</param>
	AVL_FUNCTION void RecognizeBarcode
	(
		const avl::Image&								inImage,
		const avl::Rectangle2D&							inBarcodePosition,			
		atl::Optional<const avl::CoordinateSystem2D&>	inBarcodePositionAlignment,	
		atl::Optional<avl::BarcodeFormat::Type>			inBarcodeFormat,			
		const int										inScanCount,				
		const int										inScanWidth,				
		const float									inMinStrength,				
		const float									inSmoothingStdDev,			
		atl::Conditional<atl::String>&					outDecodedText,				
		atl::Conditional<avl::BarcodeFormat::Type>&		outBarcodeFormat,			
		avl::Rectangle2D&								outAlignedBarcodePosition,
		atl::Array<avl::Segment2D>&						diagScheduledScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an array of bar widths to sequence of digits or text in accordance to the selected barcode standard.</summary>
	/// <param name="inBarWidths">Widths of the barcode bars (starting with width of the black bar).</param>
	/// <param name="inBarcodeFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="outDecodedText">Decoded barcode text or nothing if decoding failed.</param>
	/// <param name="outBarcodeFormat">Decoded barcode format or nothing if decoding failed.</param>
	AVL_FUNCTION void DecodeBarcode
	(
		const atl::Array<float>&			inBarWidths,		
		atl::Optional<avl::BarcodeFormat::Type>	inBarcodeFormat,	
		atl::Conditional<atl::String>&			outDecodedText,		
		atl::Conditional<avl::BarcodeFormat::Type>&	outBarcodeFormat	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes a single barcode on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the region of interest to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inBarcodeFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="inMinGradientLength">Minimal gradient length of edge pixels used for detecting barcodes. Default value: 8.0f.</param>
	/// <param name="inBaseBarWidth">Estimated width of the thinnest bar. Default value: 3.</param>
	/// <param name="inDetectionScanCount">Number of scan lines used in detecting barcode. Default value: 5.</param>
	/// <param name="inReadingScanCount">Number of parallel scans run until first successful read. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the single scan. Default value: 5.</param>
	/// <param name="inMinStrength">Minimal strength of an extracted edge. Default value: 5.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the profile extracted in each scan. Default value: 0.25f.</param>
	/// <param name="outBarcodePosition">Position of the found barcode.</param>
	/// <param name="outDecodedText">Decoded barcode content or nothing if all of the scans failed.</param>
	/// <param name="outBarcodeFormat">Decoded barcode format or nothing if all of the scans failed.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	/// <param name="diagGradientImage">Image of gradient directions.</param>
	/// <param name="diagBarcodeCandidates">Places with high gradient values that are further investigated.</param>
	/// <param name="diagScheduledScanSegments">Scheduled scan segments.</param>
	AVL_FUNCTION void ReadSingleBarcode
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Rectangle2D&>			inRoi,			
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		atl::Optional<avl::BarcodeFormat::Type>			inBarcodeFormat,
		float							inMinGradientLength,		
		int									inBaseBarWidth,				
		int									inDetectionScanCount,		
		const int							inReadingScanCount,			
		const int							inScanWidth,				
		const float						inMinStrength,				
		const float						inSmoothingStdDev,			
		atl::Conditional<avl::Rectangle2D>&	outBarcodePosition,			
		atl::Conditional<atl::String>&		outDecodedText,				
		atl::Conditional<avl::BarcodeFormat::Type>&	outBarcodeFormat,	
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL,	
		avl::Image&							diagGradientImage = atl::Dummy<avl::Image>(),			
		atl::Array<avl::Rectangle2D>&		diagBarcodeCandidates = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<avl::Segment2D>&			diagScheduledScanSegments = atl::Dummy< atl::Array<avl::Segment2D> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects and recognizes multiple barcodes on the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inRoiAlignment">Adjusts the barcode rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inBarcodeFormat">Format of the barcode. Default value: EAN13.</param>
	/// <param name="inMinGradientLength">Minimal gradient length of edge pixels used for detecting barcodes. Default value: 8.0f.</param>
	/// <param name="inBaseBarWidth">Estimated width of the thinnest bar. Default value: 3.</param>
	/// <param name="inDetectionScanCount">Number of scan lines used in detecting barcode. Default value: 5.</param>
	/// <param name="inReadingScanCount">Number of parallel scans run until first successful read. Default value: 5.</param>
	/// <param name="inScanWidth">Width of the single scan. Default value: 5.</param>
	/// <param name="inMinStrength">Minimal strength of an extracted edge. Default value: 5.0f.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied to the profile extracted in each scan. Default value: 0.25f.</param>
	/// <param name="outBarcodePositions">Positions of the found barcodes.</param>
	/// <param name="outDecodedTexts">Decoded barcode content.</param>
	/// <param name="outBarcodeFormats">Decoded barcode format.</param>
	/// <param name="outAlignedRoi">Input ROI after transformation (in the image coordinates).</param>
	/// <param name="diagGradientImage">Image of gradient directions.</param>
	/// <param name="diagBarcodeCandidates">Places with high gradient values that are further investigated.</param>
	/// <param name="diagScheduledScanSegments">Scheduled scan segments.</param>
	AVL_FUNCTION void ReadMultipleBarcodes
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Rectangle2D&>			inRoi,
		atl::Optional<const avl::CoordinateSystem2D&>	inRoiAlignment,	
		atl::Optional<avl::BarcodeFormat::Type>			inBarcodeFormat,
		float							inMinGradientLength,		
		int									inBaseBarWidth,				
		int									inDetectionScanCount,		
		const int							inReadingScanCount,			
		const int							inScanWidth,				
		const float						inMinStrength,				
		const float						inSmoothingStdDev,			
		atl::Array<avl::Rectangle2D>&		outBarcodePositions,		
		atl::Array<atl::String>&			outDecodedTexts,			
		atl::Optional<atl::Array<avl::BarcodeFormat::Type>&>	outBarcodeFormats = atl::NIL,	
		atl::Optional<avl::Rectangle2D&>	outAlignedRoi = atl::NIL,	
		avl::Image&							diagGradientImage = atl::Dummy<avl::Image>(),			
		atl::Array<avl::Rectangle2D>&		diagBarcodeCandidates = atl::Dummy< atl::Array<avl::Rectangle2D> >(),		
		atl::Array<atl::Array<avl::Segment2D> >&	diagScheduledScanSegments = atl::Dummy< atl::Array<atl::Array<avl::Segment2D> > >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Determines the barcode quality.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBarcodeFormat">Default value: EAN13.</param>
	AVL_FUNCTION void GradeBarcode
	(
		const avl::Image&						inImage,
		avl::BarcodeFormat::Type				inBarcodeFormat,
		const avl::Rectangle2D&					inBarcodePosition,
		atl::Conditional<avl::BarcodeGrades>&	outGrades,
		atl::Conditional<avl::BarcodeGrades>&	outValues,
		atl::Array<avl::BarcodesErrors::Type>&	outMessage,
		atl::Conditional<avl::Profile>&			diagCodeProfile = atl::Dummy< atl::Conditional<avl::Profile> >()
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_BARCODES_H

