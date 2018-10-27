//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _GRAYGOLDENTEMPLATE_H
#define _GRAYGOLDENTEMPLATE_H

#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Region/Region.h"

namespace avl
{
	struct GrayGoldenTemplate
	{
		Image		goldenImage;
		Rectangle2D	goldenImagePosition;
		Region		goldenImageMask;
		Region		goldenImageEdgeRegion;

		GrayGoldenTemplate()
		{}

		GrayGoldenTemplate
		(
			 const Image& goldenImage_,
			 const Rectangle2D& goldenImagePosition_,
			 const Region& goldenImageMask_,
			 const Region& goldenImageEdgeRegion_ 
		) :
			 goldenImage(goldenImage_),
			 goldenImagePosition(goldenImagePosition_),
			 goldenImageMask(goldenImageMask_),
			 goldenImageEdgeRegion(goldenImageEdgeRegion_) 
		{}

		const Image& GoldenImage( void ) const					{ return goldenImage;			};
		const Rectangle2D& GoldenImagePosition( void ) const	{ return goldenImagePosition;	};
		const Region& GoldenImageMask( void ) const				{ return goldenImageMask;		};
		const Region& GoldenImageEdgeRegion( void ) const		{ return goldenImageEdgeRegion;	};

		bool operator == ( const avl::GrayGoldenTemplate& rhs ) const
		{
			return goldenImage == rhs.goldenImage && goldenImagePosition == rhs.goldenImagePosition &&
				goldenImageMask == rhs.goldenImageMask && goldenImageEdgeRegion == rhs.goldenImageEdgeRegion
			;
		}

		bool operator != ( const avl::GrayGoldenTemplate& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

