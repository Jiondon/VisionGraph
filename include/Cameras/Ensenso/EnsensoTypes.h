//
// Adaptive Vision Library 4.10.1.62046
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#pragma once

#include "ATL/AtlString.h"

namespace avl
{
	struct EnsensoCameraInformation
	{
		atl::String deviceId;
		atl::File settings;
		atl::File calibration;
	};
}
