//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _THRESHOLDMETHOD_H__
#define _THRESHOLDMETHOD_H__

namespace avl
{
	namespace ThresholdSelectionMethod
	{
		enum Type
		{
			ClusteringKittler,
			ClusteringKMeans, 			// KMeans clustering
			ClusteringOtsu,   			// Otsu clustering
			Entropy,
			HistogramIntermodes
		};
	}
	namespace ThresholdDynamicReferenceMethod
	{
		enum Type
		{
			Mean,
			Median,
			Middle
		};
	}
}

#endif
