//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_LUMENERA_H
#define AVL_LUMENERA_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Lumenera/LumeneraInterface.h"
#include "AVLCommon/IoBaseState.h"

namespace avl
{


	typedef KitBaseState<LumeneraInterface> Lumenera_State;

	typedef Lumenera_State Lumenera_SkeletonTracingState;


	/// <summary>Captures a frame using Lumenera.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Lumenera_GrabImage
	(
		Lumenera_State&	ioState,
		const atl::Optional<int>	inDeviceID,	
		const avl::LumeneraImageFormatParams&			inImageFormat,			
		const avl::LumeneraAcquisitionControlParams&	inAcquisitionControl,	
		avl::Image&					outImage	
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using Lumenera.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Lumenera_GrabImage_WithTimeout
	(
		Lumenera_State&	ioState,
		const atl::Optional<int>	inDeviceID,	
		int											inTimeout,				
		const avl::LumeneraImageFormatParams&			inImageFormat,			
		const avl::LumeneraAcquisitionControlParams&	inAcquisitionControl,	
		atl::Conditional<avl::Image>&					outImage	
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts capturing images from an Lumenera camera.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	AVL_FUNCTION void Lumenera_StartAcquisition
	(
		Lumenera_State&	ioState,
		const atl::Optional<int>	inDeviceID,	
		const avl::LumeneraImageFormatParams&			inImageFormat,			
		const avl::LumeneraAcquisitionControlParams&	inAcquisitionControl	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stop image acquisition in a Lumenera device.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_StopAcquisition
	(
		Lumenera_State&								ioState,
		const atl::Optional<int>&	inDeviceID		
	)
	THROW_AVL_ERRORS;

	/// <summary>Set parameter</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_SetParameter
	(
		Lumenera_State&						ioState,
		const atl::Optional<int>&			inDeviceID,		
		const avl::LumeneraProperties::Type	inType,
		const float							inParameter
	)
	THROW_AVL_ERRORS;

	/// <summary>Get parameter</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_GetParameter
	(
		Lumenera_State&						ioState,
		const atl::Optional<int>&			inDeviceID,		
		const avl::LumeneraProperties::Type	inType,
		float&								outParameter
	)
	THROW_AVL_ERRORS;

	/// <summary>Configure pin direction, true for output</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_GpioConfigure
	(
		Lumenera_State&				ioState,
		const atl::Optional<int>&	inDeviceID,		
		const bool					inGpio0,
		const bool					inGpio1,
		const bool					inGpio2,
		const bool					inGpio3
	)
	THROW_AVL_ERRORS;

	/// <summary>Select GPO functionality, true for manual toggling using GpioWrite filter (see LucamGpoSelect in Lumenera API for default mode)</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_GpioSelect
	(
		Lumenera_State&				ioState,
		const atl::Optional<int>&	inDeviceID,		
		const bool					inGpio0,
		const bool					inGpio1,
		const bool					inGpio2,
		const bool					inGpio3
	)
	THROW_AVL_ERRORS;

	/// <summary>Write GPO pins</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_GpioWrite
	(
		Lumenera_State&				ioState,
		const atl::Optional<int>&	inDeviceID,		
		const bool					inGpo0,
		const bool					inGpo1,
		const bool					inGpo2,
		const bool					inGpo3
	)
	THROW_AVL_ERRORS;

	/// <summary>Read GPI pins</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Lumenera_GpioRead
	(
		Lumenera_State&				ioState,
		const atl::Optional<int>&	inDeviceID,		
		bool&						outGpi0,
		bool&						outGpi1,
		bool&						outGpi2,
		bool&						outGpi3
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_LUMENERA_H

