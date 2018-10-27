//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IDS_H
#define AVL_IDS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Cameras/IDS/IDSEnums.h"
#include "Cameras/IDS/IDSInterface.h"

namespace avl
{



	struct IDS_BaseState
	{
		atl::Optional<atl::String> deviceId;
		IDSInterface* ids;

		IDS_BaseState()
			: ids(nullptr)
		{}

		~IDS_BaseState()
		{
			delete ids;
		}

		IDSInterface* operator->()
		{
			return ids;
		}

	private:
		IDS_BaseState(const IDS_BaseState&); //=delete
		IDS_BaseState& operator=(const IDS_BaseState&); //=delete
	};



	/// <summary>Captures an image from an IDS camera.</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Pixel format. Supported values: Raw8, Mono8, Rgb8, Bgr8, Rgba8, Bgra8. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Capacity of input frames queue. Default value: 3.</param>
	/// <param name="inAutoReconnect">Automatically reconnect with the camera. Default value: True.</param>
	/// <param name="inTriggerMode">Camera trigger mode. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inHorizontalBinning">Horizontal binning. Default value: atl::NIL.</param>
	/// <param name="inVerticalBinning">Vertical binning. Default value: atl::NIL.</param>
	/// <param name="inMirror">Mirror effect. Default value: atl::NIL.</param>
	/// <param name="inAutoBlackLevel">Enable auto black level. Default value: atl::NIL.</param>
	/// <param name="inBlackLevelOffset">Black level offset. Default value: atl::NIL.</param>
	/// <param name="inGamma">Set gamma value. Default value: atl::NIL.</param>
	/// <param name="inGainBoost">Set gain boost mode. Default value: atl::NIL.</param>
	/// <param name="inGainMaster">Set gain master value. Default value: atl::NIL.</param>
	/// <param name="inGainRed">Set gain red value. Default value: atl::NIL.</param>
	/// <param name="inGainGreen">Set gain green value. Default value: atl::NIL.</param>
	/// <param name="inGainBlue">Set gain blue value. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION bool IDS_GrabImage
	(
		IDS_BaseState&									ioState,
		const atl::Optional<atl::String>&				inDeviceID,				
		const atl::String&								inPixelFormat,			
		int												inInputQueueSize,		
		bool											inAutoReconnect,		
		const atl::Optional<avl::IDSTriggerMode::Type>&	inTriggerMode,			
		const atl::Optional<avl::Box>&					inAoi,					
		const atl::Optional<float>&						inFrameRate,			
		const atl::Optional<float>&						inExposureTime,			
		const atl::Optional<avl::IDSBinning::Type>&		inHorizontalBinning,	
		const atl::Optional<avl::IDSBinning::Type>&		inVerticalBinning,		
		const atl::Optional<avl::IDSMirror::Type>&		inMirror,				
		const atl::Optional<bool>&						inAutoBlackLevel,		
		const atl::Optional<int>&						inBlackLevelOffset,		
		const atl::Optional<int>&						inGamma,				
		const atl::Optional<bool>&						inGainBoost,			
		const atl::Optional<int>&						inGainMaster,			
		const atl::Optional<int>&						inGainRed,				
		const atl::Optional<int>&						inGainGreen,			
		const atl::Optional<int>&						inGainBlue,				
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from an IDS camera.</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Pixel format. Supported values: Raw8, Mono8, Rgb8, Bgr8, Rgba8, Bgra8. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Capacity of input frames queue. Default value: 3.</param>
	/// <param name="inAutoReconnect">Automatically reconnect with the camera. Default value: True.</param>
	/// <param name="inTriggerMode">Camera trigger mode. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 100.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inHorizontalBinning">Horizontal binning. Default value: atl::NIL.</param>
	/// <param name="inVerticalBinning">Vertical binning. Default value: atl::NIL.</param>
	/// <param name="inMirror">Mirror effect. Default value: atl::NIL.</param>
	/// <param name="inAutoBlackLevel">Enable auto black level. Default value: atl::NIL.</param>
	/// <param name="inBlackLevelOffset">Black level offset. Default value: atl::NIL.</param>
	/// <param name="inGamma">Set gamma value. Default value: atl::NIL.</param>
	/// <param name="inGainBoost">Set gain boost mode. Default value: atl::NIL.</param>
	/// <param name="inGainMaster">Set gain master value. Default value: atl::NIL.</param>
	/// <param name="inGainRed">Set gain red value. Default value: atl::NIL.</param>
	/// <param name="inGainGreen">Set gain green value. Default value: atl::NIL.</param>
	/// <param name="inGainBlue">Set gain blue value. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION bool IDS_GrabImage_WithTimeout
	(
		IDS_BaseState&									ioState,
		const atl::Optional<atl::String>&				inDeviceID,				
		const atl::String&								inPixelFormat,			
		int												inInputQueueSize,		
		bool											inAutoReconnect,		
		const atl::Optional<avl::IDSTriggerMode::Type>&	inTriggerMode,			
		int												inTimeout,				
		const atl::Optional<avl::Box>&					inAoi,					
		const atl::Optional<float>&						inFrameRate,			
		const atl::Optional<float>&						inExposureTime,			
		const atl::Optional<avl::IDSBinning::Type>&		inHorizontalBinning,	
		const atl::Optional<avl::IDSBinning::Type>&		inVerticalBinning,		
		const atl::Optional<avl::IDSMirror::Type>&		inMirror,				
		const atl::Optional<bool>&						inAutoBlackLevel,		
		const atl::Optional<int>&						inBlackLevelOffset,		
		const atl::Optional<int>&						inGamma,				
		const atl::Optional<bool>&						inGainBoost,			
		const atl::Optional<int>&						inGainMaster,			
		const atl::Optional<int>&						inGainRed,				
		const atl::Optional<int>&						inGainGreen,			
		const atl::Optional<int>&						inGainBlue,				
		atl::Conditional<avl::Image>&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a camera</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Pixel format. Supported values: Raw8, Mono8, Rgb8, Bgr8, Rgba8, Bgra8. Default value: \"Mono8\".</param>
	/// <param name="inInputQueueSize">Capacity of input frames queue. Default value: 3.</param>
	/// <param name="inAutoReconnect">Automatically reconnect with the camera. Default value: True.</param>
	/// <param name="inTriggerMode">Camera trigger mode. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inHorizontalBinning">Horizontal binning. Default value: atl::NIL.</param>
	/// <param name="inVerticalBinning">Vertical binning. Default value: atl::NIL.</param>
	/// <param name="inMirror">Mirror effect. Default value: atl::NIL.</param>
	/// <param name="inAutoBlackLevel">Enable auto black level. Default value: atl::NIL.</param>
	/// <param name="inBlackLevelOffset">Black level offset. Default value: atl::NIL.</param>
	/// <param name="inGamma">Set gamma value. Default value: atl::NIL.</param>
	/// <param name="inGainBoost">Set gain boost mode. Default value: atl::NIL.</param>
	/// <param name="inGainMaster">Set gain master value. Default value: atl::NIL.</param>
	/// <param name="inGainRed">Set gain red value. Default value: atl::NIL.</param>
	/// <param name="inGainGreen">Set gain green value. Default value: atl::NIL.</param>
	/// <param name="inGainBlue">Set gain blue value. Default value: atl::NIL.</param>
	AVL_FUNCTION void IDS_StartAcquisition
	(
		IDS_BaseState&									ioState,
		const atl::Optional<atl::String>&				inDeviceID,				
		const atl::String&								inPixelFormat,			
		int												inInputQueueSize,		
		bool											inAutoReconnect,		
		const atl::Optional<avl::IDSTriggerMode::Type>&	inTriggerMode,			
		const atl::Optional<avl::Box>&					inAoi,					
		const atl::Optional<float>&						inFrameRate,			
		const atl::Optional<float>&						inExposureTime,			
		const atl::Optional<avl::IDSBinning::Type>&		inHorizontalBinning,	
		const atl::Optional<avl::IDSBinning::Type>&		inVerticalBinning,		
		const atl::Optional<avl::IDSMirror::Type>&		inMirror,				
		const atl::Optional<bool>&						inAutoBlackLevel,		
		const atl::Optional<int>&						inBlackLevelOffset,		
		const atl::Optional<int>&						inGamma,				
		const atl::Optional<bool>&						inGainBoost,			
		const atl::Optional<int>&						inGainMaster,			
		const atl::Optional<int>&						inGainRed,				
		const atl::Optional<int>&						inGainGreen,			
		const atl::Optional<int>&						inGainBlue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Load specific camera parameters</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	/// <param name="inLoadFromEEPROM">If true loads configuration from EEPROM.</param>
	/// <param name="inFile">Parameters file path.</param>
	AVL_FUNCTION void IDS_LoadParameterSet
	(
		IDS_BaseState&								ioState,
		const atl::Optional<atl::String>&			inDeviceID,				
		bool										inLoadFromEEPROM,		
		const atl::File&							inFile					
	)
	THROW_AVL_ERRORS;

	/// <summary>Force software-controlled capture of an image while a capturing process triggered by hardware is in progress</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	AVL_FUNCTION void IDS_ForceTrigger
	(
		IDS_BaseState&								ioState,
		const atl::Optional<atl::String>&			inDeviceID				
	)
	THROW_AVL_ERRORS;

	/// <summary>"Configure digital inputs/outputs of IDS camera</summary>
	/// <param name="inDeviceID">Device serial number or user definable camera ID. Default value: atl::NIL.</param>
	/// <param name="inGPIO">GPIO id.</param>
	/// <param name="inConfiguration">GPIO Configuration.</param>
	/// <param name="inState">GPIO state (true = High, false = Low).</param>
	AVL_FUNCTION void IDS_ConfigureGPIO
	(
		IDS_BaseState&							ioState,
		const atl::Optional<atl::String>&		inDeviceID,		
		int										inGPIO,			
		avl::IDSGPIOConfiguration::Type			inConfiguration,
		bool									inState			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IDS_H

