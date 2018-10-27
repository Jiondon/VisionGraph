//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_REALARITHMETIC_H
#define AVS_REALARITHMETIC_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "ATL/NumericRange.h"
#include "ATL/Optional.h"

namespace avl
{


	/// <summary>Computes the absolute value of a number.</summary>
	AVL_FUNCTION void AbsoluteReal
	(
		const float	inValue,
		float&		outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the negation of a number.</summary>
	AVL_FUNCTION void NegateReal
	(
		const float	inValue,
		float&		outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the absolute value of two numbers difference.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	AVL_FUNCTION void RealDifference
	(
		const float	inA,
		const float	inB,
		float&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the absolute value of two doubles difference.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 0.0D.</param>
	AVL_FUNCTION void DoubleDifference
	(
		const double&	inA,
		const double&	inB,
		double&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the quotient of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 1.0f.</param>
	AVL_FUNCTION void DivideReals
	(
		const float	inA,
		const float	inB,
		float&		outQuotient
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the quotient of two numbers.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 1.0D.</param>
	AVL_FUNCTION void DivideDoubles
	(
		const double	inA,
		const double	inB,
		double&		outQuotient
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the difference of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	AVL_FUNCTION void SubtractReals
	(
		const float	inA,
		const float	inB,
		float&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the difference of two doubles.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 0.0D.</param>
	AVL_FUNCTION void SubtractDoubles
	(
		const double&	inA,
		const double&	inB,
		double&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the higher of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	AVL_FUNCTION void MaximumReal
	(
		const float		inA,
		const float		inB,
		float&			outMaximum
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the lower of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	AVL_FUNCTION void MinimumReal
	(
		const float		inA,
		const float		inB,
		float&			outMinimum
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	AVL_FUNCTION void AverageReals
	(
		const float		inA,
		const float		inB,
		float&			outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of two doubles.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 0.0D.</param>
	AVL_FUNCTION void AverageDoubles
	(
		const double&		inA,
		const double&		inB,
		double&			outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of reals.</summary>
	AVL_FUNCTION void AverageReals_OfArray
	(
		const atl::Array<float>&	inArray,
		float&						outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of reals; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void AverageReals_OfArray_OrNil
	(
		const atl::Array<float>&	inArray,
		atl::Conditional<float>&	outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of doubles.</summary>
	AVL_FUNCTION void AverageDoubles_OfArray
	(
		const atl::Array<double>&	inArray,
		double&					outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of doubles; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void AverageDoubles_OfArray_OrNil
	(
		const atl::Array<double>&	inArray,
		atl::Conditional<double>&	outAverage
	)
	THROW_AVL_ERRORS;

	struct AverageReals_OfLoopState : public BaseState
	{
		int count;
		float totalSum;

		AverageReals_OfLoopState()
			: count(0), totalSum(0.0f)
		{}
	};

	struct AverageDoubles_OfLoopState : public BaseState
	{
		int count;
		double totalSum;

		AverageDoubles_OfLoopState()
			: count(0), totalSum(0.0)
		{}
	};


	/// <summary>Returns the average of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void AverageReals_OfLoop
	(
		AverageReals_OfLoopState&	ioState,	
		const float&			inValue,
		float&					outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void AverageDoubles_OfLoop
	(
		AverageDoubles_OfLoopState&	ioState,	
		const double&			inValue,
		double&				outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two reals.</summary>
	/// <param name="inLambda">Interpolation between the input reals where 0.0 value is equal to inReal0 and 1.0 to inReal1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpReals
	(
		const float			inReal0,
		const float			inReal1,
		const float			inLambda,	
		float&				outReal
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the greatest value in an array of real numbers.</summary>
	AVL_FUNCTION void MaximumReal_OfArray
	(
		const atl::Optional<float>&				inInitialValue,
		const atl::Array<float>&				inArray,
		float&									outMaximum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the greatest value in an array of real numbers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void MaximumReal_OfArray_OrNil
	(
		const atl::Array<float>&				inArray,
		atl::Conditional<float>&				outMaximum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the smallest value in an array of real numbers.</summary>
	AVL_FUNCTION void MinimumReal_OfArray
	(
		const atl::Optional<float>&				inInitialValue,
		const atl::Array<float>&				inArray,
		float&									outMinimum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the smallest value in an array of real numbers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void MinimumReal_OfArray_OrNil
	(
		const atl::Array<float>&				inArray,
		atl::Conditional<float>&				outMinimum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	struct MaximumReal_OfLoopState : public BaseState
	{
		float maximum;
		int maximumIndex;
		int currentIndex;

		MaximumReal_OfLoopState()
			: maximum( atl::NumericRange<float>::Min() ), maximumIndex(0), currentIndex(0)
		{}
	};

	struct MaximumDouble_OfLoopState : public BaseState
	{
		double maximum;
		int maximumIndex;
		int currentIndex;

		MaximumDouble_OfLoopState()
			: maximum( atl::NumericRange<double>::Min() ), maximumIndex(0), currentIndex(0)
		{}
	};


	/// <summary>Returns the greatest of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void MaximumReal_OfLoop
	(
		MaximumReal_OfLoopState&	ioState,	
		float inValue,
		float& outMaximum,
		int& outIterationIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the greatest of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void MaximumDouble_OfLoop
	(
		MaximumDouble_OfLoopState&	ioState,
		double					inValue,
		double&				outMaximum,
		int&						outIterationIndex
	)
	THROW_AVL_ERRORS;

	struct MinimumReal_OfLoopState : public BaseState
	{
		float minimum;
		int minimumIndex;
		int currentIndex;

		MinimumReal_OfLoopState()
			: minimum( atl::NumericRange<float>::Max() ), minimumIndex(0), currentIndex(0)
		{}
	};

	struct MinimumDouble_OfLoopState : public BaseState
	{
		double minimum;
		int minimumIndex;
		int currentIndex;

		MinimumDouble_OfLoopState()
			: minimum( atl::NumericRange<double>::Max() ), minimumIndex(0), currentIndex(0)
		{}
	};


	/// <summary>Returns the smallest of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void MinimumReal_OfLoop
	(
		MinimumReal_OfLoopState&	ioState,	
		float inValue,
		float& outMinimum,
		int& outIterationIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the smallest of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void MinimumDouble_OfLoop
	(
		MinimumDouble_OfLoopState&	ioState,	
		double					inValue,
		double&				outMinimum,
		int&						outIterationIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the real number represented by a string.</summary>
	AVL_FUNCTION void ParseReal
	(
		const atl::String&		inString,
		atl::Conditional<float>&	outReal
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the double number represented by a string.</summary>
	AVL_FUNCTION void ParseDouble
	(
		const atl::String&			inString,
		atl::Conditional<double>&	outDouble
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an arithmetic sequence of real numbers.</summary>
	/// <param name="inStart">Default value: 0.0f.</param>
	/// <param name="inCount">Default value: 10.</param>
	/// <param name="inStep">Default value: 1.0f.</param>
	AVL_FUNCTION void CreateRealSequence
	(
		float			inStart,
		int				inCount,
		float			inStep,
		atl::Array<float>&	outValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two reals with the < operator.</summary>
	AVL_FUNCTION void TestRealLessThan
	(
		const float& inValue,
		const float& inReferenceValue,
		bool& outIsLessThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two doubles with the < operator.</summary>
	AVL_FUNCTION void TestDoubleLessThan
	(
		const double& inValue,
		const double& inReferenceValue,
		bool& outIsLessThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two reals with the <= operator.</summary>
	AVL_FUNCTION void TestRealLessOrEqual
	(
		const float& inValue,
		const float& inReferenceValue,
		bool& outIsLessOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two doubles with the <= operator.</summary>
	AVL_FUNCTION void TestDoubleLessOrEqual
	(
		const double& inValue,
		const double& inReferenceValue,
		bool& outIsLessOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two reals with the > operator.</summary>
	AVL_FUNCTION void TestRealGreaterThan
	(
		const float& inValue,
		const float& inReferenceValue,
		bool& outIsGreaterThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two doubles with the > operator.</summary>
	AVL_FUNCTION void TestDoubleGreaterThan
	(
		const double& inValue,
		const double& inReferenceValue,
		bool& outIsGreaterThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two reals with the >= operator.</summary>
	AVL_FUNCTION void TestRealGreaterOrEqual
	(
		const float& inValue,
		const float& inReferenceValue,
		bool& outIsGreaterOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two doubles with the >= operator.</summary>
	AVL_FUNCTION void TestDoubleGreaterOrEqual
	(
		const double& inValue,
		const double& inReferenceValue,
		bool& outIsGreaterOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two reals are equal.</summary>
	/// <param name="inEpsilon">Maximum difference of values that are still considered equal. Default value: 0.001f.</param>
	AVL_FUNCTION void TestRealEqualTo
	(
		const float& inValue,
		const float& inReferenceValue,
		const float& inEpsilon,		
		bool& outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two doubles are equal.</summary>
	/// <param name="inEpsilon">Maximum difference of values that are still considered equal. Default value: 0.001D.</param>
	AVL_FUNCTION void TestDoubleEqualTo
	(
		const double& inValue,
		const double& inReferenceValue,
		const double& inEpsilon,		
		bool& outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two reals are unequal.</summary>
	/// <param name="inEpsilon">Maximum difference of values that are still considered equal.</param>
	AVL_FUNCTION void TestRealUnequalTo
	(
		const float& inValue,
		const float& inReferenceValue,
		const float& inEpsilon,			
		bool&			 outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two doubles are unequal.</summary>
	/// <param name="inEpsilon">Maximum difference of values that are still considered equal.</param>
	AVL_FUNCTION void TestDoubleUnequalTo
	(
		const double& inValue,
		const double& inReferenceValue,
		const double& inEpsilon,			
		bool&			 outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether a real value is in the specified range.</summary>
	AVL_FUNCTION void TestRealInRange
	(
		const float&			inValue,
		atl::Optional<float>	inMinimum,
		atl::Optional<float>	inMaximum,
		bool&						outIsInRange
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether a double value is in the specified range.</summary>
	AVL_FUNCTION void TestDoubleInRange
	(
		const double&			inValue,
		atl::Optional<double>	inMinimum,
		atl::Optional<double>	inMaximum,
		bool&						outIsInRange
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Computes the sum of two numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 0.0f.</param>
	/// <param name="inC">Default value: 0.0f.</param>
	/// <param name="inD">Default value: 0.0f.</param>
	/// <param name="inE">Default value: 0.0f.</param>
	/// <param name="inF">Default value: 0.0f.</param>
	/// <param name="inG">Default value: 0.0f.</param>
	/// <param name="inH">Default value: 0.0f.</param>
	AVL_FUNCTION void AvsFilter_AddReals
	(
		const float inA,
		const float inB,
		const float inC,
		const float inD,
		const float inE,
		const float inF,
		const float inG,
		const float inH,
		float& outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_AddReals_OfArray
	(
		const atl::Array<float>&	inRealArray,
		float&						outSum
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_AddReals_OfLoopState
	{
		float stateVariable;

		AvsFilter_AddReals_OfLoopState() : stateVariable(0.0f) {}
	};


	/// <summary>Computes the sum of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_AddReals_OfLoop
	(
		AvsFilter_AddReals_OfLoopState& ioState,
		float	inReal,
		float&	outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of two or more doubles.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 0.0D.</param>
	/// <param name="inC">Default value: 0.0D.</param>
	/// <param name="inD">Default value: 0.0D.</param>
	/// <param name="inE">Default value: 0.0D.</param>
	/// <param name="inF">Default value: 0.0D.</param>
	/// <param name="inG">Default value: 0.0D.</param>
	/// <param name="inH">Default value: 0.0D.</param>
	AVL_FUNCTION void AvsFilter_AddDoubles
	(
		const double& inA,
		const double& inB,
		const double& inC,
		const double& inD,
		const double& inE,
		const double& inF,
		const double& inG,
		const double& inH,
		double& outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_AddDoubles_OfArray
	(
		const atl::Array<double>&	inDoubleArray,
		double&					outSum
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_AddDoubles_OfLoopState
	{
		double stateVariable;

		AvsFilter_AddDoubles_OfLoopState() : stateVariable(0.0) {}
	};


	/// <summary>Computes the sum of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_AddDoubles_OfLoop
	(
		AvsFilter_AddDoubles_OfLoopState& ioState,
		double		inDouble,
		double&	outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of real numbers.</summary>
	/// <param name="inA">Default value: 0.0f.</param>
	/// <param name="inB">Default value: 1.0f.</param>
	/// <param name="inC">Default value: 1.0f.</param>
	/// <param name="inD">Default value: 1.0f.</param>
	/// <param name="inE">Default value: 1.0f.</param>
	/// <param name="inF">Default value: 1.0f.</param>
	/// <param name="inG">Default value: 1.0f.</param>
	/// <param name="inH">Default value: 1.0f.</param>
	AVL_FUNCTION void AvsFilter_MultiplyReals
	(
		const float inA,
		const float inB,
		const float inC,
		const float inD,
		const float inE,
		const float inF,
		const float inG,
		const float inH,
		float& outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyReals_OfArray
	(
		const atl::Array<float>&	inRealArray,
		float&						outProduct
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_MultiplyReals_OfLoopState
	{
		float stateVariable;

		AvsFilter_MultiplyReals_OfLoopState() : stateVariable(1.0f) {}
	};


	/// <summary>Computes the product of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyReals_OfLoop
	(
		AvsFilter_MultiplyReals_OfLoopState& ioState,
		float	inReal,
		float&	outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies linear transformation to real number.</summary>
	/// <param name="inA">Value multiplied. Default value: 1.0f.</param>
	/// <param name="inB">Value added. Default value: 0.0f.</param>
	AVL_FUNCTION void AvsFilter_RescaleReal
	(
		float		inReal,
		float		inA,		
		float		inB,		
		float&		outReal
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of double numbers.</summary>
	/// <param name="inA">Default value: 0.0D.</param>
	/// <param name="inB">Default value: 1.0D.</param>
	/// <param name="inC">Default value: 1.0D.</param>
	/// <param name="inD">Default value: 1.0D.</param>
	/// <param name="inE">Default value: 1.0D.</param>
	/// <param name="inF">Default value: 1.0D.</param>
	/// <param name="inG">Default value: 1.0D.</param>
	/// <param name="inH">Default value: 1.0D.</param>
	AVL_FUNCTION void AvsFilter_MultiplyDoubles
	(
		const double inA,
		const double inB,
		const double inC,
		const double inD,
		const double inE,
		const double inF,
		const double inG,
		const double inH,
		double& outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyDoubles_OfArray
	(
		const atl::Array<double>&	inDoubleArray,
		double&					outProduct
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_MultiplyDoubles_OfLoopState
	{
		double stateVariable;

		AvsFilter_MultiplyDoubles_OfLoopState() : stateVariable(1.0) {}
	};


	/// <summary>Computes the product of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyDoubles_OfLoop
	(
		AvsFilter_MultiplyDoubles_OfLoopState& ioState,
		double		inDouble,
		double&	outProduct
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_REALARITHMETIC_H

