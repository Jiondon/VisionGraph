//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _EDGEGOLDENTEMPLATE_H
#define _EDGEGOLDENTEMPLATE_H

#include "Geometry/Geometry.h"
#include "Region/Region.h"

namespace avl
{
	struct EdgeGoldenTemplate
	{
		Rectangle2D	goldenImagePosition;
		Region		goldenImageMask;
		Region		goldenEdges;

		EdgeGoldenTemplate()
		{}

		EdgeGoldenTemplate
		(
			 const Rectangle2D& goldenImagePosition_,
			 const Region& goldenImageMask_,
			 const Region& goldenEdges_ 
		) :
			 goldenImagePosition(goldenImagePosition_),
			 goldenImageMask(goldenImageMask_),
			 goldenEdges(goldenEdges_) 
		{}

		const Rectangle2D& GoldenImagePosition( void ) const	{ return goldenImagePosition;	};
		const Region& GoldenImageMask( void ) const				{ return goldenImageMask;		}
		const Region& GoldenEdges( void ) const					{ return goldenEdges;			};

		bool operator == ( const avl::EdgeGoldenTemplate& rhs ) const
		{
			return goldenImagePosition == rhs.goldenImagePosition && goldenImageMask == rhs.goldenImageMask && goldenEdges == rhs.goldenEdges
			;
		}

		bool operator != ( const avl::EdgeGoldenTemplate& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

