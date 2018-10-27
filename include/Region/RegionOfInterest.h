//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGION_OF_INTEREST_H
#define AVL_REGION_OF_INTEREST_H

#include "ATL/Utils.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "Basic/Types.h"
#include <cstring>
#include "Geometry/Geometry.h"
#include "Path/Path.h"
#include "Region.h"

namespace avl
{

	namespace RegionOfInterestType
	{
		enum Type
		{
			Region,
			Rectangle,
			Circle,
			Polygon
		};
	}

	class RegionOfInterest
	{
	public:
		RegionOfInterestType::Type tag;

		avl::Region region;
		avl::Rectangle2D rectangle;
		avl::Circle2D circle;
		avl::Path polygon;

		RegionOfInterest()
			: tag(RegionOfInterestType::Region)
		{
		}

		RegionOfInterest(const avl::Region& region)
			: tag(RegionOfInterestType::Region)
			, region(region)
		{
		}

		RegionOfInterest(const avl::Rectangle2D& rectangle)
			: tag(RegionOfInterestType::Rectangle)
			, rectangle(rectangle)
		{
		}

		RegionOfInterest(const avl::Circle2D& circle)
			: tag(RegionOfInterestType::Circle)
			, circle(circle)
		{
		}

		RegionOfInterest(const avl::Path& polygon)
			: tag(RegionOfInterestType::Polygon)
		{
			if (!polygon.closed)
			{
				throw atl::DomainError("Open path in constructor of RegionOfInterest");
			}

			this->polygon = polygon;
		}
	};
}

#endif
