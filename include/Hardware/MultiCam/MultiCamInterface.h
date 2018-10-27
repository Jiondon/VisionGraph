//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_MULTICAM_INTERFACE_H
#define AVL_MULTICAM_INTERFACE_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "AVLCommon/CancellationTypes.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"
#include "MultiCamEnums.h"

namespace avl
{
	class MultiCamInterface
	{
	public:
		virtual ~MultiCamInterface() {}

		virtual void BindToBoard(atl::Optional<const atl::String&> boardName, atl::Optional<const atl::String&> boardTopology) = 0;

		virtual void SetCameraFile(atl::Optional<const atl::File&> cameraFile) = 0;
		virtual void SetParameters(atl::Optional<const atl::String&> tapConfiguration, avl::MultiCamColorFormat::Type colorFormat ) = 0;
		virtual void BindToChannel(const atl::String& connector) = 0;
		virtual void Start(MultiCamAcquisitionMode::Type acquisitionMode, atl::Optional<int> pageLengthLn) = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, avl::Image& outImage) = 0;

		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;
		virtual void SetRuntimeParameters( atl::Optional<int> gain ) = 0;

		virtual void SetDigitalOutput( int inOutputIndex, const atl::Optional<MultiCamOutputStyle::Type>& inStyle, MultiCamOutputState::Type inState ) = 0;
		virtual void GetDigitalInput ( int input, const atl::Optional<MultiCamInputStyle::Type>& inStyle, MultiCamInputState::Type& outState ) = 0;

		virtual void SetIntegerParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, int value ) = 0;
		virtual void SetFloatParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, float value ) = 0;
		virtual void SetStringParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, const atl::String& value ) = 0;

		virtual void GetIntegerParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, int& value ) = 0;
		virtual void GetFloatParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, float& value ) = 0;
		virtual void GetStringParameter( MultiCamDestinationClass::Type destinationClass, const atl::String& parameter, atl::String& value ) = 0;
	};
}

#endif 
