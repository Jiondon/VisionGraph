//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SAVEIMAGESTATEIMPLBASE_H
#define SAVEIMAGESTATEIMPLBASE_H

#include "Image.h"
#include "AVLCommon/Config.h"

namespace avl
{
	struct SaveImageStateImplBase
	{
		avl::Image cachedImage;

		virtual ~SaveImageStateImplBase()
		{

		}
	};

	namespace pImpl_helpers
	{
		AVL_FUNCTION SaveImageStateImplBase* CreateSaveImageStateImpl();
	}
}

#endif //SAVEIMAGESTATEIMPLBASE_H