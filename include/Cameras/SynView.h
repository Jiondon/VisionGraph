//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SYNVIEW_H
#define AVL_SYNVIEW_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/SynView/SynViewInterface.h"

namespace avl
{


	struct SynView_BaseStructState : public BaseState
	{
		SynViewInterface* synView;

		SynView_BaseStructState()
			: synView(nullptr)
		{
		}

		~SynView_BaseStructState()
		{
			delete synView;
		}

	private:
		SynView_BaseStructState(const SynView_BaseStructState&); //=delete
		SynView_BaseStructState& operator=(const SynView_BaseStructState&); //=delete
	};

	typedef SynView_BaseStructState SynView_GrabImageState;
	typedef SynView_BaseStructState SynView_SetUserOutputState;
	typedef SynView_BaseStructState SynView_GetDigitalIOStatesState;
	typedef SynView_BaseStructState SynView_ConfigureDigitalIOState;
	typedef SynView_BaseStructState SynView_ConfigureTimerState;
	typedef SynView_BaseStructState SynView_StartAcquisitionState;
	typedef SynView_BaseStructState SynView_GrabImage_WithTimeoutState;
	typedef SynView_BaseStructState SynView_GenerateSoftwareTriggerState;
	typedef SynView_BaseStructState SynView_ConfigureStrobeState;
	typedef SynView_BaseStructState SynView_SetBoolParameterState;
	typedef SynView_BaseStructState SynView_SetRealParameterState;
	typedef SynView_BaseStructState SynView_SetIntegerParameterState;
	typedef SynView_BaseStructState SynView_SetEnumParameterState;
	typedef SynView_BaseStructState SynView_SetStringParameterState;
	typedef SynView_BaseStructState SynView_GetBoolParameterState;
	typedef SynView_BaseStructState SynView_GetRealParameterState;
	typedef SynView_BaseStructState SynView_GetIntegerParameterState;
	typedef SynView_BaseStructState SynView_GetEnumParameterState;
	typedef SynView_BaseStructState SynView_GetStringParameterState;
	typedef SynView_BaseStructState SynView_ExecuteCommandState;



	/// <summary>Captures a frame using SynView.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inColorFormat">Image color format.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool SynView_GrabImage
	(
		SynView_GrabImageState&								ioState,
		atl::Optional<const atl::String&>					inDeviceID,				
		avl::SynViewColorFormat::Type						inColorFormat,			
		const avl::SynViewAcquisitionParams&				inAcquisitionParams,
		const avl::SynViewImageFormatParams&				inImageFormatParams,
		const avl::SynViewAnalogParams&						inAnalogParams,
		avl::Image&											outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using SynView; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inColorFormat">Image color format.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool SynView_GrabImage_WithTimeout
	(
		SynView_GrabImage_WithTimeoutState&					ioState,
		atl::Optional<const atl::String&>					inDeviceID,				
		avl::SynViewColorFormat::Type						inColorFormat,			
		int													inTimeout,				
		const avl::SynViewAcquisitionParams&				inAcquisitionParams,
		const avl::SynViewImageFormatParams&				inImageFormatParams,
		const avl::SynViewAnalogParams&						inAnalogParams,
		atl::Conditional<avl::Image>&						outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a SynView camera.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inColorFormat">Image color format.</param>
	AVL_FUNCTION void SynView_StartAcquisition
	(
		SynView_StartAcquisitionState&						ioState,
		atl::Optional<const atl::String&>					inDeviceID,				
		avl::SynViewColorFormat::Type						inColorFormat,			
		const avl::SynViewAcquisitionParams&				inAcquisitionParams,
		const avl::SynViewImageFormatParams&				inImageFormatParams,
		const avl::SynViewAnalogParams&						inAnalogParams
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets SynView user outputs.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inUserOutput">User output for configuration.</param>
	/// <param name="inValue">Status of the selected user output.</param>
	AVL_FUNCTION void SynView_SetUserOutput
	(
		SynView_SetUserOutputState&			ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		avl::SynViewUserOutputs::Type		inUserOutput,	
		bool								inValue			

	)
	THROW_AVL_ERRORS;

	/// <summary>Gets SynView digital IO states.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inLineNumber">I/O line for querying.</param>
	/// <param name="outState">Current status of the selected line.</param>
	AVL_FUNCTION void SynView_GetDigitalIOStates
	(
		SynView_GetDigitalIOStatesState& 	ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inLineNumber,			
		bool&								outState				
	)
	THROW_AVL_ERRORS;

	/// <summary>Configure SynView digital IO.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inLineNumber">I/O line for configuration.</param>
	/// <param name="inLineInverter">Invert the signal on the selected line. Default value: atl::NIL.</param>
	/// <param name="inLineDebounceDuration">Input line debounce duration in us (0 for disable debouncer). Default value: atl::NIL.</param>
	/// <param name="inLineSource">Selects a device internal signal that should drive the output signal of the selected line. Default value: atl::NIL.</param>
	AVL_FUNCTION void SynView_ConfigureDigitalIO
	(
		SynView_ConfigureDigitalIOState&	ioState,
		atl::Optional<const atl::String&>	inDeviceID,				
		int									inLineNumber,			
		atl::Optional<bool>					inLineInverter,			
		atl::Optional<float>			inLineDebounceDuration, 
		atl::Optional<avl::SynViewLineSource::Type>	inLineSource	
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures one of the internal hardware timers available in the camera.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inTimerSelector">Timer selector.</param>
	/// <param name="inTimerDuration">Sets the duration (in microseconds) of the timer active pulse.</param>
	/// <param name="inTimerDelay">Sets the delay (in microseconds) applied between activating the timer and issuing the timer active signal.</param>
	/// <param name="inTimerTriggerSource">Internal device signal activating the selected timer.</param>
	AVL_FUNCTION void SynView_ConfigureTimer
	(
		SynView_ConfigureTimerState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID,				
		avl::SynViewTimerSelector::Type			inTimerSelector,		
		int										inTimerDuration,		
		int										inTimerDelay,			
		avl::SynViewTimerTriggerSource::Type	inTimerTriggerSource	
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates a software trigger, trigger source should be set to 'software'.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	AVL_FUNCTION void SynView_GenerateSoftwareTrigger
	(
		SynView_GenerateSoftwareTriggerState&	ioState,
		atl::Optional<const atl::String&>		inDeviceID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Controls the built-in camera strobe.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inStrobeEnabled">Selects the LED clusters of the strobe light that should be enabled.</param>
	/// <param name="inStrobeDuration">Duration of the strobe pulse in usec.</param>
	/// <param name="inStrobeDelay">A delay before the strobe pulse starts after frame trigger is applied in usec.</param>
	AVL_FUNCTION void SynView_ConfigureStrobe
	(
		SynView_ConfigureStrobeState&			ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		avl::SynViewStrobeEnable::Type			inStrobeEnabled,	
		float								inStrobeDuration,	
		float								inStrobeDelay		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void SynView_SetBoolParameter
	(
		SynView_SetBoolParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool								inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Real.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void SynView_SetRealParameter
	(
		SynView_SetRealParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float							inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void SynView_SetIntegerParameter
	(
		SynView_SetIntegerParameterState&	ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int									inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Enumeration.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void SynView_SetEnumParameter
	(
		SynView_SetEnumParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void SynView_SetStringParameter
	(
		SynView_SetStringParameterState&	ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void SynView_GetBoolParameter
	(
		SynView_GetBoolParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Real.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void SynView_GetRealParameter
	(
		SynView_GetRealParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float&							outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void SynView_GetIntegerParameter
	(
		SynView_GetIntegerParameterState&	ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Enumeration.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void SynView_GetEnumParameter
	(
		SynView_GetEnumParameterState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void SynView_GetStringParameter
	(
		SynView_GetStringParameterState&	ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Executes a command.</summary>
	/// <param name="inDeviceID">Tries to find the camera in all available IDs (UserID, VendorName, ModelName...). Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	AVL_FUNCTION void SynView_ExecuteCommand
	(
		SynView_ExecuteCommandState&		ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SYNVIEW_H

