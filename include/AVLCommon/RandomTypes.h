//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_RANDOM_TYPES_H
#define AVL_RANDOM_TYPES_H

#include "RandomStateImplBase.h"

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"

namespace avl
{
	namespace pImpl_helpers
	{
		/* For internal use only */

		AVL_FUNCTION RandomStateImplBase* CreateRandomStateImpl();
	}

	struct RandomStateImpl;

	struct RandomState : public BaseState
	{
	public:
		RandomState()
		{
			impl = pImpl_helpers::CreateRandomStateImpl();
		}
		~RandomState()
		{
			delete impl;
		}

		RandomStateImpl* Impl();

		RandomState(RandomState&& r)
		{
			impl = r.impl;
			r.impl = nullptr;
		}

	private:
		RandomState(const RandomState&);// = delete;
		RandomState& operator=(const RandomState&);// = delete;
		RandomState& operator=(RandomState&&);// = delete;

	private:
		RandomStateImplBase* impl;
	};
} // namespace avl


#endif // AVL_RANDOM_TYPES_H
