//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_LUMENERA_INTERFACE_H
#define AVL_LUMENERA_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"
#include "Geometry/Geometry.h"
#include "AVLCommon/CancellationTypes.h"
#include "LumeneraParameters.h"
#include <stdint.h>

namespace avl
{
	class LumeneraInterface
	{
	public:
		// identifier type for device
		typedef uint32_t DeviceIdType;

		virtual ~LumeneraInterface() {}

		virtual void BindToDevice(const atl::Optional<uint32_t>&) = 0;
		virtual void SetCancellationObject( ICancellationProvider* ) = 0;

		virtual void SetImageFormatParams(const LumeneraImageFormatParams&) = 0;
		virtual void SetAcquisitionParams(const LumeneraAcquisitionControlParams&) = 0;

		virtual void StartAcquisition() = 0;
		virtual void StopAcquisition() = 0;

		//These seem to apply to video preview only
		virtual void SetParameter(const LumeneraProperties::Type, const float) = 0;
		virtual void GetParameter(const LumeneraProperties::Type, float&) = 0;

		virtual void GpioConfigure(const bool gpio0, const bool gpio1, const bool gpio2, const bool gpio3) = 0;
		virtual void GpioSelect(const bool gpio0, const bool gpio1, const bool gpio2, const bool gpio3) = 0;
		virtual void GpioWrite(const bool gpo0, const bool gpo1, const bool gpo2, const bool gpo3) = 0;
		virtual void GpioRead(bool& gpi0, bool& gpi1, bool& gpi2, bool& gpi3) = 0;

		//Grab Image Functions
		virtual bool GrabImage(avl::Image& outImage, atl::Optional<int> inTimeout) = 0;
	};
}

#endif // AVL_LUMENERA_INTERFACE_H
