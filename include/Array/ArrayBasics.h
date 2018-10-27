//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_ARRAYBASICS_H
#define AVS_ARRAYBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"

namespace avl
{


	/// Finds all locations of a given value in the input array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inValue">Value to look for.</param>
	/// <param name="outIndices">Indices of the value occurrences in the array.</param>
	template <typename Type>
	void FindAll
	(
		const atl::Array<Type>&	inArray,	
		const Type&				inValue,	
		atl::Array<int>&		outIndices,	
		bool&					outFound	
	)
	{
		outIndices.Clear();

		for( int i = 0; i < inArray.Size(); ++i )
			if (inArray[i] == inValue)
				outIndices.PushBack(i);
		outFound = outIndices.Size() > 0;
	}

	/// Finds first location of a given value in the input array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inValue">Value to look for.</param>
	/// <param name="outIndex">Index of the first value occurrence in the array.</param>
	template <typename Type>
	void FindFirst
	(
		const atl::Array<Type>&	inArray,	
		const Type&				inValue,	
		atl::Conditional<int>&	outIndex,	
		bool&					outFound
	)
	{
		outIndex = atl::NIL;

		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] == inValue)
			{
				outIndex = i;
				return;
			}
		}
		outFound = outIndex.HasValue();
	}

	/// Finds last location of a given value in the input array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inValue">Value to look for.</param>
	/// <param name="outIndex">Index of the last value occurrence in the array.</param>
	template <typename Type>
	void FindLast
	(
		const atl::Array<Type>&	inArray,	
		const Type&				inValue,	
		atl::Conditional<int>&	outIndex,	
		bool&					outFound
	)
	{
		outIndex = atl::NIL;

		for (int i = inArray.Size() - 1; i >= 0; --i)
		{
			if (inArray[i] == inValue)
			{
				outIndex = i;
				return;
			}
		}
		outFound = outIndex.HasValue();
	}

	/// If the input array is not empty, then it is copied to the output; otherwise Nil is returned.
	/// <param name="inArray">Array that may be empty or not.</param>
	/// <param name="outNotEmptyArray">Not empty array or Nil.</param>
	template <typename Type>
	void SkipEmptyArray
	(
		const atl::Array<Type>&			inArray,			
		atl::Conditional<atl::Array<Type> >&	outNotEmptyArray,	
		bool&							outIsNotEmpty
	)
	{
		if (inArray.Empty())
		{
			outNotEmptyArray = atl::NIL;
			outIsNotEmpty = false;
		}
		else
		{
			outNotEmptyArray = inArray;
			outIsNotEmpty = true;
		}
	}

	/// If the input array has enough elements, then it is copied to the output; otherwise Nil is returned.
	/// <param name="inArray">Array that may have too few elements.</param>
	/// <param name="inMinSize">Minimum number of elements. Default value: 2.</param>
	/// <param name="outBigEnoughArray">Array with at least inMinSize elements, or Nil.</param>
	template <typename Type>
	void SkipShortArray
	(
		const atl::Array<Type>&					inArray,			
		int										inMinSize,			
		atl::Conditional<atl::Array<Type> >&	outBigEnoughArray,	
		bool&									outIsBigEnough
	)
	{
		if (inMinSize < 0)
			throw atl::DomainError("inMinSize must be greater or equal 0 in SkipShortArray.");

		if (inArray.Size() < inMinSize)
		{
			outBigEnoughArray = atl::NIL;
			outIsBigEnough = false;
		}
		else
		{
			outBigEnoughArray = inArray;
			outIsBigEnough = true;
		}
	}

	/// If the input array is short enough, then it is copied to the output; otherwise Nil is returned.
	/// <param name="inArray">Array that may have too many elements.</param>
	/// <param name="inMaxSize">Maximum number of elements. Default value: 2.</param>
	/// <param name="outSmallEnoughArray">Array with at most inMaxSize elements, or Nil.</param>
	template <typename Type>
	void SkipLongArray
	(
		const atl::Array<Type>&					inArray,				
		int										inMaxSize,				
		atl::Conditional<atl::Array<Type> >&	outSmallEnoughArray,	
		bool&									outIsSmallEnough
	)
	{
		if (inArray.Size() > inMaxSize)
		{
			outSmallEnoughArray = atl::NIL;
			outIsSmallEnough = false;
		}
		else
		{
			outSmallEnoughArray = inArray;
			outIsSmallEnough = true;
		}
	}

	/// If the input array has exactly one element, then the element is copied to the output; otherwise Nil is returned.
	/// <param name="inArray">Array that may have exactly one element.</param>
	/// <param name="outObject">The single array element, or Nil.</param>
	template <typename Type>
	void SkipNotSingle
	(
		const atl::Array<Type>&					inArray,			
		typename atl::ToConditionalType<Type>::Type&	outObject,	
		bool&									outIsSingle
	)
	{
		if (inArray.Size() != 1)
		{
			outObject = atl::NIL;
			outIsSingle = false;
		}
		else
		{
			outObject = inArray[0];
			outIsSingle = true;
		}
	}

	/// If the input array contains no Nil values, then it is copied to the output; otherwise Nil is returned.
	/// <param name="inArray">Array that may contain Nil values or not.</param>
	/// <param name="outArray">Array or Nil.</param>
	template <typename Type>
	void SkipArrayWithNils
	(
		const atl::Array< typename atl::ToConditionalType<Type>::Type >&	inArray,	
		atl::Conditional< atl::Array<Type> >&								outArray,	
		bool&																outIsWithoutNils
	)
	{
		bool containsNil = false;
		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] == atl::NIL)
			{
				containsNil = true;
				break;
			}
		}
		if (containsNil)
		{
			outArray = atl::NIL;
		}
		else
		{
			outArray = atl::Array<Type>(inArray.Size());
			for (int i = 0; i < inArray.Size(); ++i)
			{
				(outArray.Get())[i] = inArray[i].Get();
			}
		}
		outIsWithoutNils = !containsNil;
	}

	/// If the input array contains exactly requested number of elements, it is copied to the output; otherwise, Nil is returned.
	/// <param name="inArray">Array that may contain N elements or not.</param>
	/// <param name="inN">Requested number of elements. Default value: 1.</param>
	/// <param name="outArray">Array or Nil.</param>
	template <typename Type>
	void ExactlyNElements_OrNil_Deprecated
	(
		const atl::Array<Type>&			inArray,	
		const int					inN,		
		atl::Conditional<atl::Array<Type> >&	outArray	
	)
	{
		if (inArray.Size() == inN)
		{
			outArray = inArray;
		}
		else
		{
			outArray = atl::NIL;
		}
	}

	/// Creates an array of element indices, i.e. {0, 1, 2, ..., N-1}, where N is the length of the input array.
	/// <param name="outArray">Array indices.</param>
	template <typename Type>
	void ArrayIndices
	(
		const atl::Array<Type>&		inArray,
		atl::Array<int>&			outArray	
	)
	{
		outArray.Resize(inArray.Size());

		for (int i = 0; i < outArray.Size(); ++i)
			outArray[i] = i;
	}

	/// If the input arrays have equal size, then they are copied to the output; otherwise Nils are returned.
	template <typename Type>
	void SkipUnequalSizeArrays
	(
		const atl::Array<Type>&					inArray1,
		const atl::Array<Type>&					inArray2,
		atl::Conditional<atl::Array<Type> >&	outArray1,
		atl::Conditional<atl::Array<Type> >&	outArray2,
		bool&									outHaveEqualSize
	)
	{
		if (inArray1.Size() == inArray2.Size())
		{
			outArray1 = inArray1;
			outArray2 = inArray2;
			outHaveEqualSize = true;
		}
		else
		{
			outArray1 = atl::NIL;
			outArray2 = atl::NIL;
			outHaveEqualSize = false;
		}
	}

} // namespace avl

namespace avs
{

	/// Returns the number of elements in an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="outSize">Number of the array elements.</param>
	template <typename Type>
	void AvsFilter_ArraySize
	(
		const atl::Array<Type>&	inArray,
		int&				outSize 
	)
	{
		outSize = inArray.Size();
	}

	/// Extracts a single element from an array at the specified index.
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndex">Index within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outValue">Element from the array.</param>
	template <typename Type>
	void AvsFilter_GetArrayElement
	(
		const atl::Array<Type>&	inArray,	
		int						inIndex,	
		bool					inInverse,	
		Type&					outValue	
	)
	{
		if (inIndex < 0)
		{
			throw atl::DomainError(L"Negative index in GetArrayElement.");
		}
		if (inIndex >= inArray.Size())
		{
			throw atl::DomainError(L"Index out of range in GetArrayElement.");
		}

		outValue = inArray[inInverse ? inArray.Size() - 1 - inIndex : inIndex];
	}

	/// Extracts a single element from an array at the specified index; returns NIL if the index is out of range.
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndex">Index within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outConditionalValue">Element from the array.</param>
	template <typename Type>
	void AvsFilter_GetArrayElement_OrNil
	(
		const atl::Array<Type>&	inArray,			
		int						inIndex,			
		bool					inInverse,			
		typename atl::ToConditionalType<Type>::Type&	outConditionalValue 
	)
	{
		if (inIndex < 0)
		{
			throw atl::DomainError(L"Negative index in GetArrayElement_OrNil.");
		}
		if (inIndex >= inArray.Size())
		{
			outConditionalValue = atl::NIL;
		}
		else
		{
			outConditionalValue = inArray[inInverse ? inArray.Size() - 1 - inIndex : inIndex];
		}
	}

	/// Extracts a single element from an array at the specified index; returns NIL if the index is out of range or negative.
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndex">Index within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outConditionalValue">Element from the array.</param>
	template <typename Type>
	void AvsFilter_GetArrayElement_OrNil_Deprecated
	(
		const atl::Array<Type>&	inArray,			
		int						inIndex,			
		bool					inInverse,			
		typename atl::ToConditionalType<Type>::Type&	outConditionalValue 
	)
	{
		if (inIndex >= inArray.Size() || inIndex < 0)
		{
			outConditionalValue = atl::NIL;
		}
		else
		{
			outConditionalValue = inArray[inInverse ? inArray.Size() - 1 - inIndex : inIndex];
		}
	}

	/// Sets an element of an array to a new value.
	/// <param name="inIndex">Index within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="inNewValue">Value to be set.</param>
	template <typename Type>
	void AvsFilter_SetArrayElement
	(
		atl::Array<Type>&	ioArray,
		int					inIndex,	
		bool				inInverse,	
		const Type&			inNewValue	
	)
	{
		if (!(0 <= inIndex && inIndex < ioArray.Size()))
		{
			throw atl::DomainError(L"Index out of range in SetArrayElement.");
		}

		ioArray[inInverse ? ioArray.Size() - 1 - inIndex : inIndex] = inNewValue;
	}

	/// Sets elements of an array to new values.
	/// <param name="inIndices">Indices within the array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="inNewValues">Values to be set.</param>
	template <typename Type>
	void AvsFilter_SetMultipleArrayElements
	(
		atl::Array<Type>&		ioArray,
		const atl::Array<int>&	inIndices,	
		bool					inInverse,	
		const atl::Array<Type>&	inNewValues	
	)
	{
		if (inIndices.Size() != inNewValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array lengths in SetMultipleArrayElements.");
		}
		for (int i = 0; i < inIndices.Size(); ++i)
		{
			if (!(0 <= inIndices[i] && inIndices[i] < ioArray.Size()))
			{
				throw atl::DomainError(L"Index out of range in SetMultipleArrayElements.");
			}
		}

		for (int i = 0; i < inIndices.Size(); ++i)
		{
			ioArray[inInverse ? ioArray.Size() - 1 - inIndices[i] : inIndices[i]] = inNewValues[i];
		}
	}

	/// Creates an array of the specified size with all elements initialized to the specified value.
	/// <param name="inSize">Size of the array being constructed.</param>
	/// <param name="inValue">Common value of the array elements.</param>
	/// <param name="outArray">Created array.</param>
	template <typename Type>
	void AvsFilter_CreateUniformArray
	(
		const int			inSize,		
		const Type&			inValue,	
		atl::Array<Type>&	outArray	
	)
	{
		if (inSize < 0)
		{
			throw atl::DomainError(L"Negative inSize value in CreateUniformArray.");
		}

		outArray.Reset(inSize, inValue);
	}

	/// Creates an array from up to 8 individual objects.
	/// <param name="inValue1">First input value. Default value: atl::NIL.</param>
	/// <param name="inValue2">Second input value. Default value: atl::NIL.</param>
	/// <param name="inValue3">Third input value. Default value: atl::NIL.</param>
	/// <param name="inValue4">Fourth input value. Default value: atl::NIL.</param>
	/// <param name="inValue5">Fifth input value. Default value: atl::NIL.</param>
	/// <param name="inValue6">Sixth input value. Default value: atl::NIL.</param>
	/// <param name="inValue7">Seventh input value. Default value: atl::NIL.</param>
	/// <param name="inValue8">Eighth input value. Default value: atl::NIL.</param>
	/// <param name="outArray">Constructed array.</param>
	template <typename Type>
	void AvsFilter_CreateArray
	(
		const typename atl::ToOptionalType<const Type&>::Type& inValue1, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue2, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue3, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue4, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue5, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue6, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue7, 
		const typename atl::ToOptionalType<const Type&>::Type& inValue8, 
		atl::Array<Type>& outArray			
	)
	{
		outArray.Clear();
		outArray.Reserve(8);

		if (inValue1 != atl::NIL) outArray.PushBack(inValue1.Get());
		if (inValue2 != atl::NIL) outArray.PushBack(inValue2.Get());
		if (inValue3 != atl::NIL) outArray.PushBack(inValue3.Get());
		if (inValue4 != atl::NIL) outArray.PushBack(inValue4.Get());
		if (inValue5 != atl::NIL) outArray.PushBack(inValue5.Get());
		if (inValue6 != atl::NIL) outArray.PushBack(inValue6.Get());
		if (inValue7 != atl::NIL) outArray.PushBack(inValue7.Get());
		if (inValue8 != atl::NIL) outArray.PushBack(inValue8.Get());
	}

	/// Extracts up to 8 individual elements from an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inStart">First element index.</param>
	/// <param name="inCount">Number of elements to extract.</param>
	/// <param name="outValue1">First output value.</param>
	/// <param name="outValue2">Second output value.</param>
	/// <param name="outValue3">Third output value.</param>
	/// <param name="outValue4">Fourth output value.</param>
	/// <param name="outValue5">Fifth output value.</param>
	/// <param name="outValue6">Sixth output value.</param>
	/// <param name="outValue7">Seventh output value.</param>
	/// <param name="outValue8">Eighth output value.</param>
	template <typename Type>
	void AvsFilter_GetArrayElements
	(
		const atl::Array<Type>& inArray,	
		const int inStart,					
		const int inCount,					
		Type& outValue1,					
		Type& outValue2,					
		Type& outValue3,					
		Type& outValue4,					
		Type& outValue5,					
		Type& outValue6,					
		Type& outValue7,					
		Type& outValue8						
	)
	{
		int inArraySize = inArray.Size();
		int lastIndex = inStart + (inCount - 1);

		if (inCount < 1 || inCount > 8)
		{
			throw atl::DomainError(L"Bad count in GetArrayElements.");
		}

		if (   inStart < 0
			|| inStart >= inArraySize
			|| lastIndex < 0
			|| lastIndex >= inArraySize)
		{
			throw atl::DomainError(L"Index out of range in GetArrayElements.");
		}

		if (inCount > 0) outValue1 = inArray[inStart + 0]; else outValue1 = Type();
		if (inCount > 1) outValue2 = inArray[inStart + 1]; else outValue2 = Type();
		if (inCount > 2) outValue3 = inArray[inStart + 2]; else outValue3 = Type();
		if (inCount > 3) outValue4 = inArray[inStart + 3]; else outValue4 = Type();
		if (inCount > 4) outValue5 = inArray[inStart + 4]; else outValue5 = Type();
		if (inCount > 5) outValue6 = inArray[inStart + 5]; else outValue6 = Type();
		if (inCount > 6) outValue7 = inArray[inStart + 6]; else outValue7 = Type();
		if (inCount > 7) outValue8 = inArray[inStart + 7]; else outValue8 = Type();
	}

	/// Extracts multiple elements from an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndices">Indices within the array.</param>
	/// <param name="inInverse">Reversed order in the array.</param>
	/// <param name="outValues">Output values.</param>
	template <typename Type>
	void AvsFilter_GetMultipleArrayElements
	(
		const atl::Array<Type>&	inArray,	
		const atl::Array<int>&	inIndices,	
		bool					inInverse,	
		atl::Array<Type>&		outValues	
	)
	{
		outValues.Reset(inIndices.Size());

		for (int i = 0; i < inIndices.Size(); ++i)
		{
			if (!(0 <= inIndices[i] && inIndices[i] < inArray.Size()))
			{
				outValues.Reset();
				throw atl::DomainError(L"Index out of range in GetMultipleArrayElements.");
			}

			if(inInverse)
				outValues[outValues.Size() - i - 1] = inArray[inIndices[i]];
			else
				outValues[i] = inArray[inIndices[i]];
		}
	}

	/// Tests whether the size of an array equals zero.
	/// <param name="inArray">Input array.</param>
	template <typename Type>
	void AvsFilter_TestArrayEmpty
	(
		const atl::Array<Type>& inArray, 
		bool& outIsEmpty
	)
	{
		outIsEmpty = inArray.Empty();
	}

	/// Tests whether the size of an array does not equal zero.
	/// <param name="inArray">Input array.</param>
	/// <param name="outIsNotEmpty">Whether the size of the array doesn't equal zero.</param>
	template <typename Type>
	void AvsFilter_TestArrayNotEmpty
	(
		const atl::Array<Type>&	inArray,		
		bool&				outIsNotEmpty	
	)
	{
		outIsNotEmpty = (inArray.Size() > 0);
	}

	/// Tests whether an array contains Nil elements.
	/// <param name="inArray">Input array.</param>
	/// <param name="outIsWithNils">Whether the array contains Nils.</param>
	template <typename Type>
	void AvsFilter_TestArrayWithNils
	(
		const atl::Array< typename atl::ToConditionalType<Type>::Type >&	inArray,		
		bool&																outIsWithNils	
	)
	{
		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] == atl::NIL)
			{
				outIsWithNils = true;
				return;
			}
		}
		outIsWithNils = false;
	}

	/// Tests whether an array does not contain Nil elements.
	/// <param name="inArray">Input array.</param>
	/// <param name="outIsWithoutNils">Whether the array does not contain Nils.</param>
	template <typename Type>
	void AvsFilter_TestArrayWithoutNils
	(
		const atl::Array< typename atl::ToConditionalType<Type>::Type >&	inArray,			
		bool&																outIsWithoutNils	
	)
	{
		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] == atl::NIL)
			{
				outIsWithoutNils = false;
				return;
			}
		}
		outIsWithoutNils = true;
	}

	/// Tests whether an array contains no other elements than Nils.
	/// <param name="inArray">Input array.</param>
	/// <param name="outIsWithNilsOnly">Whether the array contains no other elements than Nils.</param>
	template <typename Type>
	void AvsFilter_TestArrayWithNilsOnly
	(
		const atl::Array< typename atl::ToConditionalType<Type>::Type >&	inArray,			
		bool&																outIsWithNilsOnly	
	)
	{
		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] != atl::NIL)
			{
				outIsWithNilsOnly = false;
				return;
			}
		}
		outIsWithNilsOnly = true;
	}

	/// Tests whether the size of an array equals the given value.
	/// <param name="inArray">Input array.</param>
	/// <param name="inReferenceSize">Value to check.</param>
	/// <param name="outIsEqual">Whether the size of the array equals given value.</param>
	template <typename Type>
	void AvsFilter_TestArraySizeEqualTo
	(
		const atl::Array<Type>&	inArray,			
		const int				inReferenceSize,	
		bool&					outIsEqual			
	)
	{
		outIsEqual = (inArray.Size() == inReferenceSize);
	}

	/// Tests whether the number of elements in the input array falls into the specified range.
	/// <param name="inArray">Input array.</param>
	/// <param name="inMinimumSize">Minimum number of elements. Default value: atl::NIL.</param>
	/// <param name="inMaximumSize">Maximum number of elements. Default value: atl::NIL.</param>
	/// <param name="outIsInRange">Whether the size of the array is in range.</param>
	template <typename Type>
	void AvsFilter_TestArraySizeInRange
	(
		const atl::Array<Type>&		inArray,			
		const atl::Optional<int>	inMinimumSize,		
		const atl::Optional<int>	inMaximumSize,		
		bool&						outIsInRange		
	)
	{
		if (inMinimumSize != atl::NIL && inMinimumSize.Get() < 0)
			throw atl::DomainError("Negative inMinimumSize value.");

		outIsInRange = 
			(inMinimumSize == atl::NIL || inArray.Size() >= inMinimumSize.Get()) &&
			(inMaximumSize == atl::NIL || inArray.Size() <= inMaximumSize.Get());
	}

} // namespace avs

#endif // AVS_ARRAYBASICS_H

