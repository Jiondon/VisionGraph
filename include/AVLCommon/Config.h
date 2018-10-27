//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_CONFIG_H
#define AVL_CONFIG_H

#if defined (_MSC_VER)

#	if defined(__INTELLISENSE__)

#		if !defined(DLL_FUNCTION)
#			define DLL_FUNCTION __declspec(dllexport)
#		endif
#		define AVL_FUNCTION 

#	else

#		if !defined(DLL_FUNCTION)
#			define DLL_FUNCTION extern "C" __declspec(dllexport)
#		endif
#		define AVL_FUNCTION extern "C" 

#	endif

#	if _MSC_VER >= 1900
#		define THROW_AVL_ERRORS noexcept(false)
#	else
#		define THROW_AVL_ERRORS throw(...)
#	endif
#	define FORCEINLINE __forceinline

#elif defined(__MINGW32__) || defined(__GNUC__)

#	if !defined(DLL_FUNCTION)
#		define DLL_FUNCTION extern "C" __attribute__((visibility("default")))
#	endif
#	ifdef BUILDING_DLL
#		define AVL_FUNCTION extern "C" __attribute__((visibility("default")))
#	else
#		define AVL_FUNCTION extern "C"
#	endif
#	define THROW_AVL_ERRORS noexcept(false)
#	define FORCEINLINE inline __attribute__((always_inline))

#else

#	warning "Unsupported compiler"
#	if !defined(DLL_FUNCTION)
#		define DLL_FUNCTION
#	endif
#	define AVL_FUNCTION extern "C"
#	define THROW_AVL_ERRORS
#	define FORCEINLINE inline

#endif

#endif // AVL_CONFIG_H
