//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_PLATFORM_H
#define ATL_PLATFORM_H

#ifndef THROW_FUNCTION
	#ifdef _MSC_VER
		#define THROW_FUNCTION __declspec(noreturn)
	#else
		#define THROW_FUNCTION
	#endif
#endif

#ifndef HAS_CPP0X
#	if defined(_MSC_VER) && _MSC_VER >= 1600
#		define HAS_CPP0X
#	elif defined(__GXX_EXPERIMENTAL_CXX0X__)
#		define HAS_CPP0X
#	endif
#endif

#ifndef HAS_CPP11
#	if __cplusplus >= 201103L
#		define HAS_CPP11
#	elif defined(_MSC_VER) && _MSC_VER >= 1900
#		define HAS_CPP11
#	endif
#endif 

#ifndef CONSTEXPR
#	if defined(_MSC_VER) && _MSC_VER >= 1900
#		define CONSTEXPR constexpr
#	elif defined(__GNUC__) && __cplusplus >= 201103L
#		define CONSTEXPR constexpr
#	else
#		define CONSTEXPR
#	endif
#endif

#ifndef NOEXCEPT
#	if defined(_MSC_VER) && _MSC_VER >= 1900
#		define NOEXCEPT noexcept
#	elif defined(__GNUC__) && __cplusplus >= 201103L
#		define NOEXCEPT noexcept
#	else
#		define NOEXCEPT throw()
#	endif
#endif

#ifndef ATL_EXPLICIT_OPERATOR_BOOL
#	if defined(_MSC_VER) && _MSC_VER >= 1900
#		define ATL_EXPLICIT_OPERATOR_BOOL()\
		explicit operator bool () const\
		{\
			return !this->operator! ();\
		}
#	elif defined(__GNUC__) && __cplusplus >= 201103L
#		define ATL_EXPLICIT_OPERATOR_BOOL()\
		explicit operator bool () const\
		{\
			return !this->operator! ();\
		}
#	else //safe bool idiom
		namespace atl
		{
			namespace detail
			{
				struct atl_unspecified_bool
				{
					struct OPERATORS_NOT_ALLOWED;
					void true_value(OPERATORS_NOT_ALLOWED*) {}
				};
				typedef void (atl_unspecified_bool::*unspecified_bool_type)(atl_unspecified_bool::OPERATORS_NOT_ALLOWED*);
			}
		}
#		define ATL_EXPLICIT_OPERATOR_BOOL()\
		operator atl::detail::unspecified_bool_type () const\
		{\
			return (!this->operator! () ? &atl::detail::atl_unspecified_bool::true_value : (atl::detail::unspecified_bool_type)0);\
		}
#	endif
#endif

#ifndef TEMPLATE
#	if defined(_MSC_VER) && !defined(__clang__)
#		define TEMPLATE
#	else
#		define TEMPLATE template
#	endif
#endif

#endif //ATL_PLATFORM_H