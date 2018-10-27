//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GENTLAPI_H
#define AVL_GENTLAPI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Image/Image.h"

namespace avl
{



	typedef int GenTLHandle;

	#define INVALID_GENTL_HANDLE -1


	struct GenTL_LibraryDescriptor
	{
		atl::String Id;
		atl::String Vendor;
		atl::String Version;
		atl::String DisplayName;
	};

	struct GenTL_InterfaceDescriptor
	{
		atl::String TLType;
		atl::String DisplayName;
	};

	struct GenTL_DeviceDescriptor
	{
		atl::String DeviceId;
		atl::String InterfaceId;
		atl::String LibraryPath;

		atl::String DeviceDisplayName;
		atl::String DeviceModel;
		atl::String TLType;
	};



	/// <summary>Returns a list of loaded GenTL provider libraries available in the local system.</summary>
	/// <param name="outLibraryPaths">List of paths identifying libraries.</param>
	AVL_FUNCTION void GenTL_EnumLibraries
	(
		atl::Array<atl::String>&	outLibraryPaths		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads description of GenTL provider library.</summary>
	/// <param name="inLibraryPath">Path identifying provider library.</param>
	/// <param name="outDescriptor">Description retrieved from provider library.</param>
	AVL_FUNCTION void GenTL_GetLibraryDescriptor
	(
		const atl::String&			inLibraryPath,		
		GenTL_LibraryDescriptor&	outDescriptor		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a list of communication interfaces available in specified provider module library.</summary>
	/// <param name="inLibraryPath">Path identifying provider library.</param>
	/// <param name="outInterfaceIds">List of strings identifying interfaces.</param>
	AVL_FUNCTION void GenTL_EnumLibraryInterfaces
	(
		const atl::String&			inLibraryPath,		
		atl::Array<atl::String>&	outInterfaceIds		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads description of GenTL provider communication interface.</summary>
	/// <param name="inLibraryPath">Path identifying provider library.</param>
	/// <param name="inInterfaceId">String identifying communication interface.</param>
	/// <param name="outDescriptor">Description retrieved from provider interface.</param>
	AVL_FUNCTION void GenTL_GetInterfaceDescriptor
	(
		const atl::String&			inLibraryPath,		
		const atl::String&			inInterfaceId,		
		GenTL_InterfaceDescriptor&	outDescriptor		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs enumeration of GenTL devices and returns a list of present device descriptors.</summary>
	/// <param name="inLibraryPath">Path identifying provider library to limit enumeration to. Default value: atl::NIL.</param>
	/// <param name="inInterfaceId">String identifying communication interface to limit enumeration to. Default value: atl::NIL.</param>
	/// <param name="inTLType">Name of interface transport technology to limit enumeration to. Default value: atl::NIL.</param>
	/// <param name="inInterfaceScanTime">Time limit, in milliseconds, that the function will wait for device response on each enumerated interface.</param>
	/// <param name="outDevices">Returns a list with device list descriptors.</param>
	AVL_FUNCTION void GenTL_FindDevices
	(
		atl::Optional<const atl::String&>	inLibraryPath,			
		atl::Optional<const atl::String&>	inInterfaceId,			
		atl::Optional<const atl::String&>	inTLType,				
		int									inInterfaceScanTime,	
		atl::Array<GenTL_DeviceDescriptor>&	outDevices				
	)
	THROW_AVL_ERRORS;

	/// <summary>Closes a handle opened in GenTL subsystem.</summary>
	AVL_FUNCTION void GenTL_CloseHandle
	(
		GenTLHandle		inHandle
	)
	THROW_AVL_ERRORS;

	/// <summary>Closes all internally opened (cached) GenTL software modules not held any more by any opened handle.</summary>
	AVL_FUNCTION void GenTL_Cleanup
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens a handle to a device provided by GenTL library.</summary>
	/// <param name="inLibraryPath">Path identifying provider library.</param>
	/// <param name="inInterfaceId">String identifying communication interface through which device is accessed.</param>
	/// <param name="inDeviceId">Unique identifier of device in provider communication interface.</param>
	AVL_FUNCTION GenTLHandle GenTL_OpenDevice
	(
		const atl::String&		inLibraryPath,		
		const atl::String&		inInterfaceId,		
		const atl::String&		inDeviceId			
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens configuration node set (a system module configuration) of GenTL provider library.</summary>
	/// <param name="inLibraryPath">Path identifying library which system module should be accessed.</param>
	AVL_FUNCTION GenTLHandle GenTL_OpenLibrarySystemModuleSettings
	(
		const atl::String&		inLibraryPath		
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens configuration node set (an interface module configuration) of GenTL provider communication interface.</summary>
	/// <param name="inLibraryPath">Path identifying provider library.</param>
	/// <param name="inInterfaceId">String identifying communication interface which should be accessed.</param>
	AVL_FUNCTION GenTLHandle GenTL_OpenInterfaceModuleSettings
	(
		const atl::String&		inLibraryPath,		
		const atl::String&		inInterfaceId		
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens configuration node set of GenTL device (a device module configuration) of application side transport layer.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device which application side module should be accessed.</param>
	AVL_FUNCTION GenTLHandle GenTL_OpenDeviceModuleSettings
	(
		GenTLHandle					inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Opens configuration node set of application side transport layer of GenTL device first data stream (a stream module configuration).</summary>
	/// <param name="inDeviceHandle">Handle of an opened device which application side stream module should be accessed.</param>
	AVL_FUNCTION GenTLHandle GenTL_OpenDeviceStreamModuleSettings
	(
		GenTLHandle					inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Retrieves a list of available pixel formats supported by opened device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device.</param>
	/// <param name="outFormats">Array that will return a list of format strings.</param>
	AVL_FUNCTION void GenTL_GetPixelFormats
	(
		GenTLHandle					inDeviceHandle,		
		atl::Array< atl::String >&	outFormats			
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that should start acquisition.</param>
	/// <param name="inPixelFormat">Pixel format name in GenICam naming convention that will be configured as device stream PixelFormat parameter.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	AVL_FUNCTION void GenTL_StartAcquisition
	(
		GenTLHandle				inDeviceHandle,			
		const atl::String&		inPixelFormat,			
		int						inInputQueueSize = 1	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a device.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that should stop acquisition.</param>
	AVL_FUNCTION void GenTL_StopAcquisition
	(
		GenTLHandle		inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Discards remaining received and queued image frames in device video stream.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device which streaming queue should be cleared.</param>
	AVL_FUNCTION void GenTL_FlushInputQueue
	(
		GenTLHandle		inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if specified device is currently streaming video.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that will be checked for streaming.</param>
	AVL_FUNCTION bool GenTL_GetAcquisitionActive
	(
		GenTLHandle		inDeviceHandle		
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives next frame from video stream.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that is streaming video.</param>
	/// <param name="outImage">Image buffer that will receive a new frame.</param>
	/// <param name="outFrameId">Frame block Id set by device (when supported).</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION void GenTL_ReceiveImage
	(
		GenTLHandle					inDeviceHandle,				
		avl::Image&					outImage,					
		atl::Optional<atl::uint64&>	outFrameId = atl::NIL,		
		atl::Optional<atl::uint64&> outTimestamp = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Receives next frame from video stream.</summary>
	/// <param name="inDeviceHandle">Handle of an opened device that is streaming video.</param>
	/// <param name="inTimeout">Maximum time, in milliseconds, that the function is allowed to wait for the next complete frame. This parameter overrides global frame timeout configuration.</param>
	/// <param name="outImage">Image buffer that will receive a new frame.</param>
	/// <param name="outFrameId">Frame block Id set by device (when supported).</param>
	/// <param name="outTimestamp">Frame capture timestamp set by device (when supported).</param>
	AVL_FUNCTION bool GenTL_TryReceiveImage
	(
		GenTLHandle					inDeviceHandle,				
		int							inTimeout,					
		avl::Image&					outImage,					
		atl::Optional<atl::uint64&> outFrameId = atl::NIL,		
		atl::Optional<atl::uint64&> outTimestamp = atl::NIL		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GENTLAPI_H

