//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_THORLABS_H
#define AVL_THORLABS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/ThorLabs/ThorLabsInterface.h"

namespace avl
{


	struct Thorlabs_State : public BaseState
	{
		ThorLabsInterface* thorLabs;

		Thorlabs_State()
			: thorLabs(nullptr)
		{}

		~Thorlabs_State()
		{
			delete thorLabs;
		}

	private:
		Thorlabs_State(const Thorlabs_State&); //=delete
		Thorlabs_State& operator=(const Thorlabs_State&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start, default = 8). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 50000.</param>
	/// <param name="inGain">Sets gain. Default value: 120.</param>
	AVL_FUNCTION void Thorlabs_StartAcquisition
	(
		Thorlabs_State&								ioState,
		atl::Optional<const atl::String&>			inDeviceID,			
		atl::Optional<int>							inInputQueueSize,	
		atl::Optional<int>							inExposureTime,		
		atl::Optional<int>							inGain				
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a device.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void Thorlabs_StopAcquisition
	(
		Thorlabs_State&								ioState,
		atl::Optional<const atl::String&>			inDeviceID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a Thorlabs device.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start, default = 8). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 50000.</param>
	/// <param name="inGain">Sets gain. Default value: 120.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool Thorlabs_GrabImage
	(
		Thorlabs_State&									ioState,
		atl::Optional<const atl::String&>				inDeviceID,			
		atl::Optional<int>								inInputQueueSize,	
		atl::Optional<int>								inExposureTime,		
		atl::Optional<int>								inGain,				
		avl::Image&										outImage,			
		int&											outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from a Thorlabs device.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inInputQueueSize">Sets size of image queue (on acquisition start, default = 8). Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Sets the target exposure time in microseconds. Default value: 50000.</param>
	/// <param name="inGain">Sets gain. Default value: 120.</param>
	/// <param name="outImage">Captured image.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool Thorlabs_GrabImage_WithTimeout
	(
		Thorlabs_State&									ioState,
		atl::Optional<const atl::String&>				inDeviceID,				
		int												inTimeout,				
		atl::Optional<int>								inInputQueueSize,		
		atl::Optional<int>								inExposureTime,			
		atl::Optional<int>								inGain,					
		atl::Conditional<avl::Image>&					outImage,				
		int&											outFrameID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Thorlabs_SetIntegerParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		int										inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Real.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Thorlabs_SetRealParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		float									inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Thorlabs_SetBoolParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		bool									inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Thorlabs_SetStringParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		const atl::String&						inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Enum.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="inParameterValue">Value to set to parameter.</param>
	AVL_FUNCTION void Thorlabs_SetEnumParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		const atl::String&						inParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Thorlabs_GetIntegerParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		int&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Real.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Thorlabs_GetRealParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		float&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Thorlabs_GetBoolParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		bool&									outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Thorlabs_GetStringParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		atl::String&							outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Enum.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter.</param>
	/// <param name="outParameterValue">Value of parameter.</param>
	AVL_FUNCTION void Thorlabs_GetEnumParameter
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		const atl::String&						inParameterName,	
		atl::String&							outParameterValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets various camera's parameters before starting acquisition.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inRoi">Region of interest, Auto = full frame. Default value: atl::NIL.</param>
	/// <param name="inXBin">Horizontal binning factor. Default value: 1.</param>
	/// <param name="inYBin">Vertical binning factor. Default value: 1.</param>
	/// <param name="inReadoutSpeed">Speed of camera's sensor readout clock.</param>
	/// <param name="inTaps">Number of taps (simultaneous camera sensor readout operations per clock cycle).</param>
	/// <param name="inTapBalance">Whether internal tap balancing is enabled.</param>
	AVL_FUNCTION void Thorlabs_ConfigureCamera
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		atl::Optional<const avl::Box&>			inRoi,				
		int										inXBin,				
		int										inYBin,				
		avl::ThorlabsReadoutSpeed::Type			inReadoutSpeed,		
		avl::ThorlabsTaps::Type					inTaps,				
		bool									inTapBalance		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets triggering parameters.</summary>
	/// <param name="inDeviceID">Camera serial number or name, Auto = first camera. Default value: atl::NIL.</param>
	/// <param name="inTriggerEnabled">True if using trigger. Default value: False.</param>
	/// <param name="inTriggerPolarity">Polarity of trigger input.</param>
	/// <param name="inFrameCount">Number of frames to capture after trigger, Auto = continuous acquisition. Default value: atl::NIL.</param>
	AVL_FUNCTION void Thorlabs_ConfigureTrigger
	(
		Thorlabs_State&							ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		bool									inTriggerEnabled,	
		avl::ThorlabsTriggerPolarity::Type		inTriggerPolarity,	
		atl::Optional<int>						inFrameCount		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_THORLABS_H

