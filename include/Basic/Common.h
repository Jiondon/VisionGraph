//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_COMMON_H
#define AVL_COMMON_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"

namespace avl
{


	/// Produces 'True' if the input object is present or 'False' otherwise.
	/// <param name="inObject">Conditional object being inspected.</param>
	/// <param name="outIsNotNil">'True' if the object exists, 'False' otherwise.</param>
	template <typename Type>
	void TestObjectNotNil
	(
		const typename atl::ToConditionalType<const Type&>::Type& inObject,	
		bool& outIsNotNil													
	)
	{
		outIsNotNil = (inObject != atl::NIL);
	}

	/// Produces 'True' if the input object is NOT present or 'False' otherwise.
	/// <param name="inObject">Conditional object being inspected.</param>
	/// <param name="outIsNil">'True' if the object doesn't exist, 'False' otherwise.</param>
	template <typename Type>
	void TestObjectNil
	(
		const typename atl::ToConditionalType<const Type&>::Type& inObject,	
		bool& outIsNil									
	)
	{
		outIsNil = (inObject == atl::NIL);
	}

	/// Checks whether the input object is equal to another object.
	/// <param name="inObject">First of the objects being compared.</param>
	/// <param name="inReferenceObject">Second of the objects being compared.</param>
	/// <param name="outIsEqual">'True' if the objects are equal, 'False' otherwise.</param>
	template <typename Type>
	void TestObjectEqualTo
	(
		const Type& inObject,			
		const Type& inReferenceObject,	
		bool& outIsEqual				
	)
	{
		outIsEqual = (inObject == inReferenceObject);
	}

	/// Checks whether the input object is not equal to another object.
	/// <param name="inObject">First of the objects being compared.</param>
	/// <param name="inReferenceObject">Second of the objects being compared.</param>
	/// <param name="outIsUnequal">'True' if the objects are not equal, 'False' otherwise.</param>
	template <typename Type>
	void TestObjectUnequalTo
	(
		const Type& inObject,			
		const Type& inReferenceObject,	
		bool& outIsUnequal				
	)
	{
		outIsUnequal = !(inObject == inReferenceObject);
	}

	/// Creates a copy of the input data.
	/// <param name="inObject">Object to be copied.</param>
	/// <param name="outObject">Copy of the object.</param>
	template <typename Type>
	void CopyObject
	(
		const Type& inObject,	
		Type& outObject			
	)
	{
		outObject = inObject;
	}

} // namespace avl

#endif // AVL_COMMON_H

