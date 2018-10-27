//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_DAQNAVI_INTERFACE_H
#define AVL_DAQNAVI_INTERFACE_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "ATL/Array.h"

namespace avl
{

	class DAQNaviInterface
	{
	public:
		virtual ~DAQNaviInterface() {}
		virtual void BindToFirstDevice() = 0;
		virtual void BindToNamedDevice(const atl::String& devDescription) = 0;
		virtual void ReadInput(atl::Optional<int> port, atl::Array<int>& values) = 0;
		virtual void SetPortDirection(int port, bool inPortIsOutput) = 0;
		virtual void GetInterruptList(int srcChannel, int port, atl::Array<int>& values) = 0;
		virtual void InitInterrupts(const atl::Array<int>& channels, atl::uint8 triggerMode) = 0;
		virtual void SetDigitalOutput(int port, int value) = 0;
		virtual void GetDigitalOutput(int inPort, int& outValue) = 0;
		virtual void SetDigitalOutputBit(int port, int inBitId, bool inValue) = 0;
		virtual void GetDigitalOutputBit(int inPort, int inBitId, bool& outValue) = 0;
	};
}

#endif