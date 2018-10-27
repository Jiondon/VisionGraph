//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_ARRAYTRANSFORMS_H
#define AVS_ARRAYTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "AVLCommon/Enums/SortingOrder.h"
#include <cstdlib>
#include <algorithm>

namespace avl
{


	/// Selects a continuous subsequence of array elements.
	/// <param name="inArray">Input array.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outCroppedArray">Cropped array.</param>
	template <typename Type>
	void CropArray
	(
		const atl::Array<Type>&	inArray,		
		const int				inStart,
		atl::Optional<int>		inLength,
		bool					inInverse,		
		atl::Array<Type>&		outCroppedArray	
	)
	{
		if (inStart < 0)
		{
			throw atl::DomainError("inStart negative in CropArray");
		}

		if (inLength != atl::NIL && inLength.Get() < 0)
		{
			throw atl::DomainError("inLength negative in CropArray");
		}

		int startIndex = std::min( inArray.Size(), inStart );
		int endIndex = std::min(inArray.Size(), inStart + (inLength == atl::NIL ? inArray.Size() : inLength.Get()));
		
		if (inInverse)
		{
			endIndex = std::max(0, inArray.Size() - inStart);
			startIndex = std::max(0, endIndex - (inLength == atl::NIL ? inArray.Size() : inLength.Get()));
		}

		outCroppedArray.Reset();

		if (startIndex >= inArray.Size())
			return;

		outCroppedArray.Insert( inArray.Begin() + startIndex, inArray.Begin() + endIndex );
	}

	AVL_FUNCTION void SortIndicesByValues
	(int* inBegin, int* inEnd, const atl::Array<float>& inValues)
	THROW_AVL_ERRORS;

	/// Changes the order of the input array elements accordingly to an ascending/descending sequence of the value array.
	/// <param name="inArray">Elements to be sorted.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="outSortedArray">Sorted elements.</param>
	/// <param name="outSortedValues">Sorted values.</param>
	template <typename Type>
	void SortArray
	(
		const atl::Array<Type>&		inArray,			
		const atl::Array<float>&	inValues,			
		avl::SortingOrder::Type		inSortingOrder,		
		atl::Array<Type>&			outSortedArray,		
		atl::Array<float>&			outSortedValues		
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError("Inconsistent array sizes in SortArray.");
		}

		atl::Array<int> indices(inArray.Size());
		for( int i = 0; i < inArray.Size(); ++i )
			indices[i] = i;

		avl::SortIndicesByValues(indices.Begin(), indices.End(), inValues);

		outSortedArray.Clear();
		outSortedArray.Reserve(inArray.Size());
		outSortedValues.Clear();
		outSortedValues.Reserve(inArray.Size());

		if (inSortingOrder == avl::SortingOrder::Descending)
		{
			for( int i = indices.Size() - 1; i >= 0; --i )
			{
				int index = indices[i];
				outSortedArray.PushBack(inArray[index]);
				outSortedValues.PushBack(inValues[index]);
			}
		}
		else
		{
			for( int* i = indices.Begin(); i != indices.End(); ++i )
			{
				outSortedArray.PushBack(inArray[*i]);
				outSortedValues.PushBack(inValues[*i]);
			}
		}
	}

	/// Divides an array into two parts at the given index.
	/// <param name="inArray">Input array.</param>
	/// <param name="inIndex">Index of the first element that is passed to the second of the output arrays.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outArray1">First output array.</param>
	/// <param name="outArray2">Second output array.</param>
	template <typename Type>
	void SplitArray
	(
		const atl::Array<Type>&	inArray,	
		const int				inIndex,	
		bool					inInverse,	
		atl::Array<Type>&		outArray1,	
		atl::Array<Type>&		outArray2	
	)
	{
		if (inIndex < 0 || inIndex > inArray.Size())
		{
			throw atl::DomainError(L"Index out of range in SplitArray.");
		}
		const int index = (inInverse ? inArray.Size() - inIndex : inIndex);

		int size1 = index;
		int size2 = inArray.Size() - index;

		outArray1.Clear();
		outArray1.Reserve(size1);
		outArray1.Insert(outArray1.End(), inArray.Begin(), inArray.Begin() + index);

		outArray2.Clear();
		outArray2.Reserve(size2);
		outArray2.Insert(outArray2.End(), inArray.Begin() + index, inArray.End());
	}

	/// Cyclically shifts the elements of an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inShift">Input the number of positions each element should be shifted by.</param>
	/// <param name="inInverse">Reversed direction of shift.</param>
	/// <param name="outArray">Cyclically shifted array.</param>
	template <typename Type>
	void RotateArray
	(
		const atl::Array<Type>&	inArray,	
		int						inShift,	
		const bool				inInverse,	
		atl::Array<Type>&		outArray	
	)
	{
		outArray.Clear();

		if (inArray.Empty())
			return;
		
		outArray.Reserve(inArray.Size());

		if (inInverse)
		{
			inShift = -inShift;
		}

		int shift = (inShift >= 0) ? (inShift % inArray.Size()) : (inArray.Size() + inShift % inArray.Size());
		int reminder = inArray.Size() - shift;

		for( int i = 0; i < shift; ++i )
			outArray.PushBack(inArray[reminder + i]);

		for( int i = 0; i < reminder; ++i )
			outArray.PushBack(inArray[i]);
	}

	/// Transposes a matrix represented as an array of arrays.
	/// <param name="inArrayArray">Input array.</param>
	/// <param name="outArrayArray">Output array.</param>
	template <class Type>
	void TransposeArrayArray
	(
		const atl::Array<atl::Array<Type>>&	inArrayArray,	
		atl::Array<atl::Array<Type>>&		outArrayArray	
	)
	{
		int rowCount = inArrayArray.Size();

		if (rowCount == 0)
		{
			outArrayArray.Reset();
			return;
		}

		int colCount = inArrayArray.Front().Size();
		for (int i = 1; i < rowCount; ++i)
		{
			if (inArrayArray[i].Size() != colCount)
				throw atl::DomainError(L"Inconsistent array lengths in TransposeArrayArray.");
		}

		outArrayArray.Resize(colCount);
		for (int i = 0; i < colCount; ++i)
		{
			outArrayArray[i].Resize(rowCount);
		}

		for (int i = 0; i < colCount; ++i)
		{
			for (int j = 0; j < rowCount; ++j)
				outArrayArray[i][j] = inArrayArray[j][i];
		}
	}

	/// Creates two copies of the input array - one with elements removed at the beginning, the other with elements removed at the end.
	/// <param name="inArray">Input array.</param>
	/// <param name="inShift">Number of elements to be removed.</param>
	/// <param name="outArray1">Input array with inShift last elements removed.</param>
	/// <param name="outArray2">Input array with inShift first elements removed.</param>
	template <typename Type>
	void SlideArray
	(
		const atl::Array<Type>&	inArray,	
		int						inShift,	
		atl::Array<Type>&		outArray1,	
		atl::Array<Type>&		outArray2	
	)
	{
		outArray1.Clear();
		outArray2.Clear();

		int absShift  = std::abs(inShift);
		int outLength = std::max(0, inArray.Size() - absShift);
		
		if (outLength >= 1)
		{
			//assert(absShift < inArray.Size());
			outArray1.Insert(inArray.Begin(), inArray.Begin() + outLength);
			outArray2.Insert(inArray.Begin() + absShift, inArray.End());		
		}

		if (inShift < 0)
		{
			outArray1.Swap( outArray2 );
		}
	}

	/// Creates an array of the input array elements in reversed order.
	/// <param name="inArray">Input array.</param>
	/// <param name="outArray">Reversed array.</param>
	template <typename Type>
	void ReverseArray
	(
		const atl::Array<Type>&	inArray,
		atl::Array<Type>&		outArray
	)
	{
		outArray.Clear();
		outArray.Reserve(inArray.Size());

		for( int i = inArray.Size() - 1; i >= 0; --i )
			outArray.PushBack(inArray[i]);
	}

	/// Swaps two elements of an array.
	/// <param name="inIndex1">Index of the first element being swapped.</param>
	/// <param name="inIndex2">Index of the second element being swapped.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	template <typename Type>
	void SwapArrayElements
	(
		atl::Array<Type>&	ioArray,
		const int			inIndex1,	
		const int			inIndex2,	
		bool				inInverse	
	)
	{
		if (inIndex1 < 0 || inIndex1 >= ioArray.Size() || inIndex2 < 0 || inIndex2 >= ioArray.Size())
		{
			throw atl::DomainError(L"Index out of range in SwapArrayElements.");
		}

		if (inIndex1 != inIndex2)
			std::swap(ioArray[inInverse ? ioArray.Size() - 1 - inIndex1 : inIndex1], ioArray[inInverse ? ioArray.Size() - 1 - inIndex2 : inIndex2]);
	}

	/// Removes all Nil elements from an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="outArray">Output array.</param>
	/// <param name="outElementExisted">Array with the same size as input array representing if the element was not a Nil.</param>
	template <typename Type>
	void RemoveNils
	(
		const atl::Array< typename atl::ToConditionalType<Type>::Type >&	inArray,	
		atl::Array<Type>&													outArray,	
		atl::Array<bool>&													outElementExisted	
	)
	{
		outArray.Clear();
		outElementExisted.Reset( inArray.Size(), false );

		for (int i = 0; i < inArray.Size(); ++i)
		{
			if (inArray[i] != atl::NIL)
			{
				outArray.PushBack(inArray[i].Get());
				outElementExisted[i] = true;
			}
		}
	}

	/// Removes some trailing elements from the longer array of the two so that the output arrays have equal size.
	template <typename Type>
	void TrimArraysToEqualSize
	(
		const atl::Array<Type>&		inArray1,
		const atl::Array<Type>&		inArray2,
		atl::Array<Type>&			outArray1,
		atl::Array<Type>&			outArray2
	)
	{
		outArray1 = inArray1;
		outArray2 = inArray2;

		if (inArray1.Size() > inArray2.Size())
		{
			outArray1.Resize( inArray2.Size() );
		}
		else if (inArray1.Size() < inArray2.Size())
		{
			outArray2.Resize( inArray1.Size() );
		}
	}

	AVL_FUNCTION void SynchronizeArraysImpl
	(
		const atl::Array<float>&	inValues1,
		const atl::Array<float>&	inValues2,
		const float					inMaxDifference,
		atl::Array<int>&				outIndices1,
		atl::Array<int>&				outIndices2
	)
	THROW_AVL_ERRORS;

	/// Selects as many elements from each of the input arrays as possible, while assuring that the difference between corresponding values is not too big.
	template <typename Type>
	void SynchronizeArrays
	(
		const atl::Array<Type>&		inArray1,
		const atl::Array<Type>&		inArray2,
		const atl::Array<float>&	inValues1,
		const atl::Array<float>&	inValues2,
		const float					inMaxDifference,
		atl::Array<Type>&			outArray1,
		atl::Array<Type>&			outArray2
	)
	{
		if (inMaxDifference < 0)
			throw atl::DomainError("inMaxDifference negative in SynchronizeArrays.");
		if (inArray1.Size() != inValues1.Size() || inArray2.Size() != inValues2.Size())
		{
			throw atl::DomainError( "Inconsistent array lengths in SynchronizeArrays." );
		}

		atl::Array<int> fstIndices;
		atl::Array<int> sndIndices;
		SynchronizeArraysImpl( inValues1, inValues2, inMaxDifference, fstIndices, sndIndices );

		outArray1.Resize( fstIndices.Size() );
		outArray2.Resize( fstIndices.Size() );
		for (int i = 0; i < fstIndices.Size(); ++i)
		{
			outArray1[i] = inArray1[fstIndices[i]];
			outArray2[i] = inArray2[sndIndices[i]];
		}
	}

	/// Removes repeated elements from array.
	template <typename Type>
	void RemoveDuplicates
	(
		const atl::Array<Type>&		inArray,
		atl::Array<Type>&		outArray
	)
	{

		if (&inArray == &outArray)
			throw atl::DomainError("Input array is exactly the same as the output array");

		outArray.Clear();
		int outArraySize = 0;

		for (int i = 0; i < inArray.Size(); ++i)
		{
			bool elemMultiExist = false;

			for (int j = 0; j < outArraySize; ++j)
			{
				if (inArray[i] == outArray[j])
				{
					elemMultiExist = true;
					break;
				}
			}

			if (!elemMultiExist)
			{
				outArray.PushBack(inArray[i]);
				outArraySize++;
			}
		}
	}

} // namespace avl

namespace avs
{

	/// Add or removes elements at the end of an array until it reaches the requested new size.
	/// <param name="inNewSize">Default value: 1.</param>
	template <typename Type>
	void AvsFilter_ResizeArray
	(
		const atl::Array<Type>&	inArray,
		int						inNewSize,
		const Type&				inValue,
		atl::Array<Type>&		outArray
	)
	{
		if (inNewSize < 0)
			throw atl::DomainError("inNewSize negative in ResizeArray.");
		outArray = inArray;
		outArray.Resize( inNewSize, inValue );
	}

} // namespace avs

#endif // AVS_ARRAYTRANSFORMS_H

