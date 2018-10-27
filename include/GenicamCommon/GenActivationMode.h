//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEN_ACTIVATION_MODE_H
#define AVL_GEN_ACTIVATION_MODE_H

namespace avl
{
	namespace GenActivationMode
	{
		enum Type
		{
			WhenTrue,
			WhenFalse,
			OnRisingEdge,
			OnFallingEdge,
			OnAnyEdge
		};
	}
}

#endif // AVL_GEN_ACTIVATION_MODE_H
