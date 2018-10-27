//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_ADVANTECH_ADAMTCP_INTERFACE_H
#define AVL_ADVANTECH_ADAMTCP_INTERFACE_H

#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	class AdamTCPInterface
	{
	public:
		virtual ~AdamTCPInterface() {}

		virtual void BindToDevice( const atl::Optional<atl::String>& deviceIP, const atl::Optional<int>& inTimeout = atl::NIL, const atl::Optional<int>& inKeepAliveTime = atl::NIL ) = 0;
		
		virtual void Function01( int inStationAddress, int inStartAddress, int inNumberOfCoils, atl::Array<int>& outStatus, atl::Array<bool>& outStatusValues ) = 0;
		virtual void Function02( int inStationAddress, int inStartAddress, int inNumberOfCoils, atl::Array<int>& outStatus, atl::Array<bool>& outStatusValues ) = 0;
		virtual void Function03( int inStationAddress, int inStartAddress, int inNumberOfRegister, atl::Array<int>& outValues ) = 0;
		virtual void Function04( int inStationAddress, int inStartAddress, int inNumberOfRegister, atl::Array<int>& outValues ) = 0;
		virtual void Function05( int inStationAddress, int inCoilAddress, bool inState ) = 0;

		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;
	};
}

#endif //AVL_ADVANTECH_ADAMTCP_INTERFACE_H
