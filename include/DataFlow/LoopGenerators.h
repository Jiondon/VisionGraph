//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_LOOPGENERATORS_H
#define AVL_LOOPGENERATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "Basic/Common.h"

namespace avl
{


	struct Enumerate1DState : public BaseState
	{
		Enumerate1DState() 
			: index(0) 
		{}

		int index;
	};

	struct Enumerate2DState : public BaseState
	{
		Enumerate2DState() 
			: index1(0), index2(0) 
		{}

		int index1;
		int index2;
	};


	/// <summary>In each consecutive iteration produces a consecutive number from an arithmetic sequence.</summary>
	/// <param name="inStart">First value of the generated sequence.</param>
	/// <param name="inCount">Length of the generated sequence. Default value: atl::NIL.</param>
	/// <param name="inStep">Value added in each iteration.</param>
	AVL_FUNCTION bool EnumerateReals
	(
		Enumerate1DState&		ioState,
		float				inStart,	
		atl::Optional<int>		inCount,	
		float				inStep,		
		float&				outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>In each consecutive iteration produces a consecutive number from an arithmetic sequence.</summary>
	/// <param name="inStart">First value of the generated sequence.</param>
	/// <param name="inCount">Length of the generated sequence. Default value: atl::NIL.</param>
	/// <param name="inStep">Value added in each iteration.</param>
	AVL_FUNCTION bool EnumerateIntegers
	(
		Enumerate1DState&		ioState,
		int						inStart,	
		atl::Optional<int>		inCount,	
		int						inStep,		
		int&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces a total number of 'inCount1 * inCount2' of pairs of real numbers.</summary>
	/// <param name="inStart1">First element of first range.</param>
	/// <param name="inCount1">Length of first range. Default value: atl::NIL.</param>
	/// <param name="inStep1">Difference between consecutive elements of first range.</param>
	/// <param name="inStart2">First element of second range.</param>
	/// <param name="inCount2">Length of second range.</param>
	/// <param name="inStep2">Difference between consecutive elements of second range.</param>
	/// <param name="outValue1">Elements of first range in 'AAABBBCCC' order.</param>
	/// <param name="outValue2">Elements of second range in 'ABCABCABC' order.</param>
	AVL_FUNCTION bool EnumerateRealPairs
	(
		Enumerate2DState&		ioState,
		
		float				inStart1,	
		atl::Optional<int>		inCount1,	
		float				inStep1,	
		
		float				inStart2,	
		int						inCount2,	
		float				inStep2,	
		
		float&				outValue1,	
		float&				outValue2	
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces a total number of 'inCount1 * inCount2' of pairs of integer numbers.</summary>
	/// <param name="inStart1">First element of first range.</param>
	/// <param name="inCount1">Length of first range. Default value: atl::NIL.</param>
	/// <param name="inStep1">Difference between consecutive elements of first range.</param>
	/// <param name="inStart2">First element of second range.</param>
	/// <param name="inCount2">Length of second range.</param>
	/// <param name="inStep2">Difference between consecutive elements of second range.</param>
	/// <param name="outValue1">Elements of first range in 'AAABBBCCC' order.</param>
	/// <param name="outValue2">Elements of second range in 'ABCABCABC' order.</param>
	AVL_FUNCTION bool EnumerateIntegerPairs
	(
		Enumerate2DState&		ioState,
		
		int						inStart1,	
		atl::Optional<int>		inCount1,	
		int						inStep1,	
		
		int						inStart2,	
		int						inCount2,	
		int						inStep2,	
		
		int&					outValue1,	
		int&					outValue2	
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates a loop that ends at the first invocation with False on the input.</summary>
	/// <param name="inShouldLoop">If 'True' the loop will be continued. Default value: True.</param>
	AVL_FUNCTION bool Loop
	(
		bool inShouldLoop	
	)
	THROW_AVL_ERRORS;

	template<typename T>
	struct EnumerateElementsState : public BaseState
	{
		EnumerateElementsState()
			: index(0)
		{}

		int index;
	};

	template<typename T>
	struct EnumerateElementPairsState : public BaseState
	{
		EnumerateElementPairsState()
			: index1(0), index2(0)
		{}

		int index1;
		int index2;
	};



	/// In each iteration gets a consecutive element of the input array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inStart">Index of the first element to be enumerated.</param>
	/// <param name="inCount">Number of elements to be enumerated. Leave 'Auto' to enumerate to the end of the input array. Default value: atl::NIL.</param>
	/// <param name="inInvert">Flag indicating whether to enumerate backwards or not.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outIndex">Index of the output element.</param>
	template<typename T>
	bool EnumerateElements
	(
		EnumerateElementsState<T>&	ioState,
		const atl::Array<T>&		inArray,		
		int							inStart,		
		atl::Optional<int>			inCount,		
		bool						inInvert,		
		T&							outElement,		
		int&						outIndex		
	)
	{
		bool isReversed = false; // AVL version is not reversible to prevent backward iterating inside other filters

		if (inCount != atl::NIL && inCount.Get() < 0)
			throw atl::DomainError(L"Value of inCount is smaller than 0 in EnumerateElements.");

		//empty array is allowed when inCount is 0 or NIL
		if (inArray.Size() == 0 && ((inCount != atl::NIL && inCount.Get() == 0) || inCount == atl::NIL))
			return false;

		//inStart and inEnd are virtual indices (from beginning or end, depends on inInvert)
		int inEnd = inCount != atl::NIL ? inStart + inCount.Get() - 1 : inArray.Size() - 1;

		//real indices of first and last element
		int realStart = inStart;
		int realEnd = inEnd;

		if (inInvert)
		{
			realStart = inArray.Size() - 1 - inStart;
			realEnd = inArray.Size() - 1 - inEnd;
		}

		if (inStart < 0)
			throw atl::DomainError(L"Value of inStart is smaller than 0 in EnumerateElements.");
		if (inStart >= inArray.Size())
			throw atl::DomainError(L"Value of inStart is greater than or equal to number of elements in inArray in EnumerateElements.");
		if (inEnd >= inArray.Size())
			throw atl::DomainError(L"Selected range is exceeding the number of elements in inArray in EnumerateElements.");

		if (ioState.IsFirstTime())
			ioState.index = isReversed ? realEnd : realStart;
		else
			ioState.index += inInvert ^ isReversed ? -1 : +1;

		if ((!inInvert && ioState.index < realStart) || (inInvert && (ioState.index > realStart)))
			return false;

		if ((!inInvert && ioState.index > realEnd) || (inInvert && (ioState.index < realEnd)))
			return false;

		outIndex = ioState.index;
		outElement = inArray[outIndex];

		return true;
	}

	/// Produces a total number of 'inCount1 * inCount2' of pairs of elements.
	/// <param name="inArray1">First input array.</param>
	/// <param name="inStart1">Index of the first element of first array to be enumerated.</param>
	/// <param name="inCount1">Number of elements from first array to be enumerated. Leave 'Auto' to enumerate to the end of the input array. Default value: atl::NIL.</param>
	/// <param name="inArray2">Second input array.</param>
	/// <param name="inStart2">Index of the first element of second array to be enumerated.</param>
	/// <param name="inCount2">Number of elements from second array to be enumerated. Leave 'Auto' to enumerate to the end of the input array. Default value: atl::NIL.</param>
	/// <param name="outElement1">Element from the first array.</param>
	/// <param name="outElement2">Element from the second array.</param>
	/// <param name="outIndex1">Index of the output element from first array.</param>
	/// <param name="outIndex2">Index of the output element from second array.</param>
	template<typename T>
	bool EnumerateElementPairs
	(
		EnumerateElementPairsState<T>&	ioState,
		const atl::Array<T>&			inArray1,		
		int								inStart1,		
		atl::Optional<int>				inCount1,		
		const atl::Array<T>&			inArray2,		
		int								inStart2,		
		atl::Optional<int>				inCount2,		
		T&								outElement1,	
		T&								outElement2,	
		int&							outIndex1,		
		int&							outIndex2		
	)
	{
		bool isReversed = false; // AVL version is not reversible to prevent backward iterating inside other filters
		int inEnd1 = inCount1 != atl::NIL ? inStart1 + inCount1.Get() : inArray1.Size();
		int inEnd2 = inCount2 != atl::NIL ? inStart2 + inCount2.Get() : inArray2.Size();

		if (inCount1 != atl::NIL && inCount1.Get() < 0)
			throw atl::DomainError(L"Value of inCount1 is smaller than 0 in EnumerateElementPairs.");
		if (inCount2 != atl::NIL && inCount2.Get() < 0)
			throw atl::DomainError(L"Value of inCount2 is smaller than 0 in EnumerateElementPairs.");

		if (inStart1 < 0 || (inArray1.Size() > 0 && inStart1 >= inArray1.Size()))
			throw atl::DomainError("Begin marker for first array is out of range in EnumerateElementPairs.");
		if (inEnd1 > inArray1.Size())
			throw atl::DomainError("End marker for first array is out of range in EnumerateElementPairs.");

		if (inStart2 < 0 || (inArray2.Size() > 0 && inStart2 >= inArray2.Size()))
			throw atl::DomainError("Begin marker for second array is out of range in EnumerateElementPairs.");
		if (inEnd2 > inArray2.Size())
			throw atl::DomainError("End marker for second array is out of range in EnumerateElementPairs.");

		if (ioState.IsFirstTime())
		{
			ioState.index1 = inStart1;
			ioState.index2 = inStart2 + (isReversed ? 1 : -1);
		}

		if (isReversed)
		{
			--ioState.index2;
			if (ioState.index2 < inStart2)
			{
				ioState.index2 = inEnd2 - 1;
				--ioState.index1;
			}
		}
		else
		{
			++ioState.index2;
			if (ioState.index2 >= inEnd2)
			{
				ioState.index2 = inStart2;
				++ioState.index1;
			}
		}

		if (ioState.index1 < inEnd1
			&& ioState.index2 < inEnd2
			&& ioState.index1 >= inStart1
			&& ioState.index2 >= inStart2)
		{
			outElement1 = inArray1[ioState.index1];
			outElement2 = inArray2[ioState.index2];
			outIndex1 = ioState.index1;
			outIndex2 = ioState.index2;

			return true;
		}

		return false;
	}

	struct EnumerateCombinationsState : public BaseState
	{
		EnumerateCombinationsState() 
			: index(0) 
		{}

		int index;
		atl::Array<int>	combination;
	};


	/// <summary>In each consecutive iteration produces a consecutive combination of integer numbers.</summary>
	AVL_FUNCTION bool EnumerateCombinations
	(
		EnumerateCombinationsState&	ioState,
		int							inCombinationSize,
		int							inSetSize,
		atl::Array<int>&			outCombination,
		int&						outIndex
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_LOOPGENERATORS_H

