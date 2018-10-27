//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SERIALPORT_H
#define AVL_SERIALPORT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "System/ByteBuffer.h"
#include "SerialPortInt.h"

namespace avl
{


	AVL_FUNCTION void SerialPort_ReleasePort
	(
		SerialPort*	serialPort
	)
	THROW_AVL_ERRORS;

	struct SerialPortState : public BaseState
	{
		SerialPort* serialPort;

		SerialPortState()
		{
			serialPort = 0;
		}

		~SerialPortState()
		{
			if (serialPort)
				SerialPort_ReleasePort(serialPort);
		}

	private:
		SerialPortState(const SerialPortState&); //=delete
		SerialPortState& operator=(const SerialPortState&); //=delete
	};


	/// <summary>Configures the serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="inPort">Serial port name. Default value: \"COM1\".</param>
	/// <param name="inBaudRate">Serial baud rate. Default value: 9600.</param>
	/// <param name="inParity">Serial parity.</param>
	/// <param name="inDataBits">Serial character size. Default value: 8.</param>
	/// <param name="inFlowControl">Serial flow control.</param>
	/// <param name="inStopBits">Serial stop bits.</param>
	AVL_FUNCTION void SerialPort_Config
	(
		SerialPortState&					ioState,
		int									inPortId,			
		const atl::String&					inPort,				
		const int&							inBaudRate,			
		avl::SerialPortParity::Type			inParity,			
		const int&							inDataBits,			
		avl::SerialPortFlowControl::Type	inFlowControl,		
		avl::SerialPortStopBits::Type		inStopBits			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes one character in binary mode to serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="inData">Character value.</param>
	AVL_FUNCTION void SerialPort_WriteByte
	(
		SerialPortState&	ioState,
		int					inPortId,		
		int					inData			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes array of characters in binary mode to serial port.</summary>
	/// <param name="inData">Array of character values, each in the range from 0 to 255.</param>
	AVL_FUNCTION void SerialPort_Write_Deprecated
	(
		SerialPortState&		ioState,
		const atl::Array<int>&	inData		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes raw binary data from a byte buffer to serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="inBuffer">Buffer containing raw data to write.</param>
	AVL_FUNCTION void SerialPort_WriteBuffer
	(
		SerialPortState&		ioState,
		int						inPortId,		
		const avl::ByteBuffer&	inBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Write single ASCII character to device.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="inCharacter">Single character to send.</param>
	AVL_FUNCTION void SerialPort_WriteChar
	(
		SerialPortState&		ioState,
		int						inPortId,		
		const atl::String&		inCharacter		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes string characters to serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	AVL_FUNCTION void SerialPort_WriteString
	(
		SerialPortState&		ioState,
		int						inPortId,			
		const atl::String&		inString,
		bool					inASCIIMode,
		const atl::Array<int>&	inTerminator
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads one character in binary mode from serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="outData">Conditionally returns received character value, when one is available.</param>
	AVL_FUNCTION void SerialPort_ReadByte
	(
		SerialPortState&			ioState,
		int							inPortId,		
		atl::Conditional<int>&		outData			
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads characters in binary mode from serial port.</summary>
	/// <param name="outData">Conditionally returns non empty array of character values, when any data available.</param>
	AVL_FUNCTION void SerialPort_Read_Deprecated
	(
		SerialPortState&					ioState,
		atl::Conditional<atl::Array<int> >&	outData		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads raw binary data from serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="outBuffer">Conditionally returns non empty byte buffer with raw data, when any data available.</param>
	AVL_FUNCTION void SerialPort_ReadBuffer
	(
		SerialPortState&					ioState,
		int									inPortId,		
		atl::Conditional<avl::ByteBuffer>&	outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads single character from serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="outCharacter">Conditionally returns string with one received character.</param>
	AVL_FUNCTION void SerialPort_ReadChar
	(
		SerialPortState&				ioState,
		int								inPortId,		
		atl::Conditional<atl::String>&	outCharacter	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads string characters from serial port.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="outString">Conditionally returns string with concatenated all characters available in input buffer.</param>
	AVL_FUNCTION void SerialPort_ReadString
	(
		SerialPortState&				ioState,
		int								inPortId,		
		atl::Conditional<atl::String>&	outString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads the string from the serial port to encounter a string delimiter.</summary>
	/// <param name="inPortId">Identifies open port instance when working with multiple serial ports. Default value: 0.</param>
	/// <param name="inEndString">Delimiter string that will be searched in incoming stream.</param>
	/// <param name="outString">Conditionally returns received string without delimiter.</param>
	AVL_FUNCTION void SerialPort_ReadStringUntil
	(
		SerialPortState&				ioState,
		int								inPortId,		
		const atl::String&				inEndString,	
		atl::Conditional<atl::String>&	outString		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SERIALPORT_H

