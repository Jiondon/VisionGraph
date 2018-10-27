//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _ANCHOR3D_H
#define _ANCHOR3D_H

#include "Enums/Anchor1D.h"

namespace avl
{
	struct Anchor3D
	{
		Anchor1D::Type	anchorX;
		Anchor1D::Type	anchorY;
		Anchor1D::Type	anchorZ;

		explicit Anchor3D
		(
			Anchor1D::Type anchorX_ = Anchor1D::Middle,
			Anchor1D::Type anchorY_ = Anchor1D::Middle,
			Anchor1D::Type anchorZ_ = Anchor1D::Middle 
		) :
			 anchorX(anchorX_),
			 anchorY(anchorY_),
			 anchorZ(anchorZ_) 
		{}

		Anchor1D::Type AnchorX() const	{ return anchorX;	};
		Anchor1D::Type AnchorY() const	{ return anchorY;	};
		Anchor1D::Type AnchorZ() const	{ return anchorZ;	};

		bool operator == ( const avl::Anchor3D& rhs ) const
		{
			return anchorX == rhs.anchorX && 
			anchorY == rhs.anchorY && 
			anchorZ == rhs.anchorZ;
		}

		bool operator != ( const avl::Anchor3D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

