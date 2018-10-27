//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILEMETRICS_H
#define AVL_PROFILEMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/DistanceMeasure.h"
#include "Profile/Profile.h"

namespace avl
{


	namespace PeriodPrecisionMethod
	{
		enum Type
		{
			Basic,
			Quadratic4,
			Flex
		};
	};


	/// <summary>Computes the [mean] square error between two profiles.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="inDistanceMeasure">Measure of distance.</param>
	/// <param name="outDistance">Output distance value.</param>
	AVL_FUNCTION void ProfileDistance
	(
		const avl::Profile&			inProfile1,				
		const avl::Profile&			inProfile2,				
		avl::DistanceMeasure::Type	inDistanceMeasure,		
		float&					outDistance				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the correlation between two sub-profiles.</summary>
	/// <param name="inProfile1">First input profile.</param>
	/// <param name="inStart1">Start of the first sub-profile of interest.</param>
	/// <param name="inProfile2">Second input profile.</param>
	/// <param name="inStart2">Start of the second sub-profile of interest.</param>
	/// <param name="inLength">Length of the sub-profiles of interest. Default value: atl::NIL.</param>
	/// <param name="outCorrelation">Pearson correlation coefficient.</param>
	/// <param name="diagProfile1">First sub-profile of interest.</param>
	/// <param name="diagProfile2">Second sub-profile of interest.</param>
	AVL_FUNCTION void ProfileCorrelation
	(
		const avl::Profile&			inProfile1,					
		int							inStart1,					
		const avl::Profile&			inProfile2,					
		int							inStart2,					
		atl::Optional<int>			inLength,					
		float&					outCorrelation,				
		atl::Optional<float&>	outCovariance = atl::NIL,
		avl::Profile&				diagProfile1 = atl::Dummy<avl::Profile>(),				
		avl::Profile&				diagProfile2 = atl::Dummy<avl::Profile>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the correlation between neighboring sub-profiles of different sizes and infers the most probable period length.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inStart">Beginning index of the sub-profile of interest.</param>
	/// <param name="inMinPeriod">Minimum period length. Default value: 2.</param>
	/// <param name="inMaxPeriod">Maximum period length. Default value: 2.</param>
	/// <param name="inMinVerifiedLength">Minimum number of profile points that verify single period (increases the actual RepeatCount for small periods). Default value: 1.</param>
	/// <param name="inFlexibleVerification">Compensates errors resulting from whole-pixel precision.</param>
	/// <param name="inMinRepeatCount">The number of repeats for sufficiently big periods. Default value: 1.</param>
	/// <param name="inHarmonicHysteresis">Defines how much better must be the period T than T/2, T/3 etc. to be accepted. Default value: 0.05f.</param>
	/// <param name="inPrecisionMethod">Defines if and how sub-point precision is achieved.</param>
	/// <param name="outAutocorrelationValues">Autocorrelation values for consecutive period values.</param>
	/// <param name="outPeriod">Estimated period length.</param>
	/// <param name="outPeriodScore">Correlation value for the estimated period length.</param>
	AVL_FUNCTION void ProfileAutocorrelation
	(
		const avl::Profile&					inProfile,					
		int									inStart,					
		int									inMinPeriod,				
		int									inMaxPeriod,				
		int									inMinVerifiedLength,		
		bool								inFlexibleVerification,		
		int									inMinRepeatCount,			
		float							inHarmonicHysteresis,		
		avl::PeriodPrecisionMethod::Type	inPrecisionMethod,			
		atl::Array< float >&			outAutocorrelationValues,	
		float&							outPeriod,					
		float&							outPeriodScore				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILEMETRICS_H

