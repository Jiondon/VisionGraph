//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SCAN_MAP_STATE_H
#define SCAN_MAP_STATE_H

#include "ScanMap.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Array.h"
#include "Geometry/Geometry.h"
#include "ComputerVision/ImageAnalysis/ScanFields.h"

namespace avl
{

	struct ScanMapState : public BaseState
	{
		ScanMap scanMap;
	};

	struct ScanMapArrayState : public BaseState
	{
		atl::Array<ScanMap> scanMaps;

		SegmentScanField scanField;
		atl::Array<Segment2D> scanSegments;
	};

} // namespace avl

#endif // SCAN_MAP_STATE_H