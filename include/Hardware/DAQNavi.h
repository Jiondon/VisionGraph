//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DAQNAVI_H
#define AVL_DAQNAVI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Hardware/DAQNavi/DAQNaviInterface.h"

namespace avl
{



	namespace DAQNaviTrigger
	{
		enum Type
		{
			ActiveNone = 0,
			RisingEdge,
			FallingEdge,
			BothEdges,
			HighLevel,
			LowLevel,
		};
	}

	struct DAQNavi_State
	{
		DAQNaviInterface* daqNavi;

		DAQNavi_State()
			: daqNavi(nullptr)
		{}

		~DAQNavi_State()
		{
			delete daqNavi;
		}

		DAQNaviInterface* operator->()
		{
			return daqNavi;
		}

	private:
		DAQNavi_State(const DAQNavi_State&); //=delete
		DAQNavi_State& operator=(const DAQNavi_State&); //=delete
	};



	/// <summary>Sets the port direction (input or output).</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port number.</param>
	/// <param name="inPortIsOutput">True if port should be an output, false if port should be an input.</param>
	AVL_FUNCTION void DAQNavi_SetPortDirection
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inPort,					
		bool								inPortIsOutput			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns value from digital input.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port number.</param>
	/// <param name="outValue">Output value.</param>
	AVL_FUNCTION void DAQNavi_GetDigitalInput
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		int									inPort,			
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns values from all digital inputs.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="outValues">Output values.</param>
	AVL_FUNCTION void DAQNavi_GetDigitalInputs
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		atl::Array<int>&					outValues				
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes interrupts.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inChannels">Interrupted channel numbers.</param>
	/// <param name="inTriggerMode">Trigger mode.</param>
	AVL_FUNCTION void DAQNavi_InitInterrupts
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		const atl::Array<int>&				inChannels,				
		avl::DAQNaviTrigger::Type			inTriggerMode			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns interrupt values.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inSrcChannel">Channel number which snap event occurs.</param>
	/// <param name="inPort">Port number to scan when interrupt occurred.</param>
	/// <param name="outPortValues">Port values scanned when interrupt occurred.</param>
	AVL_FUNCTION void DAQNavi_GetDigitalInterrupt
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inSrcChannel,			
		int									inPort,					
		atl::Array<int>&					outPortValues			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets digital output value.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port used for outputting data.</param>
	/// <param name="inValue">Value to output.</param>
	AVL_FUNCTION void DAQNavi_SetDigitalOutput
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inPort,					
		int									inValue					
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets digital output bit to specified value.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port used for outputting data.</param>
	/// <param name="inBitId">Bit id within the selected port.</param>
	/// <param name="inValue">Value to output.</param>
	AVL_FUNCTION void DAQNavi_SetDigitalOutputBit
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inPort,					
		int									inBitId,				
		bool								inValue					
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets digital output value.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port used for outputting data.</param>
	/// <param name="outValue">Value to output.</param>
	AVL_FUNCTION void DAQNavi_GetDigitalOutput
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inPort,					
		int&								outValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets digital output bit value.</summary>
	/// <param name="inDeviceID">Description or index of device. Default value: atl::NIL.</param>
	/// <param name="inPort">Port used for outputting data.</param>
	/// <param name="inBitId">Bit id within the selected port.</param>
	/// <param name="outValue">Value to output.</param>
	AVL_FUNCTION void DAQNavi_GetDigitalOutputBit
	(
		DAQNavi_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inPort,					
		int									inBitId,				
		bool&								outValue				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_DAQNAVI_H

