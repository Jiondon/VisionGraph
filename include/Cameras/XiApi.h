//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_XIAPI_H
#define AVL_XIAPI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/xiApi/xiApiInterface.h"
#include "Image/Image.h"

namespace avl
{


	struct XIAPIState
	{
		XiApiInterface* xiApi;

		XIAPIState()
			: xiApi(nullptr)
		{}

		~XIAPIState()
		{
			delete xiApi;
			xiApi = nullptr;
		}

		XiApiInterface* operator->()
		{
			return xiApi;
		}

	private:
		XIAPIState(const XIAPIState&); //=delete
		XIAPIState& operator=(const XIAPIState&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inImageDataFormat">Output data format.</param>
	/// <param name="inTriggerSource">Defines source of trigger.</param>
	/// <param name="inDownsampling">Changes image resolution by binning or skipping.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain in dB. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inBadPixelCorrection">Correction of bad pixels. Default value: atl::NIL.</param>
	/// <param name="inAutomaticExposureGain">Automatic exposure gain. Default value: atl::NIL.</param>
	AVL_FUNCTION void XiApi_StartAcquisition
	(
		XIAPIState&								ioState,
		const atl::Optional<atl::String>&		inDeviceID,				
		avl::XiApiImageDataFormat::Type			inImageDataFormat,		
		avl::XiApiTriggerSource::Type			inTriggerSource,		
		avl::XiApiDownsampling::Type			inDownsampling,			
		atl::Optional<int>						inExposureTime,			
		atl::Optional<float>					inGain,					
		atl::Optional<const avl::Box&>			inAoi,					
		atl::Optional<bool>						inBadPixelCorrection,	
		atl::Optional<bool>						inAutomaticExposureGain 
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	AVL_FUNCTION void XiApi_StopAcquisition
	(
		XIAPIState&								ioState,
		const atl::Optional<atl::String>&		inDeviceID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a XIMEA camera.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inImageDataFormat">Output data format.</param>
	/// <param name="inTriggerSource">Defines source of trigger.</param>
	/// <param name="inDownsampling">Changes image resolution by binning or skipping.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain in dB. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inBadPixelCorrection">Correction of bad pixels. Default value: atl::NIL.</param>
	/// <param name="inAutomaticExposureGain">Automatic exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool XiApi_GrabImage
	(
		XIAPIState&								ioState,
		const atl::Optional<atl::String>&		inDeviceID,				
		avl::XiApiImageDataFormat::Type			inImageDataFormat,		
		avl::XiApiTriggerSource::Type			inTriggerSource,		
		avl::XiApiDownsampling::Type			inDownsampling,			
		atl::Optional<int>						inExposureTime,			
		atl::Optional<float>					inGain,					
		atl::Optional<const avl::Box&>			inAoi,					
		atl::Optional<bool>						inBadPixelCorrection,	
		atl::Optional<bool>						inAutomaticExposureGain,
		avl::Image&								outImage,				
		atl::int64&								outFrameID,				
		atl::int64&								outTimestamp			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a XIMEA camera.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 100.</param>
	/// <param name="inImageDataFormat">Output data format.</param>
	/// <param name="inTriggerSource">Defines source of trigger.</param>
	/// <param name="inDownsampling">Changes image resolution by binning or skipping.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain in dB. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inBadPixelCorrection">Correction of bad pixels. Default value: atl::NIL.</param>
	/// <param name="inAutomaticExposureGain">Automatic exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool XiApi_GrabImage_WithTimeout
	(
		XIAPIState&								ioState,
		const atl::Optional<atl::String>&		inDeviceID,				
		int										inTimeout,				
		avl::XiApiImageDataFormat::Type			inImageDataFormat,		
		avl::XiApiTriggerSource::Type			inTriggerSource,		
		avl::XiApiDownsampling::Type			inDownsampling,			
		atl::Optional<int>						inExposureTime,			
		atl::Optional<float>					inGain,					
		atl::Optional<const avl::Box&>			inAoi,					
		atl::Optional<bool>						inBadPixelCorrection,	
		atl::Optional<bool>						inAutomaticExposureGain,
		atl::Conditional<avl::Image>&			outImage,				
		atl::Conditional<atl::int64>&			outFrameID,				
		atl::Conditional<atl::int64>&			outTimestamp			
	)
	THROW_AVL_ERRORS;

	/// <summary>Defines selected GPI (digital input) functionality.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inGPISelector">GPI number. Default value: 1.</param>
	AVL_FUNCTION void XiApi_SetGPIMode
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		int									inGPISelector,	
		avl::XiApiGPIMode::Type				inGPIMode
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the value from selected GPI (digital input).</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inGPISelector">GPI number. Default value: 1.</param>
	AVL_FUNCTION void XiApi_GetGPILevel
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		int									inGPISelector,	
		int&								outGPILevel
	)
	THROW_AVL_ERRORS;

	/// <summary>Defines GPO (digital output) functionality.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inGPOSelector">GPO number. Default value: 1.</param>
	AVL_FUNCTION void XiApi_SetGPOMode
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		int									inGPOSelector,	
		avl::XiApiGPOMode::Type				inGPOMode
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer in XIMEA device.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inParameter">Parameter name.</param>
	/// <param name="inValue">Value to set.</param>
	AVL_FUNCTION void XiApi_SetParamInt
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inParameter,
		int									inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Float in XIMEA device.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inParameter">Parameter name.</param>
	/// <param name="inValue">Value to set.</param>
	AVL_FUNCTION void XiApi_SetParamFloat
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inParameter,
		float							inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer from XIMEA device.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inParameter">Parameter name.</param>
	/// <param name="outValue">Received value.</param>
	AVL_FUNCTION void XiApi_GetParamInt
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		const atl::String&					inParameter,	
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Float from XIMEA device.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	/// <param name="inParameter">Parameter name.</param>
	/// <param name="outValue">Received value.</param>
	AVL_FUNCTION void XiApi_GetParamFloat
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inParameter,
		float&							outValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger for XIMEA device.</summary>
	/// <param name="inDeviceID">Camera chip ID or camera index. Default value: atl::NIL.</param>
	AVL_FUNCTION void XiApi_GenerateSoftwareTrigger
	(
		XIAPIState&							ioState,
		const atl::Optional<atl::String>&	inDeviceID	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_XIAPI_H

