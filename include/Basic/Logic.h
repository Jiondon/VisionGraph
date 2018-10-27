//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_LOGIC_H
#define AVS_LOGIC_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"

namespace avl
{


	/// <summary>Returns True if (and only if) both arguments are False.</summary>
	AVL_FUNCTION void NotOr
	(
		bool	inValue1,
		bool	inValue2,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) at least one of the arguments is False.</summary>
	AVL_FUNCTION void NotAnd
	(
		bool	inValue1,
		bool	inValue2,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) the input argument is False.</summary>
	AVL_FUNCTION void Not
	(
		bool	inValue,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) the input arguments are both True or both False.</summary>
	AVL_FUNCTION void Iff
	(
		bool	inValue1,
		bool	inValue2,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Returns True if (and only if) all arguments are True.</summary>
	/// <param name="inValue1">Default value: True.</param>
	/// <param name="inValue2">Default value: True.</param>
	/// <param name="inValue3">Default value: True.</param>
	/// <param name="inValue4">Default value: True.</param>
	/// <param name="inValue5">Default value: True.</param>
	/// <param name="inValue6">Default value: True.</param>
	/// <param name="inValue7">Default value: True.</param>
	/// <param name="inValue8">Default value: True.</param>
	AVL_FUNCTION void AvsFilter_And
	(
		bool	inValue1,
		bool	inValue2,
		bool	inValue3,
		bool	inValue4,
		bool	inValue5,
		bool	inValue6,
		bool	inValue7,
		bool	inValue8,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) all arguments are True. Accepts conditional values.</summary>
	/// <param name="inValue1">Default value: True.</param>
	/// <param name="inValue2">Default value: True.</param>
	/// <param name="inValue3">Default value: True.</param>
	/// <param name="inValue4">Default value: True.</param>
	/// <param name="inValue5">Default value: True.</param>
	/// <param name="inValue6">Default value: True.</param>
	/// <param name="inValue7">Default value: True.</param>
	/// <param name="inValue8">Default value: True.</param>
	/// <param name="inDefault">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_MergeAnd
	(
		atl::Conditional<bool>	inValue1,
		atl::Conditional<bool>	inValue2,
		atl::Conditional<bool>	inValue3,
		atl::Conditional<bool>	inValue4,
		atl::Conditional<bool>	inValue5,
		atl::Conditional<bool>	inValue6,
		atl::Conditional<bool>	inValue7,
		atl::Conditional<bool>	inValue8,
		bool    inDefault,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) all values in the input array True.</summary>
	AVL_FUNCTION void AvsFilter_And_OfArray
	(
		const atl::Array<bool>& inBoolArray,
		bool&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) all values in the input array True. Accepts conditional values.</summary>
	/// <param name="inDefault">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_MergeAnd_OfArray
	(
		const atl::Array<atl::Conditional<bool>>&	inBoolArray,
		bool										inDefault,
		bool&										outValue
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_And_OfLoopState
	{
		bool stateVariable;

		AvsFilter_And_OfLoopState() : stateVariable(true) {}
	};


	/// <summary>Returns True if (and only if) all values appearing in consecutive iterations are True.</summary>
	AVL_FUNCTION void AvsFilter_And_OfLoop
	(
		AvsFilter_And_OfLoopState& ioState,
		bool	inBool,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) any of the arguments is True.</summary>
	/// <param name="inValue1">Default value: False.</param>
	/// <param name="inValue2">Default value: False.</param>
	/// <param name="inValue3">Default value: False.</param>
	/// <param name="inValue4">Default value: False.</param>
	/// <param name="inValue5">Default value: False.</param>
	/// <param name="inValue6">Default value: False.</param>
	/// <param name="inValue7">Default value: False.</param>
	/// <param name="inValue8">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_Or
	(
		bool	inValue1,
		bool	inValue2,
		bool	inValue3,
		bool	inValue4,
		bool	inValue5,
		bool	inValue6,
		bool	inValue7,
		bool	inValue8,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) any of the arguments is True. Accepts conditional values.</summary>
	/// <param name="inValue1">Default value: False.</param>
	/// <param name="inValue2">Default value: False.</param>
	/// <param name="inValue3">Default value: False.</param>
	/// <param name="inValue4">Default value: False.</param>
	/// <param name="inValue5">Default value: False.</param>
	/// <param name="inValue6">Default value: False.</param>
	/// <param name="inValue7">Default value: False.</param>
	/// <param name="inValue8">Default value: False.</param>
	/// <param name="inDefault">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_MergeOr
	(
		atl::Conditional<bool>	inValue1,
		atl::Conditional<bool>	inValue2,
		atl::Conditional<bool>	inValue3,
		atl::Conditional<bool>	inValue4,
		atl::Conditional<bool>	inValue5,
		atl::Conditional<bool>	inValue6,
		atl::Conditional<bool>	inValue7,
		atl::Conditional<bool>	inValue8,
		bool    inDefault,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) at least one value in the input array is True.</summary>
	AVL_FUNCTION void AvsFilter_Or_OfArray
	(
		const atl::Array<bool>& inBoolArray,
		bool&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) at least one value in the input array is True. Accepts conditional values.</summary>
	/// <param name="inDefault">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_MergeOr_OfArray
	(
		const atl::Array<atl::Conditional<bool>>&	inBoolArray,
		bool										inDefault,
		bool&										outValue
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_Or_OfLoopState
	{
		bool stateVariable;

		AvsFilter_Or_OfLoopState() : stateVariable(false) {}
	};


	/// <summary>Returns True if (and only if) at least one value appearing in consecutive iterations is True.</summary>
	AVL_FUNCTION void AvsFilter_Or_OfLoop
	(
		AvsFilter_Or_OfLoopState& ioState,
		bool	inBool,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) the number of True input values is odd.</summary>
	/// <param name="inValue1">Default value: False.</param>
	/// <param name="inValue2">Default value: False.</param>
	/// <param name="inValue3">Default value: False.</param>
	/// <param name="inValue4">Default value: False.</param>
	/// <param name="inValue5">Default value: False.</param>
	/// <param name="inValue6">Default value: False.</param>
	/// <param name="inValue7">Default value: False.</param>
	/// <param name="inValue8">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_Xor
	(
		bool	inValue1,
		bool	inValue2,
		bool	inValue3,
		bool	inValue4,
		bool	inValue5,
		bool	inValue6,
		bool	inValue7,
		bool	inValue8,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns True if (and only if) the number of True values in the input array is odd.</summary>
	AVL_FUNCTION void AvsFilter_Xor_OfArray
	(
		const atl::Array<bool>& inBoolArray,
		bool&					outValue
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_Xor_OfLoopState
	{
		bool stateVariable;

		AvsFilter_Xor_OfLoopState() : stateVariable(false) {}
	};


	/// <summary>Returns True if (and only if) the number of True values appearing in consecutive iterations is odd.</summary>
	AVL_FUNCTION void AvsFilter_Xor_OfLoop
	(
		AvsFilter_Xor_OfLoopState& ioState,
		bool	inBool,
		bool&	outValue
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_LOGIC_H

