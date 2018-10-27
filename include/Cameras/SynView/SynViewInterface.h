//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef SYNVIEW_KIT_INTERFACE_H
#define SYNVIEW_KIT_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Basic/Types.h"
#include "Image/Image.h"
#include "SynViewEnums.h"
#include "SynViewParameters.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	class SynViewInterface
	{
	public:
		virtual ~SynViewInterface() {}

		virtual void BindToNamedCamera( const atl::String& sName ) = 0;
		virtual void BindToFirstCamera( void ) = 0;

		virtual void SetAnalogParams( const SynViewAnalogParams& analogParameters ) = 0;
		
		virtual void SetFormatParams( const SynViewImageFormatParams& formatParameters ) = 0;

		virtual void SetAcquisitionParams(	const SynViewAcquisitionParams& acquisitionParameters ) = 0;


		virtual void GenerateSoftwareTrigger() = 0;

		virtual void Start( avl::SynViewColorFormat::Type inColorFormat ) = 0;
		virtual void Stop( void ) = 0;

		virtual bool GrabImage( atl::Optional<int> inTimeout, avl::Image& outImage ) = 0;
		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;

		//DigitalOutputs Functions
		virtual void SetUserOutput(SynViewUserOutputs::Type inUserOutput, bool inValue) = 0;
		virtual void GetDigitalIOState( int inLineNumber, bool& outState) = 0;
		virtual void ConfigureDigitalIO(int	inLineNumber, atl::Optional<bool> inLineInverter, 
			atl::Optional<float> inLineDebounceDuration, atl::Optional<SynViewLineSource::Type> inLineSource) = 0;
		virtual void ConfigureTimer(SynViewTimerSelector::Type inTimerSelector, int inTimerDuration, int inTimerDelay, avl::SynViewTimerTriggerSource::Type inTimerTriggerSource) = 0;

		virtual void ConfigureStrobe( avl::SynViewStrobeEnable::Type strobeEnable, float duration, float delay ) = 0;

		virtual void SetBoolParameter( const atl::String& inName, bool inValue ) = 0;
		virtual void SetRealParameter( const atl::String& inName, float inValue ) = 0;
		virtual void SetIntegerParameter( const atl::String& inName, int inValue ) = 0;
		virtual void SetEnumParameter( const atl::String& inName, const atl::String& inValue ) = 0;
		virtual void SetStringParameter( const atl::String& inName, const atl::String& inValue ) = 0;

		virtual void GetBoolParameter( const atl::String& inName, bool& outValue ) = 0;
		virtual void GetRealParameter( const atl::String& inName, float& outValue ) = 0;
		virtual void GetIntegerParameter( const atl::String& inName, int& outValue ) = 0;
		virtual void GetEnumParameter( const atl::String& inName, atl::String& outValue ) = 0;
		virtual void GetStringParameter( const atl::String& inName, atl::String& outValue ) = 0;

		virtual void ExecuteCommand( const atl::String& inName ) = 0;
	};
}

#endif // SYNVIEW_KIT_INTERFACE_H
