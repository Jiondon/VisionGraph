//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_HISTOGRAMBASICS_H
#define AVS_HISTOGRAMBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Creates a histogram assuming given bin values.</summary>
	/// <param name="inValues">Input array of bin values.</param>
	/// <param name="inDomainStart">Input domain begin. Default value: 0.0f.</param>
	/// <param name="inDomainLength">Input domain length. Default value: 256.0f.</param>
	/// <param name="inBinSize">Input length of the domain range covered by a single bin. Default value: 1.0f.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MakeHistogram
	(
		const atl::Array<int>&	inValues,			
		float				inDomainStart,		
		float				inDomainLength,		
		float				inBinSize,			
		avl::Histogram&			outHistogram		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an uniform histogram of desired parameters with common value of all bins.</summary>
	/// <param name="inValue">Common value for all bins of the constructed histogram.</param>
	/// <param name="inBinSize">Length of the domain section represented by each bin. Default value: 1.0f.</param>
	/// <param name="inDomainStart">First value of the domain represented by the histogram. Default value: 0.0f.</param>
	/// <param name="inDomainLength">Length of the domain represented by the histogram. Default value: 256.0f.</param>
	/// <param name="outHistogram">The resulting histogram.</param>
	AVL_FUNCTION void CreateUniformHistogram
	(
		int inValue,			
		float inBinSize,			
		float inDomainStart,		
		float inDomainLength,	
		avl::Histogram& outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the value of a single histogram bin.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inIndex">Input bin index.</param>
	/// <param name="inInverse">Reversed order of bins.</param>
	/// <param name="outValue">Output value of the bin.</param>
	AVL_FUNCTION void GetHistogramBin
	(
		const avl::Histogram&	inHistogram,	
		int						inIndex,		
		const bool				inInverse,		
		int&					outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets the value of a single histogram bin.</summary>
	/// <param name="inIndex">Input bin index.</param>
	/// <param name="inInverse">Reversed order of bins.</param>
	/// <param name="inNewValue">Input new value to be set.</param>
	AVL_FUNCTION void SetHistogramBin
	(
		avl::Histogram&		ioHistogram,
		int					inIndex,		
		const bool			inInverse,		
		int					inNewValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects a bin that the given value in the histogram domain falls into and returns the value of this bin.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="inBinSelectionValue">Input value in the histogram domain that will be used to select the bin.</param>
	/// <param name="outValue">Output value of the bin.</param>
	AVL_FUNCTION void GetHistogramCorrespondingBin
	(
		const avl::Histogram&	inHistogram,			
		float				inBinSelectionValue,	
		int&					outValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects a bin that the given value in the histogram domain falls into and sets the value of this bin.</summary>
	/// <param name="inBinSelectionValue">Input value in the histogram domain that will be used to select the bin.</param>
	/// <param name="inNewValue">Input new value to be set.</param>
	AVL_FUNCTION void SetHistogramCorrespondingBin
	(
		avl::Histogram&		ioHistogram,
		float			inBinSelectionValue,	
		int					inNewValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an array of histogram elements indices</summary>
	/// <param name="inHistogram">Input histogram.</param>
	AVL_FUNCTION void HistogramIndices
	(
		const avl::Histogram&	inHistogram,
		atl::Array<int>&		outIndices
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates the histogram of the array of real numbers.</summary>
	/// <param name="inArray">Array from which histogram will be generated.</param>
	/// <param name="inWeights">Weights corresponding to the elements of 'inArray'. Default value: atl::NIL.</param>
	/// <param name="inBinSize">Input bin size. Default value: 1.0f.</param>
	/// <param name="inDomainStart">Input domain begin. Default value: atl::NIL.</param>
	/// <param name="inDomainLength">Input domain length. Default value: atl::NIL.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void CreateHistogram
	(	
		const atl::Array<float>&			inArray,		
		atl::Optional<const atl::Array<int>&>	inWeights,		
		const float&						inBinSize,		
		atl::Optional<float>				inDomainStart,	
		atl::Optional<float>				inDomainLength,	
		avl::Histogram&							outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized Histogram object as avdata file.</summary>
	/// <param name="inHistogram">Histogram to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveHistogram
	(
		const avl::Histogram& inHistogram,	
		const atl::File& inFilename			
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized Histogram object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outHistogram">Deserialized output Histogram.</param>
	AVL_FUNCTION void LoadHistogram
	(
		const atl::File& inFilename,			
		avl::Histogram& outHistogram			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the cumulative histogram of input histogram.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void ConvertToCumulativeHistogram
	(
		const avl::Histogram&	inHistogram,
		avl::Histogram&			outHistogram		
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input histogram contains at least one bin, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outNotEmptyHistogram">The histogram, if it is not empty.</param>
	/// <param name="outIsNotEmpty">Indication if the input histogram is not empty.</param>
	AVL_FUNCTION void SkipEmptyHistogram
	(
		const avl::Histogram&				inHistogram,
		atl::Conditional<avl::Histogram>&	outNotEmptyHistogram,	
		bool&								outIsNotEmpty			
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input histogram contains any non-zero bin, then the histogram is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	AVL_FUNCTION void SkipEmptyDataHistogram
	(
		const avl::Histogram&				inHistogram,
		atl::Conditional<avl::Histogram>&	outNotEmptyDataHistogram,
		bool&								outIsNotEmpty
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Returns individual fields of a histogram.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outBinSize">Output bin size.</param>
	/// <param name="outDomainStart">Output domain begin.</param>
	/// <param name="outDomainLength">Output length of domain.</param>
	/// <param name="outBins">Output histogram data.</param>
	AVL_FUNCTION void AvsFilter_AccessHistogram
	(
		const avl::Histogram& inHistogram,	
		float& outBinSize,				
		float& outDomainStart,			
		float& outDomainLength,			
		atl::Array<int>& outBins				
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_HISTOGRAMBASICS_H

