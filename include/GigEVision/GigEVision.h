//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_GIGEVISION_H
#define AVS_GIGEVISION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "GenicamCommon/GenBaseState.h"
#include "GenicamCommon/GenActivationMode.h"
#include "GigEVisionTypes.h"
#include "Image/Image.h"

namespace avs
{


	struct GigEVision_GrabImage_State : public GenBaseState {};


	/// <summary>Captures an image stream from a GigE Vision compliant camera.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="outFrame">Captured frame.</param>
	/// <param name="outFrameID">Frame block ID set by device.</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool AvsFilter_GigEVision_GrabImage
	(
		GigEVision_GrabImage_State& ioState,
		const avl::GevAddress&		inAddress,			
		const avl::GevPixelFormat&	inPixelFormat,		
		int							inInputQueueSize,	
		avl::Image&					outFrame,			
		atl::int64&					outFrameID,			
		atl::int64&					outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image stream from a GigE Vision compliant camera; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outFrame">Captured frame.</param>
	/// <param name="outFrameID">Frame block ID set by device.</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool AvsFilter_GigEVision_GrabImage_WithTimeout
	(
		GigEVision_GrabImage_State&		ioState,
		const avl::GevAddress&			inAddress,			
		const avl::GevPixelFormat&		inPixelFormat,		
		int								inInputQueueSize,	
		int								inTimeout,			
		atl::Conditional<avl::Image>&	outFrame,			
		atl::Conditional<atl::int64>&	outFrameID,			
		atl::Conditional<atl::int64>&	outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_StartAcquisition
	(
		GigEVision_GrabImage_State& ioState,
		const avl::GevAddress&		inAddress,			
		const avl::GevPixelFormat&	inPixelFormat,		
		int							inInputQueueSize	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	AVL_FUNCTION void AvsFilter_GigEVision_StopAcquisition
	(
		GigEVision_GrabImage_State& ioState,
		const avl::GevAddress&		inAddress			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetStreamingStatistics_State : public GenBaseState {};


	/// <summary>Retrieves basic statistics of video streaming out of GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inReset">True to reset internal device statistics after read. Default value: False.</param>
	/// <param name="outReceivedFrames">Number of received valid frames that were put into the input queue.</param>
	/// <param name="outLostFrames">Number of all frames that the device should have sent but were not retrieved by the application.</param>
	/// <param name="outDroppedFrames">Number of received valid frames that were lost because of input queue overflow.</param>
	/// <param name="outDamagedFrames">Number of frames that were partially received but were discarded because of data damage.</param>
	/// <param name="outCurrentQueueSize">Number of frames currently held in the input queue.</param>
	/// <param name="outResendRequests">Number of times the device was requested to resend some parts of lost frames.</param>
	/// <param name="outLostPackets">Number of network packets that were expected but not retrieved.</param>
	/// <param name="outReconnections">Number of times the connection with the device was lost and automatically reestablished.</param>
	/// <param name="outLastPacketError">Last network packet related error logged by the stream receiver.</param>
	/// <param name="outLastFrameError">Last frame reconstruction related error logged by the stream receiver.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetStreamingStatistics
	(
		GigEVision_GetStreamingStatistics_State&	ioState,
		const avl::GevAddress&	inAddress,				
		bool					inReset,				
		int&					outReceivedFrames,		
		int&					outLostFrames,			
		int&					outDroppedFrames,		
		int&					outDamagedFrames,		
		int&					outCurrentQueueSize,	
		int&					outResendRequests,		
		int&					outLostPackets,			
		int&					outReconnections,		
		atl::String&			outLastPacketError,		
		atl::String&			outLastFrameError		
	)
	THROW_AVL_ERRORS;

	struct GigEVision_MultiDevice_State : public GenBaseState {};


	/// <summary>Captures frame streams from multiple synchronously triggered GigE Vision compliant cameras.</summary>
	/// <param name="inAddress1">GigE Vision identifying address of first device.</param>
	/// <param name="inAddress2">GigE Vision identifying address of second device.</param>
	/// <param name="inAddress3">GigE Vision identifying address of third device. Default value: atl::NIL.</param>
	/// <param name="inAddress4">GigE Vision identifying address of fourth device. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="inMaxTimeDiff">Maximum time difference between received frames in milliseconds. Default value: 200.</param>
	/// <param name="inTimeout">Maximum time to receive first frame. Default value: atl::NIL.</param>
	/// <param name="outFrame1">Captured frame from first device.</param>
	/// <param name="outFrame2">Captured frame from second device.</param>
	/// <param name="outFrame3">Captured frame from third device.</param>
	/// <param name="outFrame4">Captured frame from fourth device.</param>
	/// <param name="diagCurrentTimeDiff">Time difference between receive of currently captured frames.</param>
	AVL_FUNCTION bool AvsFilter_GigEVision_MultiDevice_GrabImages
	(
		GigEVision_MultiDevice_State&					ioState,
		const avl::GevAddress&							inAddress1,			
		const avl::GevAddress&							inAddress2,			
		const atl::Optional<const avl::GevAddress&>&	inAddress3,			
		const atl::Optional<const avl::GevAddress&>&	inAddress4,			
		const avl::GevPixelFormat&						inPixelFormat,		
		int												inInputQueueSize,	
		int												inMaxTimeDiff,		
		atl::Optional<int>								inTimeout,			
		atl::Conditional<avl::Image>&					outFrame1,			
		atl::Conditional<avl::Image>&					outFrame2,			
		atl::Conditional<avl::Image>&					outFrame3,			
		atl::Conditional<avl::Image>&					outFrame4,			
		int&											diagCurrentTimeDiff = atl::Dummy<int>()	
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetRealParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Real from GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetRealParameter
	(
		GigEVision_GetRealParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		float&								outValue			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetIntegerParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Integer from GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetIntegerParameter
	(
		GigEVision_GetIntegerParameter_State&	ioState,
		const avl::GevAddress&					inAddress,			
		const avl::GevParameterName&			inParameterName,	
		bool									inVerifyAccess,		
		int&									outValue			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetBoolParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Bool from GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetBoolParameter
	(
		GigEVision_GetBoolParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		bool&								outValue			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetEnumParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Enumeration from GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetEnumParameter
	(
		GigEVision_GetEnumParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		atl::String&						outValue			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_GetStringParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type String from GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_GetStringParameter
	(
		GigEVision_GetStringParameter_State&	ioState,
		const avl::GevAddress&					inAddress,			
		const avl::GevParameterName&			inParameterName,	
		bool									inVerifyAccess,		
		atl::String&							outValue			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetRealParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Real into GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetRealParameter
	(
		GigEVision_SetRealParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		float								inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetIntegerParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Integer into GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetIntegerParameter
	(
		GigEVision_SetIntegerParameter_State&	ioState,
		const avl::GevAddress&					inAddress,			
		const avl::GevParameterName&			inParameterName,	
		int										inValue,			
		bool									inVerify			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetBoolParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Bool into GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetBoolParameter
	(
		GigEVision_SetBoolParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		bool								inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetEnumParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Enumeration into GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetEnumParameter
	(
		GigEVision_SetEnumParameter_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inParameterName,	
		const atl::String&					inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetStringParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type String into GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetStringParameter
	(
		GigEVision_SetStringParameter_State&	ioState,
		const avl::GevAddress&					inAddress,			
		const avl::GevParameterName&			inParameterName,	
		const atl::String&						inValue,			
		bool									inVerify			
	)
	THROW_AVL_ERRORS;

	struct GigEVision_SetDigitalOutputs_State : public GenBaseState {};


	/// <summary>Sets user digital outputs state of GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inOutput1">State of user digital output 1.</param>
	/// <param name="inOutput2">State of user digital output 2.</param>
	/// <param name="inOutput3">State of user digital output 3.</param>
	/// <param name="inOutput4">State of user digital output 4.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_SetDigitalOutputs
	(
		GigEVision_SetDigitalOutputs_State& ioState,
		const avl::GevAddress&				inAddress,		
		bool								inOutput1,		
		bool								inOutput2,		
		bool								inOutput3,		
		bool								inOutput4		
	)
	THROW_AVL_ERRORS;

	struct GigEVision_CheckEvent_State : public GenBaseState {};


	/// <summary>Checks if device sent event notification since previous iteration.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inEventID">Numeric id of event to check.</param>
	/// <param name="outEventFired">Gets flag indicating if event was fired since last read.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_CheckEvent
	(
		GigEVision_CheckEvent_State&	ioState,
		const avl::GevAddress&			inAddress,		
		int								inEventID,		
		bool&							outEventFired	
	)
	THROW_AVL_ERRORS;

	struct GigEVision_ExecuteCommand_State : public GenBaseState {};


	/// <summary>Conditionally executes command in GigEVision device.</summary>
	/// <param name="inAddress">GigE Vision Device identifying address (IP, MAC or Serial Number).</param>
	/// <param name="inCommandName">Name of GenICam command node to access.</param>
	/// <param name="inActivationMode">Specifies how filter checks inActivation input. Default value: WhenTrue.</param>
	/// <param name="inActivation">Activates execution of command. Default value: True.</param>
	/// <param name="inVerifyAccess">True to verify GenICam command parameter access state before every command execution. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GigEVision_ExecuteCommand
	(
		GigEVision_ExecuteCommand_State&	ioState,
		const avl::GevAddress&				inAddress,			
		const avl::GevParameterName&		inCommandName,		
		avl::GenActivationMode::Type		inActivationMode,	
		bool								inActivation,		
		bool								inVerifyAccess		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a GigEVision device address.</summary>
	AVL_FUNCTION void StringToGevAddress
	(
		const atl::String&	inString,
		avl::GevAddress&	outGevAddress
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a GigEVision image pixel format.</summary>
	AVL_FUNCTION void StringToGevPixelFormat
	(
		const atl::String&		inString,
		avl::GevPixelFormat&	outPixelFormat
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a GigEVision parameter name.</summary>
	AVL_FUNCTION void StringToGevParameterName
	(
		const atl::String&		inString,
		avl::GevParameterName&	outParameterName
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_GIGEVISION_H

