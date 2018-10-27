//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ENSENSO_H
#define AVL_ENSENSO_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Ensenso/EnsensoInterface.h"
#include "AVLCommon/IoBaseState.h"

namespace avl
{


	typedef KitBaseState<EnsensoInterface> Ensenso_State;

	typedef Ensenso_State Ensenso_SkeletonTracingState;


	/// <summary>Captures a frame using Ensenso.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">Initial grab parameters. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">Initial calibration file. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">Initial global parameters. Default value: atl::NIL.</param>
	/// <param name="outGrid">Captured Grid.</param>
	/// <param name="outImage">Captured Image, when configured to do so.</param>
	/// <param name="outTimestamp">Captured Grid timestamp.</param>
	AVL_FUNCTION bool Ensenso_GrabPoint3DGrid
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>	inDeviceID,			
		const atl::Optional<atl::File>&		inSettingsFile,		
		const atl::Optional<atl::File>&		inCalibrationFile,	
		const atl::Optional<atl::File>&		inParametersFile,	
		avl::Point3DGrid&					outGrid,			
		atl::Conditional<avl::Image>&		outImage,			
		double&								outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using Ensenso.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">Initial global parameters. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outGrid">Captured Grid.</param>
	/// <param name="outImage">Captured Image, when configured to do so.</param>
	/// <param name="outTimestamp">Captured Grid timestamp.</param>
	AVL_FUNCTION bool Ensenso_GrabPoint3DGrid_WithTimeout
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>	inDeviceID,			
		const atl::Optional<atl::File>&		inSettingsFile,		
		const atl::Optional<atl::File>&		inCalibrationFile,	
		const atl::Optional<atl::File>&		inParametersFile,	
		int									inTimeout,			
		atl::Conditional<avl::Point3DGrid>&	outGrid,			
		atl::Conditional<avl::Image>&		outImage,			
		atl::Conditional<double>&			outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using Ensenso.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">Initial grab parameters. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">Initial calibration file. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">Initial global parameters. Default value: atl::NIL.</param>
	/// <param name="outSurface">Captured Surface.</param>
	/// <param name="outImage">Captured Image, when configured to do so.</param>
	/// <param name="outTimestamp">Captured timestamp.</param>
	AVL_FUNCTION bool Ensenso_GrabSurface
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>	inDeviceID,			
		const atl::Optional<atl::File>&		inSettingsFile,		
		const atl::Optional<atl::File>&		inCalibrationFile,	
		const atl::Optional<atl::File>&		inParametersFile,	
		avl::Surface&						outSurface,			
		atl::Conditional<avl::Image>&		outImage,			
		double&								outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using Ensenso.</summary>
	/// <param name="inDeviceID">Device identifying number. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">Initial global parameters. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="outSurface">Captured Surface.</param>
	/// <param name="outImage">Captured Image, when configured to do so.</param>
	/// <param name="outTimestamp">Captured timestamp.</param>
	AVL_FUNCTION bool Ensenso_GrabSurface_WithTimeout
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>	inDeviceID,			
		const atl::Optional<atl::File>&		inSettingsFile,		
		const atl::Optional<atl::File>&		inCalibrationFile,	
		const atl::Optional<atl::File>&		inParametersFile,	
		int									inTimeout,			
		atl::Conditional<avl::Surface>&		outSurface,			
		atl::Conditional<avl::Image>&		outImage,			
		atl::Conditional<double>&			outTimestamp		
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts capturing images from an Ensenso camera.</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">Initial JSON encoded parameters for camera. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">Initial global parameters. Default value: atl::NIL.</param>
	/// <param name="inSoftwareTriggered">When true, capture will wait for GenerateSoftwareTrigger. Default value: False.</param>
	AVL_FUNCTION void Ensenso_StartAcquisition
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>	inDeviceID,	
		const atl::Optional<atl::File>&		inSettingsFile,		
		const atl::Optional<atl::File>&		inCalibrationFile,	
		const atl::Optional<atl::File>&		inParametersFile,	
		const bool							inSoftwareTriggered	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stop image acquisition in a Ensenso device.</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	AVL_FUNCTION void Ensenso_StopAcquisition
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID	
	)
	THROW_AVL_ERRORS;

	/// <summary>Load calibration data from a file</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inCalibrationFile">JSON encoded parameters for camera.</param>
	AVL_FUNCTION void Ensenso_LoadCalibration
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,			
		const atl::File&					inCalibrationFile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Load parameters data from a file</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inSettingsFile">JSON encoded parameters for camera.</param>
	AVL_FUNCTION void Ensenso_LoadSettings
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		const atl::File&					inSettingsFile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Load global parameters data from a file</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inParametersFile">JSON encoded parameters for camera.</param>
	AVL_FUNCTION void Ensenso_LoadGlobalParameters
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,		
		const atl::File&					inParametersFile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Set bool parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_SetParameter_Bool
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		const bool							inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Set int parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_SetParameter_Int
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		const int							inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Set double parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_SetParameter_Double
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		const double						inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Set string parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_SetParameter_String
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		const atl::String&					inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get bool parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_GetParameter_Bool
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		bool&								outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get int parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_GetParameter_Int
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		int&								outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get double parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_GetParameter_Double
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		double&								outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get string parameter</summary>
	/// <param name="inDeviceID">Device identifying string. Default value: atl::NIL.</param>
	/// <param name="inPath">Configuration path, relative.</param>
	/// <param name="inGlobal">true: Path is relative to global configuration root; false: relative to camera configuration. Default value: False.</param>
	AVL_FUNCTION void Ensenso_GetParameter_String
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID,	
		const atl::String&					inPath,		
		const bool							inGlobal,	
		atl::String&						outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Triggers software trigger</summary>
	AVL_FUNCTION void Ensenso_GenerateSoftwareTrigger
	(
		Ensenso_State&						ioState,
		const atl::Optional<atl::String>&	inDeviceID
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_ENSENSO_H

