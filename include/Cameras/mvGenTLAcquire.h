//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MVGENTLACQUIRE_H
#define AVL_MVGENTLACQUIRE_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/mvGenTLAcquire/mvGenTLAcquireInterface.h"
#include "Cameras/mvGenTLAcquire/mvGenTLAcquireEnums.h"

namespace avl
{



	struct mvGenTLAcquireState : public BaseState
	{
		mvGenTLAcquireInterface* mvGenTL;

		mvGenTLAcquireState()
			: mvGenTL(nullptr)
		{}

		~mvGenTLAcquireState()
		{
			delete mvGenTL;
		}

		mvGenTLAcquireInterface* operator->()
		{
			return mvGenTL;
		}

	private:
		mvGenTLAcquireState(const mvGenTLAcquireState&); //=delete
		mvGenTLAcquireState& operator=(const mvGenTLAcquireState&); //=delete
	};



	/// <summary>Captures a frame from MATRIX VISION cameras using mvGenTLAcquire SDK.</summary>
	/// <param name="inDeviceID">Device name or serial number of device. Default value: atl::NIL.</param>
	/// <param name="inPixelFormat">Pixel format of output image.</param>
	/// <param name="inExposureTime">Exposure time value. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain value. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate in FPS. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Trigger mode.</param>
	/// <param name="inTriggerSource">Source of trigger.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool mvGenTLAcquire_GrabImage
	(
		mvGenTLAcquireState&					ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		avl::MVGenTLPixelFormat::Type			inPixelFormat,		
		atl::Optional<int>						inExposureTime,		
		atl::Optional<float>					inGain,				
		atl::Optional<float>					inFrameRate,		
		atl::Optional<const avl::Box&>			inAoi,				
		avl::MvIMPACTTriggerActivation::Type	inTriggerMode,		
		avl::MvIMPACTTriggerSource::Type		inTriggerSource,	
		avl::Image&								outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame from MATRIX VISION cameras using mvGenTLAcquire SDK.</summary>
	/// <param name="inDeviceID">Device name or serial number of device. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds.</param>
	/// <param name="inPixelFormat">Pixel format of output image.</param>
	/// <param name="inExposureTime">Exposure time value. Default value: atl::NIL.</param>
	/// <param name="inGain">Gain value. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate in FPS. Default value: atl::NIL.</param>
	/// <param name="inAoi">Required fragment of image to stream. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Trigger mode.</param>
	/// <param name="inTriggerSource">Source of trigger.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool mvGenTLAcquire_GrabImage_WithTimeout
	(
		mvGenTLAcquireState&					ioState,
		atl::Optional<const atl::String&>		inDeviceID,			
		int										inTimeout,				
		avl::MVGenTLPixelFormat::Type			inPixelFormat,		
		atl::Optional<int>						inExposureTime,		
		atl::Optional<float>					inGain,				
		atl::Optional<float>					inFrameRate,		
		atl::Optional<const avl::Box&>			inAoi,				
		avl::MvIMPACTTriggerActivation::Type	inTriggerMode,		
		avl::MvIMPACTTriggerSource::Type		inTriggerSource,	
		atl::Conditional<avl::Image>&			outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the state of digital inputs or outputs from matrix vision cameras.</summary>
	/// <param name="inDeviceID">Device name or serial number of device. Default value: atl::NIL.</param>
	/// <param name="inIOIndex">Index of input or output line.</param>
	/// <param name="outValue">State of IO line.</param>
	AVL_FUNCTION void mvGenTLAcquire_GetDigitalIOState
	(
		mvGenTLAcquireState&					ioState,
		atl::Optional<const atl::String&>		inDeviceID,	
		int										inIOIndex,	
		bool&									outValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets matrix vision camera digital outputs.</summary>
	/// <param name="inDeviceID">Device name or serial number of device. Default value: atl::NIL.</param>
	/// <param name="inOutput">Index of output line.</param>
	/// <param name="inValue">Logic value of digital output.</param>
	AVL_FUNCTION void mvGenTLAcquire_SetDigitalOutput
	(
		mvGenTLAcquireState&					ioState,
		atl::Optional<const atl::String&>		inDeviceID,	
		int										inOutput,	
		bool									inValue		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MVGENTLACQUIRE_H

