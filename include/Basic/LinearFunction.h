//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _LINEARFUNCTION_H
#define _LINEARFUNCTION_H

#include "ATL/AtlTypes.h"

namespace avl
{
	struct LinearFunction
	{
		float	a;
		float	b;

		explicit LinearFunction
		(
			 float a_ = 0.0f,
			 float b_ = 0.0f 
		) :
			 a(a_),
			 b(b_) 
		{}

		float A( void ) const	{ return a;	};
		float B( void ) const	{ return b;	};

		bool operator == ( const avl::LinearFunction& rhs ) const
		{
			return a == rhs.a && 
			b == rhs.b;
		}

		bool operator != ( const avl::LinearFunction& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

