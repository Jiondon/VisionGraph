//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef PLAIN_TYPES_H
#define PLAIN_TYPES_H

#include "ATL/AtlTypes.h"

namespace avl
{
	namespace PlainType
	{
		enum Type
		{
			Int8,	
			UInt8,
			Int16,
			UInt16,
			Int32,
			Real
		};	
	}

	typedef atl::uint8	u8;
	typedef atl::sint8	i8;
	typedef atl::uint16	u16;
	typedef atl::sint16	i16;
	typedef atl::sint32	i32;

	inline
	int _sizeof( PlainType::Type type )
	{
		switch (type)
		{
		case PlainType::Int8:	return sizeof( atl::sint8 );
		case PlainType::UInt8:	return sizeof( atl::uint8 ); 
		case PlainType::Int16:	return sizeof( atl::sint16 );
		case PlainType::UInt16:	return sizeof( atl::uint16 );
		case PlainType::Int32:	return sizeof( atl::sint32 );
		case PlainType::Real:	return sizeof( float );
		default:		return 0;
		}
	}

	inline PlainType::Type _typeof( atl::sint8  ) { return PlainType::Int8; }
	inline PlainType::Type _typeof( atl::uint8  ) { return PlainType::UInt8; }
	inline PlainType::Type _typeof( atl::sint16 ) { return PlainType::Int16; }
	inline PlainType::Type _typeof( atl::uint16 ) { return PlainType::UInt16; }
	inline PlainType::Type _typeof( atl::sint32 ) { return PlainType::Int32; }
	inline PlainType::Type _typeof( float   ) { return PlainType::Real; }
}

#endif // PLAIN_TYPES_H
