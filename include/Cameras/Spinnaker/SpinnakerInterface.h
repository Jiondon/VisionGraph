//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef SPINNAKER_KIT_INTERFACE_H
#define SPINNAKER_KIT_INTERFACE_H

#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace SpinnakerPixelFormat
	{
		enum Type
		{
			Mono8,
			Mono16,
			RGB8,
			RGBa8,
			RGB16,
			RGBa16,
			Bayer8,
			Bayer16,
			Raw8,
			Raw16
		};
	}

	namespace SpinnakerBayerConverter
	{
		enum Type
		{
			AVLConverter,
			Default,
			NoColorProcessing,
			NearestNeighbour,
			EdgeSensing,
			HQLinear,
			Rigorous,
			Ipp,
			DirectionalFiltering
		};
	}

	namespace SpinnakerAutoSettings
	{
		enum Type
		{
			Off,
			Once,
			Continuous
		};
	}

	class SpinnakerInterface
	{
	public:
		virtual ~SpinnakerInterface() {}

		virtual void BindToDevice(const atl::Optional<atl::String>& inDeviceSerialNumber) = 0;
		virtual bool GrabImage(avl::SpinnakerBayerConverter::Type inBayerConverter, atl::Optional<int> inTimeout, avl::Image& outImage, atl::int64& outFrameId, atl::int64& outTimeStamp) = 0;
		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;
		virtual void StartAcquisition(atl::Optional<avl::SpinnakerPixelFormat::Type> pixelType, int inBufferCount) = 0;
		virtual void StopAcquisition() = 0;

		virtual void SetParameters(atl::Optional<SpinnakerAutoSettings::Type> inExposureAuto, atl::Optional<double> inExposureTime, atl::Optional<bool> inFrameRateEnable
			, atl::Optional<double> inFrameRate, atl::Optional<avl::SpinnakerAutoSettings::Type> inGainAuto, atl::Optional<double> inGain) = 0;

		virtual void SetBoolValue(const atl::String& inParamName, bool inValue, bool inVerify) = 0;
		virtual void SetIntValue(const atl::String& inParamName, int inValue, bool inVerify) = 0;
		virtual void SetFloatValue(const atl::String& inParamName, float inValue, bool inVerify) = 0;
		virtual void SetStringValue(const atl::String& inParamName, const atl::String& inValue, bool inVerify) = 0;
		virtual void SetEnumValue(const atl::String& inParamName, const atl::String& inValue, bool inVerify) = 0;
		virtual void ExecuteCommand(const atl::String& inCommandName, bool inVerify) = 0;

		virtual void GetBoolValue(const atl::String& inParamName, bool inVerify, bool inIgnoreCache, bool& outValue) const = 0;
		virtual void GetIntValue(const atl::String& inParamName, bool inVerify, bool inIgnoreCache, int& outValue) const = 0;
		virtual void GetFloatValue(const atl::String& inParamName, bool inVerify, bool inIgnoreCache, float& outValue) const = 0;
		virtual void GetStringValue(const atl::String& inParamName, bool inVerify, bool inIgnoreCache, atl::String& outValue) const = 0;
		virtual void GetEnumValue(const atl::String& inParamName, bool inVerify, bool inIgnoreCache, atl::String& outValue) const = 0;

		virtual void GetLineStatus(int inLineSelector, bool inVerify, bool inIgnoreCache, bool& outValue) const = 0;
		virtual void SetUserOutput(int inUserOutputSelector, bool inValue, bool inVerify) = 0;
	};
}

#endif // SPINNAKER_KIT_INTERFACE_H
