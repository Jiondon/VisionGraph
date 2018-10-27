//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef POINT_GREY_KIT_INTERFACE_H
#define POINT_GREY_KIT_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"
#include "PointGreyEnums.h" //:PUBLIC
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	class PointGreyInterface
	{
	public:
		virtual ~PointGreyInterface() {}

		virtual void BindToNamedCamera( unsigned int inSerialNumber ) = 0;
		virtual void BindToFirstCamera( void ) = 0;
		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;

		virtual void SetParams( PointGreyColorMode::Type inColorMode, atl::Optional<const avl::Box&> inAoi, atl::Optional<float> inShutter,
			atl::Optional<float> inGain, atl::Optional<float> inExposure, atl::Optional<float> inFrameRate, PointGreyTriggerMode::Type triggerMode ) = 0;

		virtual void SetStrobe( int source, bool enabled, int polarity, float delay, float duration ) = 0;

		virtual void StartAcquisition( void ) = 0;
		virtual void StopAcquisition( void ) = 0;

		virtual bool GrabImage( atl::Optional<int> inTimeout, avl::Image& outImage ) = 0;
	};
}

#endif // POINT_GREY_KIT_INTERFACE_H
