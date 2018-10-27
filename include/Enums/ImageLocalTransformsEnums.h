//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _IMAGELOCALTRANSFORMSENUMS_H__
#define _IMAGELOCALTRANSFORMSENUMS_H__

namespace avl
{
	namespace MorphologyKernel
	{
		enum Type
		{
			Box3x3,
			Box5x5,
			Cross3x3,
			Cross5x5,
			Disc5x5,
			Disc7x7,
			Disc9x9
		};
	}
	namespace MeanKernel
	{
		enum Type
		{
			Box3x3,
			Box5x5
		};
	}
	namespace GaussKernel
	{
		enum Type
		{
			_3x3,
			_5x5,
			_7x7,
			_9x9,
			_11x11
		};
	}
	namespace GradientMaskOperator
	{
		enum Type
		{
			Sobel,						// Sobel operator
			Prewitt,  					// Prewitt operator
			Central,
			Forward
		};
	}
	namespace GradientOperator
	{
		enum Type
		{
			Gauss,
			Deriche,
			Lanser
		};
	}
	namespace MagnitudeMeasure
	{
		enum Type
		{
			Horizontal,   				// Horizontal estimation
			Vertical, 					// Vertical estimation
			Average,  					// Average estimation
			Sum,  						// Sum estimation
			Maximum,  					// Maximum estimation
			Hypot 						// Hypot estimation
		};
	}
	namespace SmoothImageMedianKernel
	{
		enum Type
		{
			Box
		};
	}
}

#endif
