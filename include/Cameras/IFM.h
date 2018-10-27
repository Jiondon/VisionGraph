//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IFM_H
#define AVL_IFM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/IFM/IfmInterface.h"
#include "Cameras/IFM/IfmParameters.h"

namespace avl
{


	struct Ifm_State : public BaseState
	{
		IfmInterface* ifm;

		Ifm_State() 
			: ifm(nullptr)
		{}

		~Ifm_State()
		{
			delete ifm;
		}

	private:
		Ifm_State(const Ifm_State&); //=delete
		Ifm_State& operator=(const Ifm_State&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a device.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inFrameRate">Sets the target frame rate in fps at which device should capture images. Default value: atl::NIL.</param>
	/// <param name="inResolution">Sets the resolution of output image. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Sets the trigger mode on device for capturing image. Default value: atl::NIL.</param>
	AVL_FUNCTION void IFM_StartAcquisition
	(
		Ifm_State&										ioState,
		const avl::IFMCameraAddress&					inAddress,		
		const atl::Optional<float>&					inFrameRate,	
		const atl::Optional<avl::IFMResolution::Type>&	inResolution,	
		const atl::Optional<avl::IFMTriggerMode::Type>&	inTriggerMode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from an ifm device.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inGrab3dCoordinates">Enable 3d coordinates capturing.</param>
	/// <param name="inFrameRate">Sets the target frame rate in fps at which device should capture images. Default value: atl::NIL.</param>
	/// <param name="inResolution">Sets the resolution of output image. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Sets the trigger mode on device for capturing image. Default value: atl::NIL.</param>
	/// <param name="outDistancesImage">Captured distance image.</param>
	/// <param name="outAmplitudeImage">Captured amplitude image.</param>
	/// <param name="outInvalidRois">Region array with invalid pixels: INVALID, SATURATED, INCONSISTENT and LOW_SIGNAL.</param>
	/// <param name="out3dCoordinates">Captured 3d coordinates.</param>
	AVL_FUNCTION bool IFM_GrabImage
	(
		Ifm_State&										ioState,
		const avl::IFMCameraAddress&					inAddress,					
		bool											inGrab3dCoordinates,		
		const atl::Optional<float>&					inFrameRate,				
		const atl::Optional<avl::IFMResolution::Type>&	inResolution,				
		const atl::Optional<avl::IFMTriggerMode::Type>&	inTriggerMode,				
		avl::Image&										outDistancesImage,			
		avl::Image&										outAmplitudeImage,			
		atl::Array<avl::Region>&						outInvalidRois,				
		atl::Conditional<avl::Point3DGrid>&				out3dCoordinates			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from an ifm device.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 100.</param>
	/// <param name="inGrab3dCoordinates">Enable 3d coordinates capturing.</param>
	/// <param name="inFrameRate">Sets the target frame rate in fps at which device should capture images. Default value: atl::NIL.</param>
	/// <param name="inResolution">Sets the resolution of output image. Default value: atl::NIL.</param>
	/// <param name="inTriggerMode">Sets the trigger mode on device for capturing image. Default value: atl::NIL.</param>
	/// <param name="outDistancesImage">Captured distance image.</param>
	/// <param name="outAmplitudeImage">Captured amplitude image.</param>
	/// <param name="outInvalidRois">Region array with invalid pixels: INVALID, SATURATED, INCONSISTENT and LOW_SIGNAL.</param>
	/// <param name="out3dCoordinates">Captured 3d coordinates.</param>
	AVL_FUNCTION bool IFM_GrabImage_WithTimeout
	(
		Ifm_State&										ioState,
		const avl::IFMCameraAddress&					inAddress,				
		int												inTimeout,				
		bool											inGrab3dCoordinates,	
		const atl::Optional<float>&					inFrameRate,			
		const atl::Optional<avl::IFMResolution::Type>&	inResolution,			
		const atl::Optional<avl::IFMTriggerMode::Type>&	inTriggerMode,			
		atl::Conditional<avl::Image>&					outDistancesImage,		
		atl::Conditional<avl::Image>&					outAmplitudeImage,		
		atl::Conditional<atl::Array<avl::Region>>&		outInvalidRois,			
		atl::Conditional<avl::Point3DGrid>&				out3dCoordinates		
	)
	THROW_AVL_ERRORS;

	/// <summary>Issue a device-dependent command.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inCommand">The command to be executed.</param>
	/// <param name="outResult">Result string.</param>
	AVL_FUNCTION void IFM_SourceCommand
	(
		Ifm_State&						ioState,
		const avl::IFMCameraAddress&	inAddress,		
		const atl::String&				inCommand,		
		atl::String&					outResult		
	)
	THROW_AVL_ERRORS;

	/// <summary>Set the integration time of the device.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inIndex">Index of the integration time.</param>
	/// <param name="inTime">Integration time in microseconds.</param>
	AVL_FUNCTION void IFM_SetIntegrationTime
	(
		Ifm_State&						ioState,
		const avl::IFMCameraAddress&	inAddress,		
		const int						inIndex,		
		const int						inTime			
	)
	THROW_AVL_ERRORS;

	/// <summary>Set the logic state of a specific io.</summary>
	/// <param name="inAddress">Device identifying address.</param>
	/// <param name="inNumber">Digital output number.</param>
	/// <param name="inState">Output state.</param>
	AVL_FUNCTION void IFM_SetDigitalOutput
	(
		Ifm_State&						ioState,
		const avl::IFMCameraAddress&	inAddress,		
		const int						inNumber,		
		const bool						inState			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IFM_H

