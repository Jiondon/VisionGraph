//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PYLON_H
#define AVL_PYLON_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Pylon/PylonInterface.h"

namespace avl
{



	struct Pylon_State	 : public BaseState
	{
	public:
		PylonInterface* pylon;

		Pylon_State()
			: pylon(nullptr)
		{}

		~Pylon_State()
		{
			delete pylon;
		}

	private:
		Pylon_State(const Pylon_State&); //=delete
		Pylon_State& operator=(const Pylon_State&); //=delete
	};



	/// <summary>Captures an image stream from a camera using Pylon library.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	/// <param name="inOutputQueueSize">Capacity of output frames queue. Default value: 3.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. To reset AOI set Box(0,0,0,0). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Analog gain of source image in device raw unit. Default value: atl::NIL.</param>
	/// <param name="inBlackLevel">Black level of source image. Default value: atl::NIL.</param>
	/// <param name="inTriggerEnabled">Configure trigger enable. Default value: atl::NIL.</param>
	/// <param name="inTriggerSource">Source of acquisition trigger. Default value: atl::NIL.</param>
	/// <param name="inTriggerActivation">Circumstances defining when the trigger is activated. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool Pylon_GrabImage
	(
		Pylon_State&									ioState,
		atl::Optional<const atl::String&>			inDeviceID,				
		int											inOutputQueueSize,		
		atl::Optional<avl::PylonImageFormat::Type>	inPixelFormat,			
		atl::Optional<float>					inFrameRate,			
		atl::Optional<const avl::Box&>				inAoi,					
		atl::Optional<float>					inExposureTime,			
		atl::Optional<float>					inGain,					
		atl::Optional<float>					inBlackLevel,			
		atl::Optional<bool>									inTriggerEnabled,		
		atl::Optional<avl::PylonTriggerSource::Type>		inTriggerSource,		
		atl::Optional<avl::PylonTriggerActivation::Type>	inTriggerActivation,	
		avl::Image&									outImage,						
		atl::int64&									outFrameID,						
		atl::int64&									outTimestamp					
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image stream from a camera using Pylon library; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	/// <param name="inOutputQueueSize">Capacity of output frames queue. Default value: 3.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. To reset AOI set Box(0,0,0,0). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Analog gain of source image in device raw unit. Default value: atl::NIL.</param>
	/// <param name="inBlackLevel">Black level of source image. Default value: atl::NIL.</param>
	/// <param name="inTriggerEnabled">Configure trigger enable. Default value: atl::NIL.</param>
	/// <param name="inTriggerSource">Source of acquisition trigger. Default value: atl::NIL.</param>
	/// <param name="inTriggerActivation">Circumstances defining when the trigger is activated. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool Pylon_GrabImage_WithTimeout
	(
		Pylon_State&									ioState,
		atl::Optional<const atl::String&>			inDeviceID,						
		int											inOutputQueueSize,				
		int											inTimeout,						
		atl::Optional<avl::PylonImageFormat::Type>	inPixelFormat,					
		atl::Optional<float>					inFrameRate,					
		atl::Optional<const avl::Box&>				inAoi,							
		atl::Optional<float>					inExposureTime,					
		atl::Optional<float>					inGain,							
		atl::Optional<float>					inBlackLevel,					
		atl::Optional<bool>									inTriggerEnabled,		
		atl::Optional<avl::PylonTriggerSource::Type>		inTriggerSource,		
		atl::Optional<avl::PylonTriggerActivation::Type>	inTriggerActivation,	
		atl::Conditional<avl::Image>&				outImage,						
		atl::Conditional<atl::int64>&				outFrameID,						
		atl::Conditional<atl::int64>&				outTimestamp					
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	/// <param name="inOutputQueueSize">Capacity of output frames queue. Default value: 3.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. To reset AOI set Box(0,0,0,0). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Analog gain of source image in device raw unit. Default value: atl::NIL.</param>
	/// <param name="inBlackLevel">Black level of source image. Default value: atl::NIL.</param>
	/// <param name="inTriggerEnabled">Configure trigger enable. Default value: atl::NIL.</param>
	/// <param name="inTriggerSource">Source of acquisition trigger. Default value: atl::NIL.</param>
	/// <param name="inTriggerActivation">Circumstances defining when the trigger is activated. Default value: atl::NIL.</param>
	AVL_FUNCTION void Pylon_StartAcquisition
	(
		Pylon_State&									ioState,
		atl::Optional<const atl::String&>			inDeviceID,						
		int											inOutputQueueSize,				
		atl::Optional<avl::PylonImageFormat::Type>	inPixelFormat,					
		atl::Optional<float>					inFrameRate,					
		atl::Optional<const avl::Box&>				inAoi,							
		atl::Optional<float>					inExposureTime,					
		atl::Optional<float>					inGain,							
		atl::Optional<float>					inBlackLevel,					
		atl::Optional<bool>									inTriggerEnabled,		
		atl::Optional<avl::PylonTriggerSource::Type>		inTriggerSource,		
		atl::Optional<avl::PylonTriggerActivation::Type>	inTriggerActivation		
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	AVL_FUNCTION void Pylon_StopAcquisition
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets Basler camera user output.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	AVL_FUNCTION void Pylon_SetUserOutput
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,					
		avl::PylonUserOutput::Type			inUserOutput,
		bool								inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger.</summary>
	/// <param name="inDeviceID">Serial number, model name, user defined name or full name of camera device to be opened. Default value: atl::NIL.</param>
	/// <param name="inIgnoreWaiting">Waiting for previous trigger doesn't work with all cameras. E.g. for models A600 this value should be set to true.</param>
	/// <param name="outExecuted">Use only if inTimeout is set.</param>
	AVL_FUNCTION void Pylon_GenerateSoftwareTrigger
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,					
		bool								inIgnoreWaiting,			
		atl::Optional<int>					inTimeout,
		bool&								outExecuted					
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Pylon_SetBoolParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool								inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Real.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Pylon_SetRealParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float							inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Pylon_SetIntegerParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int									inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Enumeration.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Pylon_SetEnumParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Pylon_SetStringParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Pylon_GetBoolParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Real.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Pylon_GetRealParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float&							outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Pylon_GetIntegerParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Enumeration.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Pylon_GetEnumParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Pylon_GetStringParameter
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Executes command in Basler device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inCommandName">Name of feature parameter.</param>
	AVL_FUNCTION void Pylon_ExecuteCommand
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inCommandName	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets GigeVision device statistics data.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="outTotalBufferCount">Counts the number of received frames.</param>
	/// <param name="outFailedBufferCount">Counts the number of buffers with at least one failed packet (status != success).</param>
	/// <param name="outBufferUnderrunCount">Counts the number of frames lost because there were no buffers queued to the driver.</param>
	/// <param name="outTotalPacketCount">Counts the number of received packets.</param>
	/// <param name="outFailedPacketCount">Counts the number of failed packets (status != success).</param>
	/// <param name="outResendRequestCount">Counts the number of emitted PACKETRESEND commands.</param>
	/// <param name="outResendPacketCount">Counts the number of packets requested by PACKETRESEND commands.</param>
	/// <param name="outNumEmptyBuffers">The number of empty buffers that are not used for grabbing yet.</param>
	/// <param name="outNumQueuedBuffers">The number of buffers queued at Low Level API stream grabber.</param>
	/// <param name="outNumReadyBuffers">The number of grab result buffers in the output queue that are ready for retrieval.</param>
	/// <param name="outOutputQueueSize">The size of the grab result buffer output queue.</param>
	AVL_FUNCTION void Pylon_GetGigEStatistics
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		atl::int64&							outTotalBufferCount,	
		atl::int64&							outFailedBufferCount,	
		atl::int64&							outBufferUnderrunCount,	
		atl::int64&							outTotalPacketCount,	
		atl::int64&							outFailedPacketCount,	
		atl::int64&							outResendRequestCount,	
		atl::int64&							outResendPacketCount,	
		atl::int64&							outNumEmptyBuffers,		
		atl::int64&							outNumQueuedBuffers,	
		atl::int64&							outNumReadyBuffers,		
		atl::int64&							outOutputQueueSize		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets GigeVision device statistics data.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="outTotalBufferCount">The total count of processed buffers.</param>
	/// <param name="outFailedBufferCount">The count of buffers that returned with an error status.</param>
	/// <param name="outLastFailedBufferStatus">The status code of the last failed buffer.</param>
	/// <param name="outLastFailedBufferStatusText">The message text of the status code of the last failed buffer.</param>
	/// <param name="outMissedFrameCount">The count of bad or missed frames between successfully grabbed images.</param>
	/// <param name="outResynchronizationCount">The count of stream resynchronizations.</param>
	/// <param name="outLastBlockId">The last grabbed block ID.</param>
	/// <param name="outNumEmptyBuffers">The number of empty buffers that are not used for grabbing yet.</param>
	/// <param name="outNumQueuedBuffers">The number of buffers queued at Low Level API stream grabber.</param>
	/// <param name="outNumReadyBuffers">The number of grab result buffers in the output queue that are ready for retrieval.</param>
	/// <param name="outOutputQueueSize">The size of the grab result buffer output queue.</param>
	AVL_FUNCTION void Pylon_GetUsbStatistics
	(
		Pylon_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,						
		atl::int64&							outTotalBufferCount,			
		atl::int64&							outFailedBufferCount,			
		atl::int64&							outLastFailedBufferStatus,		
		atl::String&						outLastFailedBufferStatusText,	
		atl::int64&							outMissedFrameCount,			
		atl::int64&							outResynchronizationCount,		
		atl::int64&							outLastBlockId,					
		atl::int64&							outNumEmptyBuffers,				
		atl::int64&							outNumQueuedBuffers,			
		atl::int64&							outNumReadyBuffers,				
		atl::int64&							outOutputQueueSize				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PYLON_H

