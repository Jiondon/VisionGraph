//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SPINNAKER_H
#define AVL_SPINNAKER_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Spinnaker/SpinnakerInterface.h"

namespace avl
{


	struct Spinnaker_State
	{
	public:
		SpinnakerInterface* spinnaker;

		Spinnaker_State()
			:spinnaker(nullptr)
		{}

		~Spinnaker_State()
		{
			delete spinnaker;
			spinnaker = nullptr;
		}

		SpinnakerInterface* operator->()
		{
			return spinnaker;
		}

	private:
		Spinnaker_State(const Spinnaker_State&);// = delete;
		Spinnaker_State& operator=(const Spinnaker_State&);// = delete;
	};


	/// <summary>Starts image acquisition.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inBufferCount">Number of image buffers. Default value: 10.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inExposureAuto">Sets the automatic exposure mode. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inFrameRateEnable">If enabled, inFrameRate can be used to manually control the frame rate. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate in Hertz. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Sets the automatic gain mode. Default value: atl::NIL.</param>
	/// <param name="inGain">Controls the amplification of the video signal in dB. Default value: atl::NIL.</param>
	AVL_FUNCTION void Spinnaker_StartAcquisition
	(
		Spinnaker_State&								ioState,
		const atl::Optional<atl::String>&				inDeviceSerialNumber,	
		int												inBufferCount,			
		atl::Optional<avl::SpinnakerPixelFormat::Type>	inPixelFormat,			
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inExposureAuto,			
		atl::Optional<double>							inExposureTime,			
		atl::Optional<bool>								inFrameRateEnable,		
		atl::Optional<double>							inFrameRate,			
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inGainAuto,				
		atl::Optional<double>							inGain					
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops image acquisition.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	AVL_FUNCTION void Spinnaker_StopAcquisition
	(
		Spinnaker_State&					ioState,
		const atl::Optional<atl::String>&	inDeviceSerialNumber	
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from a PointGrey camera using Spinnaker interface.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inBufferCount">Number of image buffers. Default value: 10.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inBayerConverter">Image bayer converter. Used only with Bayer pixel format.</param>
	/// <param name="inExposureAuto">Sets the automatic exposure mode. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inFrameRateEnable">If enabled, inFrameRate can be used to manually control the frame rate. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate in Hertz. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Sets the automatic gain mode. Default value: atl::NIL.</param>
	/// <param name="inGain">Controls the amplification of the video signal in dB. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool Spinnaker_GrabImage
	(
		Spinnaker_State&								ioState,
		const atl::Optional<atl::String>&				inDeviceSerialNumber,	
		int												inBufferCount,			
		atl::Optional<avl::SpinnakerPixelFormat::Type>	inPixelFormat,			
		avl::SpinnakerBayerConverter::Type				inBayerConverter,		
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inExposureAuto,			
		atl::Optional<double>							inExposureTime,			
		atl::Optional<bool>								inFrameRateEnable,		
		atl::Optional<double>							inFrameRate,			
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inGainAuto,				
		atl::Optional<double>							inGain,					
		avl::Image&										outImage,				
		atl::int64&										outFrameID,				
		atl::int64&										outTimestamp			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from a PointGrey camera using Spinnaker interface; returns Nil if no frame comes in the specified time.</summary>
	/// <param name="inDeviceSerialNumber">Source device serial number. Default value: atl::NIL.</param>
	/// <param name="inTimeout">Maximum time to wait for frame in milliseconds. Default value: 100.</param>
	/// <param name="inBufferCount">Number of image buffers. Default value: 10.</param>
	/// <param name="inPixelFormat">Image pixel format. Default value: atl::NIL.</param>
	/// <param name="inBayerConverter">Image bayer converter. Used only with Bayer pixel format.</param>
	/// <param name="inExposureAuto">Sets the automatic exposure mode. Default value: atl::NIL.</param>
	/// <param name="inExposureTime">Exposure time in microseconds. Default value: atl::NIL.</param>
	/// <param name="inFrameRateEnable">If enabled, inFrameRate can be used to manually control the frame rate. Default value: atl::NIL.</param>
	/// <param name="inFrameRate">Frame rate in Hertz. Default value: atl::NIL.</param>
	/// <param name="inGainAuto">Sets the automatic gain mode. Default value: atl::NIL.</param>
	/// <param name="inGain">Controls the amplification of the video signal in dB. Default value: atl::NIL.</param>
	/// <param name="outImage">Captured frame.</param>
	/// <param name="outFrameID">Captured frame ID.</param>
	/// <param name="outTimestamp">Captured frame timestamp.</param>
	AVL_FUNCTION bool Spinnaker_GrabImage_WithTimeout
	(
		Spinnaker_State&								ioState,
		const atl::Optional<atl::String>&				inDeviceSerialNumber,	
		int												inTimeout,				
		int												inBufferCount,			
		atl::Optional<avl::SpinnakerPixelFormat::Type>	inPixelFormat,			
		avl::SpinnakerBayerConverter::Type				inBayerConverter,		
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inExposureAuto,			
		atl::Optional<double>							inExposureTime,			
		atl::Optional<bool>								inFrameRateEnable,		
		atl::Optional<double>							inFrameRate,			
		atl::Optional<avl::SpinnakerAutoSettings::Type>	inGainAuto,				
		atl::Optional<double>							inGain,					
		atl::Conditional<avl::Image>&					outImage,				
		atl::Conditional<atl::int64>&					outFrameID,				
		atl::Conditional<atl::int64>&					outTimestamp			
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Bool.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetBoolParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inValue,		
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Integer.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetIntegerParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		int									inValue,		
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Real.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetRealParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		float								inValue,		
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type String.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetStringParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue,		
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets parameter of type Enum.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of feature parameter.</param>
	/// <param name="inValue">New value to be set into device parameter.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetEnumParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		const atl::String&					inValue,		
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Executes command in GenICam device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inCommandName">Name of command node to access.</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_ExecuteCommand
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inCommandName,	
		bool								inVerify		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets user output value.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inUserOutputSelector">Selects which bit of the User Output register is set by UserOutputValue.</param>
	/// <param name="inValue">Value of the selected user output, either logic high (enabled) or logic low (disabled).</param>
	/// <param name="inVerify">Enables AccessMode and Range verification (default = true). Default value: True.</param>
	AVL_FUNCTION void Spinnaker_SetUserOutput
	(
		Spinnaker_State&				ioState,
		atl::Optional<atl::String>&		inDeviceID,				
		int								inUserOutputSelector,	
		bool							inValue,				
		bool							inVerify				
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Bool from Spinnaker device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter node to access.</param>
	/// <param name="inVerify">Enables Range verification.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Spinnaker_GetBoolParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inVerify,		
		bool								inIgnoreCache,	
		bool&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Integer from Spinnaker device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter node to access.</param>
	/// <param name="inVerify">Enables Range verification.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Spinnaker_GetIntegerParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inVerify,		
		bool								inIgnoreCache,	
		int&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Real from Spinnaker device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter node to access.</param>
	/// <param name="inVerify">Enables Range verification.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Spinnaker_GetRealParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inVerify,		
		bool								inIgnoreCache,	
		float&								outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type String from Spinnaker device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter node to access.</param>
	/// <param name="inVerify">Enables Range verification.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Spinnaker_GetStringParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inVerify,		
		bool								inIgnoreCache,	
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets parameter of type Enumeration from Spinnaker device.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inParameterName">Name of parameter node to access.</param>
	/// <param name="inVerify">Enables Range verification.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outValue">Value retrieved from device parameter.</param>
	AVL_FUNCTION void Spinnaker_GetEnumParameter
	(
		Spinnaker_State&					ioState,
		atl::Optional<atl::String>&			inDeviceID,		
		const atl::String&					inParameterName,
		bool								inVerify,		
		bool								inIgnoreCache,	
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads line status.</summary>
	/// <param name="inDeviceID">Device identifying address. Default value: atl::NIL.</param>
	/// <param name="inLineSelector">Selects which bit of the User Output register is set by UserOutputValue.</param>
	/// <param name="inVerify">Enables Range verification. Default value: True.</param>
	/// <param name="inIgnoreCache">If true the value is read ignoring any caches.</param>
	/// <param name="outStatus">Returns the current status of the selected input or output Line.</param>
	AVL_FUNCTION void Spinnaker_GetLineStatus
	(
		Spinnaker_State&				ioState,
		atl::Optional<atl::String>&		inDeviceID,		
		int								inLineSelector,	
		bool							inVerify,		
		bool							inIgnoreCache,	
		bool&							outStatus		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SPINNAKER_H

