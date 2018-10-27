//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _QRCODE_H
#define _QRCODE_H

#include "ATL/AtlString.h"
#include "Path/Path.h"

namespace avl
{
	struct QRCode
	{
		Path		position;
		atl::String	text;
		int			version;

		explicit QRCode
		(
			Path position_ = Path(),
			atl::String text_ = "",
			int version_ = 0 
		) :
			 position(position_),
			 text(text_),
			 version(version_) 
		{}

		Path Position() const		{ return position;	};
		atl::String Text() const	{ return text;		};
		int Version() const			{ return version;	};

		bool operator == ( const avl::QRCode& rhs ) const
		{
			return position == rhs.position && 
			text == rhs.text && 
			version == rhs.version;
		}

		bool operator != ( const avl::QRCode& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

