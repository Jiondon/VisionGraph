//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _GAUSSIAN_H
#define _GAUSSIAN_H

#include "ATL/Array.h"

namespace avl
{
	struct Gaussian
	{
		atl::Array<double>				mean;
		atl::Array<double>				sigma;
		double				weight;
		int					dimensions;

		explicit Gaussian
		(
			const atl::Array<double>& mean_ = atl::Array<double>(),
			const atl::Array<double>& sigma_ = atl::Array<double>(),
			double weight_ = 0.0,
			int dimensions_ = 0 
		) :
			 mean(mean_),
			 sigma(sigma_),
			 weight(weight_),
			 dimensions(dimensions_) 
		{}

		const atl::Array<double>& Mean() const	{ return mean;			};
		const atl::Array<double>& Sigma() const	{ return sigma;			};
		double Weight() const					{ return weight;		};
		int Dimensions() const					{ return dimensions;	};

		bool operator == ( const avl::Gaussian& rhs ) const
		{
			return mean == rhs.mean && 
			sigma == rhs.sigma && 
			weight == rhs.weight && 
			dimensions == rhs.dimensions;
		}

		bool operator != ( const avl::Gaussian& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

