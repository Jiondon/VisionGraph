//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef IFM_PARAMETERS_H
#define IFM_PARAMETERS_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "Basic/Types.h"

namespace avl
{

	namespace IFMResolution
	{
		enum Type
		{
			Resolution_176x132,
			Resolution_352x264
		};
	}

	namespace IFMTriggerMode
	{
		enum Type
		{
			Continuous,
			ProcessInterface,
			PositiveEdge,
			NegativeEdge,
			PositiveAndNegativeEdge
		};
	}

	struct IFMCameraAddress
	{
		IFMCameraAddress()
			: pCICPort(80)
			, xMLRPCPort(50010)
			, applicationId(atl::NIL)
		{}

		IFMCameraAddress
		(
			atl::File					_cameraPluginPath,
			atl::String					_cameraIP,
			int							_pCICPort,
			int							_xMLRPCPort,
			atl::Optional<atl::String>	_applicationId,
			atl::File					_processingPluginPath,
			atl::String					_processingPluginParameters
		)
			: cameraPluginPath(_cameraPluginPath)
			, cameraIP(_cameraIP)
			, pCICPort(_pCICPort)
			, xMLRPCPort(_xMLRPCPort)
			, applicationId(_applicationId)
			, processingPluginPath(_processingPluginPath)
			, processingPluginParameters(_processingPluginParameters)
		{}


		atl::File					CameraPluginPath( void )			const	{	return cameraPluginPath;			}
		atl::String					CameraIpAddress( void )				const	{	return cameraIP;					}
		int							PCICPort( void )					const	{	return pCICPort;					}
		int							XMLRPCPort( void )					const	{	return xMLRPCPort;					}
		atl::Optional<atl::String>	ApplicationId( void )				const	{	return applicationId;				}
		atl::File					ProcessingPluginPath( void )		const	{	return processingPluginPath;		}
		atl::String					ProcessingPluginParameters( void )	const	{	return processingPluginParameters;	}

		bool operator == ( const avl::IFMCameraAddress& rhs ) const
		{
			return cameraPluginPath == rhs.cameraPluginPath && cameraIP == rhs.cameraIP 
				&& pCICPort == rhs.pCICPort && xMLRPCPort == rhs.xMLRPCPort && applicationId == rhs.applicationId
				&& processingPluginPath == rhs.processingPluginPath && processingPluginParameters == rhs.processingPluginParameters;
		}

		bool operator != ( const avl::IFMCameraAddress& rhs ) const
		{
			return !(operator==(rhs));
		}

		atl::File					cameraPluginPath;
		atl::String					cameraIP;
		int							pCICPort;
		int							xMLRPCPort;
		atl::Optional<atl::String>	applicationId;
		atl::File					processingPluginPath;
		atl::String					processingPluginParameters;
	};
}

#endif