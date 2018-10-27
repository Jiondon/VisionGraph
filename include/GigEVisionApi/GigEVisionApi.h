//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GIGEVISIONAPI_H
#define AVL_GIGEVISIONAPI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "Image/Image.h"

namespace avl
{



	typedef int GigEHandle;

	#define INVALID_GIGE_HANDLE -1


	struct GigEVision_DeviceDescriptor
	{
		atl::String IpAddress;
		atl::String MacAddress;
		atl::String SerialNumber;
		atl::String ManufacturerName;
		atl::String ModelName;
		atl::String UserId;
	};



	/// <summary>This function performs enumeration of network devices and returns a list of present device descriptors.</summary>
	/// <param name="inTime">Time, in milliseconds, that the function will wait for device response. This is the time that the function will block execution before return.</param>
	/// <param name="inMaxDevices">Maximum number of devices to enumerate or 0 to return all devices. Default value: 0.</param>
	/// <param name="outDevices">Returns a list with device descriptors. Array passed as buffer is cleared before search and appended with descriptors.</param>
	AVL_FUNCTION void GigEVision_FindDevices
	(
		int inTime,												
		int inMaxDevices,										
		atl::Array< GigEVision_DeviceDescriptor >& outDevices	
	)
	THROW_AVL_ERRORS;

	/// <summary>Closes a handle opened in GigE Vision subsystem.</summary>
	AVL_FUNCTION void GigEVision_CloseHandle
	(
		GigEHandle	inHandle
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens configuration node set of GigE Vision application transport layer.</summary>
	AVL_FUNCTION GigEHandle GigEVision_OpenSystemConfiguration
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens a handle to a GigE Vision device.</summary>
	/// <param name="inDeviceAddress">Textual address that identifies a device in the network.</param>
	AVL_FUNCTION GigEHandle GigEVision_OpenDevice
	(
		const atl::String& inDeviceAddress	
	)
	THROW_AVL_ERRORS;

	/// <summary>Retrieves a list of available pixel formats supported by opened device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device.</param>
	/// <param name="outFormats">Array that will return a list of format strings.</param>
	AVL_FUNCTION void GigEVision_GetPixelFormats
	(
		GigEHandle					inDeviceHandle,		
		atl::Array< atl::String >&	outFormats			
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that should start acquisition.</param>
	/// <param name="inPixelFormat">Pixel format name in GenICam naming convention that will be configured as device stream PixelFormat parameter.</param>
	/// <param name="inInputQueueSize">Capacity of queue of input frames. Default value: 1.</param>
	AVL_FUNCTION void GigEVision_StartAcquisition
	(
		GigEHandle				inDeviceHandle,			
		const atl::String&		inPixelFormat,			
		int						inInputQueueSize = 1	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that should stop acquisition.</param>
	AVL_FUNCTION void GigEVision_StopAcquisition
	(
		GigEHandle	inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if connection with specified device is still active.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that will be checked.</param>
	AVL_FUNCTION bool GigEVision_GetDeviceConnectionOpened
	(
		GigEHandle	inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if specified device is currently streaming video.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that will be checked for streaming.</param>
	AVL_FUNCTION bool GigEVision_GetAcquisitionActive
	(
		GigEHandle	inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Discards remaining queued image frames and video stream data from network buffers.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device which streaming queue should be cleared.</param>
	AVL_FUNCTION void GigEVision_FlushInputQueue
	(
		GigEHandle	inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives next frame from video stream.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that is streaming video.</param>
	/// <param name="outImage">Image buffer that will receive a new frame.</param>
	/// <param name="outFrameId">Frame block Id set by device.</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION void GigEVision_ReceiveImage
	(
		GigEHandle					inDeviceHandle,				
		avl::Image&					outImage,					
		atl::Optional<atl::uint64&>	outFrameId = atl::NIL,		
		atl::Optional<atl::uint64&> outTimestamp = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives next frame from video stream.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that is streaming video.</param>
	/// <param name="inTimeout">Maximum time in milliseconds that the function is allowed to wait for the next complete frame. This parameter overrides the global frame timeout configuration.</param>
	/// <param name="outImage">Image buffer that will receive a new frame.</param>
	/// <param name="outFrameId">Frame block Id set by device.</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool GigEVision_TryReceiveImage
	(
		GigEHandle					inDeviceHandle,				
		int							inTimeout,					
		avl::Image&					outImage,					
		atl::Optional<atl::uint64&> outFrameId = atl::NIL,		
		atl::Optional<atl::uint64&> outTimestamp = atl::NIL		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GIGEVISIONAPI_H

