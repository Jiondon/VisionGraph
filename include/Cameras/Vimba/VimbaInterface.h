//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef VIMBA_INTERFACE_H
#define VIMBA_INTERFACE_H

#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Image/Image.h" 
#include "AVLCommon/CancellationTypes.h"
#include "VimbaParameters.h"

namespace avl
{
	class VimbaInterface
	{
	public:
		virtual ~VimbaInterface() {}

		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;

		virtual void BindToCamera( const atl::Optional<const atl::String&> ) = 0;

		virtual bool GrabImage(avl::Image& outImage, atl::Optional<int> timeout) = 0;

		virtual void StartAcquisition() = 0;
		virtual void SetImageFormatParams( const VimbaImageFormatParams& params ) = 0;
		virtual void SetAcquisitionParams( const VimbaAcquisitionControlParams& params ) = 0;

		virtual void SetBoolParameter	( const atl::String& inName, bool		inValue ) = 0;
		virtual void SetRealParameter	( const atl::String& inName, float	inValue ) = 0;
		virtual void SetIntegerParameter( const atl::String& inName, int		inValue ) = 0;
		virtual void SetEnumParameter	( const atl::String& inName, const atl::String& inValue ) = 0;
		virtual void SetStringParameter	( const atl::String& inName, const atl::String& inValue ) = 0;

		virtual void GetBoolParameter	( const atl::String& inName, bool&		outValue ) = 0;
		virtual void GetRealParameter	( const atl::String& inName, float&	outValue ) = 0;
		virtual void GetIntegerParameter( const atl::String& inName, int&		outValue ) = 0;
		virtual void GetEnumParameter	( const atl::String& inName, atl::String& outValue ) = 0;
		virtual void GetStringParameter	( const atl::String& inName, atl::String& outValue ) = 0;

		virtual void SetDigitalOutput( int inLineNumber, bool inState ) = 0;
		virtual void GetDigitalInput( int inLineNumber, bool& outState ) = 0;
	};
}

#endif //VIMBA_INTERFACE_H