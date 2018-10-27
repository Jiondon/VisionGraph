//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MODBUSTCP_H
#define AVL_MODBUSTCP_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "System/TcpIp.h"
#include "System/ByteBuffer.h"

namespace avl
{



	namespace ModbusDataFormat
	{
		enum Type
		{
			UnsignedInteger,
			SignedInteger,
			Byte,
			Dint
		};
	}



	/// <summary>Connects as a client to a remote Modbus server socket.</summary>
	/// <param name="inHost">The hostname or IP address to connect to. Default value: \"localhost\".</param>
	/// <param name="inPort">Modbus port of host to connect to. 502 is the default one. Default value: 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inKeepAliveTime">When specified activates Tcp/Ip keep alive on new socket with given idle time. Default value: atl::NIL.</param>
	/// <param name="outSocket">Connected socket ID.</param>
	AVL_FUNCTION void ModbusTCP_Connect
	(
		TcpIpConnectState& ioState,
		const atl::String& inHost,					
		int inPort,									
		const atl::Optional<int>& inTimeout,		
		const atl::Optional<int>& inKeepAliveTime,	
		atl::Conditional<avl::SocketId>& outSocket	
	)
	THROW_AVL_ERRORS;

	/// <summary>Close a connected Modbus socket gracefully.</summary>
	/// <param name="inSocket">Connected socket Id.</param>
	AVL_FUNCTION void ModbusTCP_Close
	(
		avl::SocketId	inSocket		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sends data using Modbus TCP frame format</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inFunctionCode">Function code. Default value: 1.</param>
	/// <param name="inBuffer">Data to send.</param>
	/// <param name="outResponse">Response data.</param>
	AVL_FUNCTION void ModbusTCP_SendBuffer
	(
		const avl::SocketId&			inSocket,		
		const atl::Optional<int>&		inTimeout,		
		int								inUnitID,		
		int								inFunctionCode,	
		const avl::ByteBuffer&			inBuffer,		
		avl::ByteBuffer&				outResponse		
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 01. Read contiguous status of coils in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Unit identifier. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first coil.</param>
	/// <param name="inBitCount">Requested number of bits. Default value: 1.</param>
	/// <param name="outBits">Response.</param>
	AVL_FUNCTION void ModbusTCP_ReadCoils
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inBitCount,			
		atl::Array<bool>&				outBits				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 02. Read contiguous status of discrete inputs in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first input.</param>
	/// <param name="inBitCount">Requested number of bits. Default value: 1.</param>
	/// <param name="outBits">Response.</param>
	AVL_FUNCTION void ModbusTCP_ReadDiscreteInputs
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inBitCount,			
		atl::Array<bool>&				outBits				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 03. Read the contents of a contiguous block of holding registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first holding register.</param>
	/// <param name="inCount">Number of registers to read. Each register is 2 Bytes in size. Default value: 1.</param>
	/// <param name="outData">Received register values.</param>
	AVL_FUNCTION void ModbusTCP_ReadMultipleRegisters_AsByteBuffer
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,			
		avl::ByteBuffer&				outData				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 03. Read the contents of a contiguous block of holding registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first holding register.</param>
	/// <param name="inCount">Default value: 1.</param>
	/// <param name="outIntegerValue">Received integer value.</param>
	AVL_FUNCTION void ModbusTCP_ReadMultipleIntegerRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,
		avl::ModbusDataFormat::Type		inInputDataFormat,
		atl::Array<int>&				outIntegerValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 03. Read the contents of a contiguous block of holding registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first holding register.</param>
	/// <param name="inCount">Default value: 1.</param>
	/// <param name="outRealValue">Received real value.</param>
	AVL_FUNCTION void ModbusTCP_ReadMultipleRealRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,
		atl::Array<float>&			outRealValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 03. Read contiguous input registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first input register.</param>
	/// <param name="inCount">Number of registers to read. Each register is 2 Bytes in size. Default value: 1.</param>
	/// <param name="outData">Received register values.</param>
	AVL_FUNCTION void ModbusTCP_ReadInputRegisters_AsByteBuffer
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,			
		avl::ByteBuffer&				outData				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 04. Read contiguous input registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first input register.</param>
	/// <param name="inCount">Default value: 1.</param>
	/// <param name="outIntegerValues">Received integer values.</param>
	AVL_FUNCTION void ModbusTCP_ReadInputIntegerRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,
		avl::ModbusDataFormat::Type		inInputDataFormat,
		atl::Array<int>&				outIntegerValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 04. Read contiguous input registers in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first input register.</param>
	/// <param name="inCount">Default value: 1.</param>
	/// <param name="outRealValues">Received real values.</param>
	AVL_FUNCTION void ModbusTCP_ReadInputRealRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		int								inCount,
		atl::Array<float>&			outRealValues		
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 05. Write a single output to either ON or OFF in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inOutputAddress">The address of the coil to be forced.</param>
	AVL_FUNCTION void ModbusTCP_WriteCoil
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inOutputAddress,	
		bool							inStatus
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 06. Write a single holding register in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inRegisterAddress">The address of the holding register to be written.</param>
	/// <param name="inValue">Value to send.</param>
	AVL_FUNCTION void ModbusTCP_WriteSingleRegister
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inRegisterAddress,	
		int								inValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 07. Attempts to read Exception Status</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	AVL_FUNCTION void ModbusTCP_ReadExceptionStatus
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int&							outStatus
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 15. Force each coil in a sequence of coils to either ON or OFF in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first coil.</param>
	AVL_FUNCTION void ModbusTCP_ForceMultipleCoils
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		const atl::Array<bool>&			inStatuses
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 16. Write a block of contiguous registers (1 to 123 registers) in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first register.</param>
	/// <param name="inIntegerValues">Integer values to set.</param>
	AVL_FUNCTION void ModbusTCP_WriteMultipleIntegerRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		const atl::Array<int>&			inIntegerValues,	
		avl::ModbusDataFormat::Type		inDataFormat
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 16. Write a block of contiguous registers (1 to 123 registers) in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first register.</param>
	/// <param name="inRealValues">Real values to set.</param>
	AVL_FUNCTION void ModbusTCP_WriteMultipleRealRegisters
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		const atl::Array<float>&	inRealValues		
	)
	THROW_AVL_ERRORS;

	/// <summary>Function Code 16. Write a block of contiguous registers (1 to 123 registers) in a remote device</summary>
	/// <param name="inSocket">Connected socket ID on port 502.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inUnitID">Default is 1. Default value: 1.</param>
	/// <param name="inStartingAddress">The address of the first register.</param>
	/// <param name="inBuffer">Buffer with values to set.</param>
	AVL_FUNCTION void ModbusTCP_WriteMultipleRegisters_AsByteBuffer
	(
		const avl::SocketId&			inSocket,			
		const atl::Optional<int>&		inTimeout,			
		int								inUnitID,			
		int								inStartingAddress,	
		const avl::ByteBuffer&			inBuffer			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MODBUSTCP_H

