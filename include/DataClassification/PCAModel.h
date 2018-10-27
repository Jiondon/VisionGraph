//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _PCAMODEL_H
#define _PCAMODEL_H

#include "AVLCommon/MatrixTypes.h"

namespace avl
{
	struct PCAModel
	{
		Matrix	featureVector;
		Matrix	meansVector;
		Matrix	standardDeviationVector;

		explicit PCAModel
		(
			 Matrix featureVector_ = Matrix(),
			 Matrix meansVector_ = Matrix(),
			 Matrix standardDeviationVector_ = Matrix() 
		) :
			 featureVector(featureVector_),
			 meansVector(meansVector_),
			 standardDeviationVector(standardDeviationVector_) 
		{}

		Matrix FeatureVector( void ) const				{ return featureVector;				};
		Matrix MeansVector( void ) const				{ return meansVector;				};
		Matrix StandardDeviationVector( void ) const	{ return standardDeviationVector;	};

		bool operator == ( const avl::PCAModel& rhs ) const
		{
			return featureVector == rhs.featureVector && 
			meansVector == rhs.meansVector && standardDeviationVector == rhs.standardDeviationVector
			;
		}

		bool operator != ( const avl::PCAModel& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

