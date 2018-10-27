//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef SYNVIEW_PARAMETERS_H
#define SYNVIEW_PARAMETERS_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "SynViewEnums.h"

namespace avl
{

	struct SynViewImageFormatParams
	{
		SynViewImageFormatParams()
			: aoi(atl::NIL)
			, horizontalBinning(atl::NIL)
			, verticalBinning(atl::NIL)
			, horizontalDecimation(atl::NIL)
			, verticalDecimation(atl::NIL)
			, reverseX(atl::NIL)
			, reverseY(atl::NIL)
		{}

		SynViewImageFormatParams
		(
			atl::Optional<avl::Box> _aoi,
			atl::Optional<int>	_horizontalBinning,
			atl::Optional<int>	_verticalBinning,
			atl::Optional<int>	_horizontalDecimation,
			atl::Optional<int>	_verticalDecimation,
			atl::Optional<bool> _reverseX,
			atl::Optional<bool> _reverseY
		)
			: aoi(_aoi)
			, horizontalBinning(_horizontalBinning)
			, verticalBinning(_verticalBinning)
			, horizontalDecimation(_horizontalDecimation)
			, verticalDecimation(_verticalDecimation)
			, reverseX(_reverseX)
			, reverseY(_reverseY)
		{}

		atl::Optional<avl::Box> Aoi( void )				const	{ return aoi;					}
		atl::Optional<int> HorizontalBinning( void )	const	{ return horizontalBinning;		}
		atl::Optional<int> VerticalBinning( void )		const	{ return verticalBinning;		}
		atl::Optional<int> HorizontalDecimation( void ) const	{ return horizontalDecimation;	}
		atl::Optional<int> VerticalDecimation( void )	const	{ return verticalDecimation;	}
		atl::Optional<bool> ReverseX( void )			const	{ return reverseX;				}
		atl::Optional<bool> ReverseY( void )			const	{ return reverseY;				}


		bool operator == ( const avl::SynViewImageFormatParams& rhs ) const
		{
			return aoi == rhs.aoi && horizontalBinning == rhs.horizontalBinning && verticalBinning == rhs.verticalBinning
				&& horizontalDecimation == rhs.horizontalDecimation && verticalDecimation == rhs.verticalDecimation
				&& reverseX == rhs.reverseX && reverseY == rhs.reverseY;
		}

		bool operator != ( const avl::SynViewImageFormatParams& rhs ) const
		{
			return !(operator==(rhs));
		}

		atl::Optional<avl::Box> aoi;
		atl::Optional<int>	horizontalBinning;
		atl::Optional<int>	verticalBinning;
		atl::Optional<int>	horizontalDecimation;
		atl::Optional<int>	verticalDecimation;
		atl::Optional<bool> reverseX;
		atl::Optional<bool> reverseY;
	};

	struct SynViewAcquisitionParams
	{
		SynViewAcquisitionParams()
			: triggerSource(atl::NIL)
			, triggerActivation(atl::NIL)
			, exposureTime(atl::NIL)
			, exposureAutoMode(atl::NIL)
			, frameRate(atl::NIL)
		{}

		SynViewAcquisitionParams
		(
			atl::Optional<avl::SynViewTriggerSource::Type>		_triggerSource,
			atl::Optional<avl::SynViewTriggerActivation::Type>	_triggerActivation,
			atl::Optional<float>							_exposureTime,
			atl::Optional<avl::SynViewAutoMode::Type>			_exposureAutoMode,
			atl::Optional<float>							_frameRate
		)
			: triggerSource(_triggerSource)
			, triggerActivation(_triggerActivation)
			, exposureTime(_exposureTime)
			, exposureAutoMode(_exposureAutoMode)
			, frameRate(_frameRate)
		{}

		atl::Optional<avl::SynViewTriggerSource::Type>		TriggerSource( void )		const	{ return triggerSource;		}
		atl::Optional<avl::SynViewTriggerActivation::Type>	TriggerActivation( void )	const	{ return triggerActivation; }
		atl::Optional<float>							ExposureTime( void )		const	{ return exposureTime;		}
		atl::Optional<avl::SynViewAutoMode::Type>			ExposureAutoMode( void )	const	{ return exposureAutoMode;	}
		atl::Optional<float>							FrameRate( void )			const	{ return frameRate;			}

		bool operator == ( const avl::SynViewAcquisitionParams& rhs ) const
		{
			return triggerSource == rhs.triggerSource && triggerActivation == rhs.triggerActivation 
				&& exposureTime == rhs.exposureTime	&& exposureAutoMode == rhs.exposureAutoMode && frameRate == rhs.frameRate;
		}

		bool operator != ( const avl::SynViewAcquisitionParams& rhs ) const
		{
			return !(operator==(rhs));
		}

		atl::Optional<avl::SynViewTriggerSource::Type>		triggerSource;
		atl::Optional<avl::SynViewTriggerActivation::Type>	triggerActivation;
		atl::Optional<float>							exposureTime;
		atl::Optional<avl::SynViewAutoMode::Type>			exposureAutoMode;
		atl::Optional<float>							frameRate;
	};

	struct SynViewAnalogParams
	{
		SynViewAnalogParams()
			: gain(atl::NIL)
			, blackLevel(atl::NIL)
			, blackLevelAuto(atl::NIL)
		{}

		SynViewAnalogParams
		(
			atl::Optional<float> _gain,
			atl::Optional<float> _blackLevel,
			atl::Optional<avl::SynViewAutoMode::Type>  _blackLevelAuto
		)
			: gain(_gain)
			, blackLevel(_blackLevel)
			, blackLevelAuto(_blackLevelAuto)
		{}

		atl::Optional<float>					Gain( void )			const	{ return gain;			 }
		atl::Optional<float>					BlackLevel( void )		const	{ return blackLevel;	 }
		atl::Optional<avl::SynViewAutoMode::Type>	BlackLevelAuto( void )	const	{ return blackLevelAuto; }

		bool operator == ( const avl::SynViewAnalogParams& rhs ) const
		{
			return gain == rhs.gain && blackLevel == rhs.blackLevel && blackLevelAuto == rhs.blackLevelAuto;
		}

		bool operator != ( const avl::SynViewAnalogParams& rhs ) const
		{
			return !(operator==(rhs));
		}

		atl::Optional<float> gain;
		atl::Optional<float> blackLevel;
		atl::Optional<avl::SynViewAutoMode::Type>  blackLevelAuto;
	};

}

#endif