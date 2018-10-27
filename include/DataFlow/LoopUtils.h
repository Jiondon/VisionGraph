//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_LOOPUTILS_H
#define AVL_LOOPUTILS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"
#include "AVLCommon/BaseState.h"
#include "LoopControl.h"

namespace avl
{


	template<typename T>
	struct LastObjectState
	{
		T		object;
		int		index;
		int		iterationIndex;
		bool	isFirstUse;

		LastObjectState() : object(), index(), iterationIndex(-1), isFirstUse(true) {}
	};

	template<typename T>
	struct LastExtremumObjectState
	{
		T			object;
		float		value;
		int			index;
		int			iterationIndex;
		bool		isFirstUse;

		LastExtremumObjectState() : object(), value(), index(), iterationIndex(-1), isFirstUse(true) {}
	};

	struct CountValueInLoopState
	{
		int count;

		CountValueInLoopState() : count(0) {}
	};

	struct CountConditionInLoopState
	{
		int trueCount;
		int falseCount;

		CountConditionInLoopState() : trueCount(0), falseCount(0) {}
	};

	struct TestFirstIterationState : public BaseState
	{};


	/// Returns the current and the previous object.
	/// <param name="inInitialObject">Object to be used as the previous one in first iteration.</param>
	/// <param name="outCurrentObject">Object from this iteration.</param>
	/// <param name="outPreviousObject">Object from previous iteration.</param>
	template<typename T>
	void LastTwoObjects
	(
		LastObjectState<T>&		ioState,
		const T&				inObject,
		const T&				inInitialObject,		
		T&						outCurrentObject,		
		T&						outPreviousObject		
	)
	{
		outCurrentObject = inObject;

		if (ioState.isFirstUse)
		{
			ioState.isFirstUse = false;
			outPreviousObject = inInitialObject;
		}
		else
		{
			outPreviousObject = ioState.object;
		}

		ioState.object = inObject;
	}

	/// Returns an array of the N most recent objects. Initializes itself with an array of N initial objects.
	/// <param name="inMaxCount">Number of last objects that are remembered.</param>
	/// <param name="inInitialObject">Initial object of the array elements.</param>
	/// <param name="ioObjectArray">Array of N most recent objects.</param>
	template<typename T>
	void LastExactlyNObjects
	(
		const T&						inObject,
		int								inMaxCount,			
		const T&						inInitialObject,	
		atl::Array<T>&					ioObjectArray		
	)
	{
		if (inMaxCount < 0)
		{
			throw atl::DomainError("inMaxCount cannot be negative in LastExactlyNObjects.");
		}
		else if (inMaxCount == 0)
		{
			ioObjectArray.Clear();
			return;
		}

		if (ioObjectArray.Size() >= inMaxCount)
		{
			ioObjectArray.Erase(ioObjectArray.Begin(), ioObjectArray.Begin() + (ioObjectArray.Size() - inMaxCount + 1) );
		}
		else
		{
			while (ioObjectArray.Size() < (inMaxCount - 1))
				ioObjectArray.PushBack( inInitialObject );
		}

		ioObjectArray.PushBack( inObject );
	}

	/// Returns the most recent value for which the associated condition was True.
	/// <param name="inObject">Object that may be chosen.</param>
	/// <param name="inInitialObject">Object to be used before first marked object appears.</param>
	/// <param name="inCondition">Indicates whether the input object will be chosen.</param>
	/// <param name="outObject">Object from the last iteration in which the condition was true.</param>
	/// <param name="outIndex">Index of iteration when the last marked object appeared.</param>
	template<typename T>
	void LastMarkedObject
	(
		LastObjectState<T>&		ioState,
		const T&				inObject,			
		const T&				inInitialObject,	
		bool					inCondition,		
		T&						outObject,			
		int&					outIndex			
	)
	{
		++ioState.iterationIndex;

		if (ioState.isFirstUse)
		{
			ioState.isFirstUse = false;

			if (!inCondition)
				ioState.object = inInitialObject;
			ioState.index = -1;
		}

		if (inCondition)
		{
			ioState.object = inObject;
			ioState.index = ioState.iterationIndex;
		}

		outObject = ioState.object;
		outIndex = ioState.index;
	}

	/// Returns the most recent value other than Nil. If there is no such value, returns the initial object.
	/// <param name="inObject">Object that may be chosen.</param>
	/// <param name="inInitialObject">Object to be used before first proper object appears.</param>
	/// <param name="outObject">The last object that existed.</param>
	/// <param name="outIndex">Index of iteration when the last object appeared.</param>
	template<typename T>
	void LastNotNil
	(
		LastObjectState<T>&		ioState,
		const typename atl::ToConditionalType<const T&>::Type& inObject,	
		const T&				inInitialObject,	
		T&						outObject,			
		int&					outIndex			
	)
	{
		++ioState.iterationIndex;

		if (ioState.isFirstUse)
		{
			ioState.isFirstUse = false;

			if (inObject == atl::NIL)
				ioState.object = inInitialObject;
			ioState.index = -1;
		}

		if (inObject != atl::NIL)
		{
			ioState.object = inObject.Get();
			ioState.index = ioState.iterationIndex;
		}

		outObject = ioState.object;
		outIndex = ioState.index;
	}

	/// Returns the object for which the associated value was the highest among all iterations.
	/// <param name="inObject">Object that may be chosen.</param>
	/// <param name="inValue">Value associated with the input object.</param>
	/// <param name="outMaximumObject">The object whose associated value was the highest.</param>
	/// <param name="outMaximumValue">Maximum value that appeared in the loop.</param>
	/// <param name="outMaximumIndex">Index of iteration when the maximum object appeared.</param>
	template<typename T>
	void LoopMaximum
	(
		LastExtremumObjectState<T>&		ioState,
		const T&						inObject,			
		float							inValue,			
		T&								outMaximumObject,	
		float&							outMaximumValue,	
		int&							outMaximumIndex		
	)
	{
		++ioState.iterationIndex;

		if (ioState.isFirstUse || inValue > ioState.value)
		{
			ioState.object = inObject;
			ioState.value = inValue;
			ioState.index = ioState.iterationIndex;
			ioState.isFirstUse = false;
		}

		outMaximumObject = ioState.object;
		outMaximumValue = ioState.value;
		outMaximumIndex = ioState.index;
	}

	/// Returns the object for which the associated value was the lowest among all iterations.
	/// <param name="inObject">Object that may be chosen.</param>
	/// <param name="inValue">Value associated with the input object.</param>
	/// <param name="outMinimumObject">The object whose associated value was the lowest.</param>
	/// <param name="outMinimumValue">Minimum value that appeared in the loop.</param>
	/// <param name="outMinimumIndex">Index of iteration when the minimum object appeared.</param>
	template<typename T>
	void LoopMinimum
	(
		LastExtremumObjectState<T>&		ioState,
		const T&						inObject,			
		float							inValue,			
		T&								outMinimumObject,	
		float&							outMinimumValue,	
		int&							outMinimumIndex		
	)
	{
		++ioState.iterationIndex;

		if (ioState.isFirstUse || inValue < ioState.value)
		{
			ioState.object = inObject;
			ioState.value = inValue;
			ioState.index = ioState.iterationIndex;
			ioState.isFirstUse = false;
		}

		outMinimumObject = ioState.object;
		outMinimumValue = ioState.value;
		outMinimumIndex = ioState.index;
	}

	/// Counts value occurrences in all loop iterations.
	/// <param name="inInputValue">Value that will be counted if it is equal to inValue.</param>
	/// <param name="inValue">Value to count.</param>
	/// <param name="outCount">Number of value occurrences.</param>
	template<typename T>
	void CountValueInLoop
	(
		avl::CountValueInLoopState&	ioState,
		const T&					inInputValue,	
		const T&					inValue,	
		int&						outCount	
	)
	{
		if (inInputValue == inValue)
		{
			++ioState.count;
		}
		outCount = ioState.count;
	}

	/// <summary>Counts number of positive predicates in loop.</summary>
	/// <param name="inCondition">Inspected condition.</param>
	/// <param name="inReset">Reset counters and stop counting. Default value: False.</param>
	/// <param name="outTrueCount">Number of positive inspections.</param>
	/// <param name="outFalseCount">Number of negative inspections.</param>
	AVL_FUNCTION void CountConditions
	(
		avl::CountConditionInLoopState&	ioState,
		const bool&						inCondition,	
		const bool&						inReset,		
		int&							outTrueCount,	
		int&							outFalseCount	
	)
	THROW_AVL_ERRORS;

	/// 
	inline LoopControl::Type ExitMacrofilterLoop
	(
		bool inCondition
	)
	{
		return inCondition ? LoopControl::Break : LoopControl::EndLoop;
	}

	/// Returns an array of most recent objects.
	/// <param name="inMaxCount">Number of last objects that are remembered. Default value: atl::NIL.</param>
	/// <param name="ioObjectArray">Array of most recent objects.</param>
	template<typename T>
	void LastMultipleObjects
	(
		const T&						inObject,
		atl::Optional<int>				inMaxCount,		
		atl::Array<T>&					ioObjectArray	
	)
	{
		if (inMaxCount != atl::NIL)
		{
			if (inMaxCount.Get() < 0)
			{
				throw atl::DomainError("inMaxCount cannot be negative in LastMultipleObjects.");
			}
			else if (inMaxCount.Get() == 0)
			{
				ioObjectArray.Clear();
				return;
			}
			else if (ioObjectArray.Size() >= inMaxCount.Get())
			{
				ioObjectArray.Erase(ioObjectArray.Begin(), ioObjectArray.Begin() + (ioObjectArray.Size() - inMaxCount.Get() + 1));
			}
		}

		ioObjectArray.PushBack( inObject );
	}

	namespace avl_impl
	{
		template<typename T>
		struct AccumulateElementsHelper
		{
			static void Accumulate(atl::Array<T>& ioArray, const atl::Conditional<const T&>& inElement)
			{
				if (inElement != atl::NIL)
					ioArray.PushBack(inElement.Get());
			}
		};

		template<typename T>
		struct AccumulateElementsHelper< atl::Conditional<T> >
		{
			static void Accumulate(atl::Array< atl::Conditional<T> >& ioArray, const atl::Conditional<T>& inElement)
			{
				ioArray.PushBack(inElement);
			}
		};
	}


	/// Creates an array from elements appearing in many iterations.
	/// <param name="inElement">Element to be put into an array.</param>
	/// <param name="inCondition">Flag indicating whether to put the input element into an array or not.</param>
	/// <param name="inMaxSize">Maximum number of last elements that are remembered. Default value: atl::NIL.</param>
	/// <param name="ioArray">Array of accumulated elements.</param>
	template<typename T>
	void AccumulateElements
	(
		const typename atl::ToConditionalType<const T&>::Type&	inElement,		
		bool													inCondition,	
		atl::Optional<int>										inMaxSize,		
		atl::Array<T>&											ioArray			
	)
	{
		if (inCondition)
			avl_impl::AccumulateElementsHelper<T>::Accumulate(ioArray, inElement);

		if (inMaxSize != atl::NIL)
		{
			if (inMaxSize.Get() < 0)
				throw atl::DomainError(L"inMaxSize cannot be negative in AccumulateElements.");

			if (ioArray.Size() > inMaxSize.Get())
				ioArray.Erase(ioArray.Begin(), ioArray.Begin() + (ioArray.Size() - inMaxSize.Get()));
		}
	}

	/// Joins arrays appearing in consecutive iterations.
	/// <param name="inArray">Array to be appended to the end.</param>
	/// <param name="inMaxSize">Maximum number of last elements that are remembered. Default value: atl::NIL.</param>
	/// <param name="ioArray">Accumulated array.</param>
	template<typename T>
	void AccumulateArray
	(
		const atl::Array<T>&			inArray,		
		atl::Optional<int>				inMaxSize,		
		atl::Array<T>&					ioArray		
	)
	{
		ioArray.Insert(ioArray.End(), inArray.Begin(), inArray.End());

		if (inMaxSize != atl::NIL)
		{
			if (inMaxSize.Get() < 0)
				throw atl::DomainError(L"inMaxSize cannot be negative in AccumulateArray.");

			if (ioArray.Size() > inMaxSize.Get())
				ioArray.Erase(ioArray.Begin(), ioArray.Begin() + (ioArray.Size() - inMaxSize.Get()));
		}
	}

	/// Joins arrays appearing in consecutive iterations.
	/// <param name="inArray">Array to be joined.</param>
	/// <param name="ioJoinedArray">Joined array.</param>
	template<typename T>
	void JoinArrays_OfLoop
	(
		const atl::Array<T>&			inArray,		
		atl::Array<T>&					ioJoinedArray	
	)
	{
		ioJoinedArray.Insert(ioJoinedArray.End(), inArray.Begin(), inArray.End());
	}

	/// Checks if the input object is different than in the previous iteration.
	/// <param name="inInitialResult">Result of the filter at first iteration.</param>
	/// <param name="outChanged">Is object changed.</param>
	/// <param name="outPreviousObject">Object from previous iteration (in first iteration equals inObject).</param>
	template<typename T>
	void TestObjectChanged
	(
		LastObjectState<T>&		ioState,
		const T&				inObject,
		bool					inInitialResult,		
		bool&					outChanged,				
		T&						outPreviousObject		
	)
	{
		if (ioState.isFirstUse)
		{
			ioState.isFirstUse = false;
			outPreviousObject = inObject;
			outChanged = inInitialResult;
		}
		else
		{
			outChanged = (ioState.object != inObject);
			outPreviousObject = ioState.object;
		}

		ioState.object = inObject;
	}

	/// <summary>Checks if a loop is in the first iteration.</summary>
	AVL_FUNCTION void TestFirstIteration
	(
		avl::TestFirstIterationState&	ioState,
		bool&							outIsFirstIteration
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_LOOPUTILS_H

