//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ICUBE_H
#define AVL_ICUBE_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/NetGmbh/ICubeInterface.h"
#include "Image/Image.h"

namespace avl
{


	struct ICube_State
	{
		ICubeInterface* iCube;

		ICube_State()
			: iCube(nullptr)
		{}

		~ICube_State()
		{
			delete iCube;
		}

		ICubeInterface* operator->()
		{
			return iCube;
		}

	private:
		ICube_State(const ICube_State&); //=delete
		ICube_State& operator=(const ICube_State&); //=delete
	};



	/// <summary>Captures an image from an ICube camera.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 10.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool ICube_GrabImage
	(
		ICube_State&									ioState,
		atl::Optional<int>								inDeviceID,				
		int												inInputQueueSize,
		avl::ICubeGrabMode::Type						inGrabbingMode,
		atl::Optional<avl::ICubeResolutionMode::Type>	inResolutionMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inSkippingMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inBinningMode,
		atl::Optional<float>							inExposureTime,
		atl::Optional<avl::Box>							inRoi,
		avl::Image&										outImage,				
		int&											outFrameID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from an ICube camera; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 10.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 100.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	AVL_FUNCTION bool ICube_GrabImage_WithTimeout
	(
		ICube_State&									ioState,
		atl::Optional<int>								inDeviceID,				
		int												inInputQueueSize,
		avl::ICubeGrabMode::Type						inGrabbingMode,
		int												inTimeout,				
		atl::Optional<avl::ICubeResolutionMode::Type>	inResolutionMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inSkippingMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inBinningMode,
		atl::Optional<float>							inExposureTime,
		atl::Optional<avl::Box>							inRoi,
		atl::Conditional<avl::Image>&					outImage,				
		atl::Conditional<int>&							outFrameID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes and starts image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Default value: 10.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void ICube_StartAcquisition
	(
		ICube_State&									ioState,
		atl::Optional<int>								inDeviceID,				
		int												inInputQueueSize,
		avl::ICubeGrabMode::Type						inGrabbingMode,
		atl::Optional<avl::ICubeResolutionMode::Type>	inResolutionMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inSkippingMode,
		atl::Optional<avl::ICubeBinSkip::Type>			inBinningMode,
		atl::Optional<float>							inExposureTime,
		atl::Optional<avl::Box>							inRoi
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition in a camera.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void ICube_StopAcquisition
	(
		ICube_State&				ioState,
		atl::Optional<int>			inDeviceID				
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a trigger mode in an ICube device.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Type of trigger mode (see Parameter Definitions in the API Header).</param>
	AVL_FUNCTION void ICube_SetTriggerMode
	(
		ICube_State&				ioState,
		atl::Optional<int>			inDeviceID,		
		avl::ICubeTriggerMode::Type	inTriggerMode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger in ICube device.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	AVL_FUNCTION void ICube_GenerateSoftwareTrigger
	(
		ICube_State&		ioState,
		atl::Optional<int>	inDeviceID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type Integer in an ICube device.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inType">Type of the parameter to set (see Parameter Definitions in the API Header).</param>
	/// <param name="inValue">Value to set.</param>
	AVL_FUNCTION void ICube_SetParameter
	(
		ICube_State&		ioState,
		atl::Optional<int>	inDeviceID,	
		int					inType,		
		int					inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type auto in an ICube device.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inType">Type of the parameter to set (see Parameter Definitions in the API Header).</param>
	/// <param name="inValue">1 == set auto, 0 == unset auto.</param>
	AVL_FUNCTION void ICube_SetParamAuto
	(
		ICube_State&		ioState,
		atl::Optional<int>	inDeviceID,	
		int					inType,		
		bool				inValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type One Push in an ICube device.</summary>
	/// <param name="inDeviceID">Index of a camera. Default value: atl::NIL.</param>
	/// <param name="inType">Type of the parameter to set (see Parameter Definitions in the API Header).</param>
	AVL_FUNCTION void ICube_SetParamOnePush
	(
		ICube_State&		ioState,
		atl::Optional<int>	inDeviceID, 
		int					inType		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_ICUBE_H

