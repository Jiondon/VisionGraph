//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_TYPES_H
#define ATL_TYPES_H

namespace atl
{
	typedef signed   char		sint8;
	typedef unsigned char		uint8;		// aka byte
	typedef signed   short		sint16;
	typedef unsigned short		uint16;
	typedef signed   int		sint32;
	typedef unsigned int		uint32;
	typedef signed   long long	sint64;
	typedef unsigned long long	uint64;
	typedef float				float32;

	typedef uint8				byte;

	typedef float				real;
	typedef double				real64;
	typedef long long			int64;

	typedef unsigned long long int timer_t;

	enum BinaryMode { INTERNAL, EXTERNAL };

	class String;
	typedef String File;
	typedef String Directory;
}

#endif // ATL_TYPES_H
