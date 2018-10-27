//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_UTILS_H
#define ATL_UTILS_H

#include "Platform.h"
#include <type_traits>
#include <utility>

namespace atl
{
	template<bool Test, class Type = void>
		struct enable_if { };

	template<class Type>
		struct enable_if<true, Type> { typedef Type type; };

	template<bool Test, class Type = void>
		struct enable_if_not { };

	template<class Type>
		struct enable_if_not<false, Type> { typedef Type type; };

#if _MSC_VER >= 1900 || (__GNUC__ * 100 + __GNUC_MINOR__) >= 408
		template <typename T>
		using has_trivial_destructor = ::std::is_trivially_destructible<T>;
#else
		using ::std::has_trivial_destructor;
#endif

#if _MSC_VER >= 1900 || (__GNUC__ * 100 + __GNUC_MINOR__) >= 501
		template <typename T>
		using has_trivial_copy_constructor = ::std::is_trivially_copy_constructible<T>;

		template <typename T>
		using has_trivial_default_constructor = ::std::is_trivially_default_constructible<T>;

		template <typename T>
		using has_trivial_copy_assign = ::std::is_trivially_copy_assignable<T>;
#else
		using ::std::has_trivial_copy_constructor;
		using ::std::has_trivial_default_constructor;

#	ifdef __GNUC__
		using ::std::has_trivial_copy_assign;
#	else
		template<typename T> struct has_trivial_copy_assign : public ::std::has_trivial_assign<T> {};
#	endif
#endif

#ifdef __MINGW32__
#	ifndef NULL
#		define NULL 0
#	endif
#endif

}


#endif // ATL_UTILS_H
