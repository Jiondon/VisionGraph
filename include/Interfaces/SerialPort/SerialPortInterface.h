//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SERIAL_PORT_INTERFACE_H
#define SERIAL_PORT_INTERFACE_H

#include "SerialPortEnums.h"
#include "ATL/AtlString.h"


namespace avl
{
	class SerialPortInterface
	{
	public:
		virtual ~SerialPortInterface() {};

		virtual void Init(const atl::String& inPort, int inBaudRate, SerialPortParity::Type inParity,
						  int inDataBits, SerialPortFlowControl::Type inFlowControl, SerialPortStopBits::Type inStopBits) = 0;

		virtual void Write( const char* data, int size ) = 0;
		virtual void WriteString( const atl::String& s ) = 0;

		virtual int  Read( char* buffer, int size ) = 0;
		virtual bool ReadString( atl::String& outString ) = 0;
		virtual bool ReadStringUntil( const atl::String& endString, atl::String& outString ) = 0;
	};
}


#endif // SERIAL_PORT_INTERFACE_H
