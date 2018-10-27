//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef MVGENTL_ACQUIRE_ENUMS_H
#define MVGENTL_ACQUIRE_ENUMS_H

namespace avl
{
	namespace MvIMPACTTriggerActivation
	{
		enum Type
		{
			Off = 0,
			Software,
			LowLevel,
			HighLevel,
			FallingEdge,
			RisingEdge,
			AnyEdge,
		};
	}

	namespace MvIMPACTTriggerSource
	{
		enum Type
		{
			Line4 = 0,
			Line5,
			Timer1Start,
			Timer2Start,
			Timer1End,
			Timer2End,
			Timer1Active,
			Timer2Active,
			mvLogicGateOR1Output,
			mvLogicGateOR2Output,
			mvLogicGateOR3Output,
			mvLogicGateOR4Output,
			UserOutput0,
			UserOutput1,
			UserOutput2,
			UserOutput3,
			Counter1End,
			Counter2End,
			Counter3End,
			Counter4End,
			Counter1Active,
			Counter2Active,
			Counter3Active,
			Counter4Active,
		};
	}
}

#endif
