//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef GOCATOR_INTERFACE_H
#define GOCATOR_INTERFACE_H

#include "AVLCommon/CancellationTypes.h"
#include "ATL/Optional.h"
#include "ATL/Array.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Surface/Surface.h"
#include "Image/Image.h"
#include "Profile/Profile.h"
#include "GocatorTypes.h"
#include "GocatorEnums.h"

namespace avl
{

	class IGocatorInterface
	{
	public:
		virtual ~IGocatorInterface() {};

		virtual void BindToDevice( const atl::Optional<GocatorAddress>& inAddress ) = 0;
		virtual void StartAcquisition(int inInputQueueSize, const atl::Optional<GocatorTriggerSource::Type>& inTriggerSource) = 0;
		virtual void StopAcquisition() = 0;

		virtual bool GrabPoint3DGrid(
			int							inInputQueueSize,
			const atl::Optional<int>&	inTimeout,
			Point3DGrid&				outPoint3DGrid,
			atl::Conditional<Image>&	outSurfaceIntensity,
			GocatorFrameInfo&			outFrameInfo) = 0;

		virtual bool GrabSurface(
			int								inInputQueueSize,
			const atl::Optional<int>&		inTimeout,
			Surface&						outSurface,
			atl::Conditional<Image>&		outSurfaceIntensity,
			GocatorFrameInfo&				outFrameInfo) = 0;

		virtual bool GrabImages(
			int							inInputQueueSize,
			const atl::Optional<int>&	inTimeout,
			Image&						outImage1,
			Image&						outImage2,
			GocatorFrameInfo&			outFrameInfo) = 0;

		virtual bool GrabProfile(
			int							inInputQueueSize,
			const atl::Optional<int>&	inTimeout,
			atl::Array<Point2D>&		outProfileData,
			atl::Conditional<Profile>&	outProfileIntensity,
			atl::real&					outXScale,
			atl::real&					outXOffset,
			atl::real&					outZScale,
			atl::real&					outZOffset,
			GocatorFrameInfo&			outFrameInfo) = 0;

		virtual bool GrabUniformProfile(
			int								inInputQueueSize,
			const atl::Optional<int>&		inTimeout,
			Profile&						outUniformProfileData,
			atl::Conditional<Profile>&		outUniformProfileIntensity,
			atl::real&						outZScale,
			atl::real&						outZOffset,
			GocatorFrameInfo&				outFrameInfo) = 0;

		virtual bool GrabSection(
			int							inInputQueueSize,
			const atl::Optional<int>&	inTimeout,
			int							inSectionID,
			atl::Array<Point2D>&		outSection,
			atl::Conditional<Profile>&	outSectionIntensity,
			atl::real&					xScale,
			atl::real&					xOffset,
			atl::real&					zScale,
			atl::real&					zOffset,
			GocatorFrameInfo&			outFrameInfo) = 0;

		virtual bool GrabMeasurement(
			int							inInputQueueSize,
			const atl::Optional<int>&	inTimeout,
			int							inMeasurementID,
			double&						outValue,
			bool&						outDecision,
			GocatorDecisionCode::Type&	outDecisionCode,
			GocatorFrameInfo&			outFrameInfo) = 0;

		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;

		virtual void LoadJob(const atl::String& inJobName) = 0;
		virtual void GetCurrentJobName(atl::String& outJobName) = 0;
		virtual void GetTriggerSource(GocatorTriggerSource::Type& outTriggerSource) = 0;
		virtual void GenerateSoftwareTrigger() = 0;
	};

} //namespace avl


#endif //GOCATOR_INTERFACE_H