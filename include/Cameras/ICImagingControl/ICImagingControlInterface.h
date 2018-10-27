//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_ICIMAGINGCONTROL_INTERFACE_H
#define AVL_ICIMAGINGCONTROL_INTERFACE_H

#include "ATL/Optional.h"
#include "AVLCommon/CancellationTypes.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"


namespace avl
{
	namespace ICImagingControlColorFormat
	{
		enum Type
		{
			RGB32 = 0,
			RGB24,
			RGB565,
			RGB555,
			RGB8,
			UYVY,
			Y800,
			YGB1,
			YGB0,
			BY8,
			Y16,
			RGB64
		};
	}

	class ICImagingControlInterface
	{
	public:
		virtual ~ICImagingControlInterface() {}

		virtual void BindToCamera(const atl::Optional<const atl::String&>& inDeviceId) = 0;
		virtual void SetCancellationObject(avl::ICancellationProvider* workCancellation) = 0;
		virtual void StartAcquisition(int inInputQueueSize) = 0;
		virtual void StopAcquisition() = 0;

		virtual void SetParameters
		(
			avl::ICImagingControlColorFormat::Type	inPixelFormat,
			atl::Optional<avl::Box>					inRoi,
			atl::Optional<int>						inBinning,
			atl::Optional<int>						inSkipping,
			atl::Optional<int>						inGain,
			atl::Optional<bool>						inGainAuto,
			atl::Optional<double>					inExposure,
			atl::Optional<bool>						inExposureAuto,
			atl::Optional<int>						inGamma,
			atl::Optional<int>						inSharpness,
			atl::Optional<float>					inFrameRate
		) = 0;

		virtual bool GrabImage(atl::Optional<int> inTimeout, avl::Image& outImage, atl::int64& outFrameId) = 0;
		virtual void EnableExternalTrigger(bool inEnable) = 0;
		virtual void GetDigitalIOState(bool& outInputState, bool& outOutputState) = 0;
		virtual void SetDigitalOutput(bool inOutput) = 0;
	};
}

#endif