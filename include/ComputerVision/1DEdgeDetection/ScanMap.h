//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SCAN_MAP_H
#define SCAN_MAP_H

#include "AVLCommon/Config.h"
#include "ATL/Platform.h"

namespace avl
{

	class ScanMap;
	class ScanMapImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructScanMap(ScanMap&);
		AVL_FUNCTION void CopyScanMap(const ScanMap&, ScanMap&);
		AVL_FUNCTION bool TestScanMapEqual(const ScanMap&, const ScanMap&);
	}

	class ScanMap
	{
	public:
		ScanMap() : pImpl(0) {}

		~ScanMap()
		{
			pImpl_helpers::DestructScanMap(*this);
		}

		ScanMap(const ScanMap& inScanMap) : pImpl(0)
		{
			pImpl_helpers::CopyScanMap(inScanMap, *this);
		}

		ScanMap& operator=(const ScanMap& inScanMap)
		{
			pImpl_helpers::CopyScanMap(inScanMap, *this);
			return *this;
		}

#ifdef HAS_CPP0X

		ScanMap(ScanMap&& inScanMap) 
		{
			pImpl = inScanMap.pImpl;
			inScanMap.pImpl = 0;
		}

		ScanMap& operator=(ScanMap&& inScanMap) 
		{
			pImpl = inScanMap.pImpl;
			inScanMap.pImpl = 0;
			return *this;
		}

#endif // HAS_CPP0X

		bool operator == (const ScanMap& rhs) const
		{
			return pImpl_helpers::TestScanMapEqual(*this, rhs);
		}
		
		bool operator != (const ScanMap& rhs) const
		{
			return !(operator==(rhs));
		}
		
		ScanMapImpl* pImpl;
	};

}

#endif // SCAN_MAP_H
