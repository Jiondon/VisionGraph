//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GOCATOR_H
#define AVL_GOCATOR_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Gocator/GocatorEnums.h"
#include "Cameras/Gocator/GocatorInterface.h"
#include "Geometry/Geometry.h"

namespace avl
{


	struct Gocator_State : public BaseState
	{
		IGocatorInterface* iGocator;
		atl::Optional<avl::GocatorAddress> deviceId;

		Gocator_State()
			: iGocator(nullptr)
		{}

		IGocatorInterface* operator->() const
		{
			return iGocator;
		}

		~Gocator_State()
		{
			delete iGocator;
		}

	private:
		Gocator_State(const Gocator_State&); //=delete
		Gocator_State& operator=(const Gocator_State&); //=delete
	};


	/// <summary>Initializes and starts image acquisition in a Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTriggerSource">Configure Gocator trigger source. Default value: atl::NIL.</param>
	AVL_FUNCTION void Gocator_StartAcquisition
	(
		Gocator_State&									ioState,
		const atl::Optional<avl::GocatorAddress>&		inAddress,			
		int												inInputQueueSize,	
		atl::Optional<avl::GocatorTriggerSource::Type>	inTriggerSource		
	)
	THROW_AVL_ERRORS;

	/// <summary>Stop image acquisition in a Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	AVL_FUNCTION void Gocator_StopAcquisition
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress			
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Point3DGrid (Un-Resampled surface) from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	AVL_FUNCTION bool Gocator_GrabPoint3DGrid
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		avl::Point3DGrid&							outPoint3DGrid,
		atl::Conditional<avl::Image>&				outSurfaceIntensity,
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Point3DGrid (Un-Resampled surface) from Gocator device with timeout; returns Nil if no data comes in the specified time.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Maximum time to wait for data in milliseconds. Default value: 100.</param>
	AVL_FUNCTION bool Gocator_GrabPoint3DGrid_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,			
		atl::Conditional<avl::Point3DGrid>&			outPoint3DGrid,
		atl::Conditional<avl::Image>&				outSurfaceIntensity,
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Surface from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	AVL_FUNCTION bool Gocator_GrabSurface
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		avl::Surface&								outSurface,
		atl::Conditional<avl::Image>&				outSurfaceIntensity,
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Surface from Gocator device with timeout; returns Nil if no data comes in the specified time.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Maximum time to wait for data in milliseconds. Default value: 100.</param>
	AVL_FUNCTION bool Gocator_GrabSurface_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,			
		atl::Conditional<avl::Surface>&				outSurface,
		atl::Conditional<avl::Image>&				outSurfaceIntensity,
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="outImage1">First output image.</param>
	/// <param name="outImage2">Second output image.</param>
	AVL_FUNCTION bool Gocator_GrabImages
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		avl::Image&									outImage1,
		avl::Image&									outImage2,
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures images from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Maximum time to wait for data in milliseconds. Default value: 100.</param>
	/// <param name="outImage1">First output image.</param>
	/// <param name="outImage2">Second output image.</param>
	AVL_FUNCTION bool Gocator_GrabImages_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,			
		atl::Conditional<avl::Image>&				outImage1,
		atl::Conditional<avl::Image>&				outImage2,
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures profile from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="outXScale">X scale in mm.</param>
	/// <param name="outXOffset">X offset in mm.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabProfile
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		atl::Array<avl::Point2D>&					outProfileData,
		atl::Conditional<avl::Profile>&				outProfileIntensity,
		atl::real&									outXScale,			
		atl::real&									outXOffset,			
		atl::real&									outZScale,			
		atl::real&									outZOffset,			
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures profile from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Default value: 100.</param>
	/// <param name="outXScale">X scale in mm.</param>
	/// <param name="outXOffset">X offset in mm.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabProfile_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,
		atl::Conditional<atl::Array<avl::Point2D>>&	outProfileData,
		atl::Conditional<avl::Profile>&				outProfileIntensity,
		atl::Conditional<atl::real>&				outXScale,			
		atl::Conditional<atl::real>&				outXOffset,			
		atl::Conditional<atl::real>&				outZScale,			
		atl::Conditional<atl::real>&				outZOffset,			
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures uniform profile from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabUniformProfile
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		avl::Profile&								outProfileData,
		atl::Conditional<avl::Profile>&				outProfileIntensity,
		atl::real&									outZScale,			
		atl::real&									outZOffset,			
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures uniform profile from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Default value: 100.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabUniformProfile_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,
		atl::Conditional<avl::Profile>&				outProfileData,
		atl::Conditional<avl::Profile>&				outProfileIntensity,
		atl::Conditional<atl::real>&				outZScale,			
		atl::Conditional<atl::real>&				outZOffset,			
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Section from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="outXScale">X scale in mm.</param>
	/// <param name="outXOffset">X offset in mm.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabSection
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inSectionID,
		atl::Array<avl::Point2D>&					outSectionData,
		atl::Conditional<avl::Profile>&				outSectionIntensity,
		atl::real&									outXScale,			
		atl::real&									outXOffset,			
		atl::real&									outZScale,			
		atl::real&									outZOffset,			
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Section from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Default value: 100.</param>
	/// <param name="outXScale">X scale in mm.</param>
	/// <param name="outXOffset">X offset in mm.</param>
	/// <param name="outZScale">Z scale in mm.</param>
	/// <param name="outZOffset">Z offset in mm.</param>
	AVL_FUNCTION bool Gocator_GrabSection_WithTimeout
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inTimeout,
		int											inSectionID,
		atl::Conditional<atl::Array<avl::Point2D>>&	outSectionData,
		atl::Conditional<avl::Profile>&				outSectionIntensity,
		atl::Conditional<atl::real>&				outXScale,			
		atl::Conditional<atl::real>&				outXOffset,			
		atl::Conditional<atl::real>&				outZScale,			
		atl::Conditional<atl::real>&				outZOffset,			
		atl::Conditional<avl::GocatorFrameInfo>&	outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Measurement data from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	AVL_FUNCTION bool Gocator_GrabMeasurement
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		int											inInputQueueSize,	
		int											inMeasurementID,
		double&										outValue,
		bool&										outDecision,
		avl::GocatorDecisionCode::Type&				outDecisionCode,
		avl::GocatorFrameInfo&						outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures Measurement data from Gocator device.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inInputQueueSize">Number of incoming frames that can be buffered before the application is able to process them.</param>
	/// <param name="inTimeout">Default value: 100.</param>
	AVL_FUNCTION bool Gocator_GrabMeasurement_WithTimeout
	(
		Gocator_State&										ioState,
		const atl::Optional<avl::GocatorAddress>&			inAddress,			
		int													inInputQueueSize,	
		int													inTimeout,
		int													inMeasurementID,
		atl::Conditional<atl::real64>&						outValue,
		atl::Conditional<bool>&								outDecision,
		atl::Conditional<avl::GocatorDecisionCode::Type>&	outDecisionCode,
		atl::Conditional<avl::GocatorFrameInfo>&			outFrameInfo
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads new job.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="inJobName">Job name. The name must end with: ".job".</param>
	AVL_FUNCTION void Gocator_LoadJob
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		const atl::String&							inJobName			
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads current job name.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="outJobName">Current Job name.</param>
	AVL_FUNCTION void Gocator_GetCurrentJobName
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		atl::String&								outJobName			
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates software trigger.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	AVL_FUNCTION void Gocator_GenerateSoftwareTrigger
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress			
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets current trigger source.</summary>
	/// <param name="inAddress">Gocator Device identifying IP address (e.g. "127.0.0.1") or serial number (e.g. "SN:17335"). Default value: atl::NIL.</param>
	/// <param name="outTriggerSource">Current trigger source.</param>
	AVL_FUNCTION void Gocator_GetTriggerSource
	(
		Gocator_State&								ioState,
		const atl::Optional<avl::GocatorAddress>&	inAddress,			
		avl::GocatorTriggerSource::Type&			outTriggerSource	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a string to a Gocator device address.</summary>
	AVL_FUNCTION void StringToGocatorAddress
	(
		const atl::String&		inString,
		avl::GocatorAddress&	outAddress
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a Gocator device address to a String.</summary>
	AVL_FUNCTION void GocatorAddressToString
	(
		const avl::GocatorAddress&	intAddress,
		atl::String&				outString
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GOCATOR_H

