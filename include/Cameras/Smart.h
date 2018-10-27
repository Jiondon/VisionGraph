//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SMART_H
#define AVL_SMART_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "SmartBaseState.h"
#include "GenICam/GenICamTypes.h"
#include "Cameras/SynView/SynViewParameters.h"
#include "Cameras/Roseek/RoseekInterface.h"

namespace avl
{


	/// <summary>Captures an image from a smart camera using AvSMART interface. Allows for remote access to the runtime system.</summary>
	/// <param name="inIpAddress">IP address of the runtime system (e.g. a smart camera).</param>
	/// <param name="inPixelFormat">Image color format.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inWorkingMode">Working mode of image acquisition. Default value: atl::NIL.</param>
	/// <param name="inSensitivityLevel">Sensitivity level of camera sensor. Default value: atl::NIL.</param>
	/// <param name="inExposureMode">Exposure mode, should be set to Manual if you want to adjust inExposureTime manually. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Camera exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Smart_GrabImage
	(
		Smart_State&									ioState,
		const avl::SmartIPAddress&						inIpAddress,		
		avl::RoseekImageFormat::Type					inPixelFormat,		
		atl::Optional<float>							inFrameRate,		
		atl::Optional<avl::RoseekWorkingMode::Type>		inWorkingMode,		
		atl::Optional<int>								inSensitivityLevel,	
		atl::Optional<avl::RoseekExposureMode::Type>	inExposureMode,		
		atl::Optional<int>								inExposureTime,		
		atl::Optional<float>							inGain,				
		avl::Image&										outImage,			
		bool&											outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets digital outputs using AvSMART interface.</summary>
	AVL_FUNCTION void Smart_SetDigitalOutputs
	(
		Smart_State&					ioState,
		const avl::SmartIPAddress&		inIpAddress,
		bool							inVal1,
		bool							inVal2,
		bool							inVal3,
		bool							inVal4,
		bool&							outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a smart camera. Allows for remote access to the runtime system.</summary>
	/// <param name="inIpAddress">IP address of the runtime system (e.g. a smart camera).</param>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Smart_GrabImage_GenICam
	(
		Smart_State&										ioState,
		const avl::SmartIPAddress&							inIpAddress,			
		const atl::Optional<avl::GenAddress&>				inDeviceID,				
		atl::Optional<avl::RemoteGrabberPixelFormat::Type>	inPixelFormat,
		avl::Image&											outImage,				
		bool&												outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Set digital outputs.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	AVL_FUNCTION void Smart_SetDigitalOutputs_GenICam
	(
		Smart_State&								ioState,
		const avl::SmartIPAddress&					inIpAddress,
		const atl::Optional<avl::GenAddress&>		inDeviceID,			
		bool										inVal1,
		bool										inVal2,
		bool										inVal3,
		bool										inVal4,
		bool&										outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a smart camera using SynView interface. Allows for remote access to the runtime system.</summary>
	/// <param name="inIpAddress">IP address of the runtime system (e.g. a smart camera).</param>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Image color format.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Smart_GrabImage_SynView
	(
		Smart_State&								ioState,
		const avl::SmartIPAddress&					inIpAddress,			
		atl::Optional<const atl::String&>			inDeviceID,				
		avl::SynViewColorFormat::Type				inPixelFormat,			
		const avl::SynViewAcquisitionParams&		inAcquisitionParams,
		const avl::SynViewImageFormatParams&		inImageFormatParams,
		const avl::SynViewAnalogParams&				inAnalogParams,
		avl::Image&									outImage,				
		bool&										outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Configure SynView digital IO.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inLineNumber">I/O line for configuration.</param>
	/// <param name="inLineInverter">Invert the signal on the selected line. Default value: atl::NIL.</param>
	/// <param name="inLineDebounceDuration">Input line debounce duration in us (0 for disable debouncer). Default value: atl::NIL.</param>
	/// <param name="inLineSource">Selects a device internal signal that should drive the output signal of the selected line. Default value: atl::NIL.</param>
	AVL_FUNCTION void Smart_ConfigureDigitalIO_SynView
	(
		Smart_State&								ioState,
		const avl::SmartIPAddress&					inIpAddress,
		atl::Optional<const atl::String&>			inDeviceID,		
		int											inLineNumber,			
		atl::Optional<bool>							inLineInverter,			
		atl::Optional<float>						inLineDebounceDuration, 
		atl::Optional<avl::SynViewLineSource::Type>	inLineSource,	
		bool&										outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a smart camera. Allows for remote access to the runtime system.</summary>
	/// <param name="inIpAddress">IP address of the runtime system.</param>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outIsRemote">Specifies whether the program is currently executed on the runtime (True) or development (False) system.</param>
	AVL_FUNCTION bool Smart_GrabImage_WebCamera
	(
		Smart_State&					ioState,
		const avl::SmartIPAddress&		inIpAddress,		
		atl::Optional<int>				inDeviceID,			
		avl::Image&						outImage,			
		bool&							outIsRemote			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a smart camera using Roseek interface. Allows for remote access to the runtime system.</summary>
	/// <param name="inIpAddress">IP address of the runtime system (e.g. a smart camera).</param>
	/// <param name="inPixelFormat">Image color format.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inWorkingMode">Working mode of image acquisition. Default value: atl::NIL.</param>
	/// <param name="inSensitivityLevel">Sensitivity level of camera sensor. Default value: atl::NIL.</param>
	/// <param name="inExposureMode">Exposure mode, should be set to Manual if you want to adjust inExposureTime manually. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Camera exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Smart_GrabImage_Roseek
	(
		Smart_State&									ioState,
		const avl::SmartIPAddress&						inIpAddress,		
		avl::RoseekImageFormat::Type					inPixelFormat,		
		atl::Optional<float>							inFrameRate,		
		atl::Optional<avl::RoseekWorkingMode::Type>		inWorkingMode,		
		atl::Optional<int>								inSensitivityLevel,	
		atl::Optional<avl::RoseekExposureMode::Type>	inExposureMode,		
		atl::Optional<int>								inExposureTime,		
		atl::Optional<float>							inGain,				
		avl::Image&										outImage,			
		bool&											outIsRemote
	)
	THROW_AVL_ERRORS;

	/// <summary>Set digital outputs.</summary>
	AVL_FUNCTION void Smart_SetDigitalOutputs_Roseek
	(
		Smart_State&					ioState,
		const avl::SmartIPAddress&		inIpAddress,
		bool							inVal1,
		bool							inVal2,
		bool							inVal3,
		bool							inVal4,
		bool&							outIsRemote
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SMART_H

