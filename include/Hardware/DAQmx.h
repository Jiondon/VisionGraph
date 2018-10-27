//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DAQMX_H
#define AVL_DAQMX_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Hardware/DAQmx/DAQmxInterface.h"

namespace avl
{



	namespace DAQmxTerminalConfig
	{
		enum Type
		{
			Default  = 0,
			RSE,
			NRSE,
			Differential,
			Pseudodifferential,
		};
	}

	namespace DAQmxIdleState
	{
		enum Type
		{
			High  = 0,
			Low,
		};
	}

	namespace DAQmxSampleMode
	{
		enum Type
		{
			FiniteSamps = 0,
			ContSamps,
			HWTimedSinglePoint,
		};
	}

	namespace DAQmxShuntResistorLoc 
	{
		enum Type
		{
			Default = 0,
			Internal,
			External,
		};
	}

	namespace DAQmxActiveEdge
	{
		enum Type
		{
			Rising = 0,
			Falling,
		};
	}

	namespace DAQmxFrequencyUnit
	{
		enum Type
		{
			Hz = 0,
			Ticks,
		};
	}

	namespace DAQmxPulseWidthUnit
	{
		enum Type
		{
			Seconds = 0,
			Ticks,
		};
	}

	namespace DAQmxCountDirection
	{
		enum Type
		{
			CountUp = 0,
			CountDown,
			ExtControlled,
		};
	}
	
	struct DAQmx_BaseStructState : public BaseState
	{
		DAQmxInterface* daqMx;

		DAQmx_BaseStructState()
			: daqMx(nullptr)
		{}

		~DAQmx_BaseStructState()
		{
			delete daqMx;
		}

	private:
		DAQmx_BaseStructState(const DAQmx_BaseStructState&); //=delete
		DAQmx_BaseStructState& operator=(const DAQmx_BaseStructState&); //=delete
	};

	
	typedef DAQmx_BaseStructState DAQmx_StopTaskState;
	typedef DAQmx_BaseStructState DAQmx_StartTaskState;

	typedef DAQmx_BaseStructState DAQmx_CreateAnalogChannelState;
	typedef DAQmx_BaseStructState DAQmx_ReadArrayState;
	typedef DAQmx_BaseStructState DAQmx_ReadScalarState;
	typedef DAQmx_BaseStructState DAQmx_WriteScalarState;
	typedef DAQmx_BaseStructState DAQmx_WriteArrayState;
	typedef DAQmx_BaseStructState DAQmx_CreateDigitalPortState;
	typedef DAQmx_BaseStructState DAQmx_GetDigitalChannelState;
	typedef DAQmx_BaseStructState DAQmx_SetDigitalChannelState;
	typedef DAQmx_BaseStructState DAQmx_CreateCountEdgesChannelState;
	typedef DAQmx_BaseStructState DAQmx_CreatePulseChannelFreqState;
	typedef DAQmx_BaseStructState DAQmx_ConfigureTimingState;
	typedef DAQmx_BaseStructState DAQmx_ConfigDigitEdgeTriggerState;
	typedef DAQmx_BaseStructState DAQmx_ConfigAnalogEdgeTriggerState;

	typedef DAQmx_BaseStructState DAQmx_WriteDigitalArrayState;
	typedef DAQmx_BaseStructState DAQmx_WriteAnalogArrayState;

	typedef DAQmx_BaseStructState DAQmx_WriteAnalogScalarState;
	typedef DAQmx_BaseStructState DAQmx_WriteDigitalScalarState;

	typedef DAQmx_BaseStructState DAQmx_ReadAnalogScalarState;
	typedef DAQmx_BaseStructState DAQmx_ReadDigitalScalarState;
	typedef DAQmx_BaseStructState DAQmx_ReadCounterScalarState;

	typedef DAQmx_BaseStructState DAQmx_ReadDigitalArrayState;
	typedef DAQmx_BaseStructState DAQmx_ReadAnalogArrayState;
	typedef DAQmx_BaseStructState DAQmx_ReadCounterArrayState;
	typedef DAQmx_BaseStructState DAQmx_ResetDeviceState;
	


	/// <summary>Stops and clears a task.</summary>
	/// <param name="inDeviceID">Device alias, product name or serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of a task to stop.</param>
	AVL_FUNCTION void DAQmx_StopTask
	(
		DAQmx_StopTaskState&				ioState,
		atl::Optional<const atl::String&>	inDeviceID, 
		avl::DAQmxTaskID					inTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts a specified task.</summary>
	/// <param name="inDeviceID">Device alias, product name or serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of a task to start.</param>
	AVL_FUNCTION void DAQmx_StartTask
	(
		DAQmx_StartTaskState&				ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		avl::DAQmxTaskID					inTaskID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a task and channel to measure or generate analog values.</summary>
	/// <param name="inDeviceID">Device alias, product name or serial number. Default value: atl::NIL.</param>
	/// <param name="inChannel">Name of the physical channel used to create a virtual channel. Default value: atl::NIL.</param>
	/// <param name="inCVType">Electrical mode.</param>
	/// <param name="inIOType">Direction of channel.</param>
	/// <param name="inTerminalConfig">Input terminal configuration.</param>
	/// <param name="inMinValue">Minimum value, that is expected to measure or generate.</param>
	/// <param name="inMaxValue">Maximum value, that is expected to measure or generate. Default value: 5.0f.</param>
	/// <param name="inShuntResistorLocation">Location of the shunt resistor.</param>
	/// <param name="inExtShuntResistorValue">Value of the shunt resistor. Default value: atl::NIL.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_CreateAnalogChannel
	(
		DAQmx_CreateAnalogChannelState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID,					
		atl::Optional<const atl::String&>		inChannel,					
		avl::ElectricalMode::Type				inCVType,					
		avl::DirectionMode::Type				inIOType,					
		avl::DAQmxTerminalConfig::Type			inTerminalConfig,			
		float								inMinValue,					
		float								inMaxValue,					
		avl::DAQmxShuntResistorLoc::Type		inShuntResistorLocation,	
		atl::Optional<float>				inExtShuntResistorValue,	
		avl::DAQmxTaskID&						outTaskID					
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a task and channel to measure or generate digital values.</summary>
	/// <param name="inDeviceID">Device alias, product name or serial number. Default value: atl::NIL.</param>
	/// <param name="inPort">Name of a physical port used to create a virtual channel. Default value: atl::NIL.</param>
	/// <param name="inIOType">Direction of a channel.</param>
	/// <param name="inFirstLine">First line to measure or generate. Default value: atl::NIL.</param>
	/// <param name="inLastLine">Last line to measure or generate. Default value: atl::NIL.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_CreateDigitalPort
	(
		DAQmx_CreateDigitalPortState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		const atl::Optional<const atl::String&>	inPort,		
		avl::DirectionMode::Type				inIOType,	
		atl::Optional<int>						inFirstLine,
		atl::Optional<int>						inLastLine,	
		avl::DAQmxTaskID&						outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a task and channel to count number of edges.</summary>
	/// <param name="inDeviceID">Device alias, product name or serial number. Default value: atl::NIL.</param>
	/// <param name="inCounter">Name of a counter used to create virtual channel. Default value: atl::NIL.</param>
	/// <param name="inActiveEdge">Active edge for counting.</param>
	/// <param name="inInitialCount">Initial value.</param>
	/// <param name="inCountDirection">Type of counting (incrementing and decrementing values).</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_CreateCountEdgesChannel
	(
		DAQmx_CreateCountEdgesChannelState&			ioState,
		atl::Optional<const atl::String&>			inDeviceID,			
		const atl::Optional<const atl::String&>		inCounter,			
		avl::DAQmxActiveEdge::Type					inActiveEdge,		
		int											inInitialCount,		
		avl::DAQmxCountDirection::Type				inCountDirection,	
		avl::DAQmxTaskID&							outTaskID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a task and channel to generate pulse.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inCounter">Name of a counter used to create virtual channel. Default value: atl::NIL.</param>
	/// <param name="inIdleState">Resting state of an output terminal.</param>
	/// <param name="inInitDelay">Time (in seconds) to wait before generating pulse.</param>
	/// <param name="inFrequency">Frequency of generated pulse.</param>
	/// <param name="inDutyCycle">The width of the pulse divided by the pulse period.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_CreatePulseChannelFreq
	(
		DAQmx_CreatePulseChannelFreqState&		ioState,
		atl::Optional<const atl::String&>		inDeviceID,		
		atl::Optional<const atl::String&>		inCounter,		
		avl::DAQmxIdleState::Type				inIdleState,	
		float								inInitDelay,	
		float								inFrequency,	
		float								inDutyCycle,	
		avl::DAQmxTaskID&						outTaskID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes multiple samples to a specified digital task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to write samples to.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to write samples. Default value: atl::NIL.</param>
	/// <param name="inValues">Array of samples to write.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_WriteDigitalArray
	(	
		DAQmx_WriteDigitalArrayState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		const atl::Array<int>&					inValues,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes multiple samples to a specified analog task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to write samples to.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to write samples. Default value: atl::NIL.</param>
	/// <param name="inValues">Array of samples to write.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_WriteAnalogArray
	(
		DAQmx_WriteDigitalArrayState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID, 
		avl::DAQmxTaskID					inTaskID,	
		atl::Optional<int>					inTimeout,	
		const atl::Array<float>&		inValues,	
		atl::Conditional<avl::DAQmxTaskID>&	outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a digital input to a specified value.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to write samples to.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to write sample. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to write.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_WriteDigitalScalar
	(
		DAQmx_WriteDigitalScalarState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		int										inValue,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets an analog input to a specified value.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to write samples to.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to write sample. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to write.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_WriteAnalogScalar
	(
		DAQmx_WriteAnalogScalarState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		float								inValue,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads a sample from a specified digital task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read sample from.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read sample. Default value: atl::NIL.</param>
	/// <param name="outValue">Value read from the task.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadDigitalScalar
	(
		DAQmx_ReadDigitalScalarState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		int&									outValue,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads a sample from a specified analog task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read sample from.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read sample. Default value: atl::NIL.</param>
	/// <param name="outValue">Value read from task.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadAnalogScalar
	(
		DAQmx_ReadAnalogScalarState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		float&								outValue,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads a sample from a specified counter task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read sample from.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read sample. Default value: atl::NIL.</param>
	/// <param name="outValue">Value read from task.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadCounterScalar
	(
		DAQmx_ReadCounterScalarState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		float&								outValue,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads multiple samples from a specified digital task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read samples from.</param>
	/// <param name="inSamples">Number of samples to read.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read samples. Default value: atl::NIL.</param>
	/// <param name="outValues">Array of read values.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadDigitalArray
	(
		DAQmx_ReadDigitalArrayState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID, 
		avl::DAQmxTaskID					inTaskID,	
		int									inSamples,	
		atl::Optional<int>					inTimeout,	
		atl::Array<int>&					outValues,	
		atl::Conditional<avl::DAQmxTaskID>&	outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads multiple samples from a specified analog task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read samples from.</param>
	/// <param name="inSamples">Number of samples to read.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read samples. Default value: atl::NIL.</param>
	/// <param name="outValues">Array of read values.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadAnalogArray
	(
		DAQmx_ReadAnalogArrayState&				ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		int										inSamples,	
		atl::Optional<int>						inTimeout,	
		atl::Array<float>&					outValues,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads multiple samples from a specified counter task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read samples from.</param>
	/// <param name="inSamples">Number of samples to read.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to read samples. Default value: atl::NIL.</param>
	/// <param name="outValues">Array of read values.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ReadCounterArray
	(
		DAQmx_ReadCounterArrayState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		int										inSamples,	
		atl::Optional<int>						inTimeout,	
		atl::Array<float>&					outValues,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns array of values from a digital channels.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to read sample from.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to get sample. Default value: atl::NIL.</param>
	/// <param name="outValues">Digital values read from task.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_GetDigitalChannel
	(
		DAQmx_GetDigitalChannelState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID, 
		avl::DAQmxTaskID						inTaskID,	
		atl::Optional<int>						inTimeout,	
		atl::Array<bool>&						outValues,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets array of values to a digital channels.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task to write sample to.</param>
	/// <param name="inTimeout">Time (in milliseconds) to wait for the function to set sample. Default value: atl::NIL.</param>
	/// <param name="inValues">Values to write to channel.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_SetDigitalChannel
	(
		DAQmx_SetDigitalChannelState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID,		
		avl::DAQmxTaskID						inTaskID,		
		atl::Optional<int>						inTimeout,		
		const atl::Array<bool>&					inValues,		
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Configure timing in specified task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task where timing is used.</param>
	/// <param name="inTimingMode">Mode of the timing.</param>
	/// <param name="inSource">Source terminal of sample clock. Default value: atl::NIL.</param>
	/// <param name="inRate">Sampling rate in samples per second.</param>
	/// <param name="inActiveEdge">Active edge to generate or acquire samples.</param>
	/// <param name="inSampleMode">Sampling mode.</param>
	/// <param name="inSampsPerChanToAcq">Number of samples to acquire or generate for each channel.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ConfigureTiming
	(
		DAQmx_ConfigureTimingState&				ioState,
		atl::Optional<const atl::String&>		inDeviceID,				
		avl::DAQmxTaskID						inTaskID,				
		avl::TimingMode::Type					inTimingMode,			
		atl::Optional<const atl::String&>		inSource,				
		float								inRate,					
		avl::DAQmxActiveEdge::Type				inActiveEdge,			
		avl::DAQmxSampleMode::Type				inSampleMode,			
		int										inSampsPerChanToAcq,	
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures a trigger in a specified task.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task where triggering is used.</param>
	/// <param name="inTriggerSource">Source of trigger.</param>
	/// <param name="inTriggerEdge">Edge of trigger.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ConfigDigitEdgeTrigger
	(
		DAQmx_ConfigDigitEdgeTriggerState&		ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		avl::DAQmxTaskID						inTaskID,			
		const atl::String&						inTriggerSource,	
		avl::DAQmxActiveEdge::Type				inTriggerEdge,		
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns values from a digital channel.</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number. Default value: atl::NIL.</param>
	/// <param name="inTaskID">ID of task where triggering is used.</param>
	/// <param name="inTriggerSource">Source of trigger.</param>
	/// <param name="inTriggerSlope">Slope of trigger.</param>
	/// <param name="inTriggerLevel">Threshold of trigger.</param>
	/// <param name="outTaskID">ID of a created task.</param>
	AVL_FUNCTION void DAQmx_ConfigAnalogEdgeTrigger
	(
		DAQmx_ConfigAnalogEdgeTriggerState&		ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		avl::DAQmxTaskID						inTaskID,			
		const atl::String&						inTriggerSource,	
		avl::DAQmxActiveEdge::Type				inTriggerSlope,		
		float								inTriggerLevel,		
		atl::Conditional<avl::DAQmxTaskID>&		outTaskID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Resets a selected device</summary>
	/// <param name="inDeviceID">Device alias, product name or a serial number.</param>
	AVL_FUNCTION void DAQmx_ResetDevice
	(
		DAQmx_ResetDeviceState&	ioState,
		const atl::String&		inDeviceID 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_DAQMX_H

