//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef REMOTE_CLIENT_INTERFACE_H
#define REMOTE_CLIENT_INTERFACE_H

#include "AVLCommon/CancellationTypes.h"
#include "GrabberInterface.h"
#include "Image/Image.h"

namespace avl
{
	class RemoteClientInterface
	{
	public:
		virtual GrabberInterface* LoadGrabber(const SmartIPAddress& inAddress, RemoteGrabberInterfaceType::Type inInterface, ICancellationProvider* workCancellation) = 0;
		virtual bool ConnectedToRemoteGrabber() = 0;
		virtual ~RemoteClientInterface() {}
	};
}

#endif //REMOTE_CLIENT_INTERFACE_H