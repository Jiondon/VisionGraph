//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SPATIAL_MAP_H
#define SPATIAL_MAP_H

#include "AVLCommon/Config.h"
#include "PlainTypes.h"

namespace avl
{

	class SpatialMap;
	class SpatialMapImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */

		AVL_FUNCTION void DestructSpatialMap(SpatialMap&);
		AVL_FUNCTION void CopySpatialMap(const SpatialMap&, SpatialMap&);
		AVL_FUNCTION bool TestSpatialMapEqual(const SpatialMap&, const SpatialMap&);
		AVL_FUNCTION bool TestSpatialMapEmpty(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapWidth(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapHeight(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapImageWidth(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapImageHeight(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapImagePitch(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapImageDepth(const SpatialMap&);
		AVL_FUNCTION int GetSpatialMapImageType(const SpatialMap&);

	}

	class SpatialMap
	{
	public:
		SpatialMap() : pImpl(0) {}

		~SpatialMap()
		{
			pImpl_helpers::DestructSpatialMap(*this);
		}

		SpatialMap(const SpatialMap& inSpatialMap) : pImpl(0)
		{
			pImpl_helpers::CopySpatialMap(inSpatialMap, *this);
		}

		avl::SpatialMap& operator=(const SpatialMap& inSpatialMap)
		{
			pImpl_helpers::CopySpatialMap(inSpatialMap, *this);
			return *this;
		}

		bool operator == (const SpatialMap& rhs) const
		{
			return pImpl_helpers::TestSpatialMapEqual(*this, rhs);
		}
		
		bool operator != (const SpatialMap& rhs) const
		{
			return !(operator==(rhs));
		}
		
		bool IsEmpty () const
		{
			return pImpl == 0 || pImpl_helpers::TestSpatialMapEmpty(*this);
		}

		int Width() const
		{
			 return pImpl == 0 ? 0 : pImpl_helpers::GetSpatialMapWidth(*this);
		}

		int Height() const
		{
			 return pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapHeight(*this);
		}

		int ImageWidth() const
		{
			return pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapImageWidth(*this);
		}

		int ImageHeight() const
		{
			return pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapImageHeight(*this);
		}

		int ImagePitch() const
		{
			return pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapImagePitch(*this);
		}

		int ImageDepth() const
		{
			return pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapImageDepth(*this);;
		}

		avl::PlainType::Type ImageType() const
		{
			return (avl::PlainType::Type)(pImpl == 0 ? 0 :  pImpl_helpers::GetSpatialMapImageType(*this));
		}

		SpatialMapImpl* pImpl;
	};

}

#endif // SPATIAL_MAP_H
