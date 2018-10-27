//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AMR_COMMON_H
#define AVL_AMR_COMMON_H

namespace avs
{
	//
	// Trivial serialization
	//
	template <typename T>
	struct has_trivial_serialization { static const bool value = false; };
}

#endif
