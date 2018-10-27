//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

// 
// Generated code using template VersionProtection.h.vtemplate. Do not modify.
// 

#ifndef VERSION_PROTECTION_H
#define VERSION_PROTECTION_H

#include "Config.h"

namespace avl
{
	namespace detail
	{
	#ifndef AVL_DISABLE_VERSION_VERIFICATION

		extern "C"
		{
			DLL_FUNCTION void avl_dll_required_in_version_4_10_0();
		}

		class ValidateVersionProtection
		{
		public:
			ValidateVersionProtection()
			{
				avl_dll_required_in_version_4_10_0();
			}
		};

		static ValidateVersionProtection avl_version_protection_verifier;
	
	#endif
	}
}

#endif //VERSION_PROTECTION_H
