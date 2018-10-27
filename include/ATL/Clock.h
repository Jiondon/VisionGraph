//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should be included directly in your program.
//

#ifndef CLOCK_H
#define CLOCK_H

// Time-measuring class

#ifdef _MSC_VER

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#else

#include <ctime>

#endif

namespace atl
{

#ifdef _MSC_VER

	class Clock
	{
	public:
		typedef double type;

		Clock()
		{
			LARGE_INTEGER freq_;
			QueryPerformanceFrequency(&freq_);
			this->freq = (double)freq_.QuadPart;
			reset();
		}

		void reset()
		{
			QueryPerformanceCounter(&clock0);
		}

		double time() const
		{
			LARGE_INTEGER clock1;
			QueryPerformanceCounter(&clock1);
			return (double)(clock1.QuadPart - clock0.QuadPart) / freq;
		}

	private:
		LARGE_INTEGER	clock0;
		double			freq;
	};

#else

	class Clock
	{
	public:
		typedef double type;

		Clock()
		{
			reset();
		}

		void reset()
		{
			clock0 = std::clock();
		}

		double time() const
		{
			return (double)(std::clock() - clock0) / CLOCKS_PER_SEC;
		}

	private:
		std::clock_t clock0;
	};

#endif

}

#endif
