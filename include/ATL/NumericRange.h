//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_NUMERIC_RANGE_H
#define ATL_NUMERIC_RANGE_H

#include <limits>
#include "Platform.h"

namespace atl
{
	namespace HelperNumericRangeImpl
	{
		template <typename T, bool has_infinity>
		struct HelperNumericRangeBase
		{
			static CONSTEXPR T Min(void) NOEXCEPT
			{
				return (std::numeric_limits<T>::min)();
			}

			static CONSTEXPR T Max(void) NOEXCEPT
			{
				return (std::numeric_limits<T>::max)();
			}
		};

		template<typename T>
		struct HelperNumericRangeBase<T, true>
		{
			static CONSTEXPR T Min(void) NOEXCEPT
			{
				return -(std::numeric_limits<T>::infinity());
			}

			static CONSTEXPR T Max(void) NOEXCEPT
			{
				return std::numeric_limits<T>::infinity();
			}
		};
	}

	template<typename T>
	struct NumericRange : public HelperNumericRangeImpl::HelperNumericRangeBase<T, std::numeric_limits<T>::has_infinity>
	{
	};
}

#endif // ATL_NUMERIC_RANGE_H
