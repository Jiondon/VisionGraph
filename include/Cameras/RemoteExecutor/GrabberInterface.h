//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef GRABBER_INTERFACE_H
#define GRABBER_INTERFACE_H

#include "ATL/AtlString.h"
#include "ATL/Array.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace RemoteGrabberInterfaceType
	{
		enum Type
		{
			WebCamera,
			SynView,
			GenICam,
			Roseek
		};
	}

	namespace RemoteGrabberPixelFormat
	{
		enum Type
		{
			Mono8,
			Mono12,
			Mono16,
			RGB8,
			BGR8,
			Bayer_GR8,
			Bayer_RG8,
			Bayer_GB8,
			Bayer_BG8
		};
	}

	typedef atl::Optional<atl::Array<atl::String>> SmartDeviceID;
	typedef atl::String SmartIPAddress;

	class GrabberInterface
	{
	public:
		GrabberInterface(ICancellationProvider* cancellation)
			: work_cancellation(cancellation)
		{}

		virtual ~GrabberInterface() {}

		bool IsWorkCancelled()
		{
			if (work_cancellation)
				return work_cancellation->IsAVLWorkCancelled();
			return false;
		}

		virtual bool IsRemote() const
		{
			return false;
		}

		virtual void BindToDevice(const SmartDeviceID& deviceID) = 0;
		virtual void StartAcquisition(const atl::Optional<RemoteGrabberPixelFormat::Type> pixelFormat) = 0;
		virtual bool GrabImage(Image& outImage) = 0;
		virtual void SetParameters(atl::Array<atl::byte>& data) = 0;

	protected:
		ICancellationProvider* work_cancellation;
	};

}

#endif //GRABBER_INTERFACE_H