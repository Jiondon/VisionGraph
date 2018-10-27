//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MVGENTL_ACQUIRE_INTERFACE_H
#define AVL_MVGENTL_ACQUIRE_INTERFACE_H

#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace MVGenTLPixelFormat
	{
		enum Type
		{
			Auto = 0,
			Mono8,
			Mono16,
			RGB24,
			BGR24
		};
	}

	class mvGenTLAcquireInterface
	{
	public:
		virtual ~mvGenTLAcquireInterface() {}

		virtual void BindToCamera(atl::Optional<const atl::String&> cameraID) = 0;
		virtual void Start() = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, Image& image) = 0;

		virtual void SetParameters
		(
			atl::Optional<int>			inExposureTime,
			atl::Optional<float>		inGain,
			atl::Optional<float>		inFrameRate,
			atl::Optional<const avl::Box&>	inAoi,
			MVGenTLPixelFormat::Type		inPixelFormat,
			int							triggerActivation,
			int							triggerSourcer
		) = 0;

		virtual void GetDigitalIOState(int line, bool& value) = 0;
		virtual void SetDigitalOutput(int output, bool value) = 0;

		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;
	};
}

#endif