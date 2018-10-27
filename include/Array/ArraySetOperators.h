//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ARRAYSETOPERATORS_H
#define AVL_ARRAYSETOPERATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"

namespace avl
{


	/// Returns an array of elements contained in at least one of the input arrays (without duplicates).
	/// <param name="inArray1">First input array.</param>
	/// <param name="inArray2">Second input array.</param>
	/// <param name="inArray3">Third input array (optional). Default value: atl::NIL.</param>
	/// <param name="inArray4">Fourth input array (optional). Default value: atl::NIL.</param>
	/// <param name="outArray">Union of the input arrays.</param>
	template <typename Type>
	void ArrayUnion
	(
		const atl::Array<Type>& inArray1,			
		const atl::Array<Type>& inArray2,			
		const atl::Optional<atl::Array<Type> >& inArray3,	
		const atl::Optional<atl::Array<Type> >& inArray4,	
		atl::Array<Type>& outArray					
	)
	{
		throw atl::RuntimeError("This function is not implemented for AVL, but is available only for Adaptive Vision Studio.");

	}

	/// Returns an array of elements contained in all of the input arrays (without duplicates).
	/// <param name="inArray1">First input array.</param>
	/// <param name="inArray2">Second input array.</param>
	/// <param name="inArray3">Third input array (optional). Default value: atl::NIL.</param>
	/// <param name="inArray4">Fourth input array (optional). Default value: atl::NIL.</param>
	/// <param name="outArray">Intersection of the input arrays.</param>
	template <typename Type>
	void ArrayIntersection
	(
		const atl::Array<Type>& inArray1,			
		const atl::Array<Type>& inArray2,			
		const atl::Optional<atl::Array<Type> >& inArray3,	
		const atl::Optional<atl::Array<Type> >& inArray4,	
		atl::Array<Type>& outArray					
	)
	{
		throw atl::RuntimeError("This function is not implemented for AVL, but is available only for Adaptive Vision Studio.");

	}

	/// Returns an array of elements contained in the first input array, but not contained in the second one (without duplicates).
	/// <param name="inArray1">First input array.</param>
	/// <param name="inArray2">Second input array.</param>
	/// <param name="outArray">Difference of the input arrays.</param>
	template <typename Type>
	void ArrayDifference
	(
		const atl::Array<Type>& inArray1,			
		const atl::Array<Type>& inArray2,			
		atl::Array<Type>& outArray					
	)
	{
		throw atl::RuntimeError("This function is not implemented for AVL, but is available only for Adaptive Vision Studio.");

	}

	/// Returns an array of elements contained in odd number of the input arrays (without duplicates).
	/// <param name="inArray1">First input array.</param>
	/// <param name="inArray2">Second input array.</param>
	/// <param name="inArray3">Third input array (optional). Default value: atl::NIL.</param>
	/// <param name="inArray4">Fourth input array (optional). Default value: atl::NIL.</param>
	/// <param name="outArray">Symmetric difference of the input arrays.</param>
	template <typename Type>
	void ArraySymmetricDifference
	(
		const atl::Array<Type>& inArray1,			
		const atl::Array<Type>& inArray2,			
		const atl::Optional<atl::Array<Type> >& inArray3,	
		const atl::Optional<atl::Array<Type> >& inArray4,	
		atl::Array<Type>& outArray					
	)
	{
		throw atl::RuntimeError("This function is not implemented for AVL, but is available only for Adaptive Vision Studio.");

	}

} // namespace avl

#endif // AVL_ARRAYSETOPERATORS_H

