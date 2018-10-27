//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_MATH_HXX
#define ATL_MATH_HXX

#include <cmath>

namespace atl
{

#ifdef __GNUC__
#	define GCC_USED __attribute__((unused))
#else
#	define GCC_USED
#endif

	const float PI		GCC_USED	= std::asin(1.0f) * 2.0f;
	const float PI_HALF GCC_USED	= PI * 0.5f;
	const float TWO_PI	GCC_USED	= PI * 2.0f;

	// trigonometry using degrees ----------------------------------------

	inline float Sin(float angle)
	{
		return std::sin( (angle * PI) / 180.0f );
	}

	inline float Cos(float angle)
	{
		return std::cos( (angle * PI) / 180.0f );
	}

	inline float Tan(float angle)
	{
		return std::tan( (angle * PI) / 180.0f );
	}

	inline float Asin(float val)
	{
		return (std::asin(val) * 180.0f) / PI;
	}

	inline float Acos(float val)
	{
		return (std::acos(val) * 180.0f) / PI;
	}

	inline float Atan(float val)
	{
		return (std::atan(val) * 180.0f) / PI;
	}

	inline float Atan2(float y, float x)
	{
		return (std::atan2( y, x ) * 180.0f) / PI;
	}

	// ------------------------------------------------------------------------------

	template <typename T>
	inline int Signum(T x)
	{
		return
			x < (T)0 ? -1 :
			x > (T)0 ? +1 :
						0;
	}

	template <typename T>
	inline T Abs(T x)
	{
#ifdef _MSC_VER
	#pragma warning(disable:4146)
#endif
		return x >= (T)0 ? x : -x;
#ifdef _MSC_VER
	#pragma warning(default:4146)
#endif
	}

	template <typename T>
	inline int Floor(T x)
	{
		if (x >= 0)
		{
			return (int)x;
		}
		else
		{
			int y = (int)x;
			return ((T)y == x) ? y : y - 1;
		}
	}

	template <typename T>
	inline int Ceil(T x)
	{
		return -Floor(-x);
	}

	template <typename T>
	inline int Round(T x)
	{
		return (int)Floor( x + 0.5f );
	}

	template <typename T>
	inline T Square(T x)
	{
		return x * x;
	}

	template <typename T>
	inline T Cube(T x)
	{
		return x * x * x;
	}

	template <typename T>
	inline T Lerp(T a, T b, float alpha)
	{
		return a + (b - a) * alpha;
	}

	inline float Hypot(float dx, float dy)
	{
		return std::sqrt(dx * dx + dy * dy);
	}

	// ------------------------------------------------------------------------------

	template <typename T>
	inline bool InRange(const T& x, const T& a, const T& b)
	{
		return a <= x && x < b;
	}

	template <typename T>
	inline bool InRangeIncl(const T& x, const T& a, const T& b)
	{
		return a <= x && x <= b;
	}

	template <typename T>
	inline T Crop(const T& x, const T& min, const T& max)
	{
		return (x >= min ? (x <= max ? x : max) : min);
	}

}

#endif
