//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_BITFLOW_INTERFACE_H
#define AVL_BITFLOW_INTERFACE_H

#include "ATL/Optional.h"
#include "AVLCommon/CancellationTypes.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"


namespace avl
{

	class BitFlowInterface
	{
	public:
		virtual ~BitFlowInterface() {}
		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;
		virtual void BindToBoardAndCamera( int board, const atl::String& cameraFileName ) = 0;
		virtual bool GrabImage( avl::Image& outImage, atl::Optional<int> inTimeout ) = 0;
		virtual void Start() = 0;
		virtual void SoftwareTrigger( bool generate, unsigned int triggers ) = 0;
		virtual bool GetHardwareTrigger( unsigned int triggers ) = 0;
		virtual void SetTriggerMode( unsigned int triggerMode, unsigned int triggerAssignments, unsigned int trigAPolarity, unsigned int trigBPolarity ) = 0;
		virtual void SetDigitalOutput( int outputNumber, bool level ) = 0;
		virtual void GetDigitalOutput( int outputNumber, bool& outState ) = 0;

		virtual void ReadValueFromRegister( int inRegId, int& outValue ) = 0;
		virtual void WriteValueToRegister( int inRegId, int inValue ) = 0;
		virtual void GetRegisterName( int inRegId, atl::String& outName ) = 0;
	};
}

#endif 