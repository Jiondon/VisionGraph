//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef ICUBE_INTERFACE_H
#define ICUBE_INTERFACE_H

#include "Basic/Types.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"
#include "ICubeEnums.h"

namespace avl
{
	class ICubeInterface
	{
	public:
		virtual ~ICubeInterface() {};

		virtual void BindToCamera(atl::Optional<int> cameraIndex) = 0;
		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;

		virtual void StopAcquisition() = 0;
		virtual void StartAcquisition(int inInputQueueSize) = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, avl::Image& outImage, int& outFrameID) = 0;

		virtual void SetParams(atl::Optional<float> inExposureTime, atl::Optional<avl::Box> roi) = 0;
		virtual void SetResetAcquisitionParams(avl::ICubeGrabMode::Type grabMode, atl::Optional<avl::ICubeResolutionMode::Type> mode,
			atl::Optional<avl::ICubeBinSkip::Type> skippingMode, atl::Optional<avl::ICubeBinSkip::Type> binningMode) = 0;

		//trigger
		virtual void SetTriggerMode(avl::ICubeTriggerMode::Type inTriggerMode) = 0;

		//additional parameters
		virtual void SetParameter(int type, int value) = 0;
		virtual void SetParamAuto(int type, bool inEnabled) = 0;
		virtual void SetParamOnePush(int type) = 0;
	};

} //namespace avl


#endif //ICUBE_INTERFACE_H