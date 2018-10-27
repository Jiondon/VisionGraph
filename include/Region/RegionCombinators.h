//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONCOMBINATORS_H
#define AVL_REGIONCOMBINATORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Computes the common part of two regions.</summary>
	/// <param name="inRegion1">First input region.</param>
	/// <param name="inRegion2">Second input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionIntersection
	(
		const avl::Region& inRegion1,
		const avl::Region& inRegion2,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct RegionIntersection_OfLoopState : public avl::BaseState
	{
		avl::Region stateVariable;
	};
	/// <summary>Computes the common part of regions appearing in consecutive iterations.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionIntersection_OfLoop
	(
		RegionIntersection_OfLoopState& ioState,
		const avl::Region& inRegion,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a region containing pixels from the first input region, but not from the second input region.</summary>
	/// <param name="inRegion1">First input region.</param>
	/// <param name="inRegion2">Second input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionDifference
	(
		const avl::Region& inRegion1,
		const avl::Region& inRegion2,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a region containing pixels from both input regions.</summary>
	/// <param name="inRegion1">First input region.</param>
	/// <param name="inRegion2">Second input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionUnion
	(
		const avl::Region& inRegion1,
		const avl::Region& inRegion2,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct RegionUnion_OfLoopState : public avl::BaseState
	{
		avl::Region stateVariable;
	};
	/// <summary>Computes the union of regions appearing in consecutive iterations.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionUnion_OfLoop
	(
		RegionUnion_OfLoopState& ioState,
		const avl::Region& inRegion,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a region containing pixels from first or second input region, but not from both.</summary>
	/// <param name="inRegion1">First input region.</param>
	/// <param name="inRegion2">Second input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionSymmetricDifference
	(
		const avl::Region& inRegion1,
		const avl::Region& inRegion2,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a region containing pixels belonging to odd number of array regions.</summary>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionSymmetricDifference_OfArray
	(
		const atl::Array<avl::Region>& inRegionArray,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

//:PUBLIC
	struct RegionSymmetricDifference_OfLoopState : public avl::BaseState
	{
		avl::Region stateVariable;
	};
	/// <summary>Computes a region containing pixels belonging to odd number of regions appearing in consecutive iterations.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionSymmetricDifference_OfLoop
	(
		RegionSymmetricDifference_OfLoopState& ioState,
		const avl::Region& inRegion,
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a region containing all the pixels that any of the input regions contains.</summary>
	/// <param name="inArray">Array of regions.</param>
	/// <param name="outRegion">Union of the input regions.</param>
	AVL_FUNCTION void RegionUnion_OfArray
	(
		const atl::Array<avl::Region>&	inArray,	
		avl::Region&					outRegion	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes common part of array of regions.</summary>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionIntersection_OfArray
	(
		const atl::Optional<avl::Region>&	inInitialRegion,
		const atl::Array<avl::Region>&		inArray,
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONCOMBINATORS_H

