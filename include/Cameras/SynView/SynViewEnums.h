//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SYNVIEW_ENUMS_H
#define SYNVIEW_ENUMS_H

namespace avl
{
	namespace SynViewColorFormat
	{
		enum Type
		{
			Mono8,
			Mono12,
			RGB8
		};
	}

	namespace SynViewTriggerSource
	{
		enum Type
		{
			Software,
			Line1,
			Line2,
			Line3,
			Line4,
			Line5,
			Line6,
			Line7,
			Line8,
			Line17,
			Line18,
			Line19,
			Line20,
			Line21,
			Line22,
			Line23,
			Line24
		};
	}

	namespace SynViewTriggerActivation
	{
		enum Type
		{
			RisingEdge,
			FallingEdge
		};
	}

	namespace SynViewTimerTriggerSource
	{
		enum Type
		{
			Off,
			FrameTrigger,
			Counter1End,
			Counter2End,
			Counter3End,
			Counter4End,
			UserOutput1,
			UserOutput2,
			UserOutput3,
			UserOutput4,
			UserOutput5,
			UserOutput6,
			UserOutput7,
			UserOutput8
		};
	}

	namespace SynViewLineSource
	{
		enum Type
		{
			Off,
			ExposureActive,
			Timer1Active,
			Timer2Active,
			Timer3Active,
			Timer4Active,
			UserOutput1,
			UserOutput2,
			UserOutput3,
			UserOutput4,
			UserOutput5,
			UserOutput6,
			UserOutput7,
			UserOutput8
		};
	}
	namespace SynViewUserOutputs
	{
		enum Type
		{
			UserOutput1,
			UserOutput2,
			UserOutput3,
			UserOutput4,
			UserOutput5,
			UserOutput6,
			UserOutput7,
			UserOutput8
		};
	}

	namespace SynViewAutoMode
	{
		enum Type
		{
			Off,
			Once,
			Continuous
		};
	}

	namespace SynViewTimerSelector
	{
		enum Type
		{
			Timer1,
			Timer2,
			Timer3,
			Timer4
		};
	}

	namespace SynViewStrobeEnable
	{
		enum Type
		{
			Off,
			AllClusters,
			LedCluster1,
			LedCluster2
		};
	}
}

#endif