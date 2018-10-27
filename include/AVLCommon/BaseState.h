//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_BASE_STATE_H
#define AVL_BASE_STATE_H

namespace avl
{
	struct BaseState
	{
	public:
		// Informs whether it is the first time this state is used
		bool IsFirstTime()
		{
			bool result = isFirstTime;
			isFirstTime = false;
			return result;
		}

	protected:
		BaseState()
			: isFirstTime(true)
		{}

	private:
		bool isFirstTime;
	};
}

#endif
