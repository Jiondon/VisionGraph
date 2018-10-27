//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef VIMBA_PARAMETERS_H
#define VIMBA_PARAMETERS_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"

namespace avl
{

	namespace VimbaPixelFormat
	{
		enum Type
		{
			Mono8,
			Mono10,
			Mono12,
			Mono14,
			Mono16,
			RGB8,
			RGB12,
			RGB16,
			BayerGR8,
			BayerRG8,
			BayerGB8,
			BayerBG8
		};
	}
	
	namespace VimbaIIDCMode
	{
		enum Type
		{
			Mode0,
			Mode1,
			Mode2,
			Mode3,
			Mode4,
			Mode5,
			Mode6
		};
	}

	namespace VimbaExposureAuto
	{
		enum Type
		{
			Off,
			Once,
			Continuous
		};
	}

	namespace VimbaExposureMode
	{
		enum Type
		{
			Timed,
			TriggerWidth
		};
	}

	namespace VimbaTriggerActivation
	{
		enum Type
		{
			FallingEdge,
			RisingEdge
		};
	}

	namespace VimbaTriggerSelector
	{
		enum Type
		{
			ExposureStart,
			ExposureActive,
			AcquisitionStart
		};
	}

	struct VimbaImageFormatParams
	{
		VimbaImageFormatParams()
			: pixelFormat(atl::NIL)
			, aoi(atl::NIL)
			, iIDCMode(atl::NIL)
		{}

		VimbaImageFormatParams
		(
			atl::Optional<avl::VimbaPixelFormat::Type> _pixelFormat,
			atl::Optional<avl::Box> _aoi,
			atl::Optional<avl::VimbaIIDCMode::Type> _iidcMode
		)
			: pixelFormat(_pixelFormat)
			, aoi(_aoi)
			, iIDCMode(_iidcMode)
		{}

		atl::Optional<avl::VimbaPixelFormat::Type> PixelFormat( void )	const	{ return pixelFormat;	}
		atl::Optional<avl::Box> Aoi( void )								const	{ return aoi;			}
		atl::Optional<avl::VimbaIIDCMode::Type> IIDCMode( void )		const	{ return iIDCMode;		}


		bool operator == ( const avl::VimbaImageFormatParams& rhs ) const
		{
			return pixelFormat == rhs.pixelFormat && aoi == rhs.aoi && iIDCMode == rhs.iIDCMode;
		}

		bool operator != ( const avl::VimbaImageFormatParams& rhs ) const
		{
			return !(operator==(rhs));
		}
		
		atl::Optional<avl::VimbaPixelFormat::Type> pixelFormat;
		atl::Optional<avl::Box> aoi;
		atl::Optional<avl::VimbaIIDCMode::Type> iIDCMode;
	};

	struct VimbaAcquisitionControlParams
	{
		VimbaAcquisitionControlParams()
			: acquisitionFrameRate(atl::NIL) 
			, exposureAuto(atl::NIL)
			, exposureMode(atl::NIL)
			, exposureTime(atl::NIL)
			, triggerActivation(atl::NIL)
			, triggerDelay(atl::NIL)
			, triggerEnabled(atl::NIL)
			, triggerSelector(atl::NIL)
		{}

		VimbaAcquisitionControlParams
		(
			atl::Optional<float> _acquisitionFrameRate,
			atl::Optional<avl::VimbaExposureAuto::Type> _exposureAuto,
			atl::Optional<avl::VimbaExposureMode::Type> _exposureMode,
			atl::Optional<float> _exposureTime,
			atl::Optional<avl::VimbaTriggerActivation::Type> _triggerActivation,
			atl::Optional<float> _triggerDelay,
			atl::Optional<bool> _triggerEnabled,
			atl::Optional<avl::VimbaTriggerSelector::Type> _triggerSelector
		)
			: acquisitionFrameRate(_acquisitionFrameRate)
			, exposureAuto(_exposureAuto)
			, exposureMode(_exposureMode)
			, exposureTime(_exposureTime)
			, triggerActivation(_triggerActivation)
			, triggerDelay(_triggerDelay)
			, triggerEnabled(_triggerEnabled)
			, triggerSelector(_triggerSelector)
		{}

		atl::Optional<float> AcquisitionFrameRate( void )						const	{ return acquisitionFrameRate; }
		atl::Optional<avl::VimbaExposureAuto::Type> ExposureAuto( void )			const	{ return exposureAuto;	}
		atl::Optional<avl::VimbaExposureMode::Type> ExposureMode( void )			const	{ return exposureMode;	}
		atl::Optional<float> ExposureTime( void )								const	{ return exposureTime;	}
		atl::Optional<avl::VimbaTriggerActivation::Type> TriggerActivation( void )	const	{ return triggerActivation; }
		atl::Optional<float> TriggerDelay( void )								const	{ return triggerDelay; }
		atl::Optional<bool> TriggerEnabled( void )									const	{ return triggerEnabled; }	
		atl::Optional<avl::VimbaTriggerSelector::Type> TriggerSelector( void )		const	{ return triggerSelector; }


		bool operator == ( const avl::VimbaAcquisitionControlParams& rhs ) const
		{
			return acquisitionFrameRate == rhs.acquisitionFrameRate && exposureAuto == rhs.exposureAuto && exposureMode == rhs.exposureMode && exposureTime == rhs.exposureTime 
				&& triggerActivation == rhs.triggerActivation && triggerDelay == rhs.triggerDelay && triggerEnabled == rhs.triggerEnabled && triggerSelector == rhs.triggerSelector;
		}

		bool operator != ( const avl::VimbaAcquisitionControlParams& rhs ) const
		{
			return !(operator==(rhs));
		}
		
		atl::Optional<float> acquisitionFrameRate;
		atl::Optional<avl::VimbaExposureAuto::Type> exposureAuto;
		atl::Optional<avl::VimbaExposureMode::Type> exposureMode;
		atl::Optional<float> exposureTime;
		atl::Optional<avl::VimbaTriggerActivation::Type> triggerActivation;
		atl::Optional<float> triggerDelay;
		atl::Optional<bool> triggerEnabled;
		atl::Optional<avl::VimbaTriggerSelector::Type> triggerSelector;

	};
}

#endif //VIMBA_PARAMETERS_H