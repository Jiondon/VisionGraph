//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_NEOUSYS_H
#define AVL_NEOUSYS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Hardware/Neousys/NeousysInterface.h"

namespace avl
{


	struct Neousys_State : public BaseState
	{
		NeousysInterface* neousys;

		Neousys_State()
			: neousys(nullptr)
		{}

		~Neousys_State()
		{
			delete neousys;
		}

	private:
		Neousys_State(const Neousys_State&); //=delete
		Neousys_State& operator=(const Neousys_State&); //=delete
	};

	namespace NeousysWatchdogTimerUnit
	{
		enum Type
		{
			Minute = 0,
			Second = 1
		};
	}


	/// <summary>Sets value to single digital output channel on a Neousys computer.</summary>
	/// <param name="inChannel">Desired output channel identifier.</param>
	/// <param name="inValue">Value to set to desired output channel.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_Single
	(
		Neousys_State&	ioState,
		int				inChannel,	
		bool			inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets values to all digital output channels at once on a Neousys computer.</summary>
	/// <param name="inValue0">Value to set to output channel 0.</param>
	/// <param name="inValue1">Value to set to output channel 1.</param>
	/// <param name="inValue2">Value to set to output channel 2.</param>
	/// <param name="inValue3">Value to set to output channel 3.</param>
	/// <param name="inValue4">Value to set to output channel 4.</param>
	/// <param name="inValue5">Value to set to output channel 5.</param>
	/// <param name="inValue6">Value to set to output channel 6.</param>
	/// <param name="inValue7">Value to set to output channel 7.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_Multiple
	(
		Neousys_State&	ioState,
		bool			inValue0,			
		bool			inValue1 = false,	
		bool			inValue2 = false,	
		bool			inValue3 = false,	
		bool			inValue4 = false,	
		bool			inValue5 = false,	
		bool			inValue6 = false,	
		bool			inValue7 = false	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets values to all digital output channels at once on a Neousys computer passed in an array form.</summary>
	/// <param name="inValues">Values to set to output channels; max 8.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_MultipleAsArray
	(
		Neousys_State&			ioState,
		const atl::Array<bool>&	inValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets value to single digital output channel on a Neousys computer. Additionally, does a read-back of the value to make sure it's identical to the written value.</summary>
	/// <param name="inChannel">Desired output channel identifier.</param>
	/// <param name="inValue">Value to set to desired output channel.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_Single_Checked
	(
		Neousys_State&	ioState,
		int				inChannel,	
		bool			inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets values to all digital output channels at once on a Neousys computer. Additionally, does a read-back of the values to make sure they're identical to the written values.</summary>
	/// <param name="inValue0">Value to set to output channel 0.</param>
	/// <param name="inValue1">Value to set to output channel 1.</param>
	/// <param name="inValue2">Value to set to output channel 2.</param>
	/// <param name="inValue3">Value to set to output channel 3.</param>
	/// <param name="inValue4">Value to set to output channel 4.</param>
	/// <param name="inValue5">Value to set to output channel 5.</param>
	/// <param name="inValue6">Value to set to output channel 6.</param>
	/// <param name="inValue7">Value to set to output channel 7.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_Multiple_Checked
	(
		Neousys_State&	ioState,
		bool			inValue0,			
		bool			inValue1 = false,	
		bool			inValue2 = false,	
		bool			inValue3 = false,	
		bool			inValue4 = false,	
		bool			inValue5 = false,	
		bool			inValue6 = false,	
		bool			inValue7 = false	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets values to all digital output channels at once on a Neousys computer passed in an array form. Additionally, does a read-back of the values to make sure they're identical to the written values.</summary>
	/// <param name="inValues">Values to set to output channels; max 8.</param>
	AVL_FUNCTION void Neousys_SetDigitalOutput_MultipleAsArray_Checked
	(
		Neousys_State&			ioState,
		const atl::Array<bool>&	inValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets value of single digital input channel on a Neousys computer.</summary>
	/// <param name="inChannel">Desired input channel identifier.</param>
	/// <param name="outValue">Value to get from desired input channel.</param>
	AVL_FUNCTION void Neousys_GetDigitalInput_Single
	(
		Neousys_State&	ioState,
		int				inChannel,	
		bool&			outValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets values of all digital input channels at once on a Neousys computer.</summary>
	/// <param name="outValue0">Value to get from input channel 0.</param>
	/// <param name="outValue1">Value to get from input channel 1.</param>
	/// <param name="outValue2">Value to get from input channel 2.</param>
	/// <param name="outValue3">Value to get from input channel 3.</param>
	/// <param name="outValue4">Value to get from input channel 4.</param>
	/// <param name="outValue5">Value to get from input channel 5.</param>
	/// <param name="outValue6">Value to get from input channel 6.</param>
	/// <param name="outValue7">Value to get from input channel 7.</param>
	AVL_FUNCTION void Neousys_GetDigitalInput_Multiple
	(
		Neousys_State&	ioState,
		bool&			outValue0,	
		bool&			outValue1,	
		bool&			outValue2,	
		bool&			outValue3,	
		bool&			outValue4,	
		bool&			outValue5,	
		bool&			outValue6,	
		bool&			outValue7	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets values of all digital input channels at once on a Neousys computer passed in an array form.</summary>
	/// <param name="outValues">Values to get from input channels; max 8.</param>
	AVL_FUNCTION void Neousys_GetDigitalInput_MultipleAsArray
	(
		Neousys_State&		ioState,
		atl::Array<bool>&	outValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets watchdog timer properties on a Neousys computer.</summary>
	/// <param name="inTicks">Number of ticks to set the watchdog timer to. Default value: 255.</param>
	/// <param name="inUnit">Unit of the ticks. Default value: Second.</param>
	AVL_FUNCTION void Neousys_SetWatchdogTimer
	(
		Neousys_State&						ioState,
		int									inTicks,	
		avl::NeousysWatchdogTimerUnit::Type	inUnit		
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts watchdog timer countdown on a Neousys computer.</summary>
	AVL_FUNCTION void Neousys_StartWatchdogTimer
	(
		Neousys_State&	ioState
	)
	THROW_AVL_ERRORS;

	/// <summary>Resets watchdog timer countdown on a Neousys computer.</summary>
	AVL_FUNCTION void Neousys_ResetWatchdogTimer
	(
		Neousys_State&	ioState
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops watchdog timer countdown on a Neousys computer.</summary>
	AVL_FUNCTION void Neousys_StopWatchdogTimer
	(
		Neousys_State&	ioState
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_NEOUSYS_H

