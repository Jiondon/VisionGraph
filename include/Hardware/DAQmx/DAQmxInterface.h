//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_DAQMX_INTERFACE_H
#define AVL_DAQMX_INTERFACE_H

#include "ATL/Optional.h"
#include "AVLCommon/CancellationTypes.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"

namespace avl
{

	typedef int DAQmxTaskID;

	namespace DirectionMode
	{
		enum Type { Input = 0, Output, }; 
	}

	namespace ElectricalMode 
	{
		enum Type { Current = 0, Voltage, }; 
	}

	namespace TimingMode
	{
		enum Type { ImplicitTiming = 0, SampleClockTiming, HandshakingTiming, }; 
	}

	class DAQmxInterface
	{
	public:
		virtual ~DAQmxInterface() {}
		virtual void BindToFirstDevice() = 0;
		virtual void BindToNamedDevice( const atl::String& device ) = 0;
		virtual void ResetDevice( const atl::String& devName ) = 0;
		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;

		virtual void StopTask( avl::DAQmxTaskID taskID ) = 0;
		virtual void StartTask( avl::DAQmxTaskID taskID ) = 0;

		virtual void CreateAnalogChannel( 
			avl::ElectricalMode::Type elecMode, 
			DirectionMode::Type io, 
			atl::Optional<const atl::String&> channel,
			int terminalConfig,
			float minValue,
			float maxValue, 
			atl::Optional<int> shuntResistorLoc,
			atl::Optional<float> extShuntResistorVal,
			avl::DAQmxTaskID& outTaskID
			) = 0;

		virtual void CreateDigitalPort(
			DirectionMode::Type io,
			atl::Optional<const atl::String&> port, 
			atl::Optional<int> firstChannel,
			atl::Optional<int> lastChannel,
			avl::DAQmxTaskID& outTaskID
		) = 0;
	
		virtual void CreateCountEdgesChannel(
			atl::Optional<const atl::String&> counter, 
			int activeEdge,
			int initialCount, 
			int countDirection,
			avl::DAQmxTaskID& outTaskID
		) = 0 ;

		virtual void CreatePulseChannelFreq(
			atl::Optional<const atl::String&> counter, 
			int idleState,
			float initDelay, 
			float frequency, 
			float dutyCycle,
			avl::DAQmxTaskID& outTaskID
		) = 0;

		virtual void ReadDigitalArray( avl::DAQmxTaskID taskID, int samples, atl::Optional<int> timeout, atl::Array<int>& outValues ) = 0;
		virtual void ReadAnalogArray( avl::DAQmxTaskID taskID,  int samples, atl::Optional<int> timeout, atl::Array<float>& outValues ) = 0;
		virtual void ReadCounterArray( avl::DAQmxTaskID taskID, int samples, atl::Optional<int> timeout, atl::Array<float>& outValues ) = 0;

		virtual void ReadDigitalScalar( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, int& outValue ) = 0;
		virtual void ReadAnalogScalar( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, float& outValue ) = 0;
		virtual void ReadCounterScalar( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, float& outValue ) = 0;

		virtual void WriteDigitalArray( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, const atl::Array<int>& inValues ) = 0;
		virtual void WriteAnalogArray( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, const atl::Array<float>& inValues ) = 0;

		virtual void WriteDigitalScalar( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, int inValue ) = 0;
		virtual void WriteAnalogScalar( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, float inValue ) = 0;

		virtual void SetDigitalChannel( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, const atl::Array<bool>& values ) = 0;
		virtual void GetDigitalChannel( avl::DAQmxTaskID taskID, atl::Optional<int> timeout, atl::Array<bool>& values ) = 0;
		virtual void ConfigureTiming( avl::DAQmxTaskID taskID, TimingMode::Type tmMode, atl::Optional<const atl::String&> source, float rate, int activeEdge, int sampleMode, int sampsPerChanToAcq ) = 0;
		virtual void ConfigureDigitalEdgeTrigger( avl::DAQmxTaskID taskID, atl::String triggerSource, int triggerEdge ) = 0;
		virtual void ConfigureAnalogEdgeTrigger( avl::DAQmxTaskID taskID, atl::String triggerSource, int triggerSlope, float triggerLevel ) = 0;
	};

}

#endif 