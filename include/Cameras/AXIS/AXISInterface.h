//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_AXIS_INTERFACE_H
#define AVL_AXIS_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"


namespace avl
{

	class AXISInterface
	{
	public:
		virtual ~AXISInterface() {}

		virtual void BindToNamedCamera( atl::String inAddress, atl::uint8 cameraID ) = 0;

		virtual void SetParams( atl::Optional<const atl::String&> login, atl::Optional<const atl::String&> password, atl::uint8 resolution, atl::uint8 rotation, atl::Optional<int> compression, atl::Optional<const atl::String&> textString ) = 0;

		virtual void GrabImage( avl::Image& outImage ) = 0;

		virtual bool IsStarted() = 0;
	};
}

#endif 