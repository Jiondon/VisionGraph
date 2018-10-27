//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AVSMART_H
#define AVL_AVSMART_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Roseek/RoseekInterface.h"

namespace avl
{


	struct AvSmart_State
	{
	public:
		RoseekInterface* iface;

		AvSmart_State()
			: iface(nullptr)
		{}

		~AvSmart_State()
		{
			delete iface;
		}

		RoseekInterface* operator->()
		{
			return iface;
		}

	private:
		AvSmart_State(const AvSmart_State&); //=delete
		AvSmart_State& operator=(const AvSmart_State&); //=delete
	};


	/// <summary>Initializes and starts image acquisition.</summary>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 3.</param>
	/// <param name="inImageFormat">Image pixel format.</param>
	/// <param name="inResolutionMode">Set resolution of image. Default value: atl::NIL.</param>
	/// <param name="inROI">Set resolution region. Has effect only if resolution mode is ROI. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inWorkingMode">Working mode of image acquisition. Default value: atl::NIL.</param>
	/// <param name="inSensitivityLevel">Sensitivity level of camera sensor. Default value: atl::NIL.</param>
	/// <param name="inExposureMode">Exposure mode, should be set to Manual if you want to adjust inExposureTime manually. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Camera exposure gain. Default value: atl::NIL.</param>
	AVL_FUNCTION void AvSMART_StartAcquisition
	(
		AvSmart_State&									ioState,
		int												inInputQueueSize,	
		avl::RoseekImageFormat::Type					inImageFormat,		
		atl::Optional<avl::RoseekResolutionMode::Type>	inResolutionMode,	
		const atl::Optional<avl::Box>&					inROI,				
		atl::Optional<float>							inFrameRate,		
		atl::Optional<avl::RoseekWorkingMode::Type>		inWorkingMode,		
		atl::Optional<int>								inSensitivityLevel,	
		atl::Optional<avl::RoseekExposureMode::Type>	inExposureMode,		
		atl::Optional<int>								inExposureTime,		
		atl::Optional<float>							inGain				
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition.</summary>
	AVL_FUNCTION void AvSMART_StopAcquisition
	(
		AvSmart_State&	ioState
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from a AvSMART device.</summary>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 3.</param>
	/// <param name="inImageFormat">Image pixel format.</param>
	/// <param name="inResolutionMode">Set resolution of image. Default value: atl::NIL.</param>
	/// <param name="inROI">Set resolution region. Has effect only if resolution mode is ROI. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inWorkingMode">Working mode of image acquisition. Default value: atl::NIL.</param>
	/// <param name="inSensitivityLevel">Sensitivity level of camera sensor. Default value: atl::NIL.</param>
	/// <param name="inExposureMode">Exposure mode, should be set to Manual if you want to adjust inExposureTime manually. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Camera exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool AvSMART_GrabImage
	(
		AvSmart_State&									ioState,
		int												inInputQueueSize,	
		avl::RoseekImageFormat::Type					inImageFormat,		
		atl::Optional<avl::RoseekResolutionMode::Type>	inResolutionMode,	
		const atl::Optional<avl::Box>&					inROI,				
		atl::Optional<float>							inFrameRate,		
		atl::Optional<avl::RoseekWorkingMode::Type>		inWorkingMode,		
		atl::Optional<int>								inSensitivityLevel,	
		atl::Optional<avl::RoseekExposureMode::Type>	inExposureMode,		
		atl::Optional<int>								inExposureTime,		
		atl::Optional<float>							inGain,				
		avl::Image&										outImage,			
		int&											outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from a AvSMART device.</summary>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them. Default value: 3.</param>
	/// <param name="inImageFormat">Image pixel format.</param>
	/// <param name="inResolutionMode">Set resolution of image. Default value: atl::NIL.</param>
	/// <param name="inROI">Set resolution region. Has effect only if resolution mode is ROI. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate in frames per second. Default value: atl::NIL.</param>
	/// <param name="inWorkingMode">Working mode of image acquisition. Default value: atl::NIL.</param>
	/// <param name="inSensitivityLevel">Sensitivity level of camera sensor. Default value: atl::NIL.</param>
	/// <param name="inExposureMode">Exposure mode, should be set to Manual if you want to adjust inExposureTime manually. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Camera frame exposition time. Default value: atl::NIL.</param>
	/// <param name="inGain">Camera exposure gain. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool AvSMART_GrabImage_WithTimeout
	(
		AvSmart_State&									ioState,
		int												inTimeout,			
		int												inInputQueueSize,	
		avl::RoseekImageFormat::Type					inImageFormat,		
		atl::Optional<avl::RoseekResolutionMode::Type>	inResolutionMode,	
		const atl::Optional<avl::Box>&					inROI,				
		atl::Optional<float>							inFrameRate,		
		atl::Optional<avl::RoseekWorkingMode::Type>		inWorkingMode,		
		atl::Optional<int>								inSensitivityLevel,	
		atl::Optional<avl::RoseekExposureMode::Type>	inExposureMode,		
		atl::Optional<int>								inExposureTime,		
		atl::Optional<float>							inGain,				
		atl::Conditional<avl::Image>&					outImage,			
		atl::Conditional<int>&							outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger.</summary>
	AVL_FUNCTION void AvSMART_GenerateSoftwareTrigger
	(
		AvSmart_State&	ioState
	)
	THROW_AVL_ERRORS;

	/// <summary>Set output I/O state.</summary>
	/// <param name="inId">Index of I/O output port.</param>
	/// <param name="inState">true = TURN_ON, false = TURN_OFF.</param>
	AVL_FUNCTION void AvSMART_SetOutputState
	(
		AvSmart_State&	ioState,
		int				inId,		
		bool			inState		
	)
	THROW_AVL_ERRORS;

	/// <summary>Get input I/O state.</summary>
	/// <param name="inId">Index of I/O output port.</param>
	/// <param name="outState">Received state.</param>
	AVL_FUNCTION void AvSMART_GetInputState
	(
		AvSmart_State&	ioState,
		int				inId,		
		bool&			outState	
	)
	THROW_AVL_ERRORS;

	/// <summary>Set the driver working mode of LED.</summary>
	/// <param name="inType">Driver type (own or external).</param>
	/// <param name="inMode">LED driver mode.</param>
	AVL_FUNCTION void AvSMART_ConfigureLEDDriverMode
	(
		AvSmart_State&					ioState,
		avl::RoseekLEDDriverType::Type	inType,	
		avl::RoseekLEDDriverMode::Type	inMode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Set the driver strength of LED.</summary>
	/// <param name="inType">Driver type (own or external).</param>
	/// <param name="inStrength">Strength. For OWN driver type the max value is 330 otherwise 1500.</param>
	AVL_FUNCTION void AvSMART_SetLEDDriverStrength
	(
		AvSmart_State&					ioState,
		avl::RoseekLEDDriverType::Type	inType,		
		int								inStrength	
	)
	THROW_AVL_ERRORS;

	/// <summary>Set the status of programmable LED state indicators supported on the camera.</summary>
	/// <param name="inId">Index of I/O output port.</param>
	/// <param name="inState">Received state.</param>
	AVL_FUNCTION void AvSMART_SetStatusLED
	(
		AvSmart_State&				ioState,
		int							inId,	
		avl::RoseekLEDStatus::Type	inState	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_AVSMART_H

