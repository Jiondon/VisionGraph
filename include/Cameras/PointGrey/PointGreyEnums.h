//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef POINTGREY_ENUMS_H
#define POINTGREY_ENUMS_H

namespace avl
{
	//:PUBLIC_TYPES_BEGIN
	namespace PointGreyColorMode
	{
		enum Type
		{
			Color,
			Grayscale,
		};
	}

	namespace PointGreyTriggerMode
	{
		enum Type
		{
			TriggerOff,
			SoftwareTrigger,
			HardwareTrigger,
		};
	}
	//:PUBLIC_TYPES_END
}

#endif // POINTGREY_ENUMS_H