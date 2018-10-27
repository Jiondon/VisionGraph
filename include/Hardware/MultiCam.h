//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MULTICAM_H
#define AVL_MULTICAM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Hardware/MultiCam/MultiCamInterface.h"

namespace avl
{


	
	struct MultiCam_State : public BaseState
	{
		MultiCamInterface* multiCam;

		MultiCam_State()
			: multiCam(nullptr)
		{
		}

		~MultiCam_State()
		{
			delete multiCam;
		}

		MultiCamInterface* operator->()
		{
			return multiCam;
		}

	private:
		MultiCam_State(const MultiCam_State&); //=delete
		MultiCam_State& operator=(const MultiCam_State&); //=delete
	};



	/// <summary>Captures a frame using Euresys frame grabber.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inTopology">Board topology. Default value: atl::NIL.</param>
	/// <param name="inCameraTapConfiguration">Tap configuration of camera. Default value: atl::NIL.</param>
	/// <param name="inConnector">Indication of connector used by channel.</param>
	/// <param name="inAcquisitionMode">Acquisition Mode.</param>
	/// <param name="inCameraFile">Camera configuration file. Default value: atl::NIL.</param>
	/// <param name="inPageLengthLn">Page Length. Default value: atl::NIL.</param>
	/// <param name="inColorFormat">Color format.</param>
	/// <param name="inGain">Linear control of gain for all digitizing units. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool MultiCam_GrabImage
	(
		MultiCam_State&						ioState,
		atl::Optional<atl::String>			inDeviceID,					
		atl::Optional<atl::String>			inTopology,					
		atl::Optional<atl::String>			inCameraTapConfiguration,	
		const atl::String&					inConnector,				
		avl::MultiCamAcquisitionMode::Type	inAcquisitionMode,			
		atl::Optional<const atl::File&>		inCameraFile,				
		atl::Optional<int>					inPageLengthLn,				
		avl::MultiCamColorFormat::Type		inColorFormat,				
		atl::Optional<int>					inGain,						
		avl::Image&							outImage					
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a frame using Euresys frame grabber.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inTopology">Board topology. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Timeout in milliseconds. Default value: atl::NIL.</param>
	/// <param name="inCameraTapConfiguration">Tap configuration of camera. Default value: atl::NIL.</param>
	/// <param name="inConnector">Indication of connector used by channel.</param>
	/// <param name="inAcquisitionMode">Acquisition Mode.</param>
	/// <param name="inCameraFile">Camera configuration file. Default value: atl::NIL.</param>
	/// <param name="inPageLengthLn">Page Length. Default value: atl::NIL.</param>
	/// <param name="inColorFormat">Color format.</param>
	/// <param name="inGain">Linear control of gain for all digitizing units. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool MultiCam_GrabImage_WithTimeout
	(
		MultiCam_State&							ioState,
		atl::Optional<atl::String>				inDeviceID,					
		atl::Optional<atl::String>				inTopology,					
		atl::Optional<int>						inTimeout,					
		atl::Optional<atl::String>				inCameraTapConfiguration,	
		const atl::String&						inConnector,				
		avl::MultiCamAcquisitionMode::Type		inAcquisitionMode,			
		atl::Optional<const atl::File&>			inCameraFile,				
		atl::Optional<int>						inPageLengthLn,				
		avl::MultiCamColorFormat::Type			inColorFormat,				
		atl::Optional<int>						inGain,						
		atl::Conditional<avl::Image>&			outImage					
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads camera configuration file.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inTopology">Board topology. Default value: atl::NIL.</param>
	/// <param name="inConnector">Indication of connector used by channel.</param>
	/// <param name="inCameraFile">Camera configuration file. Default value: atl::NIL.</param>
	AVL_FUNCTION void MultiCam_LoadConfigurationFile
	(
		MultiCam_State&							ioState,
		atl::Optional<atl::String>				inDeviceID,		
		atl::Optional<atl::String>				inTopology,		
		const atl::String&						inConnector,	
		atl::Optional<const atl::File&>			inCameraFile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets digital output.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inOutput">Output pin index.</param>
	/// <param name="inOutputStyle">Controlling the electrical style of I/O lines used as outputs. If Nil then lease style as it is. Default value: atl::NIL.</param>
	/// <param name="inOutputState">Issuing the logic state of I/O lines used as outputs.</param>
	AVL_FUNCTION void MultiCam_SetDigitalOutput
	(
		MultiCam_State&											ioState,	
		atl::Optional<atl::String>								inDeviceID,		
		int														inOutput,		
		const atl::Optional<avl::MultiCamOutputStyle::Type>&	inOutputStyle,	
		avl::MultiCamOutputState::Type							inOutputState	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reporting the logic state of I/O lines used as inputs.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inInput">Input pin index.</param>
	/// <param name="inInputStyle">Controlling the electrical style of I/O lines used as inputs. If Nil then lease style as it is. Default value: atl::NIL.</param>
	/// <param name="outState">Returns the current logic state of I/O line.</param>
	AVL_FUNCTION void MultiCam_GetDigitalInput
	(
		MultiCam_State&											ioState,	
		atl::Optional<atl::String>								inDeviceID,		
		int														inInput,		
		const atl::Optional<avl::MultiCamInputStyle::Type>&		inInputStyle,	
		avl::MultiCamInputState::Type&							outState		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type integer into euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="inValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_SetIntegerParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		int									inValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type real into euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="inValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_SetRealParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		float							inValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String into euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="inValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_SetStringParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		const atl::String&					inValue				
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type integer from euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="outValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_GetIntegerParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		int&								outValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type real from euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="outValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_GetRealParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		float&							outValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String from euresys device.</summary>
	/// <param name="inDeviceID">Board name, board identifier or serial number. Default value: atl::NIL.</param>
	/// <param name="inConnector">Connector. Default value: atl::NIL.</param>
	/// <param name="inDestinationClass">Class where the value should be set ( board or channel ).</param>
	/// <param name="inName">Parameter name.</param>
	/// <param name="outValue">Parameter value.</param>
	AVL_FUNCTION void MultiCam_GetStringParameter
	(
		MultiCam_State&						ioState,	
		atl::Optional<atl::String>			inDeviceID,			
		atl::Optional<atl::String>			inConnector,		
		avl::MultiCamDestinationClass::Type	inDestinationClass, 
		const atl::String&					inName,				
		atl::String&						outValue			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MULTICAM_H

