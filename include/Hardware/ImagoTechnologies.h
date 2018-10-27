//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGOTECHNOLOGIES_H
#define AVL_IMAGOTECHNOLOGIES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "Hardware/VisionBox/VisionBoxInterface.h"

namespace avl
{


	struct VisionBox_BaseStateStruct : public BaseState
	{
		VisionBoxInterface* iface;

		VisionBox_BaseStateStruct()
		{
			iface = nullptr;
		}

		~VisionBox_BaseStateStruct()
		{
			delete iface;
			iface = nullptr;
		}
	private:
		VisionBox_BaseStateStruct(const VisionBox_BaseStateStruct&); // = delete
		VisionBox_BaseStateStruct& operator=(const VisionBox_BaseStateStruct&); // = delete
	};

	typedef VisionBox_BaseStateStruct VisionBox_State;


	/// <summary>Returns number of available inputs of RS 422 port.</summary>
	AVL_FUNCTION void VisionBox_RS422GetNumberOfInputs
	(
		VisionBox_State&	ioState,
		int&			outNumberOfInputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns number of available outputs of RS 422 port.</summary>
	AVL_FUNCTION void VisionBox_RS422GetNumberOfOutputs
	(
		VisionBox_State& ioState,
		int&			outNumberOfOutputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads state of inputs as integer number.</summary>
	AVL_FUNCTION void VisionBox_RS422Get
	(
		VisionBox_State&	ioState,
		int&				outInputState
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads state of particular input of RS 422 port.</summary>
	AVL_FUNCTION void VisionBox_RS422GetBit
	(
		VisionBox_State&	ioState,
		const int			inBitIndex,
		bool&				outBitState
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets all outputs of RS422 port.</summary>
	AVL_FUNCTION void VisionBox_RS422Set
	(
		VisionBox_State&	ioState,
		const int			inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets state of particular output of RS 422 port.</summary>
	AVL_FUNCTION void VisionBox_RS422SetBit
	(
		VisionBox_State&	ioState,
		const int			inBitIndex,
		const bool			inBitState
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets source of RS 422 port outputs.</summary>
	AVL_FUNCTION void VisionBox_RS422SetSource
	(
		VisionBox_State&						ioState,
		const int								inBitIndex,
		const avl::VisionBoxRS422OutSource::Type	inSourceType,
		const bool								invertOutput
	)
	THROW_AVL_ERRORS;

	/// <summary>Enables IO Scheduler logic in FPGA unit of Vision Box.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerStart
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Resets and disable IO Scheduler logic.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerReset
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns number of available outputs of IO Scheduler unit of Vision Box computer.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerGetNumberOfOutputs
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		int&				outNumberOfOutputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns number of occupied entries in IO Scheduler buffer.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerGetBufferFillLevel
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		int&				outBufferFillLevel
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns maximum number of entries in IO Scheduler buffer.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerGetBufferMaxElementCount
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		int&				outBufferSize
	)
	THROW_AVL_ERRORS;

	/// <summary>Puts value in IO Scheduler buffer.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerPushValue
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		const int			inCompareValue,
		const int			inOutputValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Connects signal to IO Scheduler input.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerSetTriggerSource
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		const int			inInputIndex,
		const bool			inInvertInput
	)
	THROW_AVL_ERRORS;

	/// <summary>Configure pulse parameters of IO Scheduler output.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerSetOutputPulsTiming
	(
		VisionBox_State&	ioState,
		const int			inSchedulerUnitNumber,
		const int			inDelayInUs,
		const int			inTimeInUs
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets values of selected counter in IO Scheduler unit.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerGetCounter
	(
		VisionBox_State&						ioState,
		const int								inSchedulerUnitNumber,
		avl::VisionBoxIOSchedulerCounter::Type	inCounterType,
		int&								outCounterValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures comparison element of IO Scheduler unit.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerSetCompareSource
	(
		VisionBox_State&						ioState,
		const int								inSchedulerUnitNumber,
		avl::VisionBoxIOSchedulerCmpSrc::Type	inCompareSource
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures direction of encoder input of IO Scheduler unit.</summary>
	AVL_FUNCTION void VisionBox_IOSchedulerSetEncoderDirection
	(
		VisionBox_State&							ioState,
		const int									inSchedulerUnitNumber,
		avl::VisionBoxIOSchedulerEncoderDir::Type	inEncoderDirection
	)
	THROW_AVL_ERRORS;

	/// <summary>Sends byte array through RS232 port.</summary>
	AVL_FUNCTION void VisionBox_RS232WriteNBytes
	(
		VisionBox_State&		ioState,
		const atl::Array<int>&	inBytesToWrite
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads byte array from RS232 port.</summary>
	AVL_FUNCTION void VisionBox_RS232ReadNBytes
	(
		VisionBox_State&	ioState,
		const int			inBytesToRead,
		const int			inTimeoutInMs,
		atl::Array<int>&	outData,
		int&				outBytesReceived
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of bytes waiting in RS232 buffer.</summary>
	AVL_FUNCTION void VisionBox_RS232GetAvailableByteCount
	(
		VisionBox_State&	ioState,
		int&				outBytesAvailable
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures RS232 port. Has to be called before any other Vision Box' RS232 operation.</summary>
	AVL_FUNCTION void VisionBox_RS232ConfigureBaudRate
	(
		VisionBox_State&	ioState,
		const int			inBaudRate
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a digital output state of Imago VisionBox computers.</summary>
	/// <param name="inPort">Number of DigitalOutput device to use.</param>
	/// <param name="inOutput">Number of output to change.</param>
	/// <param name="inState">State of pin output to set.</param>
	AVL_FUNCTION void VisionBox_SetDigitalOutput
	(
		VisionBox_State&	ioState,
		const int			inPort,		
		const int			inOutput,	
		const bool			inState		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of digital outputs.</summary>
	AVL_FUNCTION void VisionBox_GetNumberOfDigitalOutputs
	(
		VisionBox_State&	ioState,
		const int			inPort,
		int&				outNumberOfOutputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets source for specified digital output pin.</summary>
	AVL_FUNCTION void VisionBox_SetDigitalOutputSource
	(
		VisionBox_State&	ioState,
		const int			inPort,
		const int			inPin,
		avl::VisionBoxDigitalOutSource::Type	inSource,
		const bool								inInvertOutput	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads a digital input state of Imago VisionBox computers.</summary>
	/// <param name="inPort">Number of DigitalInput device to use.</param>
	/// <param name="inInput">Number of input to read.</param>
	/// <param name="outState">State of selected input pin.</param>
	AVL_FUNCTION void VisionBox_GetDigitalInput
	(
		VisionBox_State&		ioState,
		const int				inPort,		
		const int				inInput,	
		bool&					outState	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of available digital inputs.</summary>
	/// <param name="inPort">Number of DigitalInput device to use.</param>
	/// <param name="outNumberOfInputs">Number of Digital Inputs.</param>
	AVL_FUNCTION void VisionBox_GetNumberOfDigitalInputs
	(
		VisionBox_State&	ioState,
		const int			inPort,				
		int&				outNumberOfInputs	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes software trigger.</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inState">Set software trigger on or off.</param>
	AVL_FUNCTION void VisionBox_StrobeSoftwareTrigger
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,	
		const bool			inState			
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes Strobe. Has to be called before any other Strobe related function.</summary>
	/// <param name="inReset">Default value: True.</param>
	AVL_FUNCTION void VisionBox_StrobeInit
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,
		const bool			inReset
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes limits</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inLimitCurrent">Calculate allowed off-time or maximum current.</param>
	/// <param name="inMaxSupplyVoltage">Supply voltage.</param>
	/// <param name="inMaxLoadVoltage">Voltage across the load with MaxCurrent current.</param>
	/// <param name="inMaxOnTime">Maximum allowed on-time.</param>
	/// <param name="inMinOffTime">Minimum allowed off-time.</param>
	/// <param name="inMaxCurrent">Maximum allowed current in mA.</param>
	/// <param name="outResult">Result calculated regarding inLimitCurrent value.</param>
	AVL_FUNCTION void VisionBox_StrobeSetLimits
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,		
		const int			inLimitCurrent,		
		const int			inMaxSupplyVoltage,	
		const int			inMaxLoadVoltage,	
		const int			inMaxOnTime,		
		const int			inMinOffTime,		
		const int			inMaxCurrent,		
		int&				outResult			

	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes trigger delay</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inTriggerDelay">Delay in us.</param>
	AVL_FUNCTION void VisionBox_StrobeSetTriggerDelay
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,	
		const int			inTriggerDelay	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes on-time</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inOnTime">On-time in us.</param>
	AVL_FUNCTION void VisionBox_StrobeSetOnTime
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,	
		const int			inOnTime		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes fixed current</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inSupplyVoltage">Supply voltage used for the strobe output.</param>
	/// <param name="inLoadVoltage">The voltage across the load when the output current is equal to inCurrent.</param>
	/// <param name="inMaxOnTime">Maximum allowed on-time in us.</param>
	/// <param name="inMinOffTime">Minimum allowed off-time in us.</param>
	/// <param name="inCurrent">Output current in mA.</param>
	/// <param name="outResult">Minimum allowed off-time.</param>
	AVL_FUNCTION void VisionBox_StrobeSetFixedCurrent
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,	
		const int			inSupplyVoltage,
		const int			inLoadVoltage,	
		const int			inMaxOnTime,	
		const int			inMinOffTime,	
		const int			inCurrent,		
		int&				outResult		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes current</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inCurrent">Desired current in mA.</param>
	/// <param name="inValidate">Whether to validate current.</param>
	AVL_FUNCTION void VisionBox_StrobeSetCurrent
	(
		VisionBox_State&	ioState,
		const int			inStrobeUnit,	
		const int			inCurrent,		
		const int			inValidate		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes trigger source</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inSource">Selects the signal used as trigger source.</param>
	/// <param name="inInvertTrigger">Whether to invert trigger signal.</param>
	AVL_FUNCTION void VisionBox_StrobeSetTriggerSource
	(
		VisionBox_State&						ioState,
		const int								inStrobeUnit,	
		const avl::VisionBoxStrobeSource::Type	inSource,		
		const int								inInvertTrigger	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobes trigger mode</summary>
	/// <param name="inStrobeUnit">Number of strobe device to use.</param>
	/// <param name="inMode">Selects strobe mode.</param>
	/// <param name="outResult">Whether new mode has been selected.</param>
	AVL_FUNCTION void VisionBox_StrobeSetTriggerMode
	(
		VisionBox_State&						ioState,
		const int								inStrobeUnit,	
		const avl::VisionBoxStrobeMode::Type	inMode,			
		int&									outResult		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets trigger generator configuration</summary>
	/// <param name="inConfigCommand">String with settings command.</param>
	AVL_FUNCTION void VisionBox_SetTriggerGeneratorConfiguration
	(
		VisionBox_State&	ioState,
		const atl::String&	inConfigCommand 
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets trigger generator configuration</summary>
	/// <param name="inConfigCommand">String with value to read.</param>
	/// <param name="outValue">Requested value.</param>
	AVL_FUNCTION void VisionBox_GetTriggerGeneratorConfiguration
	(
		VisionBox_State&	ioState,
		const atl::String&	inConfigCommand,	
		int&				outValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets camera trigger configuration</summary>
	/// <param name="inDeviceNumber">Device number.</param>
	/// <param name="inChannelNumber">Channel in device - when set to auto all channels will be configured at the same time. Default value: atl::NIL.</param>
	/// <param name="inTriggerSource">Signal used to issue the trigger.</param>
	/// <param name="inTrgPOff">P Gate OFF signal.</param>
	/// <param name="inTrgPOn">P Gate ON signal.</param>
	/// <param name="inTrgNOff">N Gate OFF signal.</param>
	/// <param name="inTrgNOn">N Gate ON signal.</param>
	AVL_FUNCTION void VisionBox_SetCameraTrigger
	(
		VisionBox_State&						ioState,
		const int								inDeviceNumber,		
		const atl::Optional<int>				inChannelNumber,	
		const avl::VisionBoxTriggerSource::Type	inTriggerSource,	
		const bool								inTrgPOff,			
		const bool								inTrgPOn,			
		const bool								inTrgNOff,			
		const bool								inTrgNOn			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of outputs of camera trigger device</summary>
	AVL_FUNCTION void VisionBox_GetCameraTriggerNumberOfOutputs
	(
		VisionBox_State&	ioState,
		const int			inDeviceNumber,
		int&				outNumberOfOutputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of multiplexer outputs.</summary>
	AVL_FUNCTION void VisionBox_GetMultiplexerNumberOfOutputs
	(
		VisionBox_State&	ioState,
		int&				outNumberOfOutputs
	)
	THROW_AVL_ERRORS;

	/// <summary>Connects internal multiplexer signals</summary>
	AVL_FUNCTION void VisionBox_ConnectMultiplexerOutput
	(
		VisionBox_State&					ioState,
		const int							inOutputIndex,
		const avl::VisionBoxMuxSource::Type	inTriggerSource
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets led mode</summary>
	/// <param name="inLedIndex">Selects led.</param>
	/// <param name="inMode">Selects led mode.</param>
	AVL_FUNCTION void VisionBox_SetLedMode
	(
		VisionBox_State&					ioState,
		const int							inLedIndex,	
		const avl::VisionBoxLedMode::Type	inMode		
		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets led state</summary>
	/// <param name="inLedIndex">Selects led.</param>
	/// <param name="inLedState">Whether to turn led on or off.</param>
	AVL_FUNCTION void VisionBox_SetLed
	(
		VisionBox_State&	ioState,
		const int			inLedIndex,	
		const bool			inLedState  
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets number of available LEDs</summary>
	/// <param name="outCount">Number of LEDs in system.</param>
	AVL_FUNCTION void VisionBox_GetNumberOfLeds
	(
		VisionBox_State&	ioState,
		int&				outCount	
		
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures led signal generator</summary>
	/// <param name="inGeneratorIndex">Number of generator to configure.</param>
	/// <param name="inBlinkCount">Count of LED blinks.</param>
	/// <param name="inMs_ton">Duration of "ON" signal.</param>
	/// <param name="inMs_toff">Duration of "OFF" signal.</param>
	/// <param name="inMs_tpause">Duration of pause between sequences.</param>
	AVL_FUNCTION void VisionBox_ConfigureLedGenerator
	(
		VisionBox_State&	ioState,
		const int			inGeneratorIndex,	
		const int			inBlinkCount,		
		const int			inMs_ton,			
		const int			inMs_toff,			
		const int			inMs_tpause			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGOTECHNOLOGIES_H

