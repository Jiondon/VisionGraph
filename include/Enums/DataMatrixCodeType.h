//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _DATAMATRIXCODETYPE_H__
#define _DATAMATRIXCODETYPE_H__

namespace avl
{
	namespace DataMatrixType
	{
		enum Type
		{
			ECC_200,
			ECC_000,
			ECC_050,
			ECC_080,
			ECC_100,
			ECC_140
		};
	}
	namespace DataMatrixCodeType
	{
		enum Type
		{
			ECC_200,
			ECC_000_140
		};
	}
}

#endif
