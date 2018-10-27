//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_TCPIP_H
#define AVS_TCPIP_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Serialization/Serialization.h"
#include "System/ByteBuffer.h"
#include "DelimiterModes.h"

namespace avl
{


	typedef int	SocketId;


	AVL_FUNCTION void TcpIp_Init
	()
	THROW_AVL_ERRORS;

	AVL_FUNCTION void TcpIp_Release
	()
	THROW_AVL_ERRORS;

	struct TcpIpConnectState
	{
		TcpIpConnectState()
		{
			TcpIp_Init();
		}

		~TcpIpConnectState()
		{
			TcpIp_Release();
		}
	};

	struct TcpIpAcceptorBase
	{
		virtual ~TcpIpAcceptorBase()
		{
		}
	};

	struct TcpIpAcceptState : public TcpIpConnectState
	{
		TcpIpAcceptorBase* acceptor;

		TcpIpAcceptState()
		: acceptor(0)
		{
		}

		~TcpIpAcceptState()
		{
			delete acceptor;
		}
	};


	/// <summary>Connects as a client to a remote TCP server socket.</summary>
	/// <param name="inHost">The hostname or IP address to connect to. Default value: \"localhost\".</param>
	/// <param name="inPort">TCP port of host to connect to. Default value: 12345.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inKeepAliveTime">When specified activates Tcp/Ip keep alive on new socket with given idle time. Default value: atl::NIL.</param>
	/// <param name="outSocket">Connected socket ID.</param>
	AVL_FUNCTION void TcpIp_Connect
	(
		TcpIpConnectState& ioState,
		const atl::String& inHost,					
		int inPort,									
		const atl::Optional<int>& inTimeout,		
		const atl::Optional<int>& inKeepAliveTime,	
		atl::Conditional<avl::SocketId>& outSocket	
	)
	THROW_AVL_ERRORS;

	/// <summary>Accepts a connection from a remote client.</summary>
	/// <param name="inPort">TCP port to listen on. Default value: 12345.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inKeepAliveTime">When specified activates Tcp/Ip keep alive on new socket with given idle time. Default value: atl::NIL.</param>
	/// <param name="outSocket">Connected socket ID.</param>
	AVL_FUNCTION void TcpIp_Accept
	(
		TcpIpAcceptState& ioState,
		int inPort,									
		const atl::Optional<int>& inTimeout,		
		const atl::Optional<int>& inKeepAliveTime,	
		atl::Conditional<avl::SocketId>& outSocket	
	)
	THROW_AVL_ERRORS;

	/// <summary>Outputs a string through a connected TCP socket.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inText">Text to send through socket.</param>
	/// <param name="inSuffix">Additional data to send, like a newline, escaped. Default value: \"\\\\r\\\\n\".</param>
	AVL_FUNCTION void TcpIp_WriteText
	(
		avl::SocketId inSocket,			
		const atl::String& inText,		
		const atl::String& inSuffix		
	)
	THROW_AVL_ERRORS;

	/// <summary>Outputs a series of bytes through a connected TCP socket.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inBytes">Numerical values of bytes (0-255) to send.</param>
	AVL_FUNCTION void TcpIp_WriteBytes_Deprecated
	(
		avl::SocketId inSocket,			
		const atl::Array<int>& inBytes	
	)
	THROW_AVL_ERRORS;

	/// <summary>Outputs a block of raw data through a connected TCP socket.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inBuffer">Buffer with data to send.</param>
	AVL_FUNCTION void TcpIp_WriteBuffer
	(
		avl::SocketId			inSocket,		
		const avl::ByteBuffer&	inBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads from a connected TCP socket until receiving a specific sequence.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inDelimiter">Terminating character sequence, escaped. Default value: \"\\\\r\\\\n\".</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inAcceptEof">When false, throws an IoError on attempt to read data from beyond the end of stream; when true interrupts operation without exception in such a case. Default value: False.</param>
	/// <param name="inMode">Delimiter handling mode.</param>
	/// <param name="outText">Received data as textual string, or Nil if the operation was interrupted (by timeout or reading beyond the end of stream).</param>
	/// <param name="outEof">Indicates whether the operation was interrupted on attempt to get data from beyond the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadLine
	(
		avl::SocketId					inSocket,		
		const atl::String&				inDelimiter,	
		const atl::Optional<int>&		inTimeout,		
		bool							inAcceptEof,	
		avl::DelimiterHandling::Type	inMode,			
		atl::Conditional<atl::String>&	outText,		
		bool&							outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives a fixed number of bytes from a connected TCP socket.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inLength">Number of bytes to receive.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inAcceptEof">When false, throws an IoError on attempt to read data from beyond the end of stream; when true interrupts operation without exception in such a case. Default value: False.</param>
	/// <param name="outBuffer">Buffer with raw received data, or Nil if the operation was interrupted (by timeout or reading beyond the end of stream).</param>
	/// <param name="outEof">Indicates whether the operation was interrupted on attempt to get data from beyond the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadBuffer
	(
		avl::SocketId						inSocket,		
		int									inLength,		
		const atl::Optional<int>&			inTimeout,		
		bool								inAcceptEof,	
		atl::Conditional<avl::ByteBuffer>&	outBuffer,		
		bool&								outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives text from a connected socket until the other side closes connection.</summary>
	/// <param name="inSocket">Connected socket ID, will be closed if successfully read.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="outText">Received data as textual string, or Nil if the operation was interrupted by timeout.</param>
	/// <param name="outEof">Indicates whether the operation successfully read data to the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadAllText
	(
		avl::SocketId					inSocket,		
		const atl::Optional<int>&		inTimeout,		
		atl::Conditional<atl::String>&	outText,		
		bool&							outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives data from a connected socket until the other side closes connection.</summary>
	/// <param name="inSocket">Connected socket ID, will be closed if successfully read.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="outBuffer">Buffer with raw received data, or Nil if the operation was interrupted by timeout.</param>
	/// <param name="outEof">Indicates whether the operation successfully read data to the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadAllBuffer
	(
		avl::SocketId						inSocket,		
		const atl::Optional<int>&			inTimeout,		
		atl::Conditional<avl::ByteBuffer>&	outBuffer,		
		bool&								outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads from a connected TCP socket until receiving a specific sequence.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inDelimiter">Terminating character sequence, escaped. Default value: \"\\\\r\\\\n\".</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inMode">Delimiter handling mode - include with output, discard or preserve in buffer.</param>
	/// <param name="outText">Received data as textual string.</param>
	/// <param name="outBytes">Received octets as integer values.</param>
	/// <param name="outEof">Indicates whether the operation was interrupted on attempt to get data from beyond the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadLine_Deprecated
	(
		avl::SocketId					inSocket,		
		const atl::String&				inDelimiter,	
		const atl::Optional<int>&		inTimeout,		
		avl::DelimiterHandling::Type	inMode,			
		atl::Conditional<atl::String>&	outText,		
		atl::Array<int>&				outBytes,		
		bool&							outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives a fixed number of bytes from a connected TCP socket.</summary>
	/// <param name="inSocket">Connected socket ID.</param>
	/// <param name="inLength">Number of bytes to receive.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="outText">Received data as textual string.</param>
	/// <param name="outBytes">Received octets as integer values.</param>
	/// <param name="outEof">Indicates whether the operation was interrupted on attempt to get data from beyond the end of stream.</param>
	AVL_FUNCTION void TcpIp_ReadChunk_Deprecated
	(
		avl::SocketId					inSocket,		
		int								inLength,		
		const atl::Optional<int>&		inTimeout,		
		atl::Conditional<atl::String>&	outText,		
		atl::Array<int>&				outBytes,		
		bool&							outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives octets from a connected socket until the other side finishes sending.</summary>
	/// <param name="inSocket">Connected socket ID, will be closed if successfully read.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="outText">Received data as textual string.</param>
	/// <param name="outBytes">Received octets as integer values.</param>
	/// <param name="outEof">Whether everything has been read and socket is closed.</param>
	AVL_FUNCTION void TcpIp_ReadAll_Deprecated
	(
		avl::SocketId					inSocket,		
		const atl::Optional<int>&		inTimeout,		
		atl::Conditional<atl::String>&	outText,		
		atl::Array<int>&				outBytes,		
		bool&							outEof			
	)
	THROW_AVL_ERRORS;

	/// <summary>Close a connected TCP socket gracefully.</summary>
	/// <param name="inSocket">Connected socket Id.</param>
	AVL_FUNCTION void TcpIp_Close
	(
		avl::SocketId	inSocket		
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void TcpIp_SendSerializedObject
	(int inSocket, const atl::String& typeName, const atl::Array<atl::byte>& buffer)
	THROW_AVL_ERRORS;

	AVL_FUNCTION bool TcpIp_ReceiveSerializedObject
	(int inSocket, const atl::String& typeName, const atl::Optional<int>& inTimeout, bool inAcceptEof, atl::Array<atl::byte>& outBuffer, bool& outEof)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// 
	template <typename Type>
	void AvsFilter_TcpIp_WriteObject
	(
		avl::SocketId				inSocket,	
		const Type&					inObject,
		const atl::String&			inTypeName
	)
	{
		atl::Array<atl::byte> buffer;
		avs::SaveDataToMemory(buffer, inObject);

		avl::TcpIp_SendSerializedObject(inSocket, inTypeName, buffer);
	}

	/// 
	template <typename Type>
	void AvsFilter_TcpIp_ReadObject
	(
		avl::SocketId									inSocket,
		const atl::String&								inTypeName,
		const atl::Optional<int>&						inTimeout,
		bool											inAcceptEof,
		typename atl::ToConditionalType<Type>::Type&	outObject,
		bool&											outEof
	)
	{
		atl::Array<atl::byte> buffer;

		if (!avl::TcpIp_ReceiveSerializedObject(inSocket, inTypeName, inTimeout, inAcceptEof, buffer, outEof))
		{
			outObject = atl::NIL;
			return;
		}

		outObject.AssignNonNil();
		avs::ReadDataFromMemory<Type>(buffer, outObject.Get());
	}

} // namespace avs

#endif // AVS_TCPIP_H

