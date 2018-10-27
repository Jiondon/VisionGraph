//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _TEXTSEGMENTATION_H
#define _TEXTSEGMENTATION_H

#include "ComputerVision/TextSegmentationMethod.h"
#include "ComputerVision/TextThresholdingMethod.h"

namespace avl
{
	struct TextSegmentation
	{
		TextSegmentationMethod	segmentation;
		TextThresholdingMethod	extraction;

		explicit TextSegmentation
		(
			TextSegmentationMethod segmentation_ = TextSegmentationMethod(),
			TextThresholdingMethod extraction_ = TextThresholdingMethod() 
		) :
			 segmentation(segmentation_),
			 extraction(extraction_) 
		{}

		TextSegmentationMethod Segmentation() const	{ return segmentation;	};
		TextThresholdingMethod Extraction() const	{ return extraction;	};

		bool operator == ( const avl::TextSegmentation& rhs ) const
		{
			return segmentation == rhs.segmentation && 
			extraction == rhs.extraction;
		}

		bool operator != ( const avl::TextSegmentation& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

