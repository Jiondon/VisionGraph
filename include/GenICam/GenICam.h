//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_GENICAM_H
#define AVS_GENICAM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "GenicamCommon/GenBaseState.h"
#include "GenicamCommon/GenActivationMode.h"
#include "GenICamTypes.h"
#include "Image/Image.h"

namespace avs
{


	struct GenICam_GrabImage_State : public GenBaseState {};


	/// <summary>Captures an image stream from a camera using a GenICam GenTL provider library.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="outFrame">Captured frame.</param>
	/// <param name="outFrameID">Frame block ID set by device (when supported).</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool GenICam_GrabImage
	(
		GenICam_GrabImage_State&	ioState,
		const avl::GenAddress&		inAddress,			
		const avl::GenPixelFormat&	inPixelFormat,		
		int							inInputQueueSize,	
		avl::Image&					outFrame,			
		atl::int64&					outFrameID,			
		atl::int64&					outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image stream from a camera using a GenICam GenTL provider library; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outFrame">Captured frame.</param>
	/// <param name="outFrameID">Frame block ID set by device (when supported).</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool GenICam_GrabImage_WithTimeout
	(
		GenICam_GrabImage_State&		ioState,
		const avl::GenAddress&			inAddress,			
		const avl::GenPixelFormat&		inPixelFormat,		
		int								inInputQueueSize,	
		int								inTimeout,			
		atl::Conditional<avl::Image>&	outFrame,			
		atl::Conditional<atl::int64>&	outFrameID,			
		atl::Conditional<atl::int64>&	outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a multi-part image stream from a camera using a GenICam GenTL provider library</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outFramePart1">First part of the captured frame.</param>
	/// <param name="outFramePart2">Second part of the captured frame.</param>
	/// <param name="outFramePart3">Third part of the captured frame.</param>
	/// <param name="outFramePart4">Fourth part of the captured frame.</param>
	/// <param name="outFrameID">Frame block ID set by the device (when supported).</param>
	/// <param name="outTimestamp">Frame capture timestamp set by the device (when supported).</param>
	AVL_FUNCTION bool GenICam_GrabMultiPartImage
	(
		GenICam_GrabImage_State&					ioState,
		const avl::GenAddress&						inAddress,			
		atl::Optional<const avl::GenPixelFormat&>	inPixelFormat,		
		int											inInputQueueSize,	
		int											inTimeout,			
		atl::Conditional<avl::Image>&				outFramePart1,		
		atl::Conditional<avl::Image>&				outFramePart2,		
		atl::Conditional<avl::Image>&				outFramePart3,		
		atl::Conditional<avl::Image>&				outFramePart4,		
		atl::Conditional<atl::int64>&				outFrameID,			
		atl::Conditional<atl::int64>&				outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a camera.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	AVL_FUNCTION void GenICam_StartAcquisition
	(
		GenICam_GrabImage_State&	ioState,
		const avl::GenAddress&		inAddress,			
		const avl::GenPixelFormat&	inPixelFormat,		
		int							inInputQueueSize	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a camera.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	AVL_FUNCTION void GenICam_StopAcquisition
	(
		GenICam_GrabImage_State&	ioState,
		const avl::GenAddress&		inAddress			
	)
	THROW_AVL_ERRORS;

	struct GenICam_GetStreamingStatistics_State : public GenBaseState {};


	/// <summary>Retrieves basic statistics of video streaming out of GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="outReceivedFrames">Number of received valid frames that were put into the input queue.</param>
	/// <param name="outLostFrames">Number of all frames that the device should have sent but were not retrieved by the application.</param>
	/// <param name="outDroppedFrames">Number of received valid frames that were lost because of input queue overflow.</param>
	/// <param name="outDamagedFrames">Number of frames that were partially received but were discarded because of data damage.</param>
	/// <param name="outCurrentQueueSize">Number of frames currently held in the input queue.</param>
	AVL_FUNCTION void GenICam_GetStreamingStatistics
	(
		GenICam_GetStreamingStatistics_State&	ioState,
		const avl::GenAddress&	inAddress,				
		int&					outReceivedFrames,		
		int&					outLostFrames,			
		int&					outDroppedFrames,		
		int&					outDamagedFrames,		
		int&					outCurrentQueueSize		
	)
	THROW_AVL_ERRORS;

	struct GenICam_MultiDevice_State : public GenBaseState {};


	/// <summary>Captures frame streams from multiple synchronously triggered general cameras using GenICam GenTL provider library.</summary>
	/// <param name="inAddress1">GenTL Provider module and device identifying address of first device.</param>
	/// <param name="inAddress2">GenTL Provider module and device identifying address of second device.</param>
	/// <param name="inAddress3">GenTL Provider module and device identifying address of third device. Default value: atl::NIL.</param>
	/// <param name="inAddress4">GenTL Provider module and device identifying address of fourth device. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Requested Pixel Format in GenICam pixel naming convention. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 1.</param>
	/// <param name="inMaxTimeDiff">Maximum time difference between received frames in milliseconds. Default value: 200.</param>
	/// <param name="inTimeout">Maximum time to receive first frame. Default value: atl::NIL.</param>
	/// <param name="outFrame1">Captured frame from first device.</param>
	/// <param name="outFrame2">Captured frame from second device.</param>
	/// <param name="outFrame3">Captured frame from third device.</param>
	/// <param name="outFrame4">Captured frame from fourth device.</param>
	/// <param name="diagCurrentTimeDiff">Time difference between receive of currently captured frames.</param>
	AVL_FUNCTION bool GenICam_MultiDevice_GrabImages
	(
		GenICam_MultiDevice_State&						ioState,
		const avl::GenAddress&							inAddress1,			
		const avl::GenAddress&							inAddress2,			
		const atl::Optional<const avl::GenAddress&>&	inAddress3,			
		const atl::Optional<const avl::GenAddress&>&	inAddress4,			
		const avl::GenPixelFormat&						inPixelFormat,		
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

	struct GenICam_GetRealParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Real from GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void GenICam_GetRealParameter
	(
		GenICam_GetRealParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		float&								outValue			
	)
	THROW_AVL_ERRORS;

	struct GenICam_GetIntegerParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Integer from GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void GenICam_GetIntegerParameter
	(
		GenICam_GetIntegerParameter_State&	ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		int&								outValue			
	)
	THROW_AVL_ERRORS;

	struct GenICam_GetBoolParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Bool from GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void GenICam_GetBoolParameter
	(
		GenICam_GetBoolParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		bool&								outValue			
	)
	THROW_AVL_ERRORS;

	struct GenICam_GetEnumParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Enumeration from GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void GenICam_GetEnumParameter
	(
		GenICam_GetEnumParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		atl::String&						outValue			
	)
	THROW_AVL_ERRORS;

	struct GenICam_GetStringParameter_State : public GenBaseState {};


	/// <summary>Gets parameter of type Enumeration from GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inVerifyAccess">True to verify GenICam parameter access state before every read. Default value: False.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void GenICam_GetStringParameter
	(
		GenICam_GetStringParameter_State&	ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inVerifyAccess,		
		atl::String&						outValue			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetRealParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Real into GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void GenICam_SetRealParameter
	(
		GenICam_SetRealParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		float								inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetIntegerParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Integer into GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void GenICam_SetIntegerParameter
	(
		GenICam_SetIntegerParameter_State&	ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		int									inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetBoolParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Bool into GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void GenICam_SetBoolParameter
	(
		GenICam_SetBoolParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		bool								inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetEnumParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type Enumeration into GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void GenICam_SetEnumParameter
	(
		GenICam_SetEnumParameter_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		const atl::String&					inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetStringParameter_State : public GenBaseState {};


	/// <summary>Sets parameter of type String into GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inParameterName">Name of GenICam parameter node to access.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">True to verify GenICam parameter access state and value correctness before every write. Default value: True.</param>
	AVL_FUNCTION void GenICam_SetStringParameter
	(
		GenICam_SetStringParameter_State&	ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inParameterName,	
		const atl::String&					inValue,			
		bool								inVerify			
	)
	THROW_AVL_ERRORS;

	struct GenICam_SetDigitalOutputs_State : public GenBaseState {};


	/// <summary>Sets user digital outputs state of GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inOutput1">State of user digital output 1.</param>
	/// <param name="inOutput2">State of user digital output 2.</param>
	/// <param name="inOutput3">State of user digital output 3.</param>
	/// <param name="inOutput4">State of user digital output 4.</param>
	AVL_FUNCTION void GenICam_SetDigitalOutputs
	(
		GenICam_SetDigitalOutputs_State&	ioState,
		const avl::GenAddress&				inAddress,			
		bool								inOutput1,			
		bool								inOutput2,			
		bool								inOutput3,			
		bool								inOutput4			
	)
	THROW_AVL_ERRORS;

	struct GenICam_ExecuteCommand_State : public GenBaseState {};


	/// <summary>Conditionally executes command in GenICam device.</summary>
	/// <param name="inAddress">GenTL Provider module and device identifying address.</param>
	/// <param name="inScope">Specifies which parameters set in GenICam stack should be accessed.</param>
	/// <param name="inCommandName">Name of GenICam command node to access.</param>
	/// <param name="inActivationMode">Specifies how filter checks inActivation input. Default value: WhenTrue.</param>
	/// <param name="inActivation">Activates execution of command. Default value: True.</param>
	/// <param name="inVerifyAccess">True to verify GenICam command parameter access state before every command execution. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_GenICam_ExecuteCommand
	(
		GenICam_ExecuteCommand_State&		ioState,
		const avl::GenAddress&				inAddress,			
		avl::GenICamParameterScope::Type	inScope,			
		const avl::GenParameterName&		inCommandName,		
		avl::GenActivationMode::Type		inActivationMode,	
		bool								inActivation,		
		bool								inVerifyAccess		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a GenICam parameter name.</summary>
	AVL_FUNCTION void StringToGenParameterName
	(
		const atl::String&		inString,
		avl::GenParameterName&	outParameterName
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_GENICAM_H

