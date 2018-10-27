//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HIKVISION_H
#define AVL_HIKVISION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Hikvision/HikvisionInterface.h"

namespace avl
{


	struct Hikvision_State : public BaseState
	{
		HikvisionInterface* Hikvision;

		Hikvision_State()
			: Hikvision(nullptr)
		{}

		~Hikvision_State()
		{
			delete Hikvision;
		}

	private:
		Hikvision_State(const Hikvision_State&); //=delete
		Hikvision_State& operator=(const Hikvision_State&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start). Default value: 8.</param>
	/// <param name="inPixelFormat">Image pixel format (set on acquisition start).</param>
	/// <param name="inRoi">Region of interest (set on acquisition start). Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Sets the frame rate limit. Default value: atl::NIL.</param>
	/// <param name="inFrameRateAuto">True if frame rate is not limited. Default value: True.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 10000.0f.</param>
	/// <param name="inExposureTimeAuto">True if using automatic exposure time.</param>
	/// <param name="inGain">Sets gain in dB. Default value: 0.0f.</param>
	/// <param name="inGainAuto">True if using automatic gain.</param>
	AVL_FUNCTION void Hikvision_StartAcquisition
	(
		Hikvision_State&							ioState,
		atl::Optional<const atl::String&>			inDeviceID,			
		int											inInputQueueSize,	
		avl::HikvisionPixelFormat::Type				inPixelFormat,		
		atl::Optional<const avl::Box&>				inRoi,				
		atl::Optional<float>						inFrameRate,		
		bool										inFrameRateAuto,	
		atl::Optional<float>						inExposureTime,		
		bool										inExposureTimeAuto,	
		atl::Optional<float>						inGain,				
		bool										inGainAuto			
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a device.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void Hikvision_StopAcquisition
	(
		Hikvision_State&							ioState,
		atl::Optional<const atl::String&>			inDeviceID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a Hikvision device.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start). Default value: 8.</param>
	/// <param name="inPixelFormat">Image pixel format (set on acquisition start).</param>
	/// <param name="inRoi">Region of interest (set on acquisition start). Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Sets the frame rate limit. Default value: atl::NIL.</param>
	/// <param name="inFrameRateAuto">True if frame rate is not limited. Default value: True.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 10000.0f.</param>
	/// <param name="inExposureTimeAuto">True if using automatic exposure time.</param>
	/// <param name="inGain">Sets gain in dB. Default value: 0.0f.</param>
	/// <param name="inGainAuto">True if using automatic gain.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool Hikvision_GrabImage
	(
		Hikvision_State&								ioState,
		atl::Optional<const atl::String&>				inDeviceID,			
		int												inInputQueueSize,	
		avl::HikvisionPixelFormat::Type					inPixelFormat,		
		atl::Optional<const avl::Box&>					inRoi,				
		atl::Optional<float>							inFrameRate,		
		bool											inFrameRateAuto,	
		atl::Optional<float>							inExposureTime,		
		bool											inExposureTimeAuto,	
		atl::Optional<float>							inGain,				
		bool											inGainAuto,			
		avl::Image&										outImage,			
		atl::Conditional<int>&							outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a Hikvision device.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start). Default value: 8.</param>
	/// <param name="inPixelFormat">Image pixel format (set on acquisition start).</param>
	/// <param name="inRoi">Region of interest (set on acquisition start). Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Sets the frame rate limit. Default value: atl::NIL.</param>
	/// <param name="inFrameRateAuto">True if frame rate is not limited. Default value: True.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 10000.0f.</param>
	/// <param name="inExposureTimeAuto">True if using automatic exposure time.</param>
	/// <param name="inGain">Sets gain in dB. Default value: 0.0f.</param>
	/// <param name="inGainAuto">True if using automatic gain.</param>
	/// <param name="outImage">Captured image.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool Hikvision_GrabImage_WithTimeout
	(
		Hikvision_State&								ioState,
		atl::Optional<const atl::String&>				inDeviceID,			
		int												inTimeout,			
		int												inInputQueueSize,	
		avl::HikvisionPixelFormat::Type					inPixelFormat,		
		atl::Optional<const avl::Box&>					inRoi,				
		atl::Optional<float>							inFrameRate,		
		bool											inFrameRateAuto,	
		atl::Optional<float>							inExposureTime,		
		bool											inExposureTimeAuto,	
		atl::Optional<float>							inGain,				
		bool											inGainAuto,			
		atl::Conditional<avl::Image>&					outImage,			
		atl::Conditional<int>&							outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Hikvision_SetIntegerParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		int										inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Real.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Hikvision_SetRealParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		float									inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Hikvision_SetBoolParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		bool									inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Hikvision_SetStringParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		const atl::String&						inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Enum.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Hikvision_SetEnumParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		const atl::String&						inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Hikvision_GetIntegerParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		int&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Real.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Hikvision_GetRealParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		float&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Hikvision_GetBoolParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		bool&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Hikvision_GetStringParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		atl::String&							outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Enum.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Hikvision_GetEnumParameter
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		atl::String&							outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets triggering parameters.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inTriggerEnabled">True if using trigger. Default value: False.</param>
	/// <param name="inTriggerSelector">Triggering event selection. Default value: FrameBurstStart.</param>
	/// <param name="inTriggerSource">Trigger source. Default value: Line0.</param>
	/// <param name="inTriggerActivation">Trigger polarity. Default value: RisingEdge.</param>
	/// <param name="inTriggerDelay">Delay of trigger in microseconds. Default value: 0.0f.</param>
	AVL_FUNCTION void Hikvision_ConfigureTrigger
	(
		Hikvision_State&										ioState,
		atl::Optional<const atl::String&>						inDeviceID,				
		atl::Optional<bool>										inTriggerEnabled,		
		atl::Optional<avl::HikvisionEvent::Type>				inTriggerSelector,		
		atl::Optional<avl::HikvisionTriggerSource::Type>		inTriggerSource,		
		atl::Optional<avl::HikvisionTriggerActivation::Type>	inTriggerActivation,	
		atl::Optional<float>									inTriggerDelay			
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger in Hikvision device, trigger source should be set to 'Software'.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void Hikvision_GenerateSoftwareTrigger
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets strobe parameters.</summary>
	/// <param name="inDeviceID">Camera serial number, name or IP address, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inLineSelector">Strobe output line.</param>
	/// <param name="inLineSource">Strobe source. Default value: ExposureActive.</param>
	/// <param name="inLineInverter">True if inverting output signal. Default value: atl::NIL.</param>
	/// <param name="inStrobeEnabled">True if using strobe on selected line.</param>
	/// <param name="inStrobeDuration">Duration of strobe pulse in microseconds. Default value: atl::NIL.</param>
	/// <param name="inStrobeDelay">Delay of strobe pulse in microseconds. Default value: atl::NIL.</param>
	AVL_FUNCTION void Hikvision_ConfigureStrobe
	(
		Hikvision_State&						ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		avl::HikvisionLine::Type				inLineSelector,		
		avl::HikvisionEvent::Type				inLineSource,		
		atl::Optional<bool>						inLineInverter,		
		bool									inStrobeEnabled,	
		atl::Optional<int>						inStrobeDuration,	
		atl::Optional<int>						inStrobeDelay		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HIKVISION_H

