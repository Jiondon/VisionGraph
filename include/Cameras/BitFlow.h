//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_BITFLOW_H
#define AVL_BITFLOW_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/BitFlow/BitFlowInterface.h"

namespace avl
{


	namespace BitFlowTriggerMode
	{
		enum Type
		{
			CiTrigFreeRun = 0,
			CiTrigAqCmd,
			CiTrigAqCmdStartStop,
			CiTrigOneShot,
			CiTrigOneShotSelfTriggered,
			CiTrigContinuousData,
			CiTrigOneShotStartAStopB,
			CiTrigOneShotStartAStopA,
			CiTrigOneShotStartAStopALevel,
			CiTrigContinuousDataQualified,
		};
	}

	namespace BitFlowTrigAssignments
	{
		enum Type
		{
			Off = 0,
			CiTrigJandKSameSource,
			CiTrigJbyAandKbyB,
			CiTrigJbyAandKFreerun,
		};
	}

	namespace BitFlowTrigPolarity
	{
		enum Type
		{
			Off = 0,
			CiTrigAssertedHigh,
			CiTrigAssertedLow,
		};
	}

	namespace BitFlowTriggers
	{
		enum Type
		{
			CiTrigA = 0,
			CiTrigB,
		};
	}

	struct BitFlow_BaseState : public BaseState
	{
		BitFlowInterface* bitFlow;

		BitFlow_BaseState()
		{
			bitFlow = nullptr;
		}

		~BitFlow_BaseState()
		{
			delete bitFlow;
		}

	private:
		BitFlow_BaseState(const BitFlow_BaseState&); //=delete
		BitFlow_BaseState& operator=(const BitFlow_BaseState&); //=delete
	};
	
	typedef BitFlow_BaseState BitFlow_GrabImageState;
	typedef BitFlow_BaseState BitFlow_GrabImage_WithTimeoutState;
	typedef BitFlow_BaseState BitFlow_SoftwareTriggerState;
	typedef BitFlow_BaseState BitFlow_GetHardwareTriggerStatusState;
	typedef BitFlow_BaseState BitFlow_SetGPOutPinState;
	typedef BitFlow_BaseState BitFlow_GetGPOutPinState;
	typedef BitFlow_BaseState BitFlow_WriteValueToRegisterState;
	typedef BitFlow_BaseState BitFlow_ReadValueFromRegisterState;
	typedef BitFlow_BaseState BitFlow_GetRegisterNameState;



	/// <summary>Captures a frame using BitFlow frame grabber.</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inTriggerMode">Trigger mode of the current camera.</param>
	/// <param name="inTriggerAssignments">Assign trigger to acquisition engine.</param>
	/// <param name="inTriggerAPolarity">Polarity for trigger B.</param>
	/// <param name="inTriggerBPolarity">Polarity for trigger A.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool BitFlow_GrabImage
	(
		BitFlow_GrabImageState&					ioState,
		int										inBoardNumber,			
		const atl::File&						inCameraFileName,		
		avl::BitFlowTriggerMode::Type			inTriggerMode,			
		avl::BitFlowTrigAssignments::Type		inTriggerAssignments,	
		avl::BitFlowTrigPolarity::Type			inTriggerAPolarity,		
		avl::BitFlowTrigPolarity::Type			inTriggerBPolarity,		
		avl::Image&								outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using BitFlow frame grabber.</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inTriggerMode">Trigger mode of the current camera.</param>
	/// <param name="inTriggerAssignments">Assign trigger to acquisition engine.</param>
	/// <param name="inTriggerAPolarity">Polarity for trigger B.</param>
	/// <param name="inTriggerBPolarity">Polarity for trigger A.</param>
	/// <param name="inTimeout">Capture timeout. Default value: 5000.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool BitFlow_GrabImage_WithTimeout
	(
		BitFlow_GrabImage_WithTimeoutState&		ioState,
		int										inBoardNumber,			
		const atl::File&						inCameraFileName,		
		avl::BitFlowTriggerMode::Type			inTriggerMode,			
		avl::BitFlowTrigAssignments::Type		inTriggerAssignments,	
		avl::BitFlowTrigPolarity::Type			inTriggerAPolarity,		
		avl::BitFlowTrigPolarity::Type			inTriggerBPolarity,		
		int										inTimeout,				
		atl::Conditional<avl::Image>&			outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Perform a software trigger</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inTrigger">Trigger to assert.</param>
	/// <param name="inTriggerEnable">Trigger enabled / disabled.</param>
	AVL_FUNCTION void BitFlow_SoftwareTrigger
	(
		BitFlow_SoftwareTriggerState&	ioState,
		int								inBoardNumber,			
		const atl::File&				inCameraFileName,		
		avl::BitFlowTriggers::Type		inTrigger,				
		bool							inTriggerEnable			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the status of the hardware trigger</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inTrigger">Trigger.</param>
	/// <param name="outTriggerStatus">Status of trigger.</param>
	AVL_FUNCTION void BitFlow_GetHardwareTriggerStatus
	(
		BitFlow_GetHardwareTriggerStatusState&	ioState,
		int								inBoardNumber,			
		const atl::File&				inCameraFileName,		
		avl::BitFlowTriggers::Type		inTrigger,				
		bool&							outTriggerStatus		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets R64 GPOUT pins</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inOutput">output.</param>
	/// <param name="inValue">pin enabled.</param>
	AVL_FUNCTION void BitFlow_SetGPOutPin
	(
		BitFlow_SetGPOutPinState&		ioState,
		int								inBoardNumber,			
		const atl::File&				inCameraFileName,		
		int								inOutput,				
		bool							inValue					
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets R64 GPOUT pins state</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inOutput">output.</param>
	/// <param name="outState">pin state.</param>
	AVL_FUNCTION void BitFlow_GetGPOutPin
	(
		BitFlow_GetGPOutPinState&		ioState,
		int								inBoardNumber,			
		const atl::File&				inCameraFileName,		
		int								inOutput,				
		bool&							outState				
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads value from register</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inRegId">Register Id.</param>
	/// <param name="outValue">Register value.</param>
	AVL_FUNCTION void BitFlow_ReadValueFromRegister
	(
		BitFlow_ReadValueFromRegisterState&		ioState,
		int										inBoardNumber,			
		const atl::File&						inCameraFileName,		
		int										inRegId,				
		int&									outValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes value to register</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inRegId">Register Id.</param>
	/// <param name="inValue">Value to store.</param>
	AVL_FUNCTION void BitFlow_WriteValueToRegister
	(
		BitFlow_WriteValueToRegisterState&		ioState,
		int										inBoardNumber,			
		const atl::File&						inCameraFileName,		
		int										inRegId,				
		int										inValue					
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets register name</summary>
	/// <param name="inBoardNumber">Index of board.</param>
	/// <param name="inCameraFileName">Camera file.</param>
	/// <param name="inRegId">Register Id.</param>
	/// <param name="outName">Register name.</param>
	AVL_FUNCTION void BitFlow_GetRegisterName
	(
		BitFlow_GetRegisterNameState&		ioState,
		int									inBoardNumber,			
		const atl::File&					inCameraFileName,		
		int									inRegId,				
		atl::String&						outName					
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_BITFLOW_H

