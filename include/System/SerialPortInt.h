//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "ATL/AtlString.h"
#include "Interfaces/SerialPort/SerialPortInterface.h"

namespace avl
{
	class SerialPort
	{
	private:
		SerialPortInterface* m_Interface;
		int m_RefCount;

	public:
		SerialPort();
		~SerialPort();

		void AddRef( void );
		bool Release( void );
		
		SerialPortInterface* GetInterface( void );
		void Initialize(const atl::String& inPort, int inBaudRate, SerialPortParity::Type inParity,
						int inDataBits, SerialPortFlowControl::Type inFlowControl, SerialPortStopBits::Type inStopBits);
	};

	SerialPort *GetSerialPort( int id );
	void FreeSerialPort( SerialPort *serialPort );
}

#endif
