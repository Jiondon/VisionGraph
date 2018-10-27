//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#pragma once

class NeousysInterface
{
public:
	virtual ~NeousysInterface()
	{}

	virtual bool InitializeDigitalInputOutput() = 0;
	virtual bool InitializeWatchdogTimer() = 0;
	virtual bool IsDigitalInputOutputInitialized() = 0;
	virtual bool IsWatchdogTimerInitialized() = 0;
	virtual void SetDigitalOutputLine(unsigned char channel, bool value) = 0;
	virtual void SetDigitalOutputPort(unsigned short value) = 0;
	virtual void SetDigitalOutputLineChecked(unsigned char channel, bool value) = 0;
	virtual void SetDigitalOutputPortChecked(unsigned short value) = 0;
	virtual bool GetDigitalInputLine(unsigned char channel) = 0;
	virtual unsigned short GetDigitalInputPort() = 0;
	virtual bool SetWatchdogTimer(unsigned short ticks, unsigned char unit) = 0;
	virtual bool StartWatchdogTimer() = 0;
	virtual bool ResetWatchdogTimer() = 0;
	virtual bool StopWatchdogTimer() = 0;
};
