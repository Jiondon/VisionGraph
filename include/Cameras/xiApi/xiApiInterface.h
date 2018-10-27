//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef XIAPI_INTERFACE_H
#define XIAPI_INTERFACE_H

#include "Basic/Types.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.hxx"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"
#include "xiEnums.h"

namespace avl
{

	class XiApiInterface
	{
	public:
		virtual ~XiApiInterface() {};

		virtual void BindToCamera(const atl::Optional<atl::String>& deviceId) = 0;
		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;
		virtual void SetParameters(XiApiImageDataFormat::Type imageFormat, XiApiTriggerSource::Type inTriggerSource, atl::Optional<int> exposureTime,
			XiApiDownsampling::Type inDownsamplingRate, atl::Optional<float> gain, atl::Optional<Box> aoi, atl::Optional<bool> badPixelCorrection,
			atl::Optional<bool> automaticExposureGain) = 0;

		virtual bool GrabImage(const atl::Optional<int>& inTimeout, avl::Image& outImage, atl::int64& outFrameId, atl::int64& outTimestamp) = 0;
		virtual void StartAcquisition() = 0;
		virtual void StopAcquisition() = 0;

		//Digital IO
		virtual void SetGPIMode(int inGPISelector, XiApiGPIMode::Type inGPIMode) = 0;
		virtual void GetGPILevel(int inGPISelector, int& outGPILevel) = 0;
		virtual void SetGPOMode(int inGPOSelector, XiApiGPOMode::Type inGPOMode) = 0;

		//Set / read data
		virtual void SetParamInt(const atl::String& parameter, int value) = 0;
		virtual void SetParamFloat(const atl::String& parameter, float value) = 0;

		virtual void GetParamInt(const atl::String& parameter, int& value) = 0;
		virtual void GetParamFloat(const atl::String& parameter, float& value) = 0;

		virtual void GenerateSoftwareTrigger() = 0;
	};

} //namespace avl


#endif //XIAPI_INTERFACE_H