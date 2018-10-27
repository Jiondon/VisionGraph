//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef THORLABS_INTERFACE_H
#define THORLABS_INTERFACE_H

#include "Basic/Types.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace ThorlabsTriggerPolarity
	{
		enum Type
		{
			ACTIVE_HIGH,
			ACTIVE_LOW
		};
	}

	namespace ThorlabsReadoutSpeed
	{
		enum Type
		{
			_20_MHz = 0,
			_40_MHz = 1
		};
	}

	namespace ThorlabsTaps
	{
		enum Type
		{
			_1 = 0,
			_2 = 1,
			_4 = 2
		};
	}

	class ThorLabsInterface
	{
	public:
		virtual ~ThorLabsInterface() {};

		virtual void BindToCamera(atl::Optional<const atl::String&> inDeviceID) = 0;
		virtual void StartAcquisition(atl::Optional<int> inInputQueueSize) = 0;
		virtual void StopAcquisition() = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, atl::Optional<int> inInputQueueSize, avl::Image& outImage, int& outFrameID) = 0;

		virtual void SetCancellationObject(avl::ICancellationProvider* workCancellation) = 0;

		virtual void SetParameter_Integer(const atl::String& inParameterName, int inParameterValue) = 0;
		virtual void SetParameter_Real(const atl::String& inParameterName, float inParameterValue) = 0;
		virtual void SetParameter_Bool(const atl::String& inParameterName, bool inParameterValue) = 0;
		virtual void SetParameter_String(const atl::String& inParameterName, const atl::String& inParameterValue) = 0;
		virtual void SetParameter_Enum(const atl::String& inParameterName, const atl::String& inParameterValue) = 0;

		virtual void GetParameter_Integer(const atl::String& inParameterName, int& outParameterValue) = 0;
		virtual void GetParameter_Real(const atl::String& inParameterName, float& outParameterValue) = 0;
		virtual void GetParameter_Bool(const atl::String& inParameterName, bool& outParameterValue) = 0;
		virtual void GetParameter_String(const atl::String& inParameterName, atl::String& outParameterValue) = 0;
		virtual void GetParameter_Enum(const atl::String& inParameterName, atl::String& outParameterValue) = 0;

		virtual void ConfigureCamera(atl::Optional<const avl::Box&> inRoi, int inXBin, int inYBin,
			avl::ThorlabsReadoutSpeed::Type inReadoutSpeed, avl::ThorlabsTaps::Type inTaps, bool inTapBalance) = 0;
		virtual void ConfigureTrigger(bool inTriggerEnabled, avl::ThorlabsTriggerPolarity::Type inTriggerPolarity, atl::Optional<int> inFrameCount) = 0;
	};

} //namespace avl


#endif //THORLABS_INTERFACE_H