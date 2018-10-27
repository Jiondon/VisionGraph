//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONMETRICS_H
#define AVL_REGIONMETRICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Computes minimal distance between one of the points of the first region with one of the points of the second region.</summary>
	/// <param name="inRegion1">First input region.</param>
	/// <param name="inRegion2">Second input region.</param>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void RegionToRegionDistance
	(
		const avl::Region&				inRegion1,
		const avl::Region&				inRegion2,
		float						inResolution,	
		float&						outDistance,
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONMETRICS_H

