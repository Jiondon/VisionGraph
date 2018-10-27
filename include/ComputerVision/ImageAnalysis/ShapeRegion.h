//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SHAPEREGION_H
#define _SHAPEREGION_H

#include "Enums/RectangularRoiMask.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct ShapeRegion
	{
		Rectangle2D					frame;
		RectangularRoiMask::Type	mask;

		explicit ShapeRegion
		(
			Rectangle2D frame_ = Rectangle2D(),
			RectangularRoiMask::Type mask_ = RectangularRoiMask::Rectangle 
		) :
			 frame(frame_),
			 mask(mask_) 
		{}

		Rectangle2D Frame() const				{ return frame;	};
		RectangularRoiMask::Type Mask() const	{ return mask;	};

		bool operator == ( const avl::ShapeRegion& rhs ) const
		{
			return frame == rhs.frame && 
			mask == rhs.mask;
		}

		bool operator != ( const avl::ShapeRegion& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

