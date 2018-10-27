//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAMCOMBINATORS_H
#define AVL_HISTOGRAMCOMBINATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Histogram/Histogram.h"

namespace avl
{


	/// <summary>Adds two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void AddHistograms
	(
		const avl::Histogram&	inHistogram1,	
		const avl::Histogram&	inHistogram2,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds histograms of an array bar by bar.</summary>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void AddHistograms_OfArray
	(
		const atl::Array<avl::Histogram>& inHistogramArray,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct AddHistograms_OfLoopState : public avl::BaseState
	{
		avl::Histogram stateVariable;
	};
	/// <summary>Adds histograms appearing in consecutive iterations bar by bar.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void AddHistograms_OfLoop
	(
		AddHistograms_OfLoopState& ioState,
		const avl::Histogram& inHistogram,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtracts two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void SubtractHistograms
	(
		const avl::Histogram&	inHistogram1,	
		const avl::Histogram&	inHistogram2,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiplies two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MultiplyHistograms
	(
		const avl::Histogram&	inHistogram1,	
		const avl::Histogram&	inHistogram2,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiply histograms of an array bar by bar.</summary>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MultiplyHistograms_OfArray
	(
		const atl::Array<avl::Histogram>& inHistogramArray,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MultiplyHistograms_OfLoopState : public avl::BaseState
	{
		avl::Histogram stateVariable;
	};
	/// <summary>Multiply histograms appearing in consecutive iterations bar by bar.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MultiplyHistograms_OfLoop
	(
		MultiplyHistograms_OfLoopState& ioState,
		const avl::Histogram& inHistogram,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void DivideHistograms
	(
		const avl::Histogram&	inHistogram1,	
		const avl::Histogram&	inHistogram2,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the maximum of two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MaximumHistogram
	(
		const avl::Histogram&	inHistogram1,
		const avl::Histogram&	inHistogram2,
		avl::Histogram&			outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the maximum of histograms of an array bar by bar.</summary>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MaximumHistogram_OfArray
	(
		const atl::Array<avl::Histogram>& inHistogramArray,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MaximumHistogram_OfLoopState : public avl::BaseState
	{
		avl::Histogram stateVariable;
	};
	/// <summary>Computes the maximum of histograms appearing in consecutive iterations bar by bar.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MaximumHistogram_OfLoop
	(
		MaximumHistogram_OfLoopState& ioState,
		const avl::Histogram& inHistogram,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the minimum of two histograms bar by bar.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MinimumHistogram
	(
		const avl::Histogram&	inHistogram1,	
		const avl::Histogram&	inHistogram2,	
		avl::Histogram&			outHistogram	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the minimum of histograms of an array bar by bar.</summary>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MinimumHistogram_OfArray
	(
		const atl::Array<avl::Histogram>& inHistogramArray,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct MinimumHistogram_OfLoopState : public avl::BaseState
	{
		avl::Histogram stateVariable;
	};
	/// <summary>Computes the minimum of histograms appearing in consecutive iterations bar by bar.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void MinimumHistogram_OfLoop
	(
		MinimumHistogram_OfLoopState& ioState,
		const avl::Histogram& inHistogram,
		avl::Histogram& outHistogram
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes histogram representing difference between corresponding bars of given histograms.</summary>
	/// <param name="inHistogram1">Input histogram1.</param>
	/// <param name="inHistogram2">Input histogram2.</param>
	/// <param name="outHistogram">Output histogram.</param>
	AVL_FUNCTION void DifferenceHistogram
	(
		const avl::Histogram& inHistogram1,		
		const avl::Histogram& inHistogram2,		
		avl::Histogram& outHistogram			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HISTOGRAMCOMBINATORS_H

