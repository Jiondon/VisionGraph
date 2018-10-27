//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#pragma once
#ifndef HIKVISION_INTERFACE_H
#define HIKVISION_INTERFACE_H

#include "Basic/Types.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace HikvisionPixelFormat
	{
		enum Type
		{
			Mono8 = 0,
			Mono10 = 1,
			Mono10Packed = 2,
			Mono12 = 3,
			Mono12Packed = 4,
			Mono16 = 5,
			RGB8Packed = 6,
			BayerGR8 = 7,
			BayerRG8 = 8,
			BayerGB8 = 9,
			BayerBG8 = 10,
			BayerGR10 = 11,
			BayerRG10 = 12,
			BayerGB10 = 13,
			BayerBG10 = 14,
			BayerGR12 = 15,
			BayerRG12 = 16,
			BayerGB12 = 17,
			BayerBG12 = 18,
			BayerGR10Packed = 19,
			BayerRG10Packed = 20,
			BayerGB10Packed = 21,
			BayerBG10Packed = 22,
			BayerGR12Packed = 23,
			BayerRG12Packed = 24,
			BayerGB12Packed = 25,
			BayerBG12Packed = 26,
			BayerGR16 = 27,
			BayerRG16 = 28,
			BayerGB16 = 29,
			BayerBG16 = 30
		};
	}

	namespace HikvisionEvent
	{
		enum Type
		{
			AcquisitionStart = 0,
			AcquisitionEnd = 1,
			AcquisitionActive = 2,
			FrameStart = 3,
			FrameEnd = 4,
			FrameActive = 5,
			FrameBurstStart = 6,
			FrameBurstEnd = 7,
			FrameBurstActive = 8,
			LineStart = 9,
			ExposureStart = 10,
			ExposureEnd = 11,
			ExposureActive = 12
		};
	}

	namespace HikvisionTriggerSource
	{
		enum Type
		{
			Line0 = 0,
			Line1 = 1,
			Line2 = 2,
			Line3 = 3,
			Counter0 = 4,
			Software = 7,
			FrequencyConverter = 8
		};
	}

	namespace HikvisionTriggerActivation
	{
		enum Type
		{
			RisingEdge = 0,
			FallingEdge = 1,
			LevelHigh = 2,
			LevelLow = 3
		};
	}

	namespace HikvisionLine
	{
		enum Type
		{
			Line0 = 0,
			Line1 = 1,
			Line2 = 2,
			Line3 = 3,
			Line4 = 4
		};
	}

	class HikvisionInterface
	{
	public:
		virtual ~HikvisionInterface() {};

		virtual void BindToCamera(atl::Optional<const atl::String&> inDeviceID) = 0;
		virtual void StartAcquisition(int inInputQueueSize) = 0;
		virtual void StopAcquisition() = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, int inInputQueueSize, avl::Image& outImage, atl::Conditional<int>& outFrameID) = 0;

		virtual void SetCancellationObject(avl::ICancellationProvider* workCancellation) = 0;
		virtual unsigned int GetSdkVersion() = 0;

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

		virtual void SetParameters(avl::HikvisionPixelFormat::Type inPixelFormat, atl::Optional<const avl::Box&> inRoi,
			atl::Optional<float> inFrameRate, bool inFrameRateAuto, atl::Optional<float> inExposureTime, bool inExposureTimeAuto,
			atl::Optional<float> inGain, bool inGainAuto) = 0;
		virtual void ConfigureTrigger(atl::Optional<bool> inTriggerEnabled, atl::Optional<avl::HikvisionEvent::Type> inTriggerSelector,
			atl::Optional<avl::HikvisionTriggerSource::Type> inTriggerSource, atl::Optional<avl::HikvisionTriggerActivation::Type> inTriggerActivation, atl::Optional<float> inTriggerDelay) = 0;
		virtual void GenerateSoftwareTrigger() = 0;
		virtual void ConfigureStrobe(avl::HikvisionLine::Type inLineSelector, avl::HikvisionEvent::Type inLineSource, atl::Optional<bool> inLineInverter,
			bool inStrobeEnabled, atl::Optional<int> inStrobeDuration, atl::Optional<int> inStrobeDelay) = 0;
	};
} //namespace avl

#endif //HIKVISION_INTERFACE_H