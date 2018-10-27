//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REMOTE_EXECUTOR_BASE_STATE_H
#define AVL_REMOTE_EXECUTOR_BASE_STATE_H

#include "AVLCommon/BaseState.h"
#include "Cameras/RemoteExecutor/RemoteClientInterface.h" //:PUBLIC
#include "Cameras/RemoteExecutor/GrabberInterface.h" //:PUBLIC

namespace avl
{
	struct Smart_HelperStruct
	{
		virtual ~Smart_HelperStruct()
		{}
	};

	struct Smart_State : public BaseState
	{
		RemoteClientInterface* clientInterface;
		GrabberInterface* grabber;
		Smart_HelperStruct* helper;

		Smart_State()
			: clientInterface(nullptr)
			, grabber(nullptr)
			, helper(nullptr)
		{}

		virtual ~Smart_State()
		{
			delete clientInterface;
			clientInterface = nullptr;
			delete helper;
			helper = nullptr;
			//graber is destroyed by clientInterface
		}

	private:
		Smart_State(const Smart_State&); //=delete
		Smart_State& operator=(const Smart_State&); //=delete
	};
}

#endif