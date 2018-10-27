//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef MULTICAMENUMS_H
#define MULTICAMENUMS_H

// structure containing information about output image format

//:PUBLIC_TYPES_BEGIN

namespace avl
{
	namespace MultiCamColorFormat
	{
		enum Type
		{
			Y8		= 0,
			Y10		= 1,
			Y12		= 2,
			Y16		= 3,
			RAW8	= 4,
			BAYER8	= 5,
			RGB24	= 6,
			RGB32	= 7,
			ARGB32	= 8
		};
	}

	namespace MultiCamAcquisitionMode
	{
		enum Type
		{
			SNAPSHOT	= 1,
			HFR			= 2,
			PAGE		= 3,
			WEB			= 4,
			LONGPAGE	= 5,
			VIDEO		= 7
		};
	}
	
	namespace MultiCamDestinationClass
	{
		enum Type
		{
			Board	= 0,
			Channel = 1,
		};
	}

	namespace MultiCamOutputStyle
	{
		enum Type
		{
			TTL,
			ITTL,
			IOC,
			IOE,
			RELAY,
			LED,
			OC,
			LVDS,
			DIFF,
			OPTO,
			SSRLY
		};
	}

	namespace MultiCamInputStyle
	{
		enum Type
		{
			TTL,
			ITTL,
			I12v,
			RS422,
			LVDS,
			DIFF,
			CHANNELLINK,
			CMOS,
			AUTO,
			RELAY,
			_5V,
			_12V,
			TTLHiz,
			TTLPD,
			RS485,
			DTTL,
			ISO,
			POWERSTATE
		};
	}

	namespace MultiCamOutputState
	{
		enum Type
		{
			LOW,
			HIGH,
			TOGGLE
		};
	}

	namespace MultiCamInputState
	{
		enum Type
		{
			NONE,
			LOW,
			HIGH,
			WENTLOW,
			WENTHIGH,
			DISCONNECTED,
			OPEN
		};
	}

}

//:PUBLIC_TYPES_END

#endif