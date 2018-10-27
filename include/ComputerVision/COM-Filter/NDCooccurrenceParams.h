//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _NDCOOCCURRENCEPARAMS_H
#define _NDCOOCCURRENCEPARAMS_H

#include "ATL/Array.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{
	struct NDCooccurrenceParams
	{
		atl::Array<Matrix>				model;
		int					step;
		int					quant;
		int					pyramidHeight;
		int					matrixLevels;
		int					meanBox;
		int					processingType;

		explicit NDCooccurrenceParams
		(
			const atl::Array<Matrix>& model_ = atl::Array<Matrix>(),
			int step_ = 0,
			int quant_ = 0,
			int pyramidHeight_ = 0,
			int matrixLevels_ = 0,
			int meanBox_ = 0,
			int processingType_ = 0 
		) :
			 model(model_),
			 step(step_),
			 quant(quant_),
			 pyramidHeight(pyramidHeight_),
			 matrixLevels(matrixLevels_),
			 meanBox(meanBox_),
			 processingType(processingType_) 
		{}

		const atl::Array<Matrix>& Model() const	{ return model;				};
		int Step() const						{ return step;				};
		int Quant() const						{ return quant;				};
		int PyramidHeight() const				{ return pyramidHeight;		};
		int MatrixLevels() const				{ return matrixLevels;		};
		int MeanBox() const						{ return meanBox;			};
		int ProcessingType() const				{ return processingType;	};

		bool operator == ( const avl::NDCooccurrenceParams& rhs ) const
		{
			return model == rhs.model && 
			step == rhs.step && 
			quant == rhs.quant && 
			pyramidHeight == rhs.pyramidHeight && 
			matrixLevels == rhs.matrixLevels && 
			meanBox == rhs.meanBox && 
			processingType == rhs.processingType;
		}

		bool operator != ( const avl::NDCooccurrenceParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

