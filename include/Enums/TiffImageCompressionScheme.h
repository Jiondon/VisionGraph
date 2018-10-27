//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _TIFFIMAGECOMPRESSIONSCHEME_H__
#define _TIFFIMAGECOMPRESSIONSCHEME_H__

namespace avl
{
	namespace TiffImageCompressionScheme
	{
		enum Type
		{
			None,
			JPEG,
			Deflate,
			DeflateAdobe,
			LZW,
			Packbits
		};
	}
}

#endif
