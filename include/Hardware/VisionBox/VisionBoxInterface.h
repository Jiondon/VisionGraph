//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef VISION_BOX_INTERFACE_H
#define VISION_BOX_INTERFACE_H
#include "VisionBoxEnums.h"
#include "ATL/AtlString.h"
namespace avl
{
	class VisionBoxInterface
	{
	public:
		virtual ~VisionBoxInterface(){}

		/* Digital Output */
		virtual void SetDigitalOutput( unsigned int port, unsigned int pin, bool value ) = 0;
		virtual void GetNumberOfDigitalOutputs(unsigned int port, int & numberOfOutputs ) = 0;
		virtual void SetDigitalOutputSource( unsigned int port, unsigned int pin, VisionBoxDigitalOutSource::Type source, bool invertOutput) = 0;

		/* Digital Input */
		virtual void ReadDigitalInput( unsigned int port, unsigned int pin, bool& value) = 0;
		virtual void SetDigitalInputDebounceTime( unsigned int port, unsigned int lowSignalDurationInMs, unsigned int highSignalDurationInMs) = 0;
		virtual void GetNumberOfDigitalInputs( unsigned int port, int & numberOfInputs ) = 0;

		/* Strobe */
		virtual void EnableTrigger_Strobe(unsigned int strobeUnitNo, bool enable) = 0;
		virtual void SetOnTime_Strobe(unsigned int strobeUnitNo, unsigned int onTime) = 0;
		virtual void SetTriggerDelay_Strobe(unsigned int strobeUnitNo, unsigned int triggerDelay) = 0;
		virtual void SetLimits_Strobe(unsigned int strobeUnitNo, int currentLimit, int maxSupplyVoltage, int maxLoadVoltage, 
			unsigned int maxOnTime, unsigned int minOffTime, unsigned int maxCurrent, int& result) = 0;
		virtual void SetFixedCurrent_Strobe(unsigned int strobeUnitNo, int supplyVoltage, int loadVoltage, unsigned int maxOnTime, unsigned int minOffTime, unsigned int current, int& result) = 0;
		virtual void SetCurrent_Strobe(unsigned int strobeUnitNo, int current, int validate=0) = 0;
		virtual void Init_Strobe(unsigned int strobeUnitNo, bool reset = true) = 0;
		virtual void SetTriggerMode_Strobe(unsigned int strobeUnitNo, avl::VisionBoxStrobeMode::Type mode, int& result) = 0;
		virtual void SetTriggerSource_Strobe(unsigned int strobeUnitNo, VisionBoxStrobeSource::Type source, int invertTrigger) = 0;
		
		/* Trigger Generator */
		virtual void GetTriggerGenConfiguration(const atl::String& inputCommand, unsigned int& readValue) = 0;
		virtual void SetTriggerGenConfiguration(const atl::String& command) = 0;

		/* Camera Trigger */
		virtual void SetCameraTrigger(unsigned int deviceNumber, unsigned int channelIndex, VisionBoxTriggerSource::Type triggerSource, bool trgPOff = false, bool trgPOn = true, bool trgNOff=false, bool trgNOn=false) = 0;
		virtual void SetCameraTrigger_All(unsigned int deviceNumber, VisionBoxTriggerSource::Type triggerSource, bool trgPOff = false, bool trgPOn = true, bool trgNOff=false, bool trgNOn=false) = 0;
		virtual void GetCameraTriggerNumberOfOutputs(unsigned int deviceNumber, int& numberOfOutputs) = 0;

		/* Multiplexer */
		virtual void Multiplexer_ConnectOutput(int outputIndex, VisionBoxMuxSource::Type source) = 0;
		virtual void Multiplexer_GetNumberOfOutputs(int & numberOfOutputs) = 0;
		
		/* LEDs */
		virtual void GetNumberOfLEDs(int& count) = 0;
		virtual void SetLED(int ledIndex, bool state) = 0;
		virtual void SetLEDMode(int ledIndex, VisionBoxLedMode::Type mode) = 0;
		virtual void ConfigureLEDGenerator(int generatorIndex, int blinkCount, int ms_ton, int ms_toff, int ms_tpause) = 0;

		/* RS232 */
		virtual void ConfigureBaudRate_RS232(const unsigned int baudRate) = 0;
		virtual void GetAvailableBytesCount_RS232(int & availableBytes) = 0;
		virtual void ReadNByte_RS232(unsigned int bytesToRead, unsigned int & bytesReceived, unsigned char * data, unsigned int timeoutInMs) = 0;
		virtual void WriteNByte_RS232(unsigned int bytesToWrite, const unsigned char * data) = 0;

		/* RS422 */
		virtual void GetNumberOfInputs_RS422(int & numberOfInputs) = 0;
		virtual void GetNumberOfOutputs_RS422(int & numberOfOutputs) = 0;
		virtual void Get_RS422(unsigned int& inputState) = 0;
		virtual void GetBit_RS422(unsigned int bitIndex, bool& bitState) = 0;
		virtual void Set_RS422(unsigned int value) = 0;
		virtual void SetBit_RS422(unsigned int bitIndex, bool bitState) = 0;
		virtual void SetSource_RS422(unsigned int bitIndex, VisionBoxRS422OutSource::Type source, bool invertOutput) = 0;

		/* IOScheduler */
		virtual void Start_IOScheduler() = 0;
		virtual void Reset_IOScheduler() = 0;
		virtual void GetNumberOfOutputs_IOScheduler(const unsigned int schedulerUnitNo, unsigned int & numberOfOutputs) = 0;
		virtual void GetBufferFillLevel_IOScheduler(const unsigned int schedulerUnitNo, unsigned int & bufferFillLevel) = 0;
		virtual void GetBufferMaxElementCount_IOScheduler(const unsigned int schedulerUnitNo, unsigned int & bufferSize) = 0;
		virtual void PushValue_IOScheduler(const unsigned int schedulerUnitNo, const unsigned int compareValue, const unsigned int outputValue) = 0;

		virtual void SetTriggerSource_IOScheduler(const unsigned int schedulerUnitNo, const unsigned int inputIndex, const bool invertInput) = 0;
		virtual void SetOutputPulsTiminig_IOScheduler(const unsigned int schedulerUnitNo, const unsigned int delayInUs, const unsigned int onTimeInUs) = 0;
		
		virtual void GetCounter_IOScheduler(const unsigned int schedulerUnitNo, const VisionBoxIOSchedulerCounter::Type counterType, unsigned int& counterValue) = 0;
		virtual void SetCompareSource_IOScheduler(const unsigned int schedulerUnitNo, const VisionBoxIOSchedulerCmpSrc::Type compareSource) = 0;
		virtual void SetEncoderDirection(const unsigned int schedulerUnitNo, const VisionBoxIOSchedulerEncoderDir::Type encoderDirection) = 0;


	};

}

#endif //VISION_BOX_INTERFACE_H