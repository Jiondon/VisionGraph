//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_VIMBA_H
#define AVL_VIMBA_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Vimba/VimbaInterface.h"

namespace avl
{


	struct Vimba_State : public BaseState
	{
		VimbaInterface* vimba;

		Vimba_State()
			: vimba(nullptr)
		{
		}

		~Vimba_State()
		{
			delete vimba;
		}

	private:
		Vimba_State(const Vimba_State&); //=delete
		Vimba_State& operator=(const Vimba_State&); //=delete
	};



	/// <summary>Captures an image from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Vimba_GrabImage
	(
		Vimba_State&								ioState,
		atl::Optional<const atl::String&>			inDeviceID,				
		const avl::VimbaImageFormatParams&			inImageFormat,			
		const avl::VimbaAcquisitionControlParams&	inAcquisitionControl,	
		avl::Image&									outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures an image from an Allied Vision camera; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 5000.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool Vimba_GrabImage_WithTimeout
	(
		Vimba_State&								ioState,
		atl::Optional<const atl::String&>			inDeviceID,				
		int											inTimeout,				
		const avl::VimbaImageFormatParams&			inImageFormat,			
		const avl::VimbaAcquisitionControlParams&	inAcquisitionControl,	
		atl::Conditional<avl::Image>&				outImage				
	)
	THROW_AVL_ERRORS;

	/// <summary>Starts capturing images from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inImageFormat">Image format parameters.</param>
	/// <param name="inAcquisitionControl">Acquisition control parameters.</param>
	AVL_FUNCTION void Vimba_StartAcquisition
	(
		Vimba_State&								ioState,
		atl::Optional<const atl::String&>			inDeviceID,				
		const avl::VimbaImageFormatParams&			inImageFormat,			
		const avl::VimbaAcquisitionControlParams&	inAcquisitionControl	
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type Bool into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Vimba_SetBoolParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool								inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type Real into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Vimba_SetRealParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float							inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type Integer into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Vimba_SetIntegerParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int									inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type Enumeration into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Vimba_SetEnumParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a parameter of type String into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	AVL_FUNCTION void Vimba_SetStringParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a parameter of type Bool from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Vimba_GetBoolParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		bool&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a parameter of type Real from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Vimba_GetRealParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		float&							outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a parameter of type Integer from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Vimba_GetIntegerParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a parameter of type Enumeration from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Vimba_GetEnumParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a parameter of type String from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Vimba_GetStringParameter
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		const atl::String&					inParameterName,
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a digital output state into an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inLineNumber">Line number to change state.</param>
	/// <param name="inState">State to set.</param>
	AVL_FUNCTION void Vimba_SetDigitalOutput
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		int									inLineNumber,	
		bool								inState			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a digital input state from an Allied Vision camera.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inLineNumber">Line number to get state.</param>
	/// <param name="outState">State of selected line.</param>
	AVL_FUNCTION void Vimba_GetDigitalInput
	(
		Vimba_State&						ioState,
		atl::Optional<const atl::String&>	inDeviceID,		
		int									inLineNumber,	
		bool&								outState		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_VIMBA_H

