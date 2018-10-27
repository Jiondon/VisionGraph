//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _NDGAUSSIANMIXTUREPARAMS_H
#define _NDGAUSSIANMIXTUREPARAMS_H

#include "ATL/Array.h"
#include "ATL/AtlTypes.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{
	struct NDGaussianMixtureParams
	{
		int					classNo;
		atl::Array<atl::Array<float>>	means;
		atl::Array<Matrix>				covs;
		atl::Array<double>				priors;
		double				noveltyScore;

		explicit NDGaussianMixtureParams
		(
			int classNo_ = 0,
			const atl::Array<atl::Array<float>>& means_ = atl::Array<atl::Array<float>>(),
			const atl::Array<Matrix>& covs_ = atl::Array<Matrix>(),
			const atl::Array<double>& priors_ = atl::Array<double>(),
			double noveltyScore_ = 0.0 
		) :
			 classNo(classNo_),
			 means(means_),
			 covs(covs_),
			 priors(priors_),
			 noveltyScore(noveltyScore_) 
		{}

		int ClassNo() const							{ return classNo;		};
		const atl::Array<atl::Array<float>>& Means() const		{ return means;			};
		const atl::Array<Matrix>& Covs() const		{ return covs;			};
		const atl::Array<double>& Priors() const	{ return priors;		};
		double NoveltyScore() const					{ return noveltyScore;	};

		bool operator == ( const avl::NDGaussianMixtureParams& rhs ) const
		{
			return classNo == rhs.classNo && 
			means == rhs.means && 
			covs == rhs.covs && 
			priors == rhs.priors && 
			noveltyScore == rhs.noveltyScore;
		}

		bool operator != ( const avl::NDGaussianMixtureParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

