//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_INTEGERARITHMETIC_H
#define AVS_INTEGERARITHMETIC_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "ATL/NumericRange.h"
#include "ATL/Optional.h"
#include "AVLCommon/Enums/NumberSystemBase.h"

namespace avl
{


	/// <summary>Computes the absolute value of a number.</summary>
	AVL_FUNCTION void AbsoluteInteger
	(
		int		inValue,
		int&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the negation of a number.</summary>
	AVL_FUNCTION void NegateInteger
	(
		int		inValue,
		int&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the absolute value of two numbers difference.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	AVL_FUNCTION void IntegerDifference
	(
		int		inA,
		int		inB,
		int&	outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the absolute value of two Long numbers difference</summary>
	/// <param name="inA">Default value: 0L.</param>
	/// <param name="inB">Default value: 0L.</param>
	AVL_FUNCTION void LongDifference
	(
		atl::int64		inA,
		atl::int64		inB,
		atl::int64&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the quotient of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 1.</param>
	AVL_FUNCTION void DivideIntegers
	(
		int		inA,
		int		inB,
		int&	outQuotient
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the quotient of two numbers.</summary>
	/// <param name="inA">Default value: 0L.</param>
	/// <param name="inB">Default value: 1L.</param>
	AVL_FUNCTION void DivideLongIntegers
	(
		atl::int64	inA,
		atl::int64	inB,
		atl::int64& outQuotient
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes remainder of integer division of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 1.</param>
	AVL_FUNCTION void Modulo
	(
		int		inA,
		int		inB,
		int&	outRemainder
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the difference of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	AVL_FUNCTION void SubtractIntegers
	(
		int		inA,
		int		inB,
		int&	outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the difference of two Long numbers.</summary>
	/// <param name="inA">Default value: 0L.</param>
	/// <param name="inB">Default value: 0L.</param>
	AVL_FUNCTION void SubtractLongIntegers
	(
		atl::int64		inA,
		atl::int64		inB,
		atl::int64&		outDifference
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the higher of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	AVL_FUNCTION void MaximumInteger
	(
		int			inA,
		int			inB,
		int&		outMaximum
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the lower of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	AVL_FUNCTION void MinimumInteger
	(
		int			inA,
		int			inB,
		int&		outMinimum
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of two numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	AVL_FUNCTION void AverageIntegers
	(
		int			inA,
		int			inB,
		int&		outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of two Long numbers.</summary>
	/// <param name="inA">Default value: 0L.</param>
	/// <param name="inB">Default value: 0L.</param>
	AVL_FUNCTION void AverageLongIntegers
	(
		atl::int64		inA,
		atl::int64		inB,
		atl::int64&		outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of integers.</summary>
	AVL_FUNCTION void AverageIntegers_OfArray
	(
		const atl::Array<int>&	inArray,
		int&					outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of integers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void AverageIntegers_OfArray_OrNil
	(
		const atl::Array<int>&	inArray,
		atl::Conditional<int>&	outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of Long integers.</summary>
	AVL_FUNCTION void AverageLongIntegers_OfArray
	(
		const atl::Array<atl::int64>&	inArray,
		atl::int64&						outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average value of Long integers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void AverageLongIntegers_OfArray_OrNil
	(
		const atl::Array<atl::int64>&	inArray,
		atl::Conditional<atl::int64>&	outAverage
	)
	THROW_AVL_ERRORS;

	struct AverageIntegers_OfLoopState : public BaseState
	{
		AverageIntegers_OfLoopState()
			:count(0), currentAvg(0), rests(0)
		{}

		int count;
		int currentAvg;
		int rests;
	};

	struct AverageLongIntegers_OfLoopState : public BaseState
	{
		AverageLongIntegers_OfLoopState()
			:count(0L), currentAvg(0L), rests(0L)
		{}

		atl::int64 count;
		atl::int64 currentAvg;
		atl::int64 rests;
	};


	/// <summary>Returns the average of the numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void AverageIntegers_OfLoop
	(
		AverageIntegers_OfLoopState&		ioState,	
		const int&							inValue,
		int&								outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the average of the Long numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void AverageLongIntegers_OfLoop
	(
		AverageLongIntegers_OfLoopState&	ioState,	
		const atl::int64&					inValue,
		atl::int64&							outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Linearly interpolates between two integers.</summary>
	/// <param name="inLambda">Interpolation between the input integers where 0.0 value is equal to inInteger0 and 1.0 to inInteger1. Default value: 0.5f.</param>
	AVL_FUNCTION void LerpIntegers
	(
		int				inInteger0,
		int				inInteger1,
		float			inLambda,	
		int&			outInteger
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the greatest value in an array of integer numbers.</summary>
	AVL_FUNCTION void MaximumInteger_OfArray
	(
		const atl::Optional<int>&				inInitialValue,
		const atl::Array<int>&					inArray,
		int&									outMaximum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the greatest value in an array of integer numbers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void MaximumInteger_OfArray_OrNil
	(
		const atl::Array<int>&					inArray,
		atl::Conditional<int>&					outMaximum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the smallest value in an array of integer numbers.</summary>
	AVL_FUNCTION void MinimumInteger_OfArray
	(
		const atl::Optional<int>&				inInitialValue,
		const atl::Array<int>&					inArray,
		int&									outMinimum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the smallest value in an array of integer numbers; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void MinimumInteger_OfArray_OrNil
	(
		const atl::Array<int>&					inArray,
		atl::Conditional<int>&					outMinimum,
		atl::Optional<atl::Conditional<int>&>	outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	struct MaximumInteger_OfLoopState : public BaseState
	{
		int maximum;
		int maximumIndex;
		int currentIndex;

		MaximumInteger_OfLoopState()
			: maximum( atl::NumericRange<int>::Min() ), maximumIndex(0), currentIndex(0)
		{}
	};


	/// <summary>Returns the greatest of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void MaximumInteger_OfLoop
	(
		MaximumInteger_OfLoopState&	ioState,	
		int							inValue,
		int&						outMaximum,
		atl::Optional<int&>			outIterationIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	struct MinimumInteger_OfLoopState : public BaseState
	{
		MinimumInteger_OfLoopState()
			: minimum( atl::NumericRange<int>::Max() ), minimumIndex(0), currentIndex(0)
		{}

		int minimum;
		int minimumIndex;
		int currentIndex;
	};


	/// <summary>Returns the smallest of numbers appearing in consecutive iterations.</summary>
	/// <param name="ioState">Stores information from previous iterations.</param>
	AVL_FUNCTION void MinimumInteger_OfLoop
	(
		MinimumInteger_OfLoopState& ioState,	
		int							inValue,
		int&						outMinimum,
		atl::Optional<int&>			outIterationIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the integer number represented by a string.</summary>
	AVL_FUNCTION void ParseInteger
	(
		const atl::String&			inString,
		avl::NumberSystemBase::Type inBase,
		atl::Conditional<int>&		outInteger
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an arithmetic sequence of integer numbers.</summary>
	/// <param name="inStart">Default value: 0.</param>
	/// <param name="inCount">Default value: 10.</param>
	/// <param name="inStep">Default value: 1.</param>
	AVL_FUNCTION void CreateIntegerSequence
	(
		int					inStart,
		int					inCount,
		int					inStep,
		atl::Array<int>&	outValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two integers with the < operator.</summary>
	AVL_FUNCTION void TestIntegerLessThan
	(
		int			inValue,
		int			inReferenceValue,
		bool&		outIsLessThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two Long integers with the < operator.</summary>
	AVL_FUNCTION void TestLongIntegerLessThan
	(
		atl::int64		inValue,
		atl::int64		inReferenceValue,
		bool&			outIsLessThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two integers with the <= operator.</summary>
	AVL_FUNCTION void TestIntegerLessOrEqual
	(
		int		inValue,
		int		inReferenceValue,
		bool&	outIsLessOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two Long integers with the <= operator.</summary>
	AVL_FUNCTION void TestLongIntegerLessOrEqual
	(
		atl::int64	inValue,
		atl::int64	inReferenceValue,
		bool&		outIsLessOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two integers with the > operator.</summary>
	AVL_FUNCTION void TestIntegerGreaterThan
	(
		int		inValue,
		int		inReferenceValue,
		bool&	outIsGreaterThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two Long integers with the > operator.</summary>
	AVL_FUNCTION void TestLongIntegerGreaterThan
	(
		atl::int64	inValue,
		atl::int64	inReferenceValue,
		bool&		outIsGreaterThan
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two integers with the >= operator.</summary>
	AVL_FUNCTION void TestIntegerGreaterOrEqual
	(
		int		inValue,
		int		inReferenceValue,
		bool&	outIsGreaterOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two Long integers with the >= operator.</summary>
	AVL_FUNCTION void TestLongIntegerGreaterOrEqual
	(
		atl::int64	inValue,
		atl::int64	inReferenceValue,
		bool&		outIsGreaterOrEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two integers are equal.</summary>
	AVL_FUNCTION void TestIntegerEqualTo
	(
		int		inValue,
		int		inReferenceValue,
		bool&	outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two Long integers are equal.</summary>
	AVL_FUNCTION void TestLongIntegerEqualTo
	(
		atl::int64	inValue,
		atl::int64	inReferenceValue,
		bool&		outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two integers are unequal.</summary>
	AVL_FUNCTION void TestIntegerUnequalTo
	(
		int		inValue,
		int		inReferenceValue,
		bool&	outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether two Long integers are unequal.</summary>
	AVL_FUNCTION void TestLongIntegerUnequalTo
	(
		atl::int64	inValue,
		atl::int64	inReferenceValue,
		bool&		outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether an integers is in the specified range.</summary>
	AVL_FUNCTION void TestIntegerInRange
	(
		int							inValue,
		const atl::Optional<int>&	inMinimum,
		const atl::Optional<int>&	inMaximum,
		bool&						outIsInRange
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether Long integers is in the specified range.</summary>
	AVL_FUNCTION void TestLongIntegerInRange
	(
		atl::int64							inValue,
		const atl::Optional<atl::int64>&	inMinimum,
		const atl::Optional<atl::int64>&	inMaximum,
		bool&								outIsInRange
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Computes the sum of numbers.</summary>
	/// <param name="inA">Default value: 0.</param>
	/// <param name="inB">Default value: 0.</param>
	/// <param name="inC">Default value: 0.</param>
	/// <param name="inD">Default value: 0.</param>
	/// <param name="inE">Default value: 0.</param>
	/// <param name="inF">Default value: 0.</param>
	/// <param name="inG">Default value: 0.</param>
	/// <param name="inH">Default value: 0.</param>
	AVL_FUNCTION void AvsFilter_AddIntegers
	(
		int inA,
		int inB,
		int inC,
		int inD,
		int inE,
		int inF,
		int inG,
		int inH,
		int& outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_AddIntegers_OfArray
	(
		const atl::Array<int>&	inIntegerArray,
		int&					outSum
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_AddIntegers_OfLoopState
	{
		int stateVariable;

		AvsFilter_AddIntegers_OfLoopState() : stateVariable(0) {}
	};


	/// <summary>Computes the sum of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_AddIntegers_OfLoop
	(
		AvsFilter_AddIntegers_OfLoopState& ioState,
		int		inInteger,
		int&	outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of Long numbers.</summary>
	/// <param name="inA">Default value: 0L.</param>
	/// <param name="inB">Default value: 0L.</param>
	/// <param name="inC">Default value: 0L.</param>
	/// <param name="inD">Default value: 0L.</param>
	/// <param name="inE">Default value: 0L.</param>
	/// <param name="inF">Default value: 0L.</param>
	/// <param name="inG">Default value: 0L.</param>
	/// <param name="inH">Default value: 0L.</param>
	AVL_FUNCTION void AvsFilter_AddLongIntegers
	(
		atl::int64 inA,
		atl::int64 inB,
		atl::int64 inC,
		atl::int64 inD,
		atl::int64 inE,
		atl::int64 inF,
		atl::int64 inG,
		atl::int64 inH,
		atl::int64& outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of Long numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_AddLongIntegers_OfArray
	(
		const atl::Array<atl::int64>&	inLongArray,
		atl::int64&						outSum
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_AddLongIntegers_OfLoopState
	{
		atl::int64 stateVariable;

		AvsFilter_AddLongIntegers_OfLoopState() : stateVariable(0) {}
	};


	/// <summary>Computes the sum of Long numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_AddLongIntegers_OfLoop
	(
		AvsFilter_AddLongIntegers_OfLoopState& ioState,
		atl::int64		inLong,
		atl::int64&		outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of numbers.</summary>
	/// <param name="inA">Default value: 1.</param>
	/// <param name="inB">Default value: 1.</param>
	/// <param name="inC">Default value: 1.</param>
	/// <param name="inD">Default value: 1.</param>
	/// <param name="inE">Default value: 1.</param>
	/// <param name="inF">Default value: 1.</param>
	/// <param name="inG">Default value: 1.</param>
	/// <param name="inH">Default value: 1.</param>
	AVL_FUNCTION void AvsFilter_MultiplyIntegers
	(
		int inA,
		int inB,
		int inC,
		int inD,
		int inE,
		int inF,
		int inG,
		int inH,
		int& outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyIntegers_OfArray
	(
		const atl::Array<int>&	inIntegerArray,
		int&					outProduct
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_MultiplyIntegers_OfLoopState
	{
		int stateVariable;

		AvsFilter_MultiplyIntegers_OfLoopState() : stateVariable(1) {}
	};


	/// <summary>Computes the product of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyIntegers_OfLoop
	(
		AvsFilter_MultiplyIntegers_OfLoopState& ioState,
		int		inInteger,
		int&	outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies linear transformation to integer.</summary>
	/// <param name="inA">Value multiplied. Default value: 1.0f.</param>
	/// <param name="inB">Value added. Default value: 0.0f.</param>
	AVL_FUNCTION void AvsFilter_RescaleInteger
	(
		int				inInteger,
		float		inA,		
		float		inB,		
		int&			outInteger
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of long numbers.</summary>
	/// <param name="inA">Default value: 1L.</param>
	/// <param name="inB">Default value: 1L.</param>
	/// <param name="inC">Default value: 1L.</param>
	/// <param name="inD">Default value: 1L.</param>
	/// <param name="inE">Default value: 1L.</param>
	/// <param name="inF">Default value: 1L.</param>
	/// <param name="inG">Default value: 1L.</param>
	/// <param name="inH">Default value: 1L.</param>
	AVL_FUNCTION void AvsFilter_MultiplyLongIntegers
	(
		atl::int64 inA,
		atl::int64 inB,
		atl::int64 inC,
		atl::int64 inD,
		atl::int64 inE,
		atl::int64 inF,
		atl::int64 inG,
		atl::int64 inH,
		atl::int64& outProduct
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the product of long numbers of an array.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyLongIntegers_OfArray
	(
		const atl::Array<atl::int64>&	inLongArray,
		atl::int64&						outProduct
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_MultiplyLongIntegers_OfLoopState
	{
		atl::int64 stateVariable;

		AvsFilter_MultiplyLongIntegers_OfLoopState() : stateVariable(1) {}
	};


	/// <summary>Computes the product of numbers appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_MultiplyLongIntegers_OfLoop
	(
		AvsFilter_MultiplyLongIntegers_OfLoopState& ioState,
		atl::int64		inLong,
		atl::int64&		outProduct
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_INTEGERARITHMETIC_H

