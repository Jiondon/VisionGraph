//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_ARRAYSTATISTICS_H
#define AVS_ARRAYSTATISTICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"
#include "AVLCommon/Enums/SortingOrder.h"

namespace avl
{


	AVL_FUNCTION void NthIndexByValues
	(int* inBegin, int* inNth, int* inEnd, const atl::Array<float>& inValues, bool inReverse)
	THROW_AVL_ERRORS;

	/// Returns the array element corresponding to the n-th biggest/smallest value from the inValues array.
	/// <param name="inArray">Elements from which element corresponding to n-th value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Nth biggest/smallest value.</param>
	/// <param name="outIndex">Index of the found value.</param>
	template <typename Type>
	void GetNthElement
	(
		const atl::Array<Type>&		inArray,		
		const atl::Array<float>&	inValues,		
		const int					inN,
		avl::SortingOrder::Type		inSortingOrder,
		Type&						outElement,		
		float&						outValue,		
		int&						outIndex		
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetNthElement.");
		}
		if (inValues.Empty())
		{
			throw atl::DomainError(L"Empty input array in GetNthElement.");
		}
		if (inN < 0 || inN >= inArray.Size())
		{
			throw atl::DomainError(L"inN is negative or exceeds the input arrays size in GetNthElement.");
		}

		atl::Array<int> indices(inArray.Size());
		for (int i = 0; i < indices.Size(); ++i)
		{
			indices[i] = i;
		}

		avl::NthIndexByValues(indices.Begin(), indices.Begin() + inN, indices.End(), inValues, inSortingOrder == avl::SortingOrder::Descending);
		const int index = indices[inN];

		outElement = inArray[index];
		outValue = inValues[index];
		outIndex = index;
	}

	namespace detail
	{
		template<typename T>
		struct GetNthElement_Helper
		{
			static void Get(const atl::Array<T>& inArray, const atl::Array<float>& inValues, int inN, avl::SortingOrder::Type inSortingOrder, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetNthElement(inArray, inValues, inN, inSortingOrder, outElement.Get(), outValue, outIndex);
			}
		};

		template<typename T>
		struct GetNthElement_Helper< atl::Conditional<T> >
		{
			static void Get(const atl::Array< atl::Conditional<T> >& inArray, const atl::Array<float>& inValues, int inN, avl::SortingOrder::Type inSortingOrder, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetNthElement(inArray, inValues, inN, inSortingOrder, outElement, outValue, outIndex);
			}
		};
	}


	/// Returns the array element corresponding to the n-th biggest/smallest value from the inValues array; returns NIL if the arrays are empty.
	/// <param name="inArray">Elements from which element corresponding to n-th value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Nth biggest/smallest value.</param>
	/// <param name="outIndex">Index of the found value.</param>
	template <typename Type>
	void GetNthElement_OrNil
	(
		const atl::Array<Type>&							inArray,		
		const atl::Array<float>&						inValues,		
		const int										inN,
		avl::SortingOrder::Type							inSortingOrder,
		typename atl::ToConditionalType<Type>::Type&	outElement,		
		atl::Conditional<float>&						outValue,		
		atl::Conditional<int>&							outIndex		
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetNthElement_OrNil.");
		}
		if (inN < 0)
		{
			throw atl::DomainError(L"inN is negative in GetNthElement_OrNil.");
		}
		if (inN >= inArray.Size())
		{
			outElement = atl::NIL;
			outValue = atl::NIL;
			outIndex = atl::NIL;
		}
		else
		{
			outElement.AssignNonNil();
			outValue.AssignNonNil();
			outIndex.AssignNonNil();
			detail::GetNthElement_Helper<Type>::Get(inArray, inValues, inN, inSortingOrder, outElement, outValue.Get(), outIndex.Get());
		}
	}

	/// Gets array element corresponding to median value from the inValues array.
	/// <param name="inArray">Elements from which element corresponding to median value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Median value.</param>
	/// <param name="outIndex">Index of the median value.</param>
	template <typename Type>
	void GetMedianElement
	(
		const atl::Array<Type>&		inArray,	
		const atl::Array<float>&	inValues,	
		Type&						outElement,	
		float&						outValue,	
		int&						outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMedianElement.");
		}
		if (inValues.Empty())
		{
			throw atl::DomainError(L"Empty input array in GetMedianElement.");
		}

		GetNthElement<Type>(inArray, inValues, inValues.Size() / 2, avl::SortingOrder::Ascending, outElement, outValue, outIndex);
	}

	namespace detail
	{
		template<typename T>
		struct GetMedianElement_Helper
		{
			static void Get(const atl::Array<T>& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMedianElement(inArray, inValues, outElement.Get(), outValue, outIndex);
			}
		};

		template<typename T>
		struct GetMedianElement_Helper< atl::Conditional<T> >
		{
			static void Get(const atl::Array< atl::Conditional<T> >& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMedianElement(inArray, inValues, outElement, outValue, outIndex);
			}
		};
	}


	/// Gets array element corresponding to median value from the inValues array; returns NIL if the arrays are empty.
	/// <param name="inArray">Elements from which element corresponding to median value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Median value.</param>
	/// <param name="outIndex">Index of the median value.</param>
	template <typename Type>
	void GetMedianElement_OrNil
	(
		const atl::Array<Type>&							inArray,	
		const atl::Array<float>&						inValues,	
		typename atl::ToConditionalType<Type>::Type&	outElement,	
		atl::Conditional<float>&						outValue,	
		atl::Conditional<int>&							outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMedianElement_OrNil.");
		}
		if (inValues.Empty())
		{
			outElement = atl::NIL;
			outValue = atl::NIL;
			outIndex = atl::NIL;
		}
		else
		{
			outElement.AssignNonNil();
			outValue.AssignNonNil();
			outIndex.AssignNonNil();
			detail::GetMedianElement_Helper<Type>::Get(inArray, inValues, outElement, outValue.Get(), outIndex.Get());
		}
	}

	/// Returns an array element that corresponds to the smallest value in the array of values.
	/// <param name="inArray">Elements from which element corresponding to smallest value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Smallest value.</param>
	/// <param name="outIndex">Index of the smallest value.</param>
	template <typename Type>
	void GetMinimumElement
	(
		const atl::Array<Type>&		inArray,	
		const atl::Array<float>&	inValues,	
		Type&						outElement,	
		float&						outValue,	
		int&						outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMinimumElement.");
		}

		if (inValues.Empty())
		{
			throw atl::DomainError(L"Empty input array in GetMinimumElement.");
		}

		int minIndex = 0;
		for (int i = 1; i < inValues.Size(); ++i)
		{
			if (inValues[i] < inValues[minIndex])
				minIndex = i;
		}

		outElement = inArray[minIndex];
		outValue = inValues[minIndex];
		outIndex = minIndex;
	}

	namespace detail
	{
		template<typename T>
		struct GetMinimumElement_Helper
		{
			static void Get(const atl::Array<T>& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMinimumElement(inArray, inValues, outElement.Get(), outValue, outIndex);
			}
		};

		template<typename T>
		struct GetMinimumElement_Helper< atl::Conditional<T> >
		{
			static void Get(const atl::Array< atl::Conditional<T> >& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMinimumElement(inArray, inValues, outElement, outValue, outIndex);
			}
		};
	}


	/// Returns an array element that corresponds to the smallest value in the array of values; returns NIL if the arrays are empty.
	/// <param name="inArray">Elements from which element corresponding to smallest value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Smallest value.</param>
	/// <param name="outIndex">Index of the smallest value.</param>
	template <typename Type>
	void GetMinimumElement_OrNil
	(
		const atl::Array<Type>&							inArray,	
		const atl::Array<float>&						inValues,	
		typename atl::ToConditionalType<Type>::Type&	outElement,	
		atl::Conditional<float>&						outValue,	
		atl::Conditional<int>&							outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMinimumElement_OrNil.");
		}
		if (inValues.Empty())
		{
			outElement = atl::NIL;
			outValue = atl::NIL;
			outIndex = atl::NIL;
		}
		else
		{
			outElement.AssignNonNil();
			outValue.AssignNonNil();
			outIndex.AssignNonNil();
			detail::GetMinimumElement_Helper<Type>::Get(inArray, inValues, outElement, outValue.Get(), outIndex.Get());
		}
	}

	/// Returns an array element that corresponds to the biggest value in the array of values.
	/// <param name="inArray">Elements from which element corresponding to biggest value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Biggest value.</param>
	/// <param name="outIndex">Index of the biggest value.</param>
	template <typename Type>
	void GetMaximumElement
	(
		const atl::Array<Type>&		inArray,	
		const atl::Array<float>&	inValues,	
		Type&						outElement,	
		float&						outValue,	
		int&						outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMaximumElement.");
		}
		
		if (inValues.Empty())
		{
			throw atl::DomainError(L"Empty input array in GetMaximumElement.");
		}

		int maxIndex = 0;
		for( int i = 1; i < inValues.Size(); ++i )
		{
			if (inValues[i] > inValues[maxIndex])
				maxIndex = i;
		}

		outElement = inArray[maxIndex];
		outValue = inValues[maxIndex];
		outIndex = maxIndex;
	}

	namespace detail
	{
		template<typename T>
		struct GetMaximumElement_Helper
		{
			static void Get(const atl::Array<T>& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMaximumElement(inArray, inValues, outElement.Get(), outValue, outIndex);
			}
		};

		template<typename T>
		struct GetMaximumElement_Helper< atl::Conditional<T> >
		{
			static void Get(const atl::Array< atl::Conditional<T> >& inArray, const atl::Array<float>& inValues, atl::Conditional<T>& outElement, float& outValue, int& outIndex)
			{
				GetMaximumElement(inArray, inValues, outElement, outValue, outIndex);
			}
		};
	}


	/// Returns an array element that corresponds to the biggest value in the array of values; returns NIL if the arrays are empty.
	/// <param name="inArray">Elements from which element corresponding to biggest value will be chosen.</param>
	/// <param name="inValues">Values defining the order.</param>
	/// <param name="outElement">Element from the array.</param>
	/// <param name="outValue">Biggest value.</param>
	/// <param name="outIndex">Index of the biggest value.</param>
	template <typename Type>
	void GetMaximumElement_OrNil
	(
		const atl::Array<Type>&							inArray,	
		const atl::Array<float>&						inValues,	
		typename atl::ToConditionalType<Type>::Type&	outElement,	
		atl::Conditional<float>&						outValue,	
		atl::Conditional<int>&							outIndex	
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetMaximumElement_OrNil.");
		}
		if (inValues.Empty())
		{
			outElement = atl::NIL;
			outValue = atl::NIL;
			outIndex = atl::NIL;
		}
		else
		{
			outElement.AssignNonNil();
			outValue.AssignNonNil();
			outIndex.AssignNonNil();
			detail::GetMaximumElement_Helper<Type>::Get(inArray, inValues, outElement, outValue.Get(), outIndex.Get());
		}
	}

	/// Returns elements corresponding to 8 smallest/biggest values from the array of values.
	/// <param name="inArray">Input array.</param>
	/// <param name="inValues">Values defining the order.</param>
	template <typename Type>
	void GetSortedElements
	(
		const atl::Array<Type>&	inArray,		
		const atl::Array<float>&	inValues,		
		avl::SortingOrder::Type	inSortingOrder,
		atl::Conditional<float>&	outValue0,
		atl::Conditional<float>&	outValue1,
		atl::Conditional<float>&	outValue2,
		atl::Conditional<float>&	outValue3,
		atl::Conditional<float>&	outValue4,
		atl::Conditional<float>&	outValue5,
		atl::Conditional<float>&	outValue6,
		atl::Conditional<float>&	outValue7,
		typename atl::ToConditionalType<Type>::Type&	outElement0,
		typename atl::ToConditionalType<Type>::Type&	outElement1,
		typename atl::ToConditionalType<Type>::Type&	outElement2,
		typename atl::ToConditionalType<Type>::Type&	outElement3,
		typename atl::ToConditionalType<Type>::Type&	outElement4,
		typename atl::ToConditionalType<Type>::Type&	outElement5,
		typename atl::ToConditionalType<Type>::Type&	outElement6,
		typename atl::ToConditionalType<Type>::Type&	outElement7
	)
	{
		if (inArray.Size() != inValues.Size())
		{
			throw atl::DomainError(L"Inconsistent array sizes in GetSortedElements.");
		}

		int indices[9];
		int count = 0;

		for ( int i = 0; i < inValues.Size(); ++i )
		{
			int j;

			if ( inSortingOrder == avl::SortingOrder::Ascending )
			{
				for ( j = count; j > 0 && inValues[i] < inValues[indices[j - 1]]; --j )
					indices[j] = indices[j - 1];
			}
			else 
			{
				for ( j = count; j > 0 && inValues[i] > inValues[indices[j - 1]]; --j )
					indices[j] = indices[j - 1];
			}

			if (j < 8)
				indices[j] = i;
			
			if (count < 8)
				++count;
		}

		if (count > 0)	{ outValue0 = inValues[indices[0]];	outElement0 = inArray[indices[0]];	}
		else			{ outValue0 = atl::NIL;				outElement0 = atl::NIL;				}

		if (count > 1)	{ outValue1 = inValues[indices[1]];	outElement1 = inArray[indices[1]];	}
		else			{ outValue1 = atl::NIL;				outElement1 = atl::NIL;				}

		if (count > 2)	{ outValue2 = inValues[indices[2]];	outElement2 = inArray[indices[2]];	}
		else			{ outValue2 = atl::NIL;				outElement2 = atl::NIL;				}

		if (count > 3)	{ outValue3 = inValues[indices[3]];	outElement3 = inArray[indices[3]];	}
		else			{ outValue3 = atl::NIL;				outElement3 = atl::NIL;				}

		if (count > 4)	{ outValue4 = inValues[indices[4]];	outElement4 = inArray[indices[4]];	}
		else			{ outValue4 = atl::NIL;				outElement4 = atl::NIL;				}

		if (count > 5)	{ outValue5 = inValues[indices[5]];	outElement5 = inArray[indices[5]];	}
		else			{ outValue5 = atl::NIL;				outElement5 = atl::NIL;				}

		if (count > 6)	{ outValue6 = inValues[indices[6]];	outElement6 = inArray[indices[6]];	}
		else			{ outValue6 = atl::NIL;				outElement6 = atl::NIL;				}

		if (count > 7)	{ outValue7 = inValues[indices[7]];	outElement7 = inArray[indices[7]];	}
		else			{ outValue7 = atl::NIL;				outElement7 = atl::NIL;				}
	}

} // namespace avl

namespace avs
{

	/// Calculates the number of occurrences of an object in an array.
	/// <param name="inArray">Input array.</param>
	/// <param name="inValue">Value to count.</param>
	/// <param name="outCount">Number of value occurrences.</param>
	template <typename Type>
	void AvsFilter_CountValueInArray
	(
		const atl::Array<Type>&		inArray,	
		const Type&					inValue,	
		int&						outCount	
	)
	{
		outCount = 0;

		for ( int i = 0; i < inArray.Size(); ++i )
		{
			if ( inArray[i] == inValue )
			{
				++outCount;
			}
		}
	}

} // namespace avs

#endif // AVS_ARRAYSTATISTICS_H

