//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_POINTGREY_H
#define AVL_POINTGREY_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/PointGrey/PointGreyInterface.h"
#include "Cameras/PointGrey/PointGreyEnums.h"

namespace avl
{


	struct FlyCapture_GrabImageState : public BaseState
	{
	public:
		PointGreyInterface* pointGrey;

		FlyCapture_GrabImageState()
			:pointGrey(nullptr)
		{}

		~FlyCapture_GrabImageState()
		{
			delete pointGrey;
		}

	private:
		FlyCapture_GrabImageState(const FlyCapture_GrabImageState&); //=delete
		FlyCapture_GrabImageState& operator=(const FlyCapture_GrabImageState&); //=delete
	};

	typedef FlyCapture_GrabImageState FlyCapture_GrabImage_WithTimeoutState;
	typedef FlyCapture_GrabImageState FlyCapture_StartAcquisitionState;
	typedef FlyCapture_GrabImageState FlyCapture_SetStrobeState;



	/// <summary>Captures images from a PointGrey camera.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inShutter">Shutter time. Default value: atl::NIL.</param>
	/// <param name="inGain">Image analog gain value. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Camera trigger mode and source control.</param>
	/// <param name="inColorMode">Requested grayscale or color mode of output image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION bool FlyCapture_GrabImage
	(
		FlyCapture_GrabImageState&		ioState,
		atl::Optional<int>				inDeviceSerialNumber,	
		atl::Optional<const avl::Box&>	inAoi,					
		atl::Optional<float>		inShutter,				
		atl::Optional<float>		inGain,					
		atl::Optional<float>		inExposure,				
		atl::Optional<float>		inFrameRate,			
		avl::PointGreyTriggerMode::Type	inTriggerMode,			
		avl::PointGreyColorMode::Type	inColorMode,			
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from a PointGrey camera.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inShutter">Shutter time. Default value: atl::NIL.</param>
	/// <param name="inGain">Image analog gain value. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Timeout. Default value: 5000.</param>
	/// <param name="inTriggerMode">Camera trigger mode and source control.</param>
	/// <param name="inColorMode">Requested grayscale or color mode of output image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION bool FlyCapture_GrabImage_WithTimeout
	(
		FlyCapture_GrabImage_WithTimeoutState&		ioState,
		atl::Optional<int>							inDeviceSerialNumber,	
		atl::Optional<const avl::Box&>				inAoi,					
		atl::Optional<float>					inShutter,				
		atl::Optional<float>					inGain,					
		atl::Optional<float>					inExposure,				
		atl::Optional<float>					inFrameRate,			
		atl::Optional<int>							inTimeout,				
		avl::PointGreyTriggerMode::Type				inTriggerMode,			
		avl::PointGreyColorMode::Type				inColorMode,			
		atl::Conditional<avl::Image>&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts capturing images from a PointGrey camera.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inShutter">Shutter time. Default value: atl::NIL.</param>
	/// <param name="inGain">Image analog gain value. Default value: atl::NIL.</param>
	/// <param name="inExposure">Exposure time. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Requested camera frame rate. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Camera trigger mode and source control.</param>
	/// <param name="inColorMode">Requested grayscale or color mode of output image.</param>
	AVL_FUNCTION void FlyCapture_StartAcquisition
	(
		FlyCapture_StartAcquisitionState&		ioState,
		atl::Optional<int>						inDeviceSerialNumber,	
		atl::Optional<const avl::Box&>			inAoi,					
		atl::Optional<float>				inShutter,				
		atl::Optional<float>				inGain,					
		atl::Optional<float>				inExposure,				
		atl::Optional<float>				inFrameRate,			
		avl::PointGreyTriggerMode::Type			inTriggerMode,			
		avl::PointGreyColorMode::Type			inColorMode				
	)
	THROW_AVL_ERRORS;

	/// <summary>Configures PointGrey camera Strobe</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inSource">Source value.</param>
	/// <param name="inEnabled">Flag controlling on/off.</param>
	/// <param name="inPolarity">Signal polarity.</param>
	/// <param name="inDelay">Signal delay (in ms).</param>
	/// <param name="inDuration">Signal duration (in ms).</param>
	AVL_FUNCTION void FlyCapture_SetStrobe
	(
		FlyCapture_SetStrobeState&	ioState,
		atl::Optional<int>			inDeviceSerialNumber,	
		int							inSource,				
		bool						inEnabled,				
		int							inPolarity,				
		float					inDelay,				
		float					inDuration				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_POINTGREY_H

