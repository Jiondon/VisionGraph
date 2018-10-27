//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_CONDITIONALPROCESSING_H
#define AVL_CONDITIONALPROCESSING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include <map>

namespace avl
{


	/// Makes it possible to use conditional execution inside macrofilters with optional inputs.
	/// <param name="inOptionalValue">To be connected from an optional input of a macrofilter. Default value: atl::NIL.</param>
	/// <param name="outConditionalObject">Generates conditional execution.</param>
	template <typename Type>
	void OptionalToConditional
	(
		const typename atl::ToOptionalType<const Type&>::Type&	inOptionalValue,		
		typename atl::ToConditionalType<Type>::Type&			outConditionalObject	
	)
	{
		if (inOptionalValue == atl::NIL)
			outConditionalObject = atl::NIL;
		else
			outConditionalObject = inOptionalValue.Get();
	}

	/// Makes it possible to conditionally preprocess data that will be used on an optional input.
	/// <param name="inConditionalObject">Conditional object to be used on an optional input.</param>
	/// <param name="outOptionalValue">A value that can be directly used on an optional input. Default value: atl::NIL.</param>
	template <typename Type>
	void ConditionalToOptional
	(
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject,	
		typename atl::ToOptionalType<Type>::Type&					outOptionalValue		
	)
	{
		if (inConditionalObject == atl::NIL)
			outOptionalValue = atl::NIL;
		else
			outOptionalValue = inConditionalObject.Get();
	}

	/// Creates empty or single-element array from a conditional value.
	/// <param name="inConditionalObject">Input conditional object.</param>
	/// <param name="outArray">Empty or single-element array.</param>
	template <typename Type>
	void ConditionalToArray_Deprecated
	(
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject,	
		atl::Array<Type>& outArray							
	)
	{
		outArray.Clear();

		if (inConditionalObject != atl::NIL)
			outArray.PushBack(inConditionalObject.Get());
	}

	/// Checks a condition. If the condition is True, then copies the input object to the output; otherwise returns Nil.
	/// <param name="inObject">The data to be conditionally passed onto the output or not.</param>
	/// <param name="inCondition">Determines whether the data is passed onto the output or not.</param>
	/// <param name="outConditionalObject">The object if the condition is met or nothing otherwise.</param>
	template <typename Type>
	void MakeConditional
	(
		const Type&		inObject,											
		const bool		inCondition,										
		typename atl::ToConditionalType<Type>::Type& outConditionalObject	
	)
	{
		if (inCondition)
			outConditionalObject = inObject;
		else
			outConditionalObject = atl::NIL;
	}

	/// Returns the first not-Nil input object.
	/// <param name="inConditionalObject1">First conditional input object.</param>
	/// <param name="inConditionalObject2">Second conditional input object.</param>
	/// <param name="inConditionalObject3">Third conditional input object.</param>
	/// <param name="inConditionalObject4">Fourth conditional input object.</param>
	/// <param name="inConditionalObject5">Fifth conditional input object.</param>
	/// <param name="inConditionalObject6">Sixth conditional input object.</param>
	/// <param name="inConditionalObject7">Seventh conditional input object.</param>
	/// <param name="inConditionalObject8">Eighth conditional input object.</param>
	/// <param name="outConditionalObject">The first of the input objects that exists or nothing.</param>
	template <typename Type>
	void MergeConditionals
	(
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject1, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject2, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject3, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject4, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject5, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject6, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject7, 
		const typename atl::ToConditionalType<const Type&>::Type&	inConditionalObject8, 
		typename atl::ToConditionalType<Type>::Type&				outConditionalObject 
	)
	{
		if (inConditionalObject1 != atl::NIL)
			outConditionalObject = inConditionalObject1.Get();
		else if (inConditionalObject2 != atl::NIL)
			outConditionalObject = inConditionalObject2.Get();
		else if (inConditionalObject3 != atl::NIL)
			outConditionalObject = inConditionalObject3.Get();
		else if (inConditionalObject4 != atl::NIL)
			outConditionalObject = inConditionalObject4.Get();
		else if (inConditionalObject5 != atl::NIL)
			outConditionalObject = inConditionalObject5.Get();
		else if (inConditionalObject6 != atl::NIL)
			outConditionalObject = inConditionalObject6.Get();
		else if (inConditionalObject7 != atl::NIL)
			outConditionalObject = inConditionalObject7.Get();
		else if (inConditionalObject8 != atl::NIL)
			outConditionalObject = inConditionalObject8.Get();
		else
			outConditionalObject = atl::NIL;
	}

	/// Creates an array from not-Nil input elements.
	/// <param name="inConditionalObject1">First conditional input object.</param>
	/// <param name="inConditionalObject2">Second conditional input object.</param>
	/// <param name="inConditionalObject3">Third conditional input object.</param>
	/// <param name="inConditionalObject4">Fourth conditional input object.</param>
	/// <param name="inConditionalObject5">Fifth conditional input object.</param>
	/// <param name="inConditionalObject6">Sixth conditional input object.</param>
	/// <param name="inConditionalObject7">Seventh conditional input object.</param>
	/// <param name="inConditionalObject8">Eighth conditional input object.</param>
	/// <param name="outArray">Array of existing input objects.</param>
	template <typename Type>
	void MergeIntoArray
	(
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject1, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject2, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject3, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject4, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject5, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject6, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject7, 
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject8, 
		atl::Array<Type>& outArray 
	)
	{
		outArray.Clear();

		if (inConditionalObject1 != atl::NIL) outArray.PushBack(inConditionalObject1.Get());
		if (inConditionalObject2 != atl::NIL) outArray.PushBack(inConditionalObject2.Get());
		if (inConditionalObject3 != atl::NIL) outArray.PushBack(inConditionalObject3.Get());
		if (inConditionalObject4 != atl::NIL) outArray.PushBack(inConditionalObject4.Get());
		if (inConditionalObject5 != atl::NIL) outArray.PushBack(inConditionalObject5.Get());
		if (inConditionalObject6 != atl::NIL) outArray.PushBack(inConditionalObject6.Get());
		if (inConditionalObject7 != atl::NIL) outArray.PushBack(inConditionalObject7.Get());
		if (inConditionalObject8 != atl::NIL) outArray.PushBack(inConditionalObject8.Get());
	}

	/// Creates a non-conditional value from a conditional one by replacing Nil with the specified default value.
	/// <param name="inConditionalObject">Input conditional object.</param>
	/// <param name="inDefaultObject">Object to be used if the conditional object is empty.</param>
	/// <param name="outObject">Value of the conditional object, if it exists, or the default otherwise.</param>
	template <typename Type>
	void MergeDefault
	(
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject,	
		const Type&		inDefaultObject,					
		Type&			outObject							
	)
	{
		if (inConditionalObject != atl::NIL)
			outObject = inConditionalObject.Get();
		else
			outObject = inDefaultObject;
	}

	/// Chooses the first non-Nil object, or reports an error if there is no such object.
	/// <param name="inConditionalObject1">First conditional input object.</param>
	/// <param name="inConditionalObject2">Second conditional input object.</param>
	/// <param name="inConditionalObject3">Third conditional input object.</param>
	/// <param name="inConditionalObject4">Fourth conditional input object.</param>
	/// <param name="inConditionalObject5">Fifth conditional input object.</param>
	/// <param name="inConditionalObject6">Sixth conditional input object.</param>
	/// <param name="inConditionalObject7">Seventh conditional input object.</param>
	/// <param name="inConditionalObject8">Eighth conditional input object.</param>
	/// <param name="outObject">First not-Nil input object.</param>
	template <typename Type>
	void MergeBranches
	(
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject1,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject2,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject3,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject4,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject5,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject6,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject7,	
		const typename atl::ToConditionalType<const Type&>::Type& inConditionalObject8,	
		Type& outObject									
	)
	{
		if (inConditionalObject1 != atl::NIL)		outObject = inConditionalObject1.Get();
		else if (inConditionalObject2 != atl::NIL)	outObject = inConditionalObject2.Get();
		else if (inConditionalObject3 != atl::NIL)	outObject = inConditionalObject3.Get();
		else if (inConditionalObject4 != atl::NIL)	outObject = inConditionalObject4.Get();
		else if (inConditionalObject5 != atl::NIL)	outObject = inConditionalObject5.Get();
		else if (inConditionalObject6 != atl::NIL)	outObject = inConditionalObject6.Get();
		else if (inConditionalObject7 != atl::NIL)	outObject = inConditionalObject7.Get();
		else if (inConditionalObject8 != atl::NIL)	outObject = inConditionalObject8.Get();
		else
		{
			throw atl::DomainError(L"All of the conditional objects on input are Nil in MergeBranches.");
		}
	}

	/// Returns one of the two input objects depending on the specified condition.
	/// <param name="inObjectIfTrue">Object to be chosen if the condition is met.</param>
	/// <param name="inObjectIfFalse">Object to be chosen if the condition is NOT met.</param>
	/// <param name="inCondition">Determines which object is to be chosen.</param>
	/// <param name="outObject">Chosen object.</param>
	template <typename Type>
	void ChooseByPredicate
	(
		const Type&	inObjectIfTrue,		
		const Type& inObjectIfFalse,	
		bool inCondition,				
		Type& outObject					
	)
	{
		if (inCondition)
			outObject = inObjectIfTrue;
		else
			outObject = inObjectIfFalse;
	}

	/// Swaps two objects depending on the specified condition.
	/// <param name="inObject1">First object.</param>
	/// <param name="inObject2">Second object.</param>
	/// <param name="inSwap">Determines whether the objects are swapped.</param>
	/// <param name="outObject1">First output object.</param>
	/// <param name="outObject2">Second output object.</param>
	template <typename Type>
	void SwapObjects
	(
		const Type&	inObject1,	
		const Type& inObject2,	
		bool inSwap,			
		Type& outObject1,		
		Type& outObject2		
	)
	{
		if (inSwap)
		{
			outObject1 = inObject2;
			outObject2 = inObject1;
		}
		else
		{
			outObject1 = inObject1;
			outObject2 = inObject2;
		}
	}

	/// Returns one of the three input objects depending on whether the associated input value falls below, in or above the specified range.
	/// <param name="inObjectIfLower">Object to be chosen when the value is below the range.</param>
	/// <param name="inObjectIfInRange">Object to be chosen when the value is in the range.</param>
	/// <param name="inObjectIfHigher">Object to be chosen when the value is above the range.</param>
	/// <param name="inValue">Value which is compared against the range.</param>
	/// <param name="inMinimum">Lower end of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Upper end of the range. Default value: atl::NIL.</param>
	/// <param name="outObject">Chosen object.</param>
	template <typename Type>
	void ChooseByRange
	(
		const Type&	inObjectIfLower,	
		const Type& inObjectIfInRange,	
		const Type& inObjectIfHigher,	
		float inValue,				
		atl::Optional<float> inMinimum,	
		atl::Optional<float> inMaximum,	
		Type& outObject					
	)
	{
		if (inValue != inValue) // isNan
		{
			throw atl::DomainError(L"Incorrect (NaN) float value on inValue input in ChooseByRange.");
		}

		if (inMinimum != atl::NIL && inValue < inMinimum.Get())
		{
			outObject = inObjectIfLower;
		}
		else if (inMaximum != atl::NIL && inMaximum.Get() < inValue)
		{
			outObject = inObjectIfHigher;
		}
		else
		{
			outObject = inObjectIfInRange;
		}
	}

	/// Returns one of the input objects depending on the specified case index.
	/// <param name="inObjectIfCase0">Object to be chosen for the case 0.</param>
	/// <param name="inObjectIfCase1">Object to be chosen for the case 1.</param>
	/// <param name="inObjectIfCase2">Object to be chosen for the case 2.</param>
	/// <param name="inObjectIfCase3">Object to be chosen for the case 3.</param>
	/// <param name="inObjectIfCase4">Object to be chosen for the case 4.</param>
	/// <param name="inObjectIfCase5">Object to be chosen for the case 5.</param>
	/// <param name="inObjectIfCase6">Object to be chosen for the case 6.</param>
	/// <param name="inObjectIfCase7">Object to be chosen for the case 7.</param>
	/// <param name="inCaseIndex">Determines which object will be chosen.</param>
	/// <param name="outObject">Chosen object.</param>
	template <typename Type>
	void ChooseByCase
	(
		const Type&	inObjectIfCase0,	
		const Type&	inObjectIfCase1,	
		const Type&	inObjectIfCase2,	
		const Type&	inObjectIfCase3,	
		const Type&	inObjectIfCase4,	
		const Type&	inObjectIfCase5,	
		const Type&	inObjectIfCase6,	
		const Type&	inObjectIfCase7,	
		int inCaseIndex,				
		Type& outObject					
	)
	{
		switch(inCaseIndex)
		{
			case 0:		outObject = inObjectIfCase0;		break;
			case 1:		outObject = inObjectIfCase1;		break;
			case 2:		outObject = inObjectIfCase2;		break;
			case 3:		outObject = inObjectIfCase3;		break;
			case 4:		outObject = inObjectIfCase4;		break;
			case 5:		outObject = inObjectIfCase5;		break;
			case 6:		outObject = inObjectIfCase6;		break;
			case 7:		outObject = inObjectIfCase7;		break;
			
			default:
				throw atl::DomainError(L"Case index out of range in ChooseByCase.");
		}
	}

	/// Separates the elements of the input array into two output arrays. The first output array contains all elements for which the associated predicate is True.
	/// <param name="inArray">Elements to be classified.</param>
	/// <param name="inPredicate">Corresponding logical values determining the output array for each of the elements.</param>
	/// <param name="outAccepted">Array of elements corresponding to 'true' values.</param>
	/// <param name="outRejected">Array of elements corresponding to 'false' values.</param>
	template <typename Type>
	void ClassifyByPredicate
	(
		const atl::Array<Type>&	inArray,		
		const atl::Array<bool>& inPredicate,	
		atl::Array<Type>&		outAccepted,	
		atl::Array<Type>&		outRejected		
	)
	{
		if (inPredicate.Size() != inArray.Size())
		{
			throw atl::DomainError(L"Inconsistent array lengths on input in ClassifyByPredicate.");
		}

		outAccepted.Clear();
		outRejected.Clear();

		// TODO: Count and reserve memory

		for( int i = 0; i < inArray.Size(); ++i )
		{
			if (inPredicate[i])
				outAccepted.PushBack(inArray[i]);
			else
				outRejected.PushBack(inArray[i]);
		}
	}

	/// Separates the elements of the input array into three output arrays, depending on whether the related values fall below, into or above the specified range.
	/// <param name="inArray">Elements to be classified.</param>
	/// <param name="inValues">Corresponding values to be compared against the range.</param>
	/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
	/// <param name="outAccepted">Array of elements corresponding to values matching the range.</param>
	/// <param name="outRejected">Array of elements corresponding to values outside the range.</param>
	/// <param name="outLower">Array of elements corresponding to values lower than inMinimum.</param>
	/// <param name="outHigher">Array of elements corresponding to values higher than inMaximum.</param>
	/// <param name="outIsAccepted">Represents whether corresponding values are in the range.</param>
	/// <param name="outIsRejected">Represents whether corresponding values are outside the range.</param>
	template <typename Type>
	void ClassifyByRange
	(
		const atl::Array<Type>&	inArray,							
		const atl::Array<float>&  inValues,						
		atl::Optional<float> inMinimum,							
		atl::Optional<float> inMaximum,							
		atl::Optional<atl::Array<Type>&> outAccepted = atl::NIL,	
		atl::Optional<atl::Array<Type>&> outRejected = atl::NIL,	
		atl::Optional<atl::Array<Type>&> outLower = atl::NIL,		
		atl::Optional<atl::Array<Type>&> outHigher = atl::NIL,		
		atl::Optional<atl::Array<bool>&> outIsAccepted = atl::NIL,	
		atl::Optional<atl::Array<bool>&> outIsRejected = atl::NIL	
	)
	{
		if (inValues.Size() != inArray.Size())
		{
			throw atl::DomainError("Inconsistent array lengths on input in ClassifyByRange.");
		}

		if (outAccepted != atl::NIL) outAccepted.Get().Clear();
		if (outRejected != atl::NIL) outRejected.Get().Clear();
		if (outLower != atl::NIL) outLower.Get().Clear();
		if (outHigher != atl::NIL) outHigher.Get().Clear();
		if (outIsAccepted != atl::NIL) outIsAccepted.Get().Resize(inArray.Size());
		if (outIsRejected != atl::NIL) outIsRejected.Get().Resize(inArray.Size());

		for (int i = 0; i < inArray.Size(); ++i)
		{
			float value = inValues[i];
			if (value != value) // isNaN
			{
				throw atl::DomainError("Incorrect (NaN) float value on inValues input in ClassifyByRange.");
			}

			if ((inMinimum == atl::NIL || inMinimum.Get() <= value) && (inMaximum == atl::NIL || value <= inMaximum.Get()))
			{
				if (outAccepted != atl::NIL) outAccepted.Get().PushBack(inArray[i]);
				if (outIsAccepted != atl::NIL) outIsAccepted.Get()[i] = true;
				if (outIsRejected != atl::NIL) outIsRejected.Get()[i] = false;
			}
			else
			{
				if (outIsAccepted != atl::NIL) outIsAccepted.Get()[i] = false;
				if (outIsRejected != atl::NIL) outIsRejected.Get()[i] = true;

				if (inMinimum != atl::NIL && value < inMinimum.Get())
				{
					if (outLower != atl::NIL) outLower.Get().PushBack(inArray[i]);
					if (outRejected != atl::NIL) outRejected.Get().PushBack(inArray[i]);
				}
				else if (inMaximum != atl::NIL && value > inMaximum.Get())
				{
					if (outHigher != atl::NIL) outHigher.Get().PushBack(inArray[i]);
					if (outRejected != atl::NIL) outRejected.Get().PushBack(inArray[i]);
				}
			}
		}
	}

	/// Separates the elements of the input array into several output arrays, depending on the associated array of case indices.
	/// <param name="inArray">Elements to be classified.</param>
	/// <param name="inCaseIndices">Reference values corresponding to the input array elements.</param>
	/// <param name="outCase0">Elements corresponding to the case 0.</param>
	/// <param name="outCase1">Elements corresponding to the case 1.</param>
	/// <param name="outCase2">Elements corresponding to the case 2.</param>
	/// <param name="outCase3">Elements corresponding to the case 3.</param>
	/// <param name="outCase4">Elements corresponding to the case 4.</param>
	/// <param name="outCase5">Elements corresponding to the case 5.</param>
	/// <param name="outCase6">Elements corresponding to the case 6.</param>
	/// <param name="outCase7">Elements corresponding to the case 7.</param>
	template <typename Type>
	void ClassifyByCase
	(
		const atl::Array<Type>&	inArray,		
		const atl::Array<int>&  inCaseIndices,	
		atl::Array<Type>& outCase0,				
		atl::Array<Type>& outCase1,				
		atl::Array<Type>& outCase2,				
		atl::Array<Type>& outCase3,				
		atl::Array<Type>& outCase4,				
		atl::Array<Type>& outCase5,				
		atl::Array<Type>& outCase6,				
		atl::Array<Type>& outCase7				
	)
	{
		if (inCaseIndices.Size() != inArray.Size())
		{
			throw atl::DomainError(L"Inconsistent array lengths on input in ClassifyByCase.");
		}

		outCase0.Clear();
		outCase1.Clear();
		outCase2.Clear();
		outCase3.Clear();
		outCase4.Clear();
		outCase5.Clear();
		outCase6.Clear();
		outCase7.Clear();

		for( int i = 0; i < inArray.Size(); ++i )
		{
			switch(inCaseIndices[i])
			{
				case 0:		outCase0.PushBack(inArray[i]);		break;
				case 1:		outCase1.PushBack(inArray[i]);		break;
				case 2:		outCase2.PushBack(inArray[i]);		break;
				case 3:		outCase3.PushBack(inArray[i]);		break;
				case 4:		outCase4.PushBack(inArray[i]);		break;
				case 5:		outCase5.PushBack(inArray[i]);		break;
				case 6:		outCase6.PushBack(inArray[i]);		break;
				case 7:		outCase7.PushBack(inArray[i]);		break;

				default:
					throw atl::DomainError(L"Incorrect case index in ClassifyByCase.");
			}
		}
	}

	/// Groups the elements of the input array into output arrays, depending on the associated array of case indices.
	/// <param name="inArray">Elements to be grouped.</param>
	/// <param name="inCaseIndices">Reference values corresponding to the input array elements.</param>
	/// <param name="outGroupedElements">List of input elements for each case.</param>
	/// <param name="outGroupedIndices">List of input element indices for each case.</param>
	template <typename Type>
	void GroupByCase
	(
		const atl::Array<Type>&	inArray,		
		const atl::Array<int>&  inCaseIndices,	
		atl::Array<atl::Array<Type> >&	outGroupedElements,	
		atl::Array<atl::Array<int> >&	outGroupedIndices	
	)
	{
		if (inCaseIndices.Size() != inArray.Size())
		{
			throw atl::DomainError(L"Inconsistent array lengths on input in GroupByCase.");
		}

		std::map<int, int> caseDict;
		int caseCount = 0;
		for (int i = 0; i < inArray.Size(); ++i)
		{
			const int index = inCaseIndices[i];
			if (caseDict.find(index) == caseDict.end())
			{
				caseDict[index] = caseCount++;
			}
		}

		outGroupedElements.Reset( caseCount );
		outGroupedIndices.Reset( caseCount );
		for (int i = 0; i < inArray.Size(); ++i)
		{
			const int index = caseDict[inCaseIndices[i]];
			outGroupedElements[index].PushBack( inArray[i] );
			outGroupedIndices[index].PushBack( i );
		}
	}

	/// Groups the elements of the input array into output arrays, depending on the associated array of case indices. Assumes that the range of case indices is continuous and starts at zero.
	/// <param name="inArray">Elements to be grouped.</param>
	/// <param name="inCaseIndices">Reference values corresponding to the input array elements.</param>
	/// <param name="inCaseCount">Number of cases, each of which is between 0 and inCaseCount - 1 inclusive.</param>
	/// <param name="outGroupedElements">List of input elements for each case.</param>
	/// <param name="outGroupedIndices">List of input element indices for each case.</param>
	template <typename Type>
	void GroupByCase_Synchronized
	(
		const atl::Array<Type>&	inArray,		
		const atl::Array<int>&  inCaseIndices,	
		const int				inCaseCount,	
		atl::Array<atl::Array<Type> >&	outGroupedElements,	
		atl::Array<atl::Array<int> >&	outGroupedIndices	
	)
	{
		if (inCaseIndices.Size() != inArray.Size())
		{
			throw atl::DomainError(L"Inconsistent array lengths on input in GroupByCase_Synchronized.");
		}

		outGroupedElements.Reset( inCaseCount );
		outGroupedIndices.Reset( inCaseCount );
		for (int i = 0; i < inArray.Size(); ++i)
		{
			const int index = inCaseIndices[i];
			if (!(0 <= index && index < inCaseCount))
			{
				throw atl::DomainError(L"Incorrect case index in GroupByCase_Synchronized.");
			}
			outGroupedElements[index].PushBack( inArray[i] );
			outGroupedIndices[index].PushBack( i );
		}
	}

} // namespace avl

#endif // AVL_CONDITIONALPROCESSING_H

