//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef IDS_ENUMS_H
#define IDS_ENUMS_H

namespace avl
{
	namespace IDSTriggerMode
	{
		enum Type
		{
			Trigger_Off,
			Trigger_HI_LO,
			Trigger_LO_HI,
			Trigger_PRE_HI_LO,
			Trigger_PRE_LO_HI,
			Trigger_HI_LO_SYNC,
			Trigger_LO_HI_SYNC,
			Trigger_Software,
		};
	}

	namespace IDSBinning
	{
		enum Type
		{
			BINNING_DISABLE,
			BINNING_2X,
			BINNING_3X,
			BINNING_4X,
			BINNING_5X,
			BINNING_6X,
			BINNING_8X,
			BINNING_16X,
		};
	}

	namespace IDSMirror
	{
		enum Type
		{
			OFF,
			UPDOWN,
			LEFTRIGHT,
			BOTH
		};
	}

	namespace IDSGPIOConfiguration
	{
		enum Type
		{
			GPIO_INPUT,
			GPIO_OUTPUT,
			GPIO_FLASH,
			GPIO_PWM,
			GPIO_COMPORT_RX,
			GPIO_COMPORT_TX,
			GPIO_MULTI_INTEGRATION_MODE,
			GPIO_TRIGGER,
			GPIO_I2C
		};
	}
}

#endif
