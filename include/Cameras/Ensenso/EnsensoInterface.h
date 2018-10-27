//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_ENSENSO_INTERFACE_H
#define AVL_ENSENSO_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Surface/Surface.h"
#include "Geometry/Geometry.h"
#include "AVLCommon/CancellationTypes.h"
//#include "LumeneraParameters.h"
#include <stdint.h>

namespace avl
{
	class EnsensoInterface
	{
	public:
		// identifier type for device
		typedef atl::String DeviceIdType;

		virtual ~EnsensoInterface() {}

		virtual void BindToDevice(const atl::Optional<DeviceIdType>&) = 0;
		virtual void SetCancellationObject( ICancellationProvider* ) = 0;

		virtual void OpenTcpPort() = 0;

		//pass json string here
		virtual void LoadSettings(const atl::File &savedParameters) = 0;
		//from a string or EEPROM
		virtual void LoadCalibration(const atl::File& savedParameters) = 0;
		//global parameters
		virtual void LoadGlobalParameters(const atl::File& savedGlobalParameters) = 0;

		virtual void SetParameter(const atl::String& param, const bool value, const bool global) = 0;
		virtual void SetParameter(const atl::String& param, const int value, const bool global) = 0;
		virtual void SetParameter(const atl::String& param, const double value, const bool global) = 0;
		virtual void SetParameter(const atl::String& param, const atl::String& value, const bool global) = 0;

		virtual void GetParameter(const atl::String& param, bool& value, const bool global) = 0;
		virtual void GetParameter(const atl::String& param, int& value, const bool global) = 0;
		virtual void GetParameter(const atl::String& param, double& value, const bool global) = 0;
		virtual void GetParameter(const atl::String& param, atl::String& value, const bool global) = 0;

		virtual void StartAcquisition(const atl::Optional<atl::File>& savedSettingsParameters, const atl::Optional<atl::File>& savedCalibrationParameters, const atl::Optional<atl::File>& savedGlobalParameters, const bool softwareTriggered) = 0;
		virtual void StopAcquisition() = 0;

		//Grab Functions
		virtual bool GrabPoint3DGrid(avl::Point3DGrid& outGrid, atl::Conditional<avl::Image>& outImage, double& outTimestamp, const atl::Optional<atl::File>& savedSettingsParameters, const atl::Optional<atl::File>& savedCalibrationParameters, const atl::Optional<atl::File>& savedGlobalParameters, atl::Optional<int> inTimeout) = 0;
		virtual bool GrabSurface(avl::Surface& outSurface, atl::Conditional<avl::Image>& outImage, double& outTimestamp, const atl::Optional<atl::File>& savedSettingsParameters, const atl::Optional<atl::File>& savedCalibrationParameters, const atl::Optional<atl::File>& savedGlobalParameters, atl::Optional<int> inTimeout) = 0;

		virtual void GenerateSoftwareTrigger() = 0;
	};
}

#endif // AVL_ENSENSO_INTERFACE_H
