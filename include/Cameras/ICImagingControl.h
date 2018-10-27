//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ICIMAGINGCONTROL_H
#define AVL_ICIMAGINGCONTROL_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/ICImagingControl/ICImagingControlInterface.h"

namespace avl
{


	struct ICImagingControlState
	{
		ICImagingControlInterface* icImagingControl;

		ICImagingControlState()
			: icImagingControl(nullptr)
		{
		}

		~ICImagingControlState()
		{
			delete icImagingControl;
		}

		ICImagingControlInterface* operator->()
		{
			return icImagingControl;
		}

	private:
		ICImagingControlState(const ICImagingControlState&); //=delete
		ICImagingControlState& operator=(const ICImagingControlState&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 3.</param>
	/// <param name="inPixelFormat">Pixel format. Default value: RGB24.</param>
	/// <param name="inBinning">Skipping factor. Default value: atl::NIL.</param>
	/// <param name="inSkipping">Binning factor. Default value: atl::NIL.</param>
	/// <param name="inRoi">Hardware Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain value. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Enable auto gain. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inExposureAuto">Enable auto exposure. Default value: atl::NIL.</param>
	/// <param name="inGamma">Gamma value. Default value: atl::NIL.</param>
	/// <param name="inSharpness">Sharpness value. Default value: atl::NIL.</param>
	AVL_FUNCTION void ICImagingControl_StartAcquisition
	(
		ICImagingControlState&							ioState,
		const atl::Optional<const atl::String&>&		inDeviceID,			
		int												inInputQueueSize,
		const avl::ICImagingControlColorFormat::Type	inPixelFormat,		
		const atl::Optional<int>						inBinning,			
		const atl::Optional<int>						inSkipping,			
		const atl::Optional<avl::Box>					inRoi,				
		const atl::Optional<float>						inFrameRate,		
		const atl::Optional<int>						inGain,				
		const atl::Optional<bool>						inGainAuto,			
		const atl::Optional<double>						inExposure,			
		const atl::Optional<bool>						inExposureAuto,		
		const atl::Optional<int>						inGamma,			
		const atl::Optional<int>						inSharpness			
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void ICImagingControl_StopAcquisition
	(
		ICImagingControlState&						ioState,
		const atl::Optional<const atl::String&>&	inDeviceID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame from The Imaging Source cameras using ICImagingControl.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 3.</param>
	/// <param name="inPixelFormat">Pixel format. Default value: RGB24.</param>
	/// <param name="inBinning">Skipping factor. Default value: atl::NIL.</param>
	/// <param name="inSkipping">Binning factor. Default value: atl::NIL.</param>
	/// <param name="inRoi">Hardware Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain value. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Enable auto gain. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inExposureAuto">Enable auto exposure. Default value: atl::NIL.</param>
	/// <param name="inGamma">Gamma value. Default value: atl::NIL.</param>
	/// <param name="inSharpness">Sharpness value. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool ICImagingControl_GrabImage
	(
		ICImagingControlState&							ioState,
		const atl::Optional<const atl::String&>&		inDeviceID,			
		int												inInputQueueSize,
		const avl::ICImagingControlColorFormat::Type	inPixelFormat,		
		const atl::Optional<int>						inBinning,			
		const atl::Optional<int>						inSkipping,			
		const atl::Optional<avl::Box>					inRoi,				
		const atl::Optional<float>						inFrameRate,		
		const atl::Optional<int>						inGain,				
		const atl::Optional<bool>						inGainAuto,			
		const atl::Optional<double>						inExposure,			
		const atl::Optional<bool>						inExposureAuto,		
		const atl::Optional<int>						inGamma,			
		const atl::Optional<int>						inSharpness,		
		avl::Image&										outImage,			
		atl::int64&										outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame from The Imaging Source cameras using ICImagingControl.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 3.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inPixelFormat">Pixel format. Default value: RGB24.</param>
	/// <param name="inBinning">Skipping factor. Default value: atl::NIL.</param>
	/// <param name="inSkipping">Binning factor. Default value: atl::NIL.</param>
	/// <param name="inRoi">Hardware Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain value. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Enable auto gain. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inExposureAuto">Enable auto exposure. Default value: atl::NIL.</param>
	/// <param name="inGamma">Gamma value. Default value: atl::NIL.</param>
	/// <param name="inSharpness">Sharpness value. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool ICImagingControl_GrabImage_WithTimeout
	(
		ICImagingControlState&							ioState,
		const atl::Optional<const atl::String&>&		inDeviceID,			
		int												inInputQueueSize,
		int												inTimeout,			
		const avl::ICImagingControlColorFormat::Type	inPixelFormat,		
		const atl::Optional<int>						inBinning,			
		const atl::Optional<int>						inSkipping,			
		const atl::Optional<avl::Box>					inRoi,				
		const atl::Optional<float>						inFrameRate,		
		const atl::Optional<int>						inGain,				
		const atl::Optional<bool>						inGainAuto,			
		const atl::Optional<double>						inExposure,			
		const atl::Optional<bool>						inExposureAuto,		
		const atl::Optional<int>						inGamma,			
		const atl::Optional<int>						inSharpness,		
		atl::Conditional<avl::Image>&					outImage,			
		atl::Conditional<atl::int64>&					outFrameID			
	)
	THROW_AVL_ERRORS;

	/// <summary>Controls camera external trigger.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="inEnable">External trigger state.</param>
	AVL_FUNCTION void ICImagingControl_EnableExternalTrigger
	(
		ICImagingControlState&						ioState,
		const atl::Optional<const atl::String&>&	inDeviceID,	
		bool										inEnable	
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets digital IO lines state.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="outInputState">Digital input state.</param>
	/// <param name="outOutputState">Digital output state.</param>
	AVL_FUNCTION void ICImagingControl_GetDigitalIOState
	(
		ICImagingControlState&						ioState,
		const atl::Optional<const atl::String&>&	inDeviceID,		
		bool&										outInputState,	
		bool&										outOutputState	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets digital IO line state.</summary>
	/// <param name="inDeviceID">Serial number, display name, unique name or base name of the camera. Default value: atl::NIL.</param>
	/// <param name="inOutputState">Digital output state.</param>
	AVL_FUNCTION void ICImagingControl_SetDigitalOutputState
	(
		ICImagingControlState&						ioState,
		const atl::Optional<const atl::String&>&	inDeviceID,		
		bool										inOutputState	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_ICIMAGINGCONTROL_H

