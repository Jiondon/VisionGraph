//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef ROSEEK_KIT_INTERFACE_H
#define ROSEEK_KIT_INTERFACE_H

#include "ATL/Optional.h"
#include "AVLCommon/CancellationTypes.h"
#include "Image/Image.h"

namespace avl
{
	namespace RoseekImageFormat
	{
		enum Type
		{
			Mono8,
			BGR24
		};
	}

	namespace RoseekResolutionMode
	{
		enum Type
		{
			AllPixel,
			ROI,
			FullHD
		};
	}

	namespace RoseekWorkingMode
	{
		enum Type
		{
			Continuous,
			Trigger
		};
	}

	namespace RoseekExposureMode
	{
		enum Type
		{
			Auto,
			Manual
		};
	}

	namespace RoseekLEDDriverMode
	{
		enum Type
		{
			Close,
			Sync,
			Strobe,
			Constant
		};
	}

	namespace RoseekLEDDriverType
	{
		enum Type
		{
			Own,
			External,
		};
	}

	namespace RoseekLEDStatus
	{
		enum Type
		{
			Closed,
			Red,
			Green,
			RedBlink,
			GreenBlink,
			RedGreenBlink
		};
	}

	class RoseekInterface
	{
	public:
		virtual ~RoseekInterface() {}

		virtual void BindToDevice() = 0;
		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;

		virtual void StartAcquisition(
			int inInputQueueSize,
			RoseekImageFormat::Type inImageFormat,
			atl::Optional<RoseekResolutionMode::Type> inResolutionMode,
			const atl::Optional<Box>& inROI
		) = 0;

		virtual void StopAcquisition() = 0;

		virtual bool GrabImage(atl::Optional<int> inTimeout, Image& outImage, int& outFrameID) = 0;

		virtual void SetParameters(atl::Optional<float> inFrameRate,
			atl::Optional<RoseekWorkingMode::Type> inWorkingMode,
			atl::Optional<avl::RoseekExposureMode::Type> inExposureMode,
			atl::Optional<int> inExposureTime,
			atl::Optional<int> inSensitivityLevel,
			atl::Optional<float> inGain) = 0;
		virtual void GenerateSoftwareTrigger() = 0;

		virtual void ConfigureLEDDriverMode(avl::RoseekLEDDriverType::Type inType, avl::RoseekLEDDriverMode::Type inDriverMode) = 0;
		virtual void SetLEDDriverStrength(avl::RoseekLEDDriverType::Type inType, int inValue) = 0;

		virtual void SetOutputState(int inId, bool inState) = 0;
		virtual void GetInputState(int inId, bool& outState) = 0;
		virtual void SetStatusLED(int inId, RoseekLEDStatus::Type inStatus) = 0;
	};
}

#endif // ROSEEK_KIT_INTERFACE_H
