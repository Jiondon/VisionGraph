//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef IFM_INTERFACE_H
#define IFM_INTERFACE_H

#include "IfmParameters.h"
#include "Basic/Types.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	class IfmInterface
	{
	public:
		virtual ~IfmInterface() {};

		virtual void BindToCamera( const avl::IFMCameraAddress& cameraInfo ) = 0;
		virtual void StartAcquisition() = 0;
		virtual bool GrabImage(atl::Optional<int> inTimeout, bool inGrab3dCoordinates, avl::Image& outDistancesImage, avl::Image& outAmplitudeImage, atl::Array<avl::Region>& outInvalidRois, atl::Conditional<avl::Point3DGrid>& out3Dcoordinates) = 0;

		virtual void SourceCommand(const atl::String& inCommand, atl::String& outResult) = 0;
		virtual void SetIntegrationTime(const int index, const int time) = 0;

		virtual void SetCancellationObject( avl::ICancellationProvider* workCancellation ) = 0;

		virtual void SetParameters( const atl::Optional<float>& inFrameRate, const atl::Optional<IFMResolution::Type>& inResolution, const atl::Optional<avl::IFMTriggerMode::Type>& inTriggerMode ) = 0;
		virtual void SetDigitalOutput( int number, bool state ) = 0;
	};

} //namespace avl


#endif //IFM_INTERFACE_H