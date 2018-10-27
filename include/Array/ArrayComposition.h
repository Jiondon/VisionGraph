//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_ARRAYCOMPOSITION_H
#define AVS_ARRAYCOMPOSITION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"

namespace avl
{


	/// Removes the first or all of the elements of the given value from an array.
	/// <param name="inValue">Input value to be removed.</param>
	/// <param name="inRemoveAll">Remove all occurrences, not only the first one.</param>
	template <typename Type>
	void RemoveValueFromArray
	(
		atl::Array<Type>&	ioArray,
		const Type&			inValue,		
		bool				inRemoveAll		
	)
	{
		for (Type* i = ioArray.Begin(); i != ioArray.End(); )
		{
			if (*i == inValue)
			{
				i = ioArray.Erase(i);

				if (!inRemoveAll)
					break;
			}
			else
			{
				++i;
			}
		}
	}

	/// Removes the elements of indices in the given range from an array.
	/// <param name="inStart">Index of the first element to be removed.</param>
	/// <param name="inLength">Number of elements to be removed. Default value: atl::NIL.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	template <typename Type>
	void RemoveRangeFromArray
	(
		atl::Array<Type>&		ioArray,
		int						inStart,	
		atl::Optional<int>		inLength,	
		bool					inInverse	
	)
	{
		if (inLength != atl::NIL && inLength.Get() < 0)
			throw atl::DomainError("Negative inLength in RemoveRangeFromArray.");

		if (inStart < 0)
			throw atl::DomainError("Negative inStart in RemoveRangeFromArray.");

		if (inLength != atl::NIL && inLength.Get() > 0 && (!(0 <= inStart && inStart < ioArray.Size())))
			throw atl::DomainError("Index out of range in RemoveRangeFromArray.");

		int startIndex = std::min(ioArray.Size(), inStart);
		int endIndex = std::min(ioArray.Size(), inStart + (inLength == atl::NIL ? ioArray.Size() : inLength.Get()));

		if (inInverse)
		{
			endIndex = std::max(0, ioArray.Size() - inStart);
			startIndex = std::max(0, endIndex - (inLength == atl::NIL ? ioArray.Size() : inLength.Get()));
		}

		int length = endIndex - startIndex;

		if (length > 0)
		{
			ioArray.Erase(ioArray.Begin() + startIndex, ioArray.Begin() + endIndex);
		}
	}

	/// Removes the element of the given index from an array.
	/// <param name="inIndex">Index of element to be removed.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	/// <param name="outRemovedValue">Value of removed element.</param>
	template <typename Type>
	void RemoveArrayElement
	(
		atl::Array<Type>&	ioArray,
		int					inIndex,		
		bool				inInverse,		
		Type&				outRemovedValue	
	)
	{
		if (!(0 <= inIndex && inIndex < ioArray.Size()))
			throw atl::DomainError("Array index out of range in RemoveArrayElement.");

		const int index = inInverse ? ioArray.Size() - 1 - inIndex : inIndex;
		outRemovedValue = ioArray[index];	// TODO: move
		ioArray.Erase(ioArray.Begin() + index);
	}

	/// Receives an array of arrays, and creates a single one-dimensional array containing all individual elements.
	/// <param name="inArray">Array to be flattened.</param>
	/// <param name="outFlattenedArray">Flattened array.</param>
	template <typename Type>
	void FlattenArray
	(
		const atl::Array<atl::Array<Type> >&	inArray,			
		atl::Array<Type>&						outFlattenedArray	
	)
	{
		int newSize = 0;
		for (int i = 0; i < inArray.Size(); ++i)
			newSize += inArray[i].Size();

		outFlattenedArray.Clear();
		outFlattenedArray.Reserve(newSize);

		for (int i = 0; i < inArray.Size(); ++i)
			outFlattenedArray.Insert(outFlattenedArray.End(), inArray[i].Begin(), inArray[i].End());
	}

} // namespace avl

namespace avs
{

	/// Inserts a new element at the end of an array.
	/// <param name="inValue">Value to be appended.</param>
	template <typename Type>
	void AvsFilter_AppendToArray
	(
		atl::Array<Type>&	ioArray,
		const Type&			inValue		
	)
	{
		ioArray.PushBack(inValue);
	}

	/// Inserts a new element to an array at a specified location.
	/// <param name="inValue">Input value to be inserted.</param>
	/// <param name="inIndex">Input index within the inArray at which the inValue will be placed.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	template <typename Type>
	void AvsFilter_InsertToArray
	(
		atl::Array<Type>&	ioArray,
		const Type&			inValue,	
		int					inIndex,	
		bool				inInverse	
	)
	{
		if (!(0 <= inIndex && inIndex <= ioArray.Size()))
		{
			throw atl::DomainError("Index out of range in InsertToArray.");
		}

		ioArray.Insert(ioArray.Begin() + (inInverse ? ioArray.Size() - inIndex : inIndex), inValue);
	}

	/// Concatenates the input arrays one after another.
	/// <param name="inArray1">First array to be joined.</param>
	/// <param name="inArray2">Second array to be joined.</param>
	/// <param name="inArray3">Third array to be joined.</param>
	/// <param name="inArray4">Fourth array to be joined.</param>
	/// <param name="outJoinedArray">Joined array.</param>
	template <typename Type>
	void AvsFilter_JoinArrays
	(
		const atl::Array<Type>&	inArray1,		
		const atl::Array<Type>&	inArray2,		
		const atl::Array<Type>&	inArray3,		
		const atl::Array<Type>&	inArray4,		
		atl::Array<Type>&		outJoinedArray	
	)
	{
		outJoinedArray.Clear();
		outJoinedArray.Reserve(inArray1.Size() + inArray2.Size() + inArray3.Size() + inArray4.Size());

		outJoinedArray.Insert(outJoinedArray.End(), inArray1.Begin(), inArray1.End());
		outJoinedArray.Insert(outJoinedArray.End(), inArray2.Begin(), inArray2.End());
		outJoinedArray.Insert(outJoinedArray.End(), inArray3.Begin(), inArray3.End());
		outJoinedArray.Insert(outJoinedArray.End(), inArray4.Begin(), inArray4.End());
	}

	/// Inserts an array at the specified index of another one.
	/// <param name="inInsertedArray">Input array to be inserted.</param>
	/// <param name="inIndex">Input index within the inArray at which the first element of the inInsertedArray will be placed.</param>
	/// <param name="inInverse">Reversed order in the array. Default value: False.</param>
	template <typename Type>
	void AvsFilter_InsertArrayToArray
	(
		atl::Array<Type>&		ioArray,
		const atl::Array<Type>&	inInsertedArray,	
		int						inIndex,			
		bool					inInverse			
	)
	{
		if (!(0 <= inIndex && inIndex <= ioArray.Size()))
		{
			throw atl::DomainError("Index out of range in InsertArrayToArray.");
		}

		ioArray.Insert(ioArray.Begin() + (inInverse ? ioArray.Size() - inIndex : inIndex), inInsertedArray.Begin(), inInsertedArray.End());
	}

} // namespace avs

#endif // AVS_ARRAYCOMPOSITION_H

