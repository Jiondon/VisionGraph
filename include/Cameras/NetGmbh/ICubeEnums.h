//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef ICUBE_ENUMS_H
#define ICUBE_ENUMS_H

//:PUBLIC_TYPES_BEGIN

namespace avl
{
	namespace ICubeGrabMode
	{
		enum Type
		{
			RAW = 0,
			RGB = 1
		};
	}

	namespace ICubeResolutionMode
	{
		enum Type
		{
			QVGA	= 0,
			VGA		= 1,
			WVGA	= 2,
			SVGA	= 3,
			XGA		= 4,
			SXGA	= 5,
			UXGA	= 6,
			QXGA	= 7,
			QSXGA	= 8,
			WQUXGA	= 9
		};
	}

	namespace ICubeBinSkip
	{
		enum Type
		{
			BINSKIP_OFF				= 0,
			BINSKIP_SECOND_PIXEL	= 1,
			BINSKIP_FOURTH_PIXEL	= 3
		};
	}

	namespace ICubeTriggerMode
	{
		enum Type
		{
			SW_START	= 0,
			SW_DO		= 1,
			HW_START	= 2,
			STOP		= 3,
			SW_START_2	= 4,
			HW_START_2  = 5
		};
	}

}

//:PUBLIC_TYPES_END

#endif