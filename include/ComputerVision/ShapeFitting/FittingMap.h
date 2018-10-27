//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef FITTING_MAP_H
#define FITTING_MAP_H

#include "AVLCommon/Config.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{

	class FittingMap;
	class FittingMapImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructFittingMap(FittingMap&);
		AVL_FUNCTION void CopyFittingMap(const FittingMap&, FittingMap&);
		AVL_FUNCTION bool TestFittingMapEqual(const FittingMap&, const FittingMap&);
	}

	class FittingMap
	{
	public:
		FittingMap() : pImpl(0) {}

		~FittingMap()
		{
			pImpl_helpers::DestructFittingMap(*this);
		}

		FittingMap(const FittingMap& inFittingMap) : pImpl(0)
		{
			pImpl_helpers::CopyFittingMap(inFittingMap, *this);
		}

		FittingMap& operator=(const FittingMap& inFittingMap)
		{
			pImpl_helpers::CopyFittingMap(inFittingMap, *this);
			return *this;
		}

		bool operator == (const FittingMap& rhs) const
		{
			return pImpl_helpers::TestFittingMapEqual(*this, rhs);
		}
		
		bool operator != (const FittingMap& rhs) const
		{
			return !(operator==(rhs));
		}
		
		FittingMapImpl* pImpl;
	};


	struct CircleFittingMap
	{
		FittingMap	fittingMap;
		Circle2D	object;
	};

	struct ArcFittingMap
	{
		FittingMap	fittingMap;
		Arc2D		object;
	};

	struct SegmentFittingMap
	{
		FittingMap	fittingMap;
		Segment2D	object;
	};

	struct PathFittingMap
	{
		FittingMap	fittingMap;
		Path		object;
	};

} // namespace avl

#endif // FITTING_MAP_H
