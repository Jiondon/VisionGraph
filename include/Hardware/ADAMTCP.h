//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ADAMTCP_H
#define AVL_ADAMTCP_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Hardware/AdamTCP/AdvantechAdamTCPInterface.h"
#include "ATL/Array.hxx"

namespace avl
{


	struct AdamTCP_State : public BaseState
	{
		AdamTCPInterface* adam;

		AdamTCP_State()
			: adam(nullptr)
		{}

		~AdamTCP_State()
		{
			delete adam;
		}

		AdamTCPInterface* operator->()
		{
			return adam;
		}

	private:
		AdamTCP_State(const AdamTCP_State&); //=delete
		AdamTCP_State& operator=(const AdamTCP_State&); //=delete
	};



	/// <summary>Connects as a client to a remote Advantech Adam device.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address to connect to.</param>
	/// <param name="inTimeout">Timeout in milliseconds, block if not specified. Default value: atl::NIL.</param>
	/// <param name="inKeepAliveTime">When specified activates Tcp/Ip keep alive on new socket with given idle time. Default value: atl::NIL.</param>
	AVL_FUNCTION void AdamTCP_Connect
	(
		AdamTCP_State& ioState,
		const atl::String& inDeviceIP,				
		const atl::Optional<int>& inTimeout,		
		const atl::Optional<int>& inKeepAliveTime	
	)
	THROW_AVL_ERRORS;

	/// <summary>Function code 01. Read discrete output's ON/OFF status.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address. Default value: atl::NIL.</param>
	/// <param name="inStationAddress">Default value: 1.</param>
	/// <param name="inStartAddress">The address of the first coil.</param>
	/// <param name="inNumberOfCoils">Requested number of bits.</param>
	/// <param name="outValues">Received values as integers.</param>
	/// <param name="outStatuses">Received statuses as bits.</param>
	AVL_FUNCTION void AdamTCP_Function01
	(
		AdamTCP_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceIP,			
		int									inStationAddress,
		int									inStartAddress,		
		int									inNumberOfCoils,	
		atl::Array<int>&					outValues,			
		atl::Array<bool>&					outStatuses			
	)
	THROW_AVL_ERRORS;

	/// <summary>Function code 02. Read discrete input's ON/OFF status.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address. Default value: atl::NIL.</param>
	/// <param name="inStationAddress">Default value: 1.</param>
	/// <param name="inStartAddress">The address of the first input.</param>
	/// <param name="inNumberOfCoils">Requested number of bits.</param>
	/// <param name="outValues">Received values as integers.</param>
	/// <param name="outStatuses">Received statuses as bits.</param>
	AVL_FUNCTION void AdamTCP_Function02
	(
		AdamTCP_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceIP,			
		int									inStationAddress,
		int									inStartAddress,		
		int									inNumberOfCoils,	
		atl::Array<int>&					outValues,			
		atl::Array<bool>&					outStatuses			
	)
	THROW_AVL_ERRORS;

	/// <summary>Function code 03. Read the binary contents of input registers.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address. Default value: atl::NIL.</param>
	/// <param name="inStationAddress">Default value: 1.</param>
	/// <param name="inStartAddress">The address of the first holding register.</param>
	/// <param name="inNumberOfRegister">Number of registers to read.</param>
	/// <param name="outValues">Received values as integers.</param>
	AVL_FUNCTION void AdamTCP_Function03
	(
		AdamTCP_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceIP,				
		int									inStationAddress,
		int									inStartAddress,			
		int									inNumberOfRegister,		
		atl::Array<int>&					outValues				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function code 04. Read the binary contents of input registers.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address. Default value: atl::NIL.</param>
	/// <param name="inStationAddress">Default value: 1.</param>
	/// <param name="inStartAddress">The address of the first input register.</param>
	/// <param name="inNumberOfRegister">Number of registers to read.</param>
	/// <param name="outValues">Received values as integers.</param>
	AVL_FUNCTION void AdamTCP_Function04
	(
		AdamTCP_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceIP,				
		int									inStationAddress,
		int									inStartAddress,			
		int									inNumberOfRegister,		
		atl::Array<int>&					outValues				
	)
	THROW_AVL_ERRORS;

	/// <summary>Function code 05. Force a single coil to either ON or OFF.</summary>
	/// <param name="inDeviceIP">The Advantech Adam device IP address. Default value: atl::NIL.</param>
	/// <param name="inStationAddress">Default value: 1.</param>
	/// <param name="inCoilAddress">The address of the coil to be forced. Default value: 16.</param>
	/// <param name="inState">Coil state to be set.</param>
	AVL_FUNCTION void AdamTCP_Function05
	(
		AdamTCP_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceIP,			
		int									inStationAddress,
		int									inCoilAddress,		
		bool								inState				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_ADAMTCP_H

