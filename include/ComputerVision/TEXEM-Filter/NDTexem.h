//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _NDTEXEM_H
#define _NDTEXEM_H

#include "ATL/Array.h"
#include "ComputerVision/TEXEM-Filter/NDGaussianMixtureParams.h"

namespace avl
{
	struct TexemModel
	{
		int							pyramidHeight;
		bool						gaussianPyramid;
		int							gaussianKernel;
		int							tileSize;
		int							modelType;
		atl::Array<NDGaussianMixtureParams>				models;

		explicit TexemModel
		(
			int pyramidHeight_ = 0,
			bool gaussianPyramid_ = false,
			int gaussianKernel_ = 0,
			int tileSize_ = 0,
			int modelType_ = 0,
			const atl::Array<NDGaussianMixtureParams>& models_ = atl::Array<NDGaussianMixtureParams>()
		) :
			 pyramidHeight(pyramidHeight_),
			 gaussianPyramid(gaussianPyramid_),
			 gaussianKernel(2*gaussianKernel_+1),
			 tileSize(2*tileSize_+1),
			 modelType(modelType_),
			 models(models_) 
		{}

		int PyramidHeight() const							{ return pyramidHeight;		};
		bool GaussianPyramid() const						{ return gaussianPyramid;	};
		int GaussianKernel() const							{ return gaussianKernel;	};
		int TileSize() const								{ return tileSize;		};
		int ModelType() const								{ return modelType;			};
		const atl::Array<NDGaussianMixtureParams>& Models() const	{ return models;			};

		bool operator == ( const avl::TexemModel& rhs ) const
		{
			return pyramidHeight == rhs.pyramidHeight && 
			gaussianPyramid == rhs.gaussianPyramid && 
			gaussianKernel == rhs.gaussianKernel && 
			tileSize == rhs.tileSize && 
			modelType == rhs.modelType && 
			models == rhs.models;
		}

		bool operator != ( const avl::TexemModel& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

