//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_IDS_INTERFACE
#define AVL_IDS_INTERFACE

#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "Image/Image.h"
#include "IDSEnums.h"

namespace avl
{
	class IDSInterface
	{
	public:
		virtual ~IDSInterface() {}

		virtual void BindToCamera(const atl::Optional<atl::String>& deviceID) = 0;
		virtual void SetInitialParameters(const atl::Optional<avl::Box>& aoi) = 0;
		virtual void SetParameters(
			const atl::Optional<float>& inFrameRate,
			const atl::Optional<float>& inExposureTime,
			const atl::Optional<avl::IDSBinning::Type>& horizontalBinning,
			const atl::Optional<avl::IDSBinning::Type>& verticalBinning,
			const atl::Optional<avl::IDSMirror::Type>& mirror,
			const atl::Optional<bool>& inAutoBlackLevel,
			const atl::Optional<int>& inBlackLevelOffset,
			const atl::Optional<int>& inGamma,
			const atl::Optional<bool>& inGainBoost,
			const atl::Optional<int>& inGainMaster,
			const atl::Optional<int>& inGainRed,
			const atl::Optional<int>& inGainGreen,
			const atl::Optional<int>& inGainBlue) = 0;
		virtual void LoadParameterSet(const atl::File& inFileName, bool loadEEPROM) = 0;
		virtual void ForceTrigger() const = 0;

		virtual void StartAcquisition(int inputQueueSize, const atl::String& pixelFormat, const atl::Optional<IDSTriggerMode::Type>& triggerMode, bool autoReconnect) = 0;
		virtual bool GrabImage(int inTimeout, avl::Image& outImage) const = 0;

		virtual void ConfigureDigitalIO(int inGPIO, avl::IDSGPIOConfiguration::Type inConfiguration, bool inState) = 0;
	};
}

#endif