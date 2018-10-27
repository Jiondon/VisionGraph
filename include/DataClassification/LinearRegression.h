//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_LINEARREGRESSION_H
#define AVL_LINEARREGRESSION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "ATL/Error.h"
#include "ATL/Optional.h"
#include "AVLCommon/Enums/MEstimator.h"
#include "AVLCommon/Enums/TheilSenVariant.h"
#include "Basic/LinearFunction.h"

namespace avl
{


	/// <summary>Computes linear regression of given point set.</summary>
	/// <param name="inYValues">Sequence of ordinates.</param>
	/// <param name="inXValues">Sequence of abscissae, or {0, 1, 2, ...} by default. Default value: atl::NIL.</param>
	/// <param name="outLinearFunction">Linear function approximating the given point set.</param>
	/// <param name="outEstimatedValues">The result of application of the computed function to the X values.</param>
	/// <param name="outResiduals">Difference between an input Y value and the corresponding estimated value.</param>
	/// <param name="outRSquared">Coefficient of determination of output function.</param>
	AVL_FUNCTION void LinearRegression
	(
		const atl::Array<float>& inYValues,				
		const atl::Optional<atl::Array<float> >& inXValues,	
		avl::LinearFunction&	outLinearFunction,			
		atl::Array<float>&	outEstimatedValues,			
		atl::Array<float>&	outResiduals,				
		float&				outRSquared					
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes linear regression of given point set using RANSAC.</summary>
	/// <param name="inYValues">Sequence of ordinates.</param>
	/// <param name="inXValues">Sequence of abscissae, or {0, 1, 2, ...} by default. Default value: atl::NIL.</param>
	/// <param name="inMaxOutlierCount">Determines how many outlier points can be present to end the search. Default value: atl::NIL.</param>
	/// <param name="inMaxInlierDistance">Distance from a line for point to be considered an inlier.</param>
	/// <param name="inIterationCount">Number of iterations; Auto means that all point pairs will be used. Default value: atl::NIL.</param>
	/// <param name="outLinearFunction">Linear function approximating the given point set.</param>
	/// <param name="outEstimatedValues">The result of application of the computed function to the X values.</param>
	/// <param name="outResiduals">Difference between an input Y value and the corresponding estimated value.</param>
	AVL_FUNCTION void LinearRegression_RANSAC
	(
		const atl::Array<float>&					inYValues,				
		const atl::Optional<atl::Array<float> >&	inXValues,				
		atl::Optional<int>								inMaxOutlierCount,		
		float										inMaxInlierDistance,	
		atl::Optional<int>								inIterationCount,		
		avl::LinearFunction&							outLinearFunction,		
		atl::Array<float>&							outEstimatedValues,		
		atl::Array<float>&							outResiduals			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes linear regression of given point set using selected M-estimator for outlier suppression.</summary>
	/// <param name="inYValues">Sequence of ordinates.</param>
	/// <param name="inXValues">Sequence of abscissae, or {0, 1, 2, ...} by default. Default value: atl::NIL.</param>
	/// <param name="inClippingFactor">Multitude of standard deviation within which points are considered inliers. Default value: 2.5f.</param>
	/// <param name="inIterationCount">Number of iterations of outlier suppressing algorithm. Default value: 5.</param>
	/// <param name="inInitialLinearFunction">Initial approximation of the output linear function (if available). Default value: atl::NIL.</param>
	/// <param name="outLinearFunction">Linear function approximating the given point set.</param>
	/// <param name="outEstimatedValues">The result of application of the computed function to the X values.</param>
	/// <param name="outResiduals">Difference between an input Y value and the corresponding estimated value.</param>
	AVL_FUNCTION void LinearRegression_M
	(
		const atl::Array<float>&					inYValues,				
		const atl::Optional<atl::Array<float> >&	inXValues,				
		avl::MEstimator::Type							inOutlierSuppression,
		float										inClippingFactor,		
		int												inIterationCount,		
		atl::Optional<const avl::LinearFunction&>		inInitialLinearFunction,
		avl::LinearFunction&							outLinearFunction,		
		atl::Array<float>&							outEstimatedValues,		
		atl::Array<float>&							outResiduals			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes linear regression of given point set using Least Trimmed Error algorithm.</summary>
	/// <param name="inYValues">Sequence of ordinates.</param>
	/// <param name="inXValues">Sequence of abscissae, or {0, 1, 2, ...} by default. Default value: atl::NIL.</param>
	/// <param name="inSeedSubsetSize">Number of points in one combination for getting a sample line. Default value: 3.</param>
	/// <param name="inEvalSubsetSize">Number of closest points used for evaluation of a sample line, or Auto if seed points are to be used. Default value: atl::NIL.</param>
	/// <param name="outLinearFunction">Linear function approximating the given point set.</param>
	/// <param name="outEstimatedValues">The result of application of the computed function to the X values.</param>
	/// <param name="outResiduals">Difference between an input Y value and the corresponding estimated value.</param>
	/// <param name="outYInliers">Coordinate of the inlying points of the best LTE line.</param>
	/// <param name="outXInliers">Coordinate of the inlying points of the best LTE line.</param>
	/// <param name="outLTError">The Least Trimmed Error.</param>
	/// <param name="diagIterationCount">Number of combinations considered.</param>
	AVL_FUNCTION void LinearRegression_LTE
	(
		const atl::Array<float>&					inYValues,				
		const atl::Optional<atl::Array<float> >&	inXValues,				
		int											inSeedSubsetSize,		
		atl::Optional<int>							inEvalSubsetSize,		
		avl::LinearFunction&						outLinearFunction,		
		atl::Array<float>&							outEstimatedValues,		
		atl::Array<float>&							outResiduals,			
		atl::Array<float>&							outYInliers,			
		atl::Array<float>&							outXInliers,			
		float&										outLTError,				
		int&										diagIterationCount = atl::Dummy<int>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes basic statistical information out of an array of real numbers. The array must be not empty.</summary>
	/// <param name="inValues">Values used to compute statistical informations.</param>
	/// <param name="inOutlierCount">Defines how many outliers should be removed from the input values. Default value: 0.</param>
	/// <param name="inUseSampleFormula">Defines, whether to use population, or sample formulas. Default value: False.</param>
	/// <param name="outMean">Mean of the input values.</param>
	/// <param name="outMedian">Median of the input values.</param>
	/// <param name="outStandardDeviation">Standard deviation of the input values, treated as population.</param>
	/// <param name="outMinimum">Minimum of the input values.</param>
	/// <param name="outMaximum">Maximum of the input values.</param>
	/// <param name="outSpread">Difference between maximum and minimum of the input values.</param>
	/// <param name="outLinearTrend">First parameter of the linear regression function (multiplier).</param>
	AVL_FUNCTION void Statistics_OfArray
	(
		const atl::Array<float>&	inValues,					
		const int					inOutlierCount,				
		const bool					inUseSampleFormula,			
		atl::Optional<float&>		outMean = atl::NIL,			
		atl::Optional<float&>		outMedian = atl::NIL,		
		atl::Optional<float&>		outStandardDeviation = atl::NIL,
		atl::Optional<float&>		outMinimum = atl::NIL,		
		atl::Optional<float&>		outMaximum = atl::NIL,		
		atl::Optional<float&>		outSpread = atl::NIL,		
		atl::Optional<float&>		outLinearTrend = atl::NIL	
	)
	THROW_AVL_ERRORS;

	struct Statistics_OfLoopState : public BaseState
	{
		atl::Array<float> values;
		int bufferSize;
		int currentIndex;
	};


	/// <summary>Computes basic statistical information out of real numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	/// <param name="inValue">Value used to compute statistical informations.</param>
	/// <param name="inBufferSize">Defines how many numbers are taken into account. Default value: 10.</param>
	/// <param name="inOutlierCount">Defines how many outliers should be removed from the input values. Default value: 0.</param>
	/// <param name="inUseSampleFormula">Defines, whether to use population, or sample formulas.</param>
	/// <param name="outMean">Mean of the input values.</param>
	/// <param name="outMedian">Median of the input values.</param>
	/// <param name="outStandardDeviation">Standard deviation of the input values.</param>
	/// <param name="outMinimum">Minimum of the input values.</param>
	/// <param name="outMaximum">Maximum of the input values.</param>
	/// <param name="outSpread">Difference between maximum and minimum of the input values.</param>
	/// <param name="outLinearTrend">First parameter of the linear regression function (multiplier).</param>
	AVL_FUNCTION void Statistics_OfLoop
	(
		Statistics_OfLoopState&		ioState,					
		const float					inValue,					
		const int					inBufferSize,				
		const int					inOutlierCount,				
		const bool					inUseSampleFormula,			
		atl::Optional<float&>		outMean = atl::NIL,			
		atl::Optional<float&>		outMedian = atl::NIL,		
		atl::Optional<float&>		outStandardDeviation = atl::NIL,
		atl::Optional<float&>		outMinimum = atl::NIL,		
		atl::Optional<float&>		outMaximum = atl::NIL,		
		atl::Optional<float&>		outSpread = atl::NIL,		
		atl::Optional<float&>		outLinearTrend = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes linear regression of given point set using TheilSen algorithm.</summary>
	/// <param name="inYValues">Sequence of ordinates.</param>
	/// <param name="inXValues">Sequence of abscissae, or {0, 1, 2, ...} by default. Default value: atl::NIL.</param>
	/// <param name="inVariant">Switches between Theil-Sen and Siegel methods.</param>
	/// <param name="outLinearFunction">Linear function approximating the given point set.</param>
	/// <param name="outEstimatedValues">The result of application of the computed function to the X values.</param>
	/// <param name="outResiduals">Difference between an input Y value and the corresponding estimated value.</param>
	AVL_FUNCTION void LinearRegression_TheilSen
	(
		const atl::Array<float>&					inYValues,				
		const atl::Optional<atl::Array<float> >&	inXValues,				
		avl::TheilSenVariant::Type						inVariant,				
		avl::LinearFunction&							outLinearFunction,		
		atl::Array<float>&							outEstimatedValues,		
		atl::Array<float>&							outResiduals			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_LINEARREGRESSION_H

