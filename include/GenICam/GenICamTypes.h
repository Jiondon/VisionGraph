//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GENICAM_TYPES_H
#define AVL_GENICAM_TYPES_H


#include "ATL/AtlString.h"


namespace avl
{

	struct GenAddress
	{
		atl::String vendorName;
		atl::String tlType;
		atl::String deviceId;

		GenAddress()
		{
		}

		GenAddress( const atl::String& _vendorName, const atl::String& _tlType, const atl::String& _deviceId )
		: vendorName(_vendorName)
		, tlType(_tlType)
		, deviceId(_deviceId)
		{
		}

		const atl::String& VendorName( void ) const		{ return vendorName;	}
		const atl::String& TLType( void ) const			{ return tlType;		}
		const atl::String& DeviceID( void ) const		{ return deviceId;		}

		bool operator == ( const GenAddress& other ) const
		{
			return vendorName == other.vendorName && tlType == other.tlType && deviceId == other.deviceId;
		}

		bool operator != ( const GenAddress& other ) const
		{
			return !(operator == (other));
		}
	};

	typedef atl::String GenPixelFormat;
	typedef atl::String GenParameterName;


	namespace GenICamParameterScope
	{
		enum Type
		{
			Device = 0,
			DeviceModule,
			DeviceStreamModule,
			InterfaceModule,
			SystemModule,
		};
	}
}


#endif // AVL_GENICAM_TYPES_H
