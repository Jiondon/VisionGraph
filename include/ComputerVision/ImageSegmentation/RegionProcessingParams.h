//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _REGIONPROCESSINGPARAMS_H
#define _REGIONPROCESSINGPARAMS_H

#include "Enums/KernelShape.h"

namespace avl
{
	struct RegionProcessingParams
	{
		KernelShape::Type	kernel;
		int					openingRadius;
		int					closingRadius;

		explicit RegionProcessingParams
		(
			KernelShape::Type kernel_ = KernelShape::Box,
			int openingRadius_ = 0,
			int closingRadius_ = 0 
		) :
			 kernel(kernel_),
			 openingRadius(openingRadius_),
			 closingRadius(closingRadius_) 
		{}

		KernelShape::Type Kernel() const	{ return kernel;		};
		int OpeningRadius() const			{ return openingRadius;	};
		int ClosingRadius() const			{ return closingRadius;	};

		bool operator == ( const avl::RegionProcessingParams& rhs ) const
		{
			return kernel == rhs.kernel && 
			openingRadius == rhs.openingRadius && 
			closingRadius == rhs.closingRadius;
		}

		bool operator != ( const avl::RegionProcessingParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

