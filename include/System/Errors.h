//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_ERRORS_H
#define AVL_ERRORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Error.h"

namespace avl
{



	namespace ErrorType
	{
		enum Type
		{
			ANY_ERROR = atl::ANY_ERROR,
			RUNTIME_ERROR = atl::RUNTIME_ERROR,
			IO_ERROR = atl::IO_ERROR,
			SYSTEM_ERROR = atl::SYSTEM_ERROR,
			DOMAIN_ERROR = atl::DOMAIN_ERROR,
			LICENSE_ERROR = atl::LICENSE_ERROR,
			ASSERTION_ERROR = atl::ASSERTION_ERROR,
			UNHANDLED_ERROR = atl::UNHANDLED_ERROR,
			NONE = atl::NONE,
		};
	}



	/// <summary>Throws specific error</summary>
	AVL_FUNCTION void ThrowError
	(
		const avl::ErrorType::Type	inErrorType,
		const atl::String&			inMessage
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_ERRORS_H

